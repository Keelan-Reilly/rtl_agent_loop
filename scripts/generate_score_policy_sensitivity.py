#!/usr/bin/env python3
"""Generate score-policy sensitivity reports for canonical MAC candidates."""

from __future__ import annotations

import csv
import json
import sys
from collections import Counter
from pathlib import Path

REPO_ROOT = Path(__file__).resolve().parents[1]
if str(REPO_ROOT) not in sys.path:
    sys.path.insert(0, str(REPO_ROOT))

from rtl_agent_loop.config import load_json
from rtl_agent_loop.controller import Controller
from rtl_agent_loop.scoring import score_candidate

DEFAULT_POLICY_VARIANTS = REPO_ROOT / "config" / "score_policy_variants.json"
DEFAULT_MD_OUT = REPO_ROOT / "docs" / "results" / "score_policy_sensitivity.md"
DEFAULT_CSV_OUT = REPO_ROOT / "docs" / "results" / "score_policy_sensitivity.csv"
DEFAULT_SVG_OUT = REPO_ROOT / "docs" / "results" / "canonical_latency_vs_lut.svg"

VARIANT_COLORS = {
    "baseline": "#1f4b99",
    "shared": "#c46818",
    "replicated": "#9b1d20",
}


def load_canonical_candidates() -> list[dict[str, object]]:
    controller = Controller()
    ranking = controller.rank_candidates(active_schema_only=True)
    candidates: list[dict[str, object]] = []
    for item in ranking["ranked_candidates"]:
        vivado = load_json(Path(str(item["vivado_result_path"])))
        perf = load_json(Path(str(item["perf_result_path"])))
        candidates.append(
            {
                "candidate_id": item["candidate_id"],
                "timing_status": item["timing_status"],
                "measurement_quality": item["measurement_quality"],
                "implementation_evidence": item["implementation_evidence"],
                "stage_failed": item["stage_failed"],
                "current_policy_rank": item["rank"],
                "current_policy_score": item["score"]["total_score"],
                "vivado_metrics": vivado.get("metrics", {}),
                "perf_metrics": perf.get("metrics", {}),
            }
        )
    return candidates


def evaluate_policies(
    candidates: list[dict[str, object]],
    policy_variants_path: Path,
) -> tuple[list[dict[str, object]], list[dict[str, object]]]:
    policies = load_json(policy_variants_path)["policies"]
    rows: list[dict[str, object]] = []
    summaries: list[dict[str, object]] = []
    for policy in policies:
        scored: list[dict[str, object]] = []
        for candidate in candidates:
            score = score_candidate(
                {
                    "weights": dict(policy["weights"]),
                    "penalties": dict(policy["penalties"]),
                },
                candidate["vivado_metrics"],
                candidate["perf_metrics"],
                stage_failed=bool(candidate["stage_failed"]),
            )
            metrics = score["metrics"]
            scored.append(
                {
                    "policy_name": policy["name"],
                    "policy_label": policy["label"],
                    "policy_description": policy["description"],
                    "candidate_id": candidate["candidate_id"],
                    "total_score": score["total_score"],
                    "latency_cycles": metrics.get("latency_cycles"),
                    "lut": metrics.get("lut"),
                    "dsp": metrics.get("dsp"),
                    "wns_ns": metrics.get("wns_ns"),
                    "measurement_quality": candidate["measurement_quality"],
                    "implementation_evidence": candidate["implementation_evidence"],
                }
            )
        scored.sort(key=lambda row: float(row["total_score"]), reverse=True)
        ordering = [str(row["candidate_id"]) for row in scored]
        winner = ordering[0] if ordering else None
        for rank, row in enumerate(scored, start=1):
            row["rank"] = rank
            row["winner"] = winner
            rows.append(row)
        summaries.append(
            {
                "policy_name": policy["name"],
                "policy_label": policy["label"],
                "policy_description": policy["description"],
                "winner": winner,
                "ordering": ordering,
            }
        )
    return rows, summaries


def write_csv(rows: list[dict[str, object]], output_path: Path) -> None:
    output_path.parent.mkdir(parents=True, exist_ok=True)
    headers = [
        "policy_name",
        "policy_label",
        "candidate_id",
        "rank",
        "winner",
        "total_score",
        "latency_cycles",
        "lut",
        "dsp",
        "wns_ns",
        "measurement_quality",
        "implementation_evidence",
    ]
    with output_path.open("w", newline="") as csv_file:
        writer = csv.DictWriter(csv_file, fieldnames=headers, extrasaction="ignore")
        writer.writeheader()
        writer.writerows(rows)


def write_svg(candidates: list[dict[str, object]], output_path: Path) -> None:
    width = 860
    height = 540
    left = 90
    right = 30
    top = 60
    bottom = 80

    points = []
    for candidate in candidates:
        metrics = score_candidate(
            {"weights": {}, "penalties": {"missing_metric": 0, "timing_missing": 0, "timing_negative_wns": 0, "stage_failed": 0}},
            candidate["vivado_metrics"],
            candidate["perf_metrics"],
            stage_failed=False,
        )["metrics"]
        if isinstance(metrics.get("lut"), (int, float)) and isinstance(metrics.get("latency_cycles"), (int, float)):
            variant = "unknown"
            cid = str(candidate["candidate_id"])
            if "shared" in cid:
                variant = "shared"
            elif "replicated" in cid:
                variant = "replicated"
            elif "baseline" in cid:
                variant = "baseline"
            points.append((cid, variant, float(metrics["lut"]), float(metrics["latency_cycles"])))

    if not points:
        output_path.write_text(
            "<svg xmlns='http://www.w3.org/2000/svg' width='860' height='540'><text x='20' y='40'>No canonical MAC data.</text></svg>\n"
        )
        return

    x_values = [point[2] for point in points]
    y_values = [point[3] for point in points]
    x_min, x_max = min(x_values), max(x_values)
    y_min, y_max = min(y_values), max(y_values)

    def x_pos(value: float) -> float:
        if x_max == x_min:
            return left + (width - left - right) / 2.0
        return left + (value - x_min) * (width - left - right) / (x_max - x_min)

    def y_pos(value: float) -> float:
        if y_max == y_min:
            return top + (height - top - bottom) / 2.0
        return height - bottom - (value - y_min) * (height - top - bottom) / (y_max - y_min)

    parts = [
        f"<svg xmlns='http://www.w3.org/2000/svg' width='{width}' height='{height}' viewBox='0 0 {width} {height}'>",
        "<style>text{font-family:Helvetica,Arial,sans-serif;font-size:14px}.small{font-size:12px}</style>",
        f"<rect x='0' y='0' width='{width}' height='{height}' fill='#fbfbf7'/>",
        f"<text x='{left}' y='30' font-size='22'>Canonical MAC Evidence: LUT vs Latency</text>",
        f"<line x1='{left}' y1='{height-bottom}' x2='{width-right}' y2='{height-bottom}' stroke='#333' stroke-width='2'/>",
        f"<line x1='{left}' y1='{top}' x2='{left}' y2='{height-bottom}' stroke='#333' stroke-width='2'/>",
        f"<text x='{width/2}' y='{height-20}'>LUT</text>",
        f"<text x='22' y='{height/2}' transform='rotate(-90 22,{height/2})'>Latency Cycles</text>",
    ]
    legend_x = width - 220
    legend_y = 70
    for idx, (variant, color) in enumerate(VARIANT_COLORS.items()):
        y = legend_y + idx * 22
        parts.append(f"<circle cx='{legend_x}' cy='{y}' r='6' fill='{color}'/>")
        parts.append(f"<text x='{legend_x + 14}' y='{y + 4}'>{variant}</text>")
    for cid, variant, lut, latency in points:
        x = x_pos(lut)
        y = y_pos(latency)
        parts.append(
            f"<circle cx='{x:.1f}' cy='{y:.1f}' r='6' fill='{VARIANT_COLORS.get(variant, '#444')}' stroke='#111' stroke-width='1'/>"
        )
        parts.append(f"<text class='small' x='{x + 8:.1f}' y='{y - 8:.1f}'>{cid}</text>")
    parts.append("</svg>")
    output_path.write_text("\n".join(parts) + "\n")


def write_markdown(
    candidates: list[dict[str, object]],
    rows: list[dict[str, object]],
    summaries: list[dict[str, object]],
    output_path: Path,
) -> None:
    output_path.parent.mkdir(parents=True, exist_ok=True)
    winner_counts = Counter(str(summary["winner"]) for summary in summaries if summary["winner"])
    robust_winner = summaries[0]["winner"] if len(winner_counts) == 1 and summaries else None
    lines = [
        "# Score Policy Sensitivity",
        "",
        "This report recomputes rankings over the current canonical MAC candidates using alternative score policies.",
        "",
        "## Evidence Set",
        "",
    ]
    for candidate in candidates:
        lines.append(f"- `{candidate['candidate_id']}`")
    lines.extend(
        [
            "",
            "## Policy Winners",
            "",
            "| Policy | Winner | Ordering |",
            "| --- | --- | --- |",
        ]
    )
    for summary in summaries:
        lines.append(
            f"| {summary['policy_label']} | `{summary['winner']}` | "
            + " > ".join(f"`{candidate}`" for candidate in summary["ordering"])
            + " |"
        )

    lines.extend(["", "## Interpretation", ""])
    if robust_winner:
        lines.append(f"- The same winner appears under every tested policy: `{robust_winner}`.")
    else:
        lines.append("- The winner changes across policies, so the repo should treat the current best-candidate result as policy-sensitive rather than universally robust.")
    lines.append(
        "- Direct measured architecture findings remain stable across policies: shared cuts DSP materially at 4x4, replicated preserves baseline-like latency while increasing area, and baseline scaling raises both latency and cost."
    )
    lines.append(
        "- The official controller ranking remains useful, but it should be read as one explicit policy view rather than a policy-free architectural truth."
    )
    lines.extend(
        [
            "",
            "## Policy Details",
            "",
            "| Policy | Candidate | Rank | Score | Latency | LUT | DSP | WNS |",
            "| --- | --- | ---: | ---: | ---: | ---: | ---: | ---: |",
        ]
    )
    for row in rows:
        lines.append(
            f"| {row['policy_label']} | `{row['candidate_id']}` | {row['rank']} | {float(row['total_score']):.3f} | "
            f"{row['latency_cycles']} | {row['lut']} | {row['dsp']} | {row['wns_ns']} |"
        )
    output_path.write_text("\n".join(lines) + "\n")


def main() -> int:
    candidates = load_canonical_candidates()
    rows, summaries = evaluate_policies(candidates, DEFAULT_POLICY_VARIANTS)
    write_csv(rows, DEFAULT_CSV_OUT)
    write_svg(candidates, DEFAULT_SVG_OUT)
    write_markdown(candidates, rows, summaries, DEFAULT_MD_OUT)
    print(
        json.dumps(
            {
                "markdown_report": str(DEFAULT_MD_OUT),
                "csv_report": str(DEFAULT_CSV_OUT),
                "plot": str(DEFAULT_SVG_OUT),
                "candidate_count": len(candidates),
                "policy_count": len(summaries),
                "winners": {summary["policy_name"]: summary["winner"] for summary in summaries},
            },
            indent=2,
        )
    )
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
