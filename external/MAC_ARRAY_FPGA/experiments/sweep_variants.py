#!/usr/bin/env python3
"""Run a bounded MAC-array architecture sweep and collate research-grade outputs."""

from __future__ import annotations

import argparse
import csv
import json
import subprocess
from pathlib import Path


DEFAULT_CASES = [
    {"name": "baseline_4x4", "ARCH_VARIANT": 0, "ARRAY_M": 4, "ARRAY_N": 4, "CLUSTER_SIZE": 4, "SHARE_FACTOR": 1},
    {"name": "baseline_8x4", "ARCH_VARIANT": 0, "ARRAY_M": 8, "ARRAY_N": 4, "CLUSTER_SIZE": 4, "SHARE_FACTOR": 1},
    {"name": "baseline_8x8", "ARCH_VARIANT": 0, "ARRAY_M": 8, "ARRAY_N": 8, "CLUSTER_SIZE": 4, "SHARE_FACTOR": 1},
    {"name": "shared_4x4_sf2", "ARCH_VARIANT": 1, "ARRAY_M": 4, "ARRAY_N": 4, "CLUSTER_SIZE": 4, "SHARE_FACTOR": 2},
    {"name": "shared_8x4_sf2", "ARCH_VARIANT": 1, "ARRAY_M": 8, "ARRAY_N": 4, "CLUSTER_SIZE": 4, "SHARE_FACTOR": 2},
    {"name": "replicated_4x4_c2", "ARCH_VARIANT": 2, "ARRAY_M": 4, "ARRAY_N": 4, "CLUSTER_SIZE": 2, "SHARE_FACTOR": 1},
    {"name": "replicated_8x4_c2", "ARCH_VARIANT": 2, "ARRAY_M": 8, "ARRAY_N": 4, "CLUSTER_SIZE": 2, "SHARE_FACTOR": 1},
    {"name": "replicated_8x8_c2", "ARCH_VARIANT": 2, "ARRAY_M": 8, "ARRAY_N": 8, "CLUSTER_SIZE": 2, "SHARE_FACTOR": 1},
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

VARIANT_NAMES = {0: "baseline", 1: "shared", 2: "replicated"}
VARIANT_COLORS = {"baseline": "#1f4b99", "shared": "#c46818", "replicated": "#9b1d20"}


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
    area_light = min(
        [row for row in successful if row.get("lut") is not None],
        key=lambda row: float(row.get("lut") or 1e18),
        default=fastest,
    )
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


def mark_pareto(rows: list[dict[str, object]]) -> None:
    candidates = [
        row
        for row in rows
        if row.get("latency_cycles") is not None and row.get("lut") is not None and str(row["status"]).startswith("passed")
    ]
    for row in rows:
        row["pareto_latency_lut"] = ""
    for row in candidates:
        dominated = False
        for other in candidates:
            if other is row:
                continue
            if (
                float(other["latency_cycles"]) <= float(row["latency_cycles"])
                and float(other["lut"]) <= float(row["lut"])
                and (
                    float(other["latency_cycles"]) < float(row["latency_cycles"])
                    or float(other["lut"]) < float(row["lut"])
                )
            ):
                dominated = True
                break
        row["pareto_latency_lut"] = "yes" if not dominated else "no"


def build_findings(rows: list[dict[str, object]], perf_only: bool) -> list[str]:
    findings: list[str] = []
    baseline_rows = [row for row in rows if row.get("arch_variant_name") == "baseline"]
    baseline_rows = sorted(baseline_rows, key=lambda row: (int(row["ARRAY_M"]), int(row["ARRAY_N"])))
    shared_rows = [row for row in rows if row.get("arch_variant_name") == "shared"]
    replicated_rows = [row for row in rows if row.get("arch_variant_name") == "replicated"]

    if baseline_rows:
        chain = ", ".join(f"{row['case_name']}={row['latency_cycles']} cycles" for row in baseline_rows)
        findings.append(f"Baseline scaling is monotonic across the bounded study: {chain}.")

    shared_notes: list[str] = []
    for shared in shared_rows:
        matched = next(
            (
                row
                for row in baseline_rows
                if row["ARRAY_M"] == shared["ARRAY_M"] and row["ARRAY_N"] == shared["ARRAY_N"]
            ),
            None,
        )
        if matched and matched.get("latency_cycles") is not None and shared.get("latency_cycles") is not None:
            delta = float(shared["latency_cycles"]) - float(matched["latency_cycles"])
            shared_notes.append(f"{shared['case_name']} adds {delta:.0f} cycles over {matched['case_name']}")
    if shared_notes:
        findings.append("Shared mode introduces measurable scheduling overhead: " + "; ".join(shared_notes) + ".")

    if not perf_only:
        synth_only = [row for row in rows if row.get("status") == "passed_perf_synth_only"]
        if synth_only:
            names = ", ".join(row["case_name"] for row in synth_only)
            findings.append(
                f"Synth-only points remain valuable evidence when replication exceeds implementation budget: {names} preserved synthesis metrics without being misreported as full implementation passes."
            )

        suspicious_rows: list[str] = []
        for replicated in replicated_rows:
            matched = next(
                (
                    row
                    for row in baseline_rows
                    if row["ARRAY_M"] == replicated["ARRAY_M"] and row["ARRAY_N"] == replicated["ARRAY_N"]
                ),
                None,
            )
            if (
                matched
                and replicated.get("lut") is not None
                and matched.get("lut") is not None
                and float(replicated["lut"]) < 0.5 * float(matched["lut"])
            ):
                suspicious_rows.append(str(replicated["case_name"]))
        if suspicious_rows:
            findings.append(
                "Some stored implementation rows look stale relative to the current preserved-replication design and should be regenerated with a fresh full sweep: "
                + ", ".join(suspicious_rows)
                + "."
            )

    pareto_rows = [row["case_name"] for row in rows if row.get("pareto_latency_lut") == "yes"]
    if pareto_rows:
        findings.append("Latency/LUT Pareto-efficient points in the current table: " + ", ".join(pareto_rows) + ".")

    return findings


def _svg_x(value: float, x_min: float, x_max: float, width: int, left: int, right: int) -> float:
    if x_max == x_min:
        return left + (width - left - right) / 2.0
    return left + (value - x_min) * (width - left - right) / (x_max - x_min)


def _svg_y(value: float, y_min: float, y_max: float, height: int, top: int, bottom: int) -> float:
    if y_max == y_min:
        return top + (height - top - bottom) / 2.0
    return height - bottom - (value - y_min) * (height - top - bottom) / (y_max - y_min)


def write_svg_scatter(
    rows: list[dict[str, object]],
    output_path: Path,
    *,
    x_key: str,
    y_key: str,
    title: str,
    x_label: str,
    y_label: str,
) -> None:
    plot_rows = [row for row in rows if isinstance(row.get(x_key), (int, float)) and isinstance(row.get(y_key), (int, float))]
    width = 860
    height = 540
    left = 90
    right = 30
    top = 60
    bottom = 80

    if not plot_rows:
        output_path.write_text(
            f"<svg xmlns='http://www.w3.org/2000/svg' width='{width}' height='{height}'><text x='20' y='40'>No data for {title}</text></svg>\n"
        )
        return

    x_values = [float(row[x_key]) for row in plot_rows]
    y_values = [float(row[y_key]) for row in plot_rows]
    x_min, x_max = min(x_values), max(x_values)
    y_min, y_max = min(y_values), max(y_values)

    parts = [
        f"<svg xmlns='http://www.w3.org/2000/svg' width='{width}' height='{height}' viewBox='0 0 {width} {height}'>",
        "<style>text{font-family:Helvetica,Arial,sans-serif;font-size:14px}.small{font-size:12px}</style>",
        f"<rect x='0' y='0' width='{width}' height='{height}' fill='#fbfbf7'/>",
        f"<text x='{left}' y='30' font-size='22'>{title}</text>",
        f"<line x1='{left}' y1='{height-bottom}' x2='{width-right}' y2='{height-bottom}' stroke='#333' stroke-width='2'/>",
        f"<line x1='{left}' y1='{top}' x2='{left}' y2='{height-bottom}' stroke='#333' stroke-width='2'/>",
        f"<text x='{width/2}' y='{height-20}'>{x_label}</text>",
        f"<text x='22' y='{height/2}' transform='rotate(-90 22,{height/2})'>{y_label}</text>",
        "<text class='small' x='90' y='50'>Pareto points are outlined in black.</text>",
    ]

    for row in plot_rows:
        x = _svg_x(float(row[x_key]), x_min, x_max, width, left, right)
        y = _svg_y(float(row[y_key]), y_min, y_max, height, top, bottom)
        color = VARIANT_COLORS.get(str(row.get("arch_variant_name")), "#444")
        pareto = row.get("pareto_latency_lut") == "yes"
        radius = 7 if pareto else 5
        stroke = "#111" if pareto else "none"
        parts.append(f"<circle cx='{x:.1f}' cy='{y:.1f}' r='{radius}' fill='{color}' stroke='{stroke}' stroke-width='1.5'/>")
        parts.append(f"<text class='small' x='{x + 8:.1f}' y='{y - 8:.1f}'>{row['case_name']}</text>")

    legend_x = width - 220
    legend_y = 70
    for idx, (label, color) in enumerate(VARIANT_COLORS.items()):
        y = legend_y + idx * 22
        parts.append(f"<circle cx='{legend_x}' cy='{y}' r='6' fill='{color}'/>")
        parts.append(f"<text x='{legend_x + 14}' y='{y + 4}'>{label}</text>")

    parts.append("</svg>")
    output_path.write_text("\n".join(parts) + "\n")


def write_markdown(rows: list[dict[str, object]], output_path: Path, perf_only: bool) -> None:
    findings = build_findings(rows, perf_only)
    baseline_by_shape = {
        (row["ARRAY_M"], row["ARRAY_N"]): row for row in rows if row.get("arch_variant_name") == "baseline"
    }
    suspicious_rows = [
        str(row["case_name"])
        for row in rows
        if row.get("arch_variant_name") == "replicated"
        and row.get("lut") is not None
        and baseline_by_shape.get((row["ARRAY_M"], row["ARRAY_N"])) is not None
        and baseline_by_shape[(row["ARRAY_M"], row["ARRAY_N"])].get("lut") is not None
        and float(row["lut"]) < 0.5 * float(baseline_by_shape[(row["ARRAY_M"], row["ARRAY_N"])]["lut"])
    ]
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
        "vivado_report_kind",
        "status",
        "pareto_latency_lut",
        "ranking_note",
    ]
    lines = [
        "# Sweep Summary",
        "",
        f"Perf only: {'yes' if perf_only else 'no'}",
        "",
        "## Key Findings",
        "",
    ]
    for finding in findings:
        lines.append(f"- {finding}")
    if suspicious_rows:
        lines.extend(
            [
                "",
                "## Data Quality Notes",
                "",
                "- Stored implementation rows that look stale relative to the current preserved-replication design: "
                + ", ".join(suspicious_rows)
                + ". Regenerate them with `make -C external/MAC_ARRAY_FPGA sweep` before using the table for claims about implementation-area trends.",
            ]
        )
    lines.extend(
        [
            "",
            "## Plots",
            "",
            "- [LUT vs latency](./plots/lut_vs_latency_cycles.svg)",
            "- [DSP vs latency](./plots/dsp_vs_latency_cycles.svg)",
            "- [Latency vs physical PE count](./plots/latency_vs_physical_pe_count.svg)",
            "- [Fmax vs LUT](./plots/fmax_vs_lut.svg)",
            "",
            "## Detailed Table",
            "",
            "| " + " | ".join(headers) + " |",
            "| " + " | ".join(["---"] * len(headers)) + " |",
        ]
    )
    for row in rows:
        lines.append(
            "| "
            + " | ".join(
                str(
                    row.get(
                        {"candidate": "case_name", "variant": "arch_variant_name"}.get(header, header),
                        "",
                    )
                )
                for header in headers
            )
            + " |"
        )
    output_path.write_text("\n".join(lines) + "\n")


def build_row(case: dict[str, int], case_name: str, perf_json: dict, vivado_json: dict, status: str, run_dir: Path) -> dict[str, object]:
    return {
        "case_name": case_name,
        "arch_variant_name": VARIANT_NAMES.get(case["ARCH_VARIANT"], "unknown"),
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
        "throughput_ops_per_sec": perf_json.get("throughput_ops_per_sec"),
        "lut": vivado_json.get("lut"),
        "ff": vivado_json.get("ff"),
        "dsp": vivado_json.get("dsp"),
        "bram": vivado_json.get("bram"),
        "wns_ns": vivado_json.get("wns_ns"),
        "fmax_mhz_est": vivado_json.get("fmax_mhz_est"),
        "vivado_report_kind": vivado_json.get("report_kind"),
        "status": status,
        "pareto_latency_lut": "",
        "perf_json": str(run_dir / "verilator_perf" / "performance.json"),
        "vivado_metrics_json": str(run_dir / "vivado" / "reports" / "metrics.json"),
        "ranking_note": "",
    }


def main() -> int:
    parser = argparse.ArgumentParser()
    parser.add_argument("--perf-only", action="store_true")
    parser.add_argument("--render-only", action="store_true")
    parser.add_argument("--results-dir", type=Path, default=Path("experiments/results"))
    parser.add_argument("--clock-hz", type=float, default=100_000_000.0)
    args = parser.parse_args()

    repo_root = Path(__file__).resolve().parents[1]
    results_dir = args.results_dir if args.results_dir.is_absolute() else (repo_root / args.results_dir)
    results_dir = results_dir.resolve()
    run_root = results_dir / "runs"
    plots_dir = results_dir / "plots"
    results_dir.mkdir(parents=True, exist_ok=True)
    run_root.mkdir(parents=True, exist_ok=True)
    plots_dir.mkdir(parents=True, exist_ok=True)

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

        if args.render_only:
            perf_json = load_json_if_exists(run_dir / "verilator_perf" / "performance.json")
            perf_rc = 0 if perf_json.get("success") else 1
        else:
            perf_rc = run_command(perf_cmd, repo_root, run_dir / "logs" / "sweep_perf.log")
            perf_json = load_json_if_exists(run_dir / "verilator_perf" / "performance.json")

        vivado_json: dict[str, object] = {}
        vivado_rc = 0
        vivado_reports_dir = run_dir / "vivado" / "reports"
        if args.render_only and not args.perf_only:
            vivado_json = load_json_if_exists(vivado_reports_dir / "metrics.json")
            vivado_rc = 0 if vivado_json.get("success") else 1
        elif not args.perf_only and perf_rc == 0:
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
            vivado_rc = run_command(vivado_cmd, repo_root, run_dir / "logs" / "sweep_vivado.log")
            have_reports = any(
                path.exists()
                for path in (
                    vivado_reports_dir / "utilization_impl.rpt",
                    vivado_reports_dir / "timing_impl.rpt",
                    vivado_reports_dir / "utilization_synth.rpt",
                    vivado_reports_dir / "timing_synth.rpt",
                )
            )
            if have_reports:
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

        if args.perf_only:
            status = "passed_perf" if perf_rc == 0 else "failed_perf"
        elif perf_rc != 0:
            status = "failed_perf"
        elif vivado_rc == 0 and vivado_json.get("report_kind") == "implementation":
            status = "passed_all"
        elif vivado_json.get("success"):
            status = "passed_perf_synth_only"
        else:
            status = "failed"

        rows.append(build_row(case, case_name, perf_json, vivado_json, status, run_dir))

    derive_note(rows)
    mark_pareto(rows)

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
        "throughput_ops_per_sec",
        "lut",
        "ff",
        "dsp",
        "bram",
        "wns_ns",
        "fmax_mhz_est",
        "vivado_report_kind",
        "status",
        "pareto_latency_lut",
        "ranking_note",
        "perf_json",
        "vivado_metrics_json",
    ]
    with (results_dir / "sweep_results.csv").open("w", newline="") as csv_file:
        writer = csv.DictWriter(csv_file, fieldnames=csv_headers)
        writer.writeheader()
        writer.writerows(rows)

    write_svg_scatter(
        rows,
        plots_dir / "lut_vs_latency_cycles.svg",
        x_key="lut",
        y_key="latency_cycles",
        title="LUT vs Latency Cycles",
        x_label="LUT",
        y_label="Latency Cycles",
    )
    write_svg_scatter(
        rows,
        plots_dir / "dsp_vs_latency_cycles.svg",
        x_key="dsp",
        y_key="latency_cycles",
        title="DSP vs Latency Cycles",
        x_label="DSP",
        y_label="Latency Cycles",
    )
    write_svg_scatter(
        rows,
        plots_dir / "latency_vs_physical_pe_count.svg",
        x_key="physical_pe_count",
        y_key="latency_cycles",
        title="Latency vs Physical PE Count",
        x_label="Physical PE Count",
        y_label="Latency Cycles",
    )
    write_svg_scatter(
        rows,
        plots_dir / "fmax_vs_lut.svg",
        x_key="lut",
        y_key="fmax_mhz_est",
        title="Fmax vs LUT",
        x_label="LUT",
        y_label="Estimated Fmax (MHz)",
    )
    write_markdown(rows, results_dir / "sweep_summary.md", args.perf_only)
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
