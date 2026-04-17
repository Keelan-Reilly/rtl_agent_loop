from __future__ import annotations

import json
import re
from dataclasses import dataclass
from pathlib import Path
from typing import TYPE_CHECKING, Any

from .config import ValidationError, validate_manifest
from .models import REQUIRED_PARAMETER_KEYS
from .paths import CANDIDATES_DIR, OPTIMIZE_DIR

if TYPE_CHECKING:
    from .controller import Controller


FAILURE_RESOURCE_PATTERNS = (
    "resource",
    "resources exceeded",
    "out of resources",
    "cannot place",
    "device utilization",
    "over-utilized",
    "utilization exceeds",
)


@dataclass(slots=True)
class MutationCandidate:
    candidate_id: str
    manifest_path: Path
    manifest_data: dict[str, Any]
    parent_candidate_id: str
    delta: dict[str, Any]
    delta_key: str
    delta_description: str


class Optimizer:
    MUTATION_PRIORITY = (
        "ARCH_VARIANT",
        "ARRAY_M",
        "ARRAY_N",
        "CLUSTER_SIZE",
        "SHARE_FACTOR",
        "PIPE_STAGES",
        "DATA_WIDTH",
        "ACC_WIDTH",
    )

    STRONG_EXCLUSION_CLASSES = {
        "schema_invalid",
        "verification_fail",
        "synth_fail",
        "route_fail",
        "resource_exceeded",
    }
    SOFT_EXCLUSION_CLASSES = {"synth_only_measurement", "perf_regressed", "timing_fail"}
    ALLOWED_DEPENDENT_DELTA_KEYS = frozenset({"ARCH_VARIANT", "SHARE_FACTOR"})

    def __init__(
        self,
        controller: Controller,
        *,
        candidates_dir: Path | None = None,
        optimize_root: Path | None = None,
    ) -> None:
        self.controller = controller
        self.search_space = controller.search_space
        self.candidates_dir = candidates_dir or CANDIDATES_DIR
        self.optimize_root = optimize_root or OPTIMIZE_DIR

    def optimize(
        self,
        *,
        iterations: int,
        seed_candidate_ids: list[str] | None = None,
        top_k: int = 3,
        mutations_per_parent: int = 1,
        worktree_ref: str | None = None,
        active_schema_only: bool = True,
    ) -> dict[str, Any]:
        if iterations <= 0:
            raise ValidationError("--iterations must be >= 1")
        if top_k <= 0:
            raise ValidationError("--top-k must be >= 1")
        if mutations_per_parent <= 0:
            raise ValidationError("--mutations-per-parent must be >= 1")

        session_id = self._build_session_id(worktree_ref)
        session_dir = self.optimize_root / session_id
        session_dir.mkdir(parents=True, exist_ok=True)
        search_state_path = session_dir / "search_state.json"
        summary_path = session_dir / "summary.json"
        markdown_path = session_dir / "summary.md"

        candidate_views = self.controller.list_candidates(active_schema_only=active_schema_only)
        if not candidate_views:
            raise ValidationError("No registered MAC-array candidates are available for optimize")

        candidate_map = {item["candidate_id"]: item for item in candidate_views}
        seed_ids = seed_candidate_ids or sorted(candidate_map)
        for candidate_id in seed_ids:
            if candidate_id not in candidate_map:
                raise ValidationError(f"Seed candidate {candidate_id!r} is not registered under the active schema")

        state: dict[str, Any] = {
            "session_id": session_id,
            "generated_at": self.controller.utc_now(),
            "config": {
                "iterations": iterations,
                "seed_candidate_ids": seed_ids,
                "top_k": top_k,
                "mutations_per_parent": mutations_per_parent,
                "worktree_ref": worktree_ref,
                "active_schema_only": active_schema_only,
            },
            "seed_candidate_ids": seed_ids,
            "candidate_pool": sorted(seed_ids),
            "attempted_candidate_ids": [],
            "lineage_derivations": [],
            "exact_parameter_exclusions": {},
            "delta_exclusions": {},
            "failure_evidence": [],
            "best_history": [],
            "bootstrap_runs": [],
            "iterations": [],
        }

        ranking = self.controller.rank_candidates(active_schema_only=active_schema_only)
        ranking_index = {item["candidate_id"]: item for item in ranking["ranked_candidates"]}
        unranked_seeds = [candidate_id for candidate_id in seed_ids if candidate_id not in ranking_index]
        for candidate_id in unranked_seeds:
            bootstrap_run = self.controller.run_candidate(candidate_id, worktree_ref=worktree_ref)
            state["bootstrap_runs"].append(
                {
                    "candidate_id": candidate_id,
                    "run_id": bootstrap_run["run_id"],
                    "attempt_index": bootstrap_run["attempt_index"],
                    "current_state": bootstrap_run["current_state"],
                    "stage_failed": bootstrap_run["stage_failed"],
                }
            )
        if unranked_seeds:
            ranking = self.controller.rank_candidates(active_schema_only=active_schema_only)

        existing_parameter_sets = {
            self._parameter_key(self._candidate_parameters(candidate)): candidate["candidate_id"] for candidate in candidate_map.values()
        }
        existing_candidate_ids = set(candidate_map)
        best_record = self._update_best_pointer(ranking, state)
        if best_record is not None:
            state["best_history"].append(best_record)

        for iteration_index in range(1, iterations + 1):
            candidate_views = self.controller.list_candidates(active_schema_only=active_schema_only)
            candidate_map = {item["candidate_id"]: item for item in candidate_views}
            ranking = self.controller.rank_candidates(active_schema_only=active_schema_only)
            ranking_index = {item["candidate_id"]: item for item in ranking["ranked_candidates"]}
            selected_parent_ids, selection_strategy = self._select_parent_ids(
                ranking=ranking,
                candidate_map=candidate_map,
                candidate_pool=state["candidate_pool"],
                top_k=top_k,
            )

            iteration_record: dict[str, Any] = {
                "iteration": iteration_index,
                "selected_parent_ids": list(selected_parent_ids),
                "parent_selection_strategy": selection_strategy,
                "generated_children": [],
                "skipped_parents": [],
                "ranking_snapshot": {
                    "best_under_numeric_score": ranking["best_under_numeric_score"],
                    "best_timing_clean": ranking["best_timing_clean"],
                },
            }

            for parent_candidate_id in selected_parent_ids:
                parent = ranking_index.get(parent_candidate_id)
                parent_view = candidate_map[parent_candidate_id]
                parent_manifest = self._candidate_manifest(parent_view)
                proposals = self._generate_mutations_for_parent(
                    parent_manifest=parent_manifest,
                    existing_parameter_sets=existing_parameter_sets,
                    existing_candidate_ids=existing_candidate_ids,
                    delta_exclusions=state["delta_exclusions"],
                    limit=mutations_per_parent,
                )
                if not proposals:
                    iteration_record["skipped_parents"].append(
                        {
                            "candidate_id": parent_candidate_id,
                            "reason": "No unseen valid one-parameter mutations remained.",
                        }
                    )
                    continue

                for proposal in proposals:
                    self._write_manifest(proposal.manifest_path, proposal.manifest_data)
                    try:
                        register_result = self.controller.register_candidate(
                            proposal.manifest_path,
                            parent_candidate_id=parent_candidate_id,
                            revision_kind="optimize_v1_mutation",
                        )
                    except Exception:
                        if proposal.manifest_path.exists():
                            proposal.manifest_path.unlink()
                        raise
                    existing_parameter_sets[self._parameter_key(proposal.manifest_data["parameters"])] = proposal.candidate_id
                    existing_candidate_ids.add(proposal.candidate_id)
                    if proposal.candidate_id not in state["candidate_pool"]:
                        state["candidate_pool"].append(proposal.candidate_id)

                    run_result = self.controller.run_candidate(proposal.candidate_id, worktree_ref=worktree_ref)
                    child_score = self._candidate_score_from_run(run_result, ranking)
                    failure = self._classify_candidate_result(
                        parent_rank_item=parent,
                        run_result=run_result,
                        child_score=child_score,
                    )
                    self._record_exclusion(
                        state=state,
                        parameter_key=self._parameter_key(proposal.manifest_data["parameters"]),
                        delta_key=proposal.delta_key,
                        candidate_id=proposal.candidate_id,
                        failure_class=failure["failure_class"],
                        iteration=iteration_index,
                    )

                    entry = {
                        "candidate_id": proposal.candidate_id,
                        "parent_candidate_id": parent_candidate_id,
                        "manifest_path": str(proposal.manifest_path),
                        "delta": proposal.delta,
                        "delta_key": proposal.delta_key,
                        "delta_description": proposal.delta_description,
                        "register_result": {
                            "manifest_path": register_result["manifest_path"],
                            "candidate_dir": register_result["candidate_dir"],
                        },
                        "run_id": run_result["run_id"],
                        "attempt_index": run_result["attempt_index"],
                        "current_state": run_result["current_state"],
                        "failure_classification": failure,
                        "score": child_score,
                    }
                    iteration_record["generated_children"].append(entry)
                    state["attempted_candidate_ids"].append(proposal.candidate_id)
                    state["lineage_derivations"].append(
                        {
                            "parent_candidate_id": parent_candidate_id,
                            "child_candidate_id": proposal.candidate_id,
                            "revision_kind": "optimize_v1_mutation",
                            "delta_key": proposal.delta_key,
                        }
                    )
                    state["failure_evidence"].append(
                        {
                            "candidate_id": proposal.candidate_id,
                            "parent_candidate_id": parent_candidate_id,
                            "failure_class": failure["failure_class"],
                            "delta_key": proposal.delta_key,
                            "details": failure,
                        }
                    )

            ranking = self.controller.rank_candidates(active_schema_only=active_schema_only)
            best_record = self._update_best_pointer(ranking, state)
            if best_record is not None:
                state["best_history"].append(best_record)
            state["iterations"].append(iteration_record)
            self._write_json(search_state_path, state)

        final_ranking = self.controller.rank_candidates(active_schema_only=active_schema_only)
        summary = self._build_summary(session_id=session_id, ranking=final_ranking, state=state, summary_path=summary_path)
        self._write_json(search_state_path, state)
        self._write_json(summary_path, summary)
        markdown_path.write_text(self._render_summary_markdown(summary))
        summary["markdown_report_path"] = str(markdown_path)
        self._write_json(summary_path, summary)
        return summary

    def _generate_mutations_for_parent(
        self,
        *,
        parent_manifest: dict[str, Any],
        existing_parameter_sets: dict[str, str],
        existing_candidate_ids: set[str],
        delta_exclusions: dict[str, Any],
        limit: int,
    ) -> list[MutationCandidate]:
        parent_candidate_id = parent_manifest["candidate_id"]
        parent_parameters = dict(parent_manifest["parameters"])
        proposals: list[MutationCandidate] = []

        for param_name in self.MUTATION_PRIORITY:
            current_value = parent_parameters[param_name]
            allowed_values = list(self.search_space["search_space"][param_name]["allowed"])
            for allowed_value in allowed_values:
                if allowed_value == current_value:
                    continue
                candidate_parameters = dict(parent_parameters)
                candidate_parameters[param_name] = allowed_value
                if not self._repair_candidate_parameters(candidate_parameters):
                    continue
                parameter_key = self._parameter_key(candidate_parameters)
                if parameter_key in existing_parameter_sets:
                    continue

                delta = self._parameter_delta(parent_parameters, candidate_parameters)
                if not self._is_allowed_delta(param_name, delta):
                    continue
                delta_key = self._delta_key(delta)
                if self._delta_is_excluded(delta_key, delta_exclusions):
                    continue

                candidate_id = self._unique_candidate_id(parent_candidate_id, delta, existing_candidate_ids)
                manifest_data = self._build_child_manifest(
                    parent_manifest=parent_manifest,
                    child_candidate_id=candidate_id,
                    child_parameters=candidate_parameters,
                    delta=delta,
                )
                manifest_path = self.candidates_dir / f"{candidate_id}.json"
                validate_manifest(manifest_data, manifest_path, self.search_space)
                proposals.append(
                    MutationCandidate(
                        candidate_id=candidate_id,
                        manifest_path=manifest_path,
                        manifest_data=manifest_data,
                        parent_candidate_id=parent_candidate_id,
                        delta=delta,
                        delta_key=delta_key,
                        delta_description=self._delta_description(delta),
                    )
                )
                existing_parameter_sets[parameter_key] = candidate_id
                existing_candidate_ids.add(candidate_id)
                if len(proposals) >= limit:
                    return proposals

        return proposals

    def _repair_candidate_parameters(self, parameters: dict[str, int]) -> bool:
        search = self.search_space["search_space"]
        arch_variant = parameters["ARCH_VARIANT"]
        share_allowed = search["SHARE_FACTOR"]["allowed"]
        if arch_variant == 1:
            valid_share_values = [value for value in share_allowed if value >= 2]
            if not valid_share_values:
                return False
            if parameters["SHARE_FACTOR"] < 2:
                parameters["SHARE_FACTOR"] = min(valid_share_values)
        else:
            parameters["SHARE_FACTOR"] = 1
        if parameters["SHARE_FACTOR"] not in share_allowed:
            return False

        max_dimension = max(parameters["ARRAY_M"], parameters["ARRAY_N"])
        cluster_allowed = sorted(search["CLUSTER_SIZE"]["allowed"])
        if parameters["CLUSTER_SIZE"] > max_dimension:
            eligible_clusters = [value for value in cluster_allowed if value <= max_dimension]
            if not eligible_clusters:
                return False
            parameters["CLUSTER_SIZE"] = max(eligible_clusters)

        if parameters["FRAC_BITS"] >= parameters["DATA_WIDTH"]:
            frac_allowed = [value for value in search["FRAC_BITS"]["allowed"] if value < parameters["DATA_WIDTH"]]
            if not frac_allowed:
                return False
            parameters["FRAC_BITS"] = max(frac_allowed)

        if parameters["ACC_WIDTH"] <= parameters["DATA_WIDTH"]:
            acc_allowed = [value for value in search["ACC_WIDTH"]["allowed"] if value > parameters["DATA_WIDTH"]]
            if not acc_allowed:
                return False
            parameters["ACC_WIDTH"] = min(acc_allowed)

        required_input_depth = max(parameters["ARRAY_M"] * parameters["TILE_K"], parameters["ARRAY_N"] * parameters["TILE_K"])
        input_depth_allowed = sorted(search["INPUT_MEM_DEPTH"]["allowed"])
        if parameters["INPUT_MEM_DEPTH"] < required_input_depth:
            eligible_input_depths = [value for value in input_depth_allowed if value >= required_input_depth]
            if not eligible_input_depths:
                return False
            parameters["INPUT_MEM_DEPTH"] = min(eligible_input_depths)

        required_output_depth = parameters["ARRAY_M"] * parameters["ARRAY_N"]
        output_depth_allowed = sorted(search["OUTPUT_MEM_DEPTH"]["allowed"])
        if parameters["OUTPUT_MEM_DEPTH"] < required_output_depth:
            eligible_output_depths = [value for value in output_depth_allowed if value >= required_output_depth]
            if not eligible_output_depths:
                return False
            parameters["OUTPUT_MEM_DEPTH"] = min(eligible_output_depths)
        return True

    def _build_child_manifest(
        self,
        *,
        parent_manifest: dict[str, Any],
        child_candidate_id: str,
        child_parameters: dict[str, int],
        delta: dict[str, Any],
    ) -> dict[str, Any]:
        tags = list(parent_manifest.get("tags", []))
        for tag in ("optimize_v1", "auto_generated"):
            if tag not in tags:
                tags.append(tag)
        notes = str(parent_manifest.get("notes", "")).strip()
        delta_description = self._delta_description(delta)
        optimize_note = (
            f"Optimize v1 child derived from {parent_manifest['candidate_id']} with mutation {delta_description}."
        )
        merged_notes = optimize_note if not notes else f"{notes}\n\n{optimize_note}"
        return {
            "candidate_id": child_candidate_id,
            "source": "rtl_agent_loop_optimize_v1",
            "created_at": self.controller.utc_now(),
            "parameters": child_parameters,
            "notes": merged_notes,
            "tags": tags,
        }

    def _classify_candidate_result(
        self,
        *,
        parent_rank_item: dict[str, Any] | None,
        run_result: dict[str, Any],
        child_score: dict[str, Any] | None,
    ) -> dict[str, Any]:
        stages = {stage["stage_name"]: stage for stage in run_result.get("run_stages", [])}
        payloads = self._load_run_stage_payloads(run_result)

        if not run_result.get("run_id"):
            return {"failure_class": "schema_invalid", "reason": "candidate did not reach execution"}

        fast_verify = payloads.get("fast_verify", {})
        if stages.get("fast_verify", {}).get("status") == "failed":
            return {
                "failure_class": "verification_fail",
                "stage": "fast_verify",
                "outcome_classification": fast_verify.get("outcome_classification"),
                "message": fast_verify.get("message"),
            }

        vivado = payloads.get("vivado", {})
        vivado_message = str(vivado.get("message", "")).lower()
        vivado_classification = str(vivado.get("outcome_classification", ""))
        if self._looks_like_resource_exceeded(vivado, vivado_message):
            return {
                "failure_class": "resource_exceeded",
                "stage": "vivado",
                "outcome_classification": vivado_classification,
                "message": vivado.get("message"),
            }
        if vivado_classification == "synth_only":
            return {
                "failure_class": "synth_only_measurement",
                "stage": "vivado",
                "outcome_classification": vivado_classification,
                "message": vivado.get("message"),
            }
        if stages.get("vivado", {}).get("status") == "failed":
            if any(token in vivado_message for token in ("route", "routed", "place_design", "placed", "implementation route")):
                failure_class = "route_fail"
            else:
                failure_class = "synth_fail"
            return {
                "failure_class": failure_class,
                "stage": "vivado",
                "outcome_classification": vivado_classification,
                "message": vivado.get("message"),
            }

        metrics = (child_score or {}).get("metrics", {})
        wns_value = metrics.get("wns_ns")
        if isinstance(wns_value, (int, float)) and float(wns_value) < 0.0:
            return {
                "failure_class": "timing_fail",
                "stage": "scoring",
                "wns_ns": float(wns_value),
            }

        if parent_rank_item is not None and child_score is not None:
            parent_score = parent_rank_item["score"]["total_score"]
            parent_latency = parent_rank_item["score"]["metrics"].get("latency_cycles")
            child_total = child_score.get("total_score")
            child_latency = child_score.get("metrics", {}).get("latency_cycles")
            if isinstance(child_total, (int, float)) and float(child_total) < float(parent_score):
                return {
                    "failure_class": "perf_regressed",
                    "stage": "scoring",
                    "parent_total_score": parent_score,
                    "child_total_score": child_total,
                    "parent_latency_cycles": parent_latency,
                    "child_latency_cycles": child_latency,
                }
            if isinstance(parent_latency, (int, float)) and isinstance(child_latency, (int, float)) and float(child_latency) > float(parent_latency):
                return {
                    "failure_class": "perf_regressed",
                    "stage": "scoring",
                    "parent_total_score": parent_score,
                    "child_total_score": child_total,
                    "parent_latency_cycles": parent_latency,
                    "child_latency_cycles": child_latency,
                }

        return {"failure_class": "full_pass", "stage": "scoring"}

    def _candidate_score_from_run(self, run_result: dict[str, Any], ranking: dict[str, Any]) -> dict[str, Any] | None:
        if run_result.get("score"):
            return run_result["score"]
        ranked_item = next(
            (item for item in ranking.get("ranked_candidates", []) if item["candidate_id"] == run_result["candidate_id"]),
            None,
        )
        return ranked_item["score"] if ranked_item else None

    def _load_run_stage_payloads(self, run_result: dict[str, Any]) -> dict[str, dict[str, Any]]:
        payloads: dict[str, dict[str, Any]] = {}
        for stage in run_result.get("run_stages", []):
            result_path = stage.get("result_path")
            if not result_path:
                continue
            path = Path(result_path)
            if not path.exists():
                continue
            payloads[stage["stage_name"]] = json.loads(path.read_text())
        return payloads

    def _record_exclusion(
        self,
        *,
        state: dict[str, Any],
        parameter_key: str,
        delta_key: str,
        candidate_id: str,
        failure_class: str,
        iteration: int,
    ) -> None:
        if failure_class in self.STRONG_EXCLUSION_CLASSES | self.SOFT_EXCLUSION_CLASSES:
            exact = state["exact_parameter_exclusions"].setdefault(parameter_key, [])
            exact.append(
                {
                    "candidate_id": candidate_id,
                    "failure_class": failure_class,
                    "iteration": iteration,
                }
            )
            delta_entry = state["delta_exclusions"].setdefault(
                delta_key,
                {"count": 0, "failure_classes": [], "last_candidate_id": None},
            )
            delta_entry["count"] += 1
            delta_entry["failure_classes"].append(failure_class)
            delta_entry["last_candidate_id"] = candidate_id

    def _build_summary(
        self,
        *,
        session_id: str,
        ranking: dict[str, Any],
        state: dict[str, Any],
        summary_path: Path,
    ) -> dict[str, Any]:
        ranked = ranking.get("ranked_candidates", [])
        best_candidate = ranked[0] if ranked else None
        pareto_candidates = self._pareto_front(ranked)
        evidence_rules = self._discover_design_rules(state)
        return {
            "session_id": session_id,
            "generated_at": self.controller.utc_now(),
            "search_state_path": str((summary_path.parent / "search_state.json")),
            "summary_path": str(summary_path),
            "config": state["config"],
            "best_candidate": self._summary_rank_item(best_candidate),
            "best_timing_clean_candidate": self._summary_rank_item(
                next((item for item in ranked if item.get("timing_status") == "timing_clean"), None)
            ),
            "top_ranked_candidates": [self._summary_rank_item(item) for item in ranked[:5]],
            "pareto_candidates": [self._summary_rank_item(item) for item in pareto_candidates],
            "rejected_regions": self._rejected_regions(state),
            "discovered_design_rules": evidence_rules,
            "iteration_history": state["iterations"],
            "failure_evidence": state["failure_evidence"],
            "best_history": state["best_history"],
        }

    def _summary_rank_item(self, item: dict[str, Any] | None) -> dict[str, Any] | None:
        if item is None:
            return None
        metrics = item["score"]["metrics"]
        return {
            "candidate_id": item["candidate_id"],
            "rank": item.get("rank"),
            "timing_status": item.get("timing_status"),
            "measurement_quality": item.get("measurement_quality"),
            "implementation_evidence": item.get("implementation_evidence"),
            "total_score": item["score"]["total_score"],
            "metrics": {
                "latency_cycles": metrics.get("latency_cycles"),
                "lut": metrics.get("lut"),
                "dsp": metrics.get("dsp"),
                "wns_ns": metrics.get("wns_ns"),
            },
        }

    def _pareto_front(self, ranked: list[dict[str, Any]]) -> list[dict[str, Any]]:
        pareto: list[dict[str, Any]] = []
        for candidate in ranked:
            metrics = candidate["score"]["metrics"]
            latency = metrics.get("latency_cycles")
            lut = metrics.get("lut")
            wns = metrics.get("wns_ns")
            if not all(isinstance(value, (int, float)) for value in (latency, lut, wns)):
                continue
            dominated = False
            for other in ranked:
                if other["candidate_id"] == candidate["candidate_id"]:
                    continue
                other_metrics = other["score"]["metrics"]
                other_latency = other_metrics.get("latency_cycles")
                other_lut = other_metrics.get("lut")
                other_wns = other_metrics.get("wns_ns")
                if not all(isinstance(value, (int, float)) for value in (other_latency, other_lut, other_wns)):
                    continue
                if (
                    float(other_latency) <= float(latency)
                    and float(other_lut) <= float(lut)
                    and float(other_wns) >= float(wns)
                    and (
                        float(other_latency) < float(latency)
                        or float(other_lut) < float(lut)
                        or float(other_wns) > float(wns)
                    )
                ):
                    dominated = True
                    break
            if not dominated:
                pareto.append(candidate)
        return pareto[:5]

    def _discover_design_rules(self, state: dict[str, Any]) -> list[str]:
        rules: list[str] = []
        by_failure: dict[str, list[dict[str, Any]]] = {}
        for item in state["failure_evidence"]:
            by_failure.setdefault(item["failure_class"], []).append(item)

        synth_only_items = by_failure.get("synth_only_measurement", [])
        if synth_only_items:
            rules.append(
                f"{len(synth_only_items)} optimize-generated candidates ended in synth-only Vivado evidence instead of full implementation closure."
            )

        perf_regressed = by_failure.get("perf_regressed", [])
        if perf_regressed:
            rules.append(
                f"{len(perf_regressed)} optimize-generated candidates regressed score or latency relative to their immediate parent."
            )

        timing_failed = by_failure.get("timing_fail", [])
        if timing_failed:
            rules.append(f"{len(timing_failed)} optimize-generated candidates produced negative WNS despite otherwise scoreable evidence.")

        return rules

    def _rejected_regions(self, state: dict[str, Any]) -> list[dict[str, Any]]:
        regions: list[dict[str, Any]] = []
        for delta_key, entry in sorted(state["delta_exclusions"].items()):
            if entry["count"] < 1:
                continue
            regions.append(
                {
                    "delta_key": delta_key,
                    "count": entry["count"],
                    "failure_classes": entry["failure_classes"],
                    "last_candidate_id": entry["last_candidate_id"],
                }
            )
        return regions

    def _render_summary_markdown(self, summary: dict[str, Any]) -> str:
        lines = [
            "# Optimize Summary",
            "",
            f"Session: `{summary['session_id']}`",
            "",
            f"- Best candidate: `{summary['best_candidate']['candidate_id']}`" if summary["best_candidate"] else "- Best candidate: `None`",
            f"- Best timing-clean candidate: `{summary['best_timing_clean_candidate']['candidate_id']}`"
            if summary["best_timing_clean_candidate"]
            else "- Best timing-clean candidate: `None`",
            "",
            "## Top Ranked",
            "",
            "| Rank | Candidate | Score | Timing | Latency | LUT | WNS |",
            "| --- | --- | ---: | --- | ---: | ---: | ---: |",
        ]
        for item in summary["top_ranked_candidates"]:
            metrics = item["metrics"]
            lines.append(
                f"| {item['rank']} | `{item['candidate_id']}` | {item['total_score']:.3f} | {item['timing_status']} | "
                f"{metrics.get('latency_cycles', 'N/A')} | {metrics.get('lut', 'N/A')} | {metrics.get('wns_ns', 'N/A')} |"
            )

        lines.extend(["", "## Rejected Regions", ""])
        if summary["rejected_regions"]:
            for item in summary["rejected_regions"]:
                lines.append(
                    f"- `{item['delta_key']}` repeated {item['count']} time(s): {', '.join(item['failure_classes'])}"
                )
        else:
            lines.append("- No learned exclusions were recorded.")

        lines.extend(["", "## Evidence Rules", ""])
        if summary["discovered_design_rules"]:
            for rule in summary["discovered_design_rules"]:
                lines.append(f"- {rule}")
        else:
            lines.append("- No session-level design rules were extracted.")
        lines.append("")
        return "\n".join(lines)

    def _update_best_pointer(self, ranking: dict[str, Any], state: dict[str, Any]) -> dict[str, Any] | None:
        best_numeric = ranking.get("best_under_numeric_score")
        best_timing = ranking.get("best_timing_clean")
        if not best_numeric or not best_timing:
            return None

        last = state["best_history"][-1] if state["best_history"] else None
        if last is not None and last["best_numeric_score"] == best_numeric and last["best_timing_clean"] == best_timing:
            return None

        self.controller.set_best_candidates(best_numeric_score=best_numeric, best_timing_clean=best_timing)
        return {
            "recorded_at": self.controller.utc_now(),
            "best_numeric_score": best_numeric,
            "best_timing_clean": best_timing,
        }

    def _build_session_id(self, worktree_ref: str | None) -> str:
        stamp = self.controller.utc_now().replace(":", "").replace("-", "")
        clean_ref = re.sub(r"[^a-z0-9_]+", "_", (worktree_ref or "local").lower()).strip("_")
        return f"{stamp}_{clean_ref}"

    def _select_parent_ids(
        self,
        *,
        ranking: dict[str, Any],
        candidate_map: dict[str, dict[str, Any]],
        candidate_pool: list[str],
        top_k: int,
    ) -> tuple[list[str], str]:
        pool_ids = set(candidate_pool)
        ranked_pool = [item["candidate_id"] for item in ranking["ranked_candidates"] if item["candidate_id"] in pool_ids]
        if ranked_pool:
            return ranked_pool[:top_k], "ranked_pool"

        fallback_ids: list[str] = []
        for candidate_id in candidate_pool:
            if candidate_id in candidate_map and candidate_id not in fallback_ids:
                fallback_ids.append(candidate_id)
            if len(fallback_ids) >= top_k:
                break
        return fallback_ids, "seed_pool_fallback"

    def _candidate_manifest(self, candidate_view: dict[str, Any]) -> dict[str, Any]:
        manifest = json.loads(candidate_view["manifest_json"])
        if not isinstance(manifest, dict):
            raise ValidationError(f"Candidate {candidate_view['candidate_id']!r} has invalid manifest_json")
        for key in ("candidate_id", "parameters", "notes", "tags"):
            if key not in manifest:
                raise ValidationError(f"Candidate {candidate_view['candidate_id']!r} is missing manifest field {key!r}")
        return manifest

    def _candidate_parameters(self, candidate_view: dict[str, Any]) -> dict[str, int]:
        return dict(self._candidate_manifest(candidate_view)["parameters"])

    def _is_allowed_delta(self, param_name: str, delta: dict[str, Any]) -> bool:
        if len(delta) == 1:
            return True
        if param_name == "ARCH_VARIANT" and set(delta) == self.ALLOWED_DEPENDENT_DELTA_KEYS:
            return True
        return False

    def _parameter_delta(self, before: dict[str, int], after: dict[str, int]) -> dict[str, Any]:
        delta: dict[str, Any] = {}
        for key in REQUIRED_PARAMETER_KEYS:
            if before[key] != after[key]:
                delta[key] = {"from": before[key], "to": after[key]}
        return delta

    def _delta_description(self, delta: dict[str, Any]) -> str:
        if not delta:
            return "no-op"
        return ",".join(
            f"{key}:{delta[key]['from']}->{delta[key]['to']}"
            for key in sorted(delta)
        )

    def _delta_key(self, delta: dict[str, Any]) -> str:
        return "|".join(
            f"{key}:{delta[key]['from']}->{delta[key]['to']}"
            for key in sorted(delta)
        )

    def _parameter_key(self, parameters: dict[str, int]) -> str:
        return json.dumps({key: parameters[key] for key in sorted(parameters)}, sort_keys=True)

    def _delta_is_excluded(self, delta_key: str, delta_exclusions: dict[str, Any]) -> bool:
        entry = delta_exclusions.get(delta_key)
        if not entry:
            return False
        return entry.get("count", 0) >= 2 and any(
            failure in self.STRONG_EXCLUSION_CLASSES for failure in entry.get("failure_classes", [])
        )

    def _unique_candidate_id(
        self,
        parent_candidate_id: str,
        delta: dict[str, Any],
        existing_candidate_ids: set[str],
    ) -> str:
        token = self._delta_token(delta)
        base = f"{parent_candidate_id}_opt_{token}"
        candidate_id = base
        suffix = 2
        while candidate_id in existing_candidate_ids or (self.candidates_dir / f"{candidate_id}.json").exists():
            candidate_id = f"{base}_{suffix}"
            suffix += 1
        return candidate_id

    def _delta_token(self, delta: dict[str, Any]) -> str:
        return "_".join(
            f"{key.lower()}_{delta[key]['to']}"
            for key in sorted(delta)
        )

    def _looks_like_resource_exceeded(self, vivado_payload: dict[str, Any], message: str) -> bool:
        if any(pattern in message for pattern in FAILURE_RESOURCE_PATTERNS):
            return True
        metrics = vivado_payload.get("metrics", {})
        util = metrics.get("utilization", {}) if isinstance(metrics.get("utilization"), dict) else {}
        for key in ("lut_util_percent", "ff_util_percent", "dsp_util_percent", "bram_util_percent"):
            value = metrics.get(key, util.get(key))
            if isinstance(value, (int, float)) and float(value) > 100.0:
                return True
        return False

    def _write_manifest(self, path: Path, payload: dict[str, Any]) -> None:
        path.parent.mkdir(parents=True, exist_ok=True)
        path.write_text(json.dumps(payload, indent=2) + "\n")

    def _write_json(self, path: Path, payload: dict[str, Any]) -> None:
        path.parent.mkdir(parents=True, exist_ok=True)
        path.write_text(json.dumps(payload, indent=2) + "\n")
