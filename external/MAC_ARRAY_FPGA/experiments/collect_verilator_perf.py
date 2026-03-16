#!/usr/bin/env python3
"""Build and run a Verilator simulation, then emit machine-readable performance JSON."""

from __future__ import annotations

import argparse
import json
import re
import shutil
import subprocess
from pathlib import Path


def parse_key_value(items: list[str]) -> dict[str, str]:
    parsed: dict[str, str] = {}
    for item in items:
        key, value = item.split("=", 1)
        parsed[key] = value
    return parsed


def main() -> int:
    parser = argparse.ArgumentParser()
    parser.add_argument("--run-dir", type=Path, required=True)
    parser.add_argument("--top", default="top_level")
    parser.add_argument("--clock-hz", type=float, default=100_000_000.0)
    parser.add_argument("--parameter", action="append", default=[])
    parser.add_argument("--generic", action="append", default=[])
    parser.add_argument("--build-only", action="store_true")
    parser.add_argument("--expected", type=Path, default=None)
    parser.add_argument("--max-cycles", type=int, default=1024)
    args = parser.parse_args()

    repo_root = Path(__file__).resolve().parents[1]
    run_dir = args.run_dir.resolve()
    perf_root = run_dir / "verilator_perf"
    obj_dir = perf_root / "obj_dir"
    output_mem = perf_root / "sim_output.mem"
    perf_json = perf_root / "performance.json"
    log_path = perf_root / "verilator_perf.log"
    data_dir = perf_root / "data"
    perf_root.mkdir(parents=True, exist_ok=True)
    data_dir.mkdir(parents=True, exist_ok=True)

    parameters = parse_key_value(args.parameter + args.generic)
    hdl_dir = repo_root / "hdl"
    tb_path = repo_root / "tb" / "tb_full_pipeline.cpp"
    generator_path = repo_root / "python" / "generate_test_vectors.py"
    expected_path = args.expected.resolve() if args.expected else (data_dir / "expected_output.mem")

    verilator = shutil.which("verilator")
    if verilator is None:
        payload = {
            "success": False,
            "top": args.top,
            "parameters": parameters,
            "message": "verilator was not found in PATH",
            "log_path": str(log_path),
        }
        perf_json.write_text(json.dumps(payload, indent=2) + "\n")
        return 2

    hdl_paths = list(hdl_dir.glob("*.sv"))
    hdl_paths.sort(key=lambda path: (0 if path.name == "types_pkg.sv" else 1, path.name))
    hdl_files = [str(path) for path in hdl_paths]
    build_cmd = [
        verilator,
        "-sv",
        "--cc",
        "--exe",
        "--build",
        "--top-module",
        args.top,
        "--Mdir",
        str(obj_dir),
        "-I" + str(hdl_dir),
        "-CFLAGS",
        "-std=c++17",
        str(tb_path),
    ]
    for key, value in parameters.items():
        build_cmd.append(f"-G{key}={value}")
    build_cmd.extend(hdl_files)

    sim_bin = obj_dir / f"V{args.top}"
    run_cmd = [
        str(sim_bin),
        "--expected",
        str(expected_path),
        "--max-cycles",
        str(args.max_cycles),
    ]

    stdout_text = ""
    with log_path.open("w") as logf:
        vector_cmd = [
            "python3",
            str(generator_path),
            "--array-m",
            parameters.get("ARRAY_M", "4"),
            "--array-n",
            parameters.get("ARRAY_N", "4"),
            "--tile-k",
            parameters.get("TILE_K", "4"),
            "--data-width",
            parameters.get("DATA_WIDTH", "16"),
            "--frac-bits",
            parameters.get("FRAC_BITS", "8"),
            "--acc-width",
            parameters.get("ACC_WIDTH", "32"),
            "--input-mem-depth",
            parameters.get("INPUT_MEM_DEPTH", "16"),
            "--output-mem-depth",
            parameters.get("OUTPUT_MEM_DEPTH", "16"),
            "--output-dir",
            str(data_dir),
        ]
        logf.write(f"repo_root={repo_root}\n")
        logf.write(f"parameters={json.dumps(parameters, sort_keys=True)}\n")
        logf.write(f"vector_cmd={' '.join(vector_cmd)}\n")
        logf.write(f"build_cmd={' '.join(build_cmd)}\n")
        vector_gen = subprocess.run(vector_cmd, cwd=repo_root, stdout=logf, stderr=subprocess.STDOUT)
        if vector_gen.returncode != 0:
            payload = {
                "success": False,
                "top": args.top,
                "parameters": parameters,
                "command": vector_cmd,
                "returncode": vector_gen.returncode,
                "log_path": str(log_path),
                "message": "Test-vector generation failed",
            }
            perf_json.write_text(json.dumps(payload, indent=2) + "\n")
            return vector_gen.returncode
        build = subprocess.run(build_cmd, cwd=repo_root, stdout=logf, stderr=subprocess.STDOUT)
        if build.returncode != 0:
            payload = {
                "success": False,
                "top": args.top,
                "parameters": parameters,
                "command": build_cmd,
                "returncode": build.returncode,
                "log_path": str(log_path),
                "message": "Verilator build failed",
            }
            perf_json.write_text(json.dumps(payload, indent=2) + "\n")
            return build.returncode
        if args.build_only:
            payload = {
                "success": True,
                "top": args.top,
                "parameters": parameters,
                "command": build_cmd,
                "build_only": True,
                "binary_path": str(sim_bin),
                "log_path": str(log_path),
            }
            perf_json.write_text(json.dumps(payload, indent=2) + "\n")
            return 0

        logf.write(f"run_cmd={' '.join(run_cmd)}\n")
        run = subprocess.run(run_cmd, cwd=perf_root, stdout=subprocess.PIPE, stderr=subprocess.STDOUT, text=True)
        stdout_text = run.stdout
        logf.write(stdout_text)
        if run.returncode != 0:
            payload = {
                "success": False,
                "top": args.top,
                "parameters": parameters,
                "command": run_cmd,
                "returncode": run.returncode,
                "log_path": str(log_path),
                "message": "Verilator execution failed",
            }
            perf_json.write_text(json.dumps(payload, indent=2) + "\n")
            return run.returncode

    match = re.search(r"LATENCY_CYCLES=(\d+)", stdout_text)
    cycles = int(match.group(1)) if match else 0
    seconds = cycles / args.clock_hz if args.clock_hz else 0.0
    ops = (
        int(parameters.get("ARRAY_M", 4))
        * int(parameters.get("ARRAY_N", 4))
        * int(parameters.get("TILE_K", 4))
    )
    throughput = ops / seconds if seconds > 0 else 0.0

    payload = {
        "success": True,
        "top": args.top,
        "parameters": parameters,
        "arch_variant_name": {
            "0": "baseline",
            "1": "shared",
            "2": "replicated",
        }.get(parameters.get("ARCH_VARIANT", "0"), "unknown"),
        "latency_cycles": cycles,
        "latency_time_ms": seconds * 1_000.0,
        "throughput_ops_per_sec": throughput,
        "command": run_cmd,
        "build_command": build_cmd,
        "vector_command": vector_cmd,
        "log_path": str(log_path),
        "output_mem": str(output_mem),
        "expected_mem": str(expected_path),
    }
    perf_json.write_text(json.dumps(payload, indent=2) + "\n")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
