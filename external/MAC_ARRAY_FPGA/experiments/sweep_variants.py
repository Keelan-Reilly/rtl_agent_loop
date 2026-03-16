#!/usr/bin/env python3
"""Run a bounded MAC-array architecture sweep and collate results."""

from __future__ import annotations

import argparse
import csv
import json
import subprocess
from pathlib import Path


DEFAULT_CASES = [
    {
        "name": "baseline_4x4",
        "ARCH_VARIANT": 0,
        "ARRAY_M": 4,
        "ARRAY_N": 4,
        "CLUSTER_SIZE": 4,
        "SHARE_FACTOR": 1,
    },
    {
        "name": "baseline_8x4",
        "ARCH_VARIANT": 0,
        "ARRAY_M": 8,
        "ARRAY_N": 4,
        "CLUSTER_SIZE": 4,
        "SHARE_FACTOR": 1,
    },
    {
        "name": "baseline_8x8",
        "ARCH_VARIANT": 0,
        "ARRAY_M": 8,
        "ARRAY_N": 8,
        "CLUSTER_SIZE": 4,
        "SHARE_FACTOR": 1,
    },
    {
        "name": "shared_4x4_sf2",
        "ARCH_VARIANT": 1,
        "ARRAY_M": 4,
        "ARRAY_N": 4,
        "CLUSTER_SIZE": 4,
        "SHARE_FACTOR": 2,
    },
    {
        "name": "shared_8x4_sf2",
        "ARCH_VARIANT": 1,
        "ARRAY_M": 8,
        "ARRAY_N": 4,
        "CLUSTER_SIZE": 4,
        "SHARE_FACTOR": 2,
    },
    {
        "name": "replicated_4x4_c2",
        "ARCH_VARIANT": 2,
        "ARRAY_M": 4,
        "ARRAY_N": 4,
        "CLUSTER_SIZE": 2,
        "SHARE_FACTOR": 1,
    },
    {
        "name": "replicated_8x4_c2",
        "ARCH_VARIANT": 2,
        "ARRAY_M": 8,
        "ARRAY_N": 4,
        "CLUSTER_SIZE": 2,
        "SHARE_FACTOR": 1,
    },
    {
        "name": "replicated_8x8_c2",
        "ARCH_VARIANT": 2,
        "ARRAY_M": 8,
        "ARRAY_N": 8,
        "CLUSTER_SIZE": 2,
        "SHARE_FACTOR": 1,
    },
]

FIXED_DEFAULTS = {
    "DATA_WIDTH": 16,
    "FRAC_BITS": 8,
    "ACC_WIDTH": 32,
    "PIPE_STAGES": 1,
    "TILE_K": 4,
    "INPUT_MEM_DEPTH": 64,
    "OUTPUT_MEM_DEPTH": 64,
}


def run_command(command: list[str], cwd: Path, log_path: Path) -> int:
    log_path.parent.mkdir(parents=True, exist_ok=True)
    with log_path.open("w") as logf:
        proc = subprocess.run(command, cwd=cwd, stdout=logf, stderr=subprocess.STDOUT)
    return proc.returncode


def load_json_if_exists(path: Path) -> dict:
    if not path.exists():
        return {}
    return json.loads(path.read_text())


def derive_note(rows: list[dict[str, object]]) -> None:
    successful = [row for row in rows if str(row["status"]).startswith("passed")]
    if not successful:
        return

    fastest = min(successful, key=lambda row: float(row.get("latency_cycles") or 1e18))
    area_light = min(successful, key=lambda row: float(row.get("lut") or 1e18))
    densest = max(successful, key=lambda row: float(row.get("shadow_pe_count") or 0.0))
    timing_clean = [row for row in successful if row.get("wns_ns") is not None and float(row["wns_ns"]) >= 0.0]
    timing_best = min(timing_clean, key=lambda row: float(row.get("latency_cycles") or 1e18)) if timing_clean else None

    for row in rows:
        notes: list[str] = []
        if row["case_name"] == fastest["case_name"]:
            notes.append("fastest")
        if row["case_name"] == area_light["case_name"]:
            notes.append("area-light")
        if timing_best and row["case_name"] == timing_best["case_name"]:
            notes.append("timing-clean best")
        if row["case_name"] == densest["case_name"]:
            notes.append("most replicated")
        row["ranking_note"] = ", ".join(notes) if notes else ""


def write_markdown(rows: list[dict[str, object]], output_path: Path, perf_only: bool) -> None:
    headers = [
        "candidate",
        "variant",
        "ARRAY_M",
        "ARRAY_N",
        "CLUSTER_SIZE",
        "SHARE_FACTOR",
        "physical_pe_count",
        "shadow_pe_count",
        "total_compute_steps",
        "latency_cycles",
        "latency_time_ms",
        "lut",
        "ff",
        "dsp",
        "bram",
        "wns_ns",
        "fmax_mhz_est",
        "status",
        "ranking_note",
    ]
    lines = [
        "# Sweep Summary",
        "",
        f"Perf only: {'yes' if perf_only else 'no'}",
        "",
        "| " + " | ".join(headers) + " |",
        "| " + " | ".join(["---"] * len(headers)) + " |",
    ]
    for row in rows:
        lines.append(
            "| "
            + " | ".join(
                str(
                    row.get(
                        {
                            "candidate": "case_name",
                            "variant": "arch_variant_name",
                        }.get(header, header),
                        "",
                    )
                )
                for header in headers
            )
            + " |"
        )
    output_path.write_text("\n".join(lines) + "\n")


def main() -> int:
    parser = argparse.ArgumentParser()
    parser.add_argument("--perf-only", action="store_true")
    parser.add_argument("--results-dir", type=Path, default=Path("experiments/results"))
    parser.add_argument("--clock-hz", type=float, default=100_000_000.0)
    args = parser.parse_args()

    repo_root = Path(__file__).resolve().parents[1]
    results_dir = args.results_dir.resolve()
    run_root = results_dir / "runs"
    results_dir.mkdir(parents=True, exist_ok=True)
    run_root.mkdir(parents=True, exist_ok=True)

    perf_script = repo_root / "experiments" / "collect_verilator_perf.py"
    vivado_script = repo_root / "fpga" / "vivado" / "run_batch.sh"
    parse_script = repo_root / "fpga" / "vivado" / "parse_reports.py"
    xdc_path = repo_root / "fpga" / "vivado" / "constraints" / "mac_array_constraints.xdc"

    rows: list[dict[str, object]] = []
    for case in DEFAULT_CASES:
        case_params = {**FIXED_DEFAULTS, **case}
        case_name = str(case_params.pop("name"))
        run_dir = run_root / case_name

        perf_cmd = [
            "python3",
            str(perf_script),
            "--run-dir",
            str(run_dir),
            "--top",
            "top_level",
            "--clock-hz",
            str(args.clock_hz),
        ]
        for key in sorted(case_params):
            perf_cmd.extend(["--parameter", f"{key}={case_params[key]}"])

        perf_log = run_dir / "logs" / "sweep_perf.log"
        perf_rc = run_command(perf_cmd, repo_root, perf_log)
        perf_json = load_json_if_exists(run_dir / "verilator_perf" / "performance.json")

        vivado_json: dict[str, object] = {}
        vivado_rc = 0
        vivado_reports_dir = run_dir / "vivado" / "reports"
        if not args.perf_only and perf_rc == 0:
            vivado_cmd = [
                str(vivado_script),
                "--run-dir",
                str(run_dir / "vivado"),
                "--repo-root",
                str(repo_root),
                "--part",
                "xc7a35tcpg236-1",
                "--top",
                "top_level",
                "--xdc",
                str(xdc_path),
                "--clock-period-ns",
                "10.0",
            ]
            for key in sorted(case_params):
                vivado_cmd.extend(["--generic", f"{key}={case_params[key]}"])
            vivado_log = run_dir / "logs" / "sweep_vivado.log"
            vivado_rc = run_command(vivado_cmd, repo_root, vivado_log)
            have_vivado_reports = any(
                path.exists()
                for path in (
                    vivado_reports_dir / "utilization_impl.rpt",
                    vivado_reports_dir / "timing_impl.rpt",
                    vivado_reports_dir / "utilization_synth.rpt",
                    vivado_reports_dir / "timing_synth.rpt",
                )
            )
            if have_vivado_reports:
                parse_cmd = [
                    "python3",
                    str(parse_script),
                    "--reports-dir",
                    str(vivado_reports_dir),
                    "--clock-period-ns",
                    "10.0",
                    "--output",
                    str(vivado_reports_dir / "metrics.json"),
                ]
                parse_rc = run_command(parse_cmd, repo_root, run_dir / "logs" / "sweep_parse.log")
                if vivado_rc == 0:
                    vivado_rc = parse_rc
            vivado_json = load_json_if_exists(vivado_reports_dir / "metrics.json")

        status = "passed_perf" if perf_rc == 0 else "failed_perf"
        if not args.perf_only:
            if perf_rc != 0:
                status = "failed_perf"
            elif vivado_rc == 0:
                status = "passed_all"
            elif vivado_json.get("success"):
                status = "passed_perf_synth_only"
            else:
                status = "failed"

        rows.append(
            {
                "case_name": case_name,
                "arch_variant_name": {
                    0: "baseline",
                    1: "shared",
                    2: "replicated",
                }.get(case["ARCH_VARIANT"], "unknown"),
                "ARCH_VARIANT": case["ARCH_VARIANT"],
                "ARRAY_M": case["ARRAY_M"],
                "ARRAY_N": case["ARRAY_N"],
                "CLUSTER_SIZE": case["CLUSTER_SIZE"],
                "SHARE_FACTOR": case["SHARE_FACTOR"],
                "physical_pe_count": perf_json.get("physical_pe_count"),
                "shadow_pe_count": perf_json.get("shadow_pe_count"),
                "total_compute_steps": perf_json.get("total_compute_steps"),
                "latency_cycles": perf_json.get("latency_cycles"),
                "latency_time_ms": perf_json.get("latency_time_ms"),
                "lut": vivado_json.get("lut"),
                "ff": vivado_json.get("ff"),
                "dsp": vivado_json.get("dsp"),
                "bram": vivado_json.get("bram"),
                "wns_ns": vivado_json.get("wns_ns"),
                "fmax_mhz_est": vivado_json.get("fmax_mhz_est"),
                "status": status,
                "perf_json": str(run_dir / "verilator_perf" / "performance.json"),
                "vivado_metrics_json": str(vivado_reports_dir / "metrics.json"),
                "ranking_note": "",
            }
        )

    derive_note(rows)

    csv_headers = [
        "case_name",
        "arch_variant_name",
        "ARCH_VARIANT",
        "ARRAY_M",
        "ARRAY_N",
        "CLUSTER_SIZE",
        "SHARE_FACTOR",
        "physical_pe_count",
        "shadow_pe_count",
        "total_compute_steps",
        "latency_cycles",
        "latency_time_ms",
        "lut",
        "ff",
        "dsp",
        "bram",
        "wns_ns",
        "fmax_mhz_est",
        "status",
        "ranking_note",
        "perf_json",
        "vivado_metrics_json",
    ]
    csv_path = results_dir / "sweep_results.csv"
    with csv_path.open("w", newline="") as csv_file:
        writer = csv.DictWriter(csv_file, fieldnames=csv_headers)
        writer.writeheader()
        writer.writerows(rows)

    write_markdown(rows, results_dir / "sweep_summary.md", args.perf_only)
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
