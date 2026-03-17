#!/usr/bin/env python3
"""Generate a compact evidence bundle from canonical MAC results and sweep artifacts."""

from __future__ import annotations

import csv
import json
import math
import sys
from dataclasses import dataclass
from pathlib import Path
from typing import Any

REPO_ROOT = Path(__file__).resolve().parents[1]
if str(REPO_ROOT) not in sys.path:
    sys.path.insert(0, str(REPO_ROOT))

from rtl_agent_loop.controller import Controller

CANDIDATE_ORDER = [
    "mac_baseline_4x4_dw16",
    "mac_baseline_8x4_dw16",
    "mac_baseline_8x8_dw16",
    "mac_shared_4x4_sf2_dw16",
    "mac_shared_8x4_sf2_dw16",
    "mac_shared_8x8_sf2_dw16",
    "mac_replicated_4x4_c2_dw16",
    "mac_replicated_8x4_c2_dw16",
    "mac_replicated_8x8_c2_dw16",
]

SWEEP_CASE_BY_CANDIDATE = {
    "mac_baseline_4x4_dw16": "baseline_4x4",
    "mac_baseline_8x4_dw16": "baseline_8x4",
    "mac_baseline_8x8_dw16": "baseline_8x8",
    "mac_shared_4x4_sf2_dw16": "shared_4x4_sf2",
    "mac_shared_8x4_sf2_dw16": "shared_8x4_sf2",
    "mac_shared_8x8_sf2_dw16": "shared_8x8_sf2",
    "mac_replicated_4x4_c2_dw16": "replicated_4x4_c2",
    "mac_replicated_8x4_c2_dw16": "replicated_8x4_c2",
    "mac_replicated_8x8_c2_dw16": "replicated_8x8_c2",
}

RESULTS_DIR = REPO_ROOT / "docs" / "results"
CANONICAL_MD = RESULTS_DIR / "canonical_mac_results.md"
CANONICAL_CSV = RESULTS_DIR / "canonical_mac_results.csv"
INSIGHT_MD = RESULTS_DIR / "architecture_insight_extract.md"
STATUS_MD = RESULTS_DIR / "current_execution_status.md"
SWEEP_CSV = REPO_ROOT / "external" / "MAC_ARRAY_FPGA" / "experiments" / "results" / "sweep_results.csv"
SENSITIVITY_CSV = RESULTS_DIR / "score_policy_sensitivity.csv"


@dataclass
class CandidateEvidence:
    candidate_id: str
    run_dir: str | None
    attempt_index: int | None
    run_status: str | None
    current_state: str | None
    outcome_tier: str
    latency_cycles: float | None
    lut: float | None
    dsp: float | None
    wns_ns: float | None
    fmax_mhz_est: float | None
    total_score: float | None
    score_provisional: bool
    implementation_evidence: str
    measurement_quality: str
    provenance_note: str


def load_json_file(path: Path) -> Any:
    return json.loads(path.read_text())


def read_score_metrics(status: dict[str, Any]) -> tuple[float | None, dict[str, Any]]:
    latest_score = status.get("latest_score")
    if not latest_score:
        return None, {}
    metrics_json = latest_score.get("metrics_json")
    if isinstance(metrics_json, str):
        metrics = json.loads(metrics_json)
    else:
        metrics = metrics_json or {}
    return latest_score.get("total_score"), metrics


def classify_outcome(status: dict[str, Any]) -> str:
    summary = status.get("resolved_artifact_summary", {})
    quality = summary.get("measurement_quality")
    impl = summary.get("implementation_evidence")
    latest_run = status.get("latest_run") or {}
    run_status = latest_run.get("status")
    if quality == "full" and impl == "full_implementation":
        return "full_pass"
    if quality == "provisional_synth_only" or impl == "synth_only":
        return "synth_only"
    if run_status == "failed":
        return "failed"
    if run_status == "running":
        return "running"
    return "missing"


def build_candidate_rows() -> list[CandidateEvidence]:
    controller = Controller()
    rows: list[CandidateEvidence] = []
    for candidate_id in CANDIDATE_ORDER:
        status = controller.get_status(candidate_id, include_runs=True)
        latest_run = status.get("latest_run") or {}
        resolved = status.get("resolved_artifact_summary") or {}
        total_score, metrics = read_score_metrics(status)
        rows.append(
            CandidateEvidence(
                candidate_id=candidate_id,
                run_dir=latest_run.get("run_dir"),
                attempt_index=latest_run.get("attempt_index"),
                run_status=latest_run.get("status"),
                current_state=(status.get("candidate") or {}).get("current_state"),
                outcome_tier=classify_outcome(status),
                latency_cycles=metrics.get("latency_cycles"),
                lut=metrics.get("lut"),
                dsp=metrics.get("dsp"),
                wns_ns=metrics.get("wns_ns"),
                fmax_mhz_est=metrics.get("fmax_mhz_est"),
                total_score=total_score,
                score_provisional=bool(resolved.get("score_provisional")),
                implementation_evidence=str(resolved.get("implementation_evidence", "missing")),
                measurement_quality=str(resolved.get("measurement_quality", "missing")),
                provenance_note=str(resolved.get("artifact_provenance_note", "")),
            )
        )
    return rows


def write_canonical_csv(rows: list[CandidateEvidence]) -> None:
    RESULTS_DIR.mkdir(parents=True, exist_ok=True)
    with CANONICAL_CSV.open("w", newline="") as handle:
        writer = csv.DictWriter(
            handle,
            fieldnames=[
                "candidate_id",
                "canonical_run_dir",
                "attempt_index",
                "run_status",
                "current_state",
                "outcome_tier",
                "latency_cycles",
                "lut",
                "dsp",
                "wns_ns",
                "fmax_mhz_est",
                "total_score",
                "score_provisional",
                "implementation_evidence",
                "measurement_quality",
                "provenance_note",
            ],
        )
        writer.writeheader()
        for row in rows:
            writer.writerow(
                {
                    "candidate_id": row.candidate_id,
                    "canonical_run_dir": row.run_dir,
                    "attempt_index": row.attempt_index,
                    "run_status": row.run_status,
                    "current_state": row.current_state,
                    "outcome_tier": row.outcome_tier,
                    "latency_cycles": row.latency_cycles,
                    "lut": row.lut,
                    "dsp": row.dsp,
                    "wns_ns": row.wns_ns,
                    "fmax_mhz_est": row.fmax_mhz_est,
                    "total_score": row.total_score,
                    "score_provisional": str(row.score_provisional).lower(),
                    "implementation_evidence": row.implementation_evidence,
                    "measurement_quality": row.measurement_quality,
                    "provenance_note": row.provenance_note,
                }
            )


def write_canonical_md(rows: list[CandidateEvidence]) -> None:
    lines = [
        "# Canonical MAC Results",
        "",
        "| candidate_id | canonical run dir | outcome tier | latency_cycles | lut | dsp | wns_ns | fmax_mhz_est | total_score | score_provisional | implementation_evidence | measurement_quality |",
        "| --- | --- | --- | ---: | ---: | ---: | ---: | ---: | ---: | --- | --- | --- |",
    ]
    for row in rows:
        run_dir = f"`{row.run_dir}`" if row.run_dir else ""
        lines.append(
            f"| `{row.candidate_id}` | {run_dir} | `{row.outcome_tier}` | "
            f"{format_num(row.latency_cycles)} | {format_num(row.lut)} | {format_num(row.dsp)} | "
            f"{format_num(row.wns_ns)} | {format_num(row.fmax_mhz_est)} | {format_num(row.total_score)} | "
            f"`{str(row.score_provisional).lower()}` | `{row.implementation_evidence}` | `{row.measurement_quality}` |"
        )
    lines.extend(["", "## Notes", ""])
    for row in rows:
        if row.provenance_note:
            lines.append(f"- `{row.candidate_id}`: {row.provenance_note}")
    CANONICAL_MD.write_text("\n".join(lines) + "\n")


def format_num(value: float | None) -> str:
    if value is None:
        return ""
    if math.isfinite(value) and float(value).is_integer():
        return str(int(value))
    return f"{value:.3f}".rstrip("0").rstrip(".")


def load_sweep_rows() -> dict[str, dict[str, str]]:
    if not SWEEP_CSV.exists():
        return {}
    with SWEEP_CSV.open() as handle:
        reader = csv.DictReader(handle)
        return {row["case_name"]: row for row in reader}


def load_policy_rows() -> dict[str, list[dict[str, str]]]:
    with SENSITIVITY_CSV.open() as handle:
        reader = csv.DictReader(handle)
        grouped: dict[str, list[dict[str, str]]] = {}
        for row in reader:
            grouped.setdefault(row["policy_name"], []).append(row)
        for entries in grouped.values():
            entries.sort(key=lambda item: int(item["rank"]))
        return grouped


def load_official_ranking() -> tuple[list[str], list[str]]:
    controller = Controller()
    ranking = controller.rank_candidates(active_schema_only=True)
    ranked = [str(item["candidate_id"]) for item in ranking.get("ranked_candidates", [])]
    disqualified = [str(item["candidate_id"]) for item in ranking.get("disqualified_candidates", [])]
    return ranked, disqualified


def diff_note(canonical: CandidateEvidence, sweep_row: dict[str, str] | None) -> str:
    if sweep_row is None:
        return "No sweep row present."
    if canonical.outcome_tier == "synth_only":
        return "Canonical run preserved synth-only Vivado evidence; stored sweep row should not be treated as equally trustworthy."
    comparisons = [
        ("latency_cycles", canonical.latency_cycles),
        ("lut", canonical.lut),
        ("dsp", canonical.dsp),
        ("wns_ns", canonical.wns_ns),
    ]
    for key, c_value in comparisons:
        s_raw = sweep_row.get(key)
        s_value = float(s_raw) if s_raw not in (None, "") else None
        if c_value is None or s_value is None:
            continue
        if abs(float(c_value) - s_value) > 1e-6:
            return "Canonical and sweep values differ; inspect freshness and run provenance."
    return "Canonical and sweep agree on the overlapping measured metrics."


def build_insight_markdown(rows: list[CandidateEvidence]) -> str:
    by_id = {row.candidate_id: row for row in rows}
    sweep_rows = load_sweep_rows()
    policies = load_policy_rows()
    winners = {policy: entries[0]["candidate_id"] for policy, entries in policies.items() if entries}
    official_order, disqualified = load_official_ranking()
    lines = [
        "# Architecture Insight Extract",
        "",
        "## Baseline Findings",
        "",
        f"- `mac_baseline_4x4_dw16` to `mac_baseline_8x4_dw16` increases latency from {format_num(by_id['mac_baseline_4x4_dw16'].latency_cycles)} to {format_num(by_id['mac_baseline_8x4_dw16'].latency_cycles)} cycles and LUT from {format_num(by_id['mac_baseline_4x4_dw16'].lut)} to {format_num(by_id['mac_baseline_8x4_dw16'].lut)}.",
        f"- `mac_baseline_8x8_dw16` extends the same trend to {format_num(by_id['mac_baseline_8x8_dw16'].latency_cycles)} cycles and {format_num(by_id['mac_baseline_8x8_dw16'].lut)} LUT.",
        "",
        "## Shared Findings",
        "",
        f"- `mac_shared_4x4_sf2_dw16` lowers DSP from {format_num(by_id['mac_baseline_4x4_dw16'].dsp)} to {format_num(by_id['mac_shared_4x4_sf2_dw16'].dsp)} versus baseline 4x4, but raises latency from {format_num(by_id['mac_baseline_4x4_dw16'].latency_cycles)} to {format_num(by_id['mac_shared_4x4_sf2_dw16'].latency_cycles)} cycles.",
        f"- `mac_shared_8x4_sf2_dw16` keeps the same pattern at larger size: DSP {format_num(by_id['mac_baseline_8x4_dw16'].dsp)} to {format_num(by_id['mac_shared_8x4_sf2_dw16'].dsp)}, latency {format_num(by_id['mac_baseline_8x4_dw16'].latency_cycles)} to {format_num(by_id['mac_shared_8x4_sf2_dw16'].latency_cycles)} cycles.",
        f"- `mac_shared_8x8_sf2_dw16` extends the same tradeoff at the widest bounded point: DSP {format_num(by_id['mac_baseline_8x8_dw16'].dsp)} to {format_num(by_id['mac_shared_8x8_sf2_dw16'].dsp)}, latency {format_num(by_id['mac_baseline_8x8_dw16'].latency_cycles)} to {format_num(by_id['mac_shared_8x8_sf2_dw16'].latency_cycles)} cycles, and LUT stays near baseline at {format_num(by_id['mac_shared_8x8_sf2_dw16'].lut)}.",
        "",
        "## Replicated Findings",
        "",
        f"- `mac_replicated_4x4_c2_dw16` preserves baseline-like latency at {format_num(by_id['mac_replicated_4x4_c2_dw16'].latency_cycles)} cycles but raises LUT to {format_num(by_id['mac_replicated_4x4_c2_dw16'].lut)} and DSP to {format_num(by_id['mac_replicated_4x4_c2_dw16'].dsp)}.",
        f"- `mac_replicated_8x4_c2_dw16` does the same at larger scale: latency stays at {format_num(by_id['mac_replicated_8x4_c2_dw16'].latency_cycles)} cycles while LUT rises to {format_num(by_id['mac_replicated_8x4_c2_dw16'].lut)}.",
        "",
        "## Ranking Robustness Findings",
        "",
        f"- Official policy order over fully measured canonical candidates: {' > '.join(f'`{candidate}`' for candidate in official_order)}.",
        f"- Official ranking disqualifies: {', '.join(f'`{candidate}`' for candidate in disqualified) if disqualified else 'none'}.",
        f"- Policy winners: default=`{winners.get('default_current')}`, latency=`{winners.get('latency_priority')}`, area=`{winners.get('area_priority')}`, timing=`{winners.get('timing_priority')}`, balanced=`{winners.get('balanced_no_throughput')}`.",
        "- The official best candidate is robust across most tested policies, but not all of them.",
        "",
        "## Canonical vs Sweep Consistency Findings",
        "",
    ]
    for candidate_id in CANDIDATE_ORDER:
        note = diff_note(by_id[candidate_id], sweep_rows.get(SWEEP_CASE_BY_CANDIDATE[candidate_id]))
        lines.append(f"- `{candidate_id}`: {note}")
    lines.extend(
        [
            "",
            "## Provisional / Synth-Only Findings",
            "",
            f"- `mac_replicated_8x8_c2_dw16` produced canonical `{by_id['mac_replicated_8x8_c2_dw16'].outcome_tier}` evidence with implementation_evidence=`{by_id['mac_replicated_8x8_c2_dw16'].implementation_evidence}` and score_provisional=`{str(by_id['mac_replicated_8x8_c2_dw16'].score_provisional).lower()}`.",
            f"- The preserved synth-only result still records LUT={format_num(by_id['mac_replicated_8x8_c2_dw16'].lut)} and WNS={format_num(by_id['mac_replicated_8x8_c2_dw16'].wns_ns)}, which is useful as an implementation-limit signal even though it does not enter the full ranking.",
            "",
            "## Current Unknowns / Unresolved Questions",
            "",
            "- A fresh full external sweep is still needed to replace the stale-looking `replicated_8x8_c2` implementation row in the sweep table.",
            "- `shared_8x8_sf2` is now a canonical point, but it is still missing from the external bounded sweep matrix and sweep CSV.",
            "- The canonical controller flow still has only one synth-only stress point, so wider implementation-limit frontiers are not yet mapped.",
            "",
            "## Single Highest-Value Next Experiment",
            "",
            "- Refresh the external bounded sweep with `shared_8x8_sf2` included, then add one more canonical shared-vs-replicated stress pair at `8x8` or `PIPE_STAGES=2` to map where DSP savings stop justifying scheduling overhead.",
        ]
    )
    return "\n".join(lines) + "\n"


def build_status_markdown(rows: list[CandidateEvidence]) -> str:
    sweep_session_running = False
    # This file is generated while a long sweep may still be running externally.
    sweep_marker = "unknown"
    if (REPO_ROOT / "external" / "MAC_ARRAY_FPGA" / "experiments" / "results" / "sweep_results.csv").exists():
        sweep_marker = "present"
    lines = [
        "# Current Execution Status",
        "",
        "## Completed Use Cases",
        "",
        "- Canonical controller-owned single-candidate evaluation: completed for baseline 4x4, baseline 8x4, baseline 8x8, shared 4x4, shared 8x4, shared 8x8, replicated 4x4, replicated 8x4, and replicated 8x8 stress.",
        "- Active-schema ranking and best-candidate flow: regenerated against the refreshed canonical set.",
        "- Score-policy sensitivity analysis: regenerated.",
        "- Canonical vs sweep reconciliation: completed for overlapping points using the current sweep CSV.",
        "",
        "## Incomplete Or Compute-Bound Use Cases",
        "",
        "- External full bounded sweep refresh may still be in progress; check the live `make -C external/MAC_ARRAY_FPGA sweep` job before treating the broader sweep as fully refreshed.",
        "",
        "## Strongest Artifacts",
        "",
        "- Canonical controller-owned full-pass runs under `runs/<candidate_id>/attempt_<n>/` are the strongest evidence tier.",
        "- `mac_replicated_8x8_c2_dw16` synth-only canonical run is strong provisional evidence for an implementation limit.",
        "",
        "## Stale Or Provisional Artifacts",
        "",
        "- The current external sweep still contains a stale-looking `replicated_8x8_c2` implementation row until a fresh full sweep replaces it.",
        "- The current external sweep does not yet include `shared_8x8_sf2`, so controller vs sweep comparison is not yet available for that point.",
        f"- Sweep CSV presence at generation time: `{sweep_marker}`.",
    ]
    return "\n".join(lines) + "\n"


def main() -> None:
    rows = build_candidate_rows()
    write_canonical_csv(rows)
    write_canonical_md(rows)
    INSIGHT_MD.write_text(build_insight_markdown(rows))
    STATUS_MD.write_text(build_status_markdown(rows))
    print(
        json.dumps(
            {
                "canonical_markdown": str(CANONICAL_MD),
                "canonical_csv": str(CANONICAL_CSV),
                "insight_markdown": str(INSIGHT_MD),
                "status_markdown": str(STATUS_MD),
                "candidate_count": len(rows),
            },
            indent=2,
        )
    )


if __name__ == "__main__":
    main()
