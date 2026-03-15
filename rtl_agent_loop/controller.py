from __future__ import annotations

import json
from datetime import datetime, timezone
from pathlib import Path
from typing import Any

from .config import ValidationError, load_json, load_score_weights, load_search_space, validate_manifest
from .models import CandidateManifest, StageResult
from .paths import BEST_CANDIDATES_PATH, DEFAULT_SCORE_WEIGHTS_PATH, RUNS_DIR, SCRIPTS_DIR, VAR_DIR
from .scoring import score_candidate
from .sqlite_store import SQLiteStore
from .state_machine import (
    ALL_STAGE_NAMES,
    EXECUTABLE_STAGE_NAMES,
    SCORED,
    SCORING_STAGE_NAME,
    STAGES,
    STAGE_ORDER,
    normalize_stage_range,
)
from .subprocess_utils import run_command, shell_join


def utc_now() -> str:
    return datetime.now(timezone.utc).strftime("%Y-%m-%dT%H:%M:%SZ")


class Controller:
    def __init__(self, store: SQLiteStore | None = None) -> None:
        self.store = store or SQLiteStore()
        self.search_space = load_search_space()
        self.score_weights = load_score_weights()

    def init_db(self) -> None:
        self.store.init_db()

    def register_candidate(
        self,
        manifest_path: Path,
        *,
        parent_candidate_id: str | None = None,
        revision_kind: str | None = None,
        derived_from_run_id: int | None = None,
        supersedes_candidate_id: str | None = None,
    ) -> dict[str, Any]:
        manifest_data = load_json(manifest_path)
        manifest = validate_manifest(manifest_data, manifest_path.resolve(), self.search_space)
        self.store.init_db()
        if self.store.candidate_exists(manifest.candidate_id):
            raise ValidationError(f"Candidate {manifest.candidate_id!r} is already registered")

        parent = None
        if parent_candidate_id is not None:
            parent = self.store.get_candidate(parent_candidate_id)
            if parent is None:
                raise ValidationError(f"Parent candidate {parent_candidate_id!r} is not registered")

        if supersedes_candidate_id is not None and self.store.get_candidate(supersedes_candidate_id) is None:
            raise ValidationError(f"Superseded candidate {supersedes_candidate_id!r} is not registered")

        if derived_from_run_id is not None and self.store.get_run(derived_from_run_id) is None:
            raise ValidationError(f"Derived-from run {derived_from_run_id!r} does not exist")

        candidate_root = RUNS_DIR / manifest.candidate_id
        candidate_root.mkdir(parents=True, exist_ok=True)
        stored_manifest_path = candidate_root / "candidate_manifest.json"
        stored_manifest_path.write_text(json.dumps(manifest.raw, indent=2) + "\n")

        manifest = CandidateManifest(
            candidate_id=manifest.candidate_id,
            source=manifest.source,
            created_at=manifest.created_at,
            parameters=manifest.parameters,
            notes=manifest.notes,
            tags=manifest.tags,
            manifest_path=stored_manifest_path,
            raw=manifest.raw,
        )
        lineage_root_candidate_id = parent["lineage_root_candidate_id"] if parent else manifest.candidate_id
        self.store.register_candidate(
            manifest,
            candidate_root,
            utc_now(),
            parent_candidate_id=parent_candidate_id,
            lineage_root_candidate_id=lineage_root_candidate_id,
            revision_kind=revision_kind,
            derived_from_run_id=derived_from_run_id,
            supersedes_candidate_id=supersedes_candidate_id,
        )
        return {
            "candidate_id": manifest.candidate_id,
            "current_state": "registered",
            "manifest_path": str(stored_manifest_path),
            "candidate_dir": str(candidate_root),
            "parent_candidate_id": parent_candidate_id,
            "lineage_root_candidate_id": lineage_root_candidate_id,
            "revision_kind": revision_kind,
            "derived_from_run_id": derived_from_run_id,
            "supersedes_candidate_id": supersedes_candidate_id,
        }

    def run_candidate(
        self,
        candidate_id: str,
        *,
        start_stage: str | None = None,
        end_stage: str | None = None,
        worktree_ref: str | None = None,
    ) -> dict[str, Any]:
        self.store.init_db()
        candidate = self.store.get_candidate(candidate_id)
        if candidate is None:
            raise ValidationError(f"Candidate {candidate_id!r} is not registered")

        try:
            resolved_start_stage, resolved_end_stage = normalize_stage_range(start_stage, end_stage)
        except ValueError as exc:
            raise ValidationError(str(exc)) from exc

        run_id, attempt_index, owner_token, run_dir = self.store.create_run(
            candidate_id,
            utc_now(),
            Path(candidate["candidate_dir"]),
            requested_start_stage=resolved_start_stage,
            requested_end_stage=resolved_end_stage,
            worktree_ref=worktree_ref,
        )
        run_dir.mkdir(parents=True, exist_ok=True)

        manifest_path = Path(candidate["manifest_path"])
        current_state = candidate["current_state"]
        stage_outputs: dict[str, dict[str, Any]] = {}
        selected_stage_names = self._selected_stage_names(resolved_start_stage, resolved_end_stage)
        final_status = "completed"
        stage_failed = False
        executed_stage_names: list[str] = []

        for stage_name in ALL_STAGE_NAMES:
            if stage_name not in selected_stage_names:
                self.store.upsert_run_stage(
                    run_id=run_id,
                    candidate_id=candidate_id,
                    stage_name=stage_name,
                    stage_order=STAGE_ORDER[stage_name],
                    status="skipped",
                    owner_token=owner_token,
                    details={"event": "skipped", "reason": "outside_requested_range"},
                )

        for stage in STAGES:
            if stage.name not in selected_stage_names:
                continue

            executed_stage_names.append(stage.name)
            self.store.transition_state(
                candidate_id=candidate_id,
                run_id=run_id,
                stage=stage.name,
                from_state=current_state,
                to_state=stage.pending_state,
                details={"event": "stage_pending", "run_dir": str(run_dir), "owner_token": owner_token},
                transitioned_at=utc_now(),
            )
            current_state = stage.pending_state
            stage_started_at = utc_now()
            self.store.upsert_run_stage(
                run_id=run_id,
                candidate_id=candidate_id,
                stage_name=stage.name,
                stage_order=STAGE_ORDER[stage.name],
                status="running",
                owner_token=owner_token,
                started_at=stage_started_at,
                details={"event": "stage_running"},
            )

            result = self._run_stage(stage.name, manifest_path, run_dir, stage.result_relpath)
            stage_outputs[stage.name] = result.payload

            self.store.record_artifact(
                candidate_id=candidate_id,
                run_id=run_id,
                stage=stage.name,
                artifact_type="stage_result",
                path=str(result.result_path),
                metadata={"passed": result.passed, "owner_token": owner_token},
                recorded_at=utc_now(),
            )
            log_path = result.payload.get("log_path")
            if log_path:
                self.store.record_artifact(
                    candidate_id=candidate_id,
                    run_id=run_id,
                    stage=stage.name,
                    artifact_type="log",
                    path=str(run_dir / log_path),
                    metadata={"owner_token": owner_token},
                    recorded_at=utc_now(),
                )

            next_state = stage.success_state if result.passed else stage.failure_state
            stage_status = "passed" if result.passed else "failed"
            resolved_log_path = str(run_dir / log_path) if log_path else None
            self.store.upsert_run_stage(
                run_id=run_id,
                candidate_id=candidate_id,
                stage_name=stage.name,
                stage_order=STAGE_ORDER[stage.name],
                status=stage_status,
                owner_token=owner_token,
                started_at=stage_started_at,
                ended_at=utc_now(),
                result_path=str(result.result_path),
                log_path=resolved_log_path,
                details={
                    "event": "stage_complete",
                    "message": result.payload.get("message"),
                    "status": result.payload.get("status"),
                },
            )
            self.store.transition_state(
                candidate_id=candidate_id,
                run_id=run_id,
                stage=stage.name,
                from_state=current_state,
                to_state=next_state,
                details={
                    "event": "stage_complete",
                    "result_path": str(result.result_path),
                    "status": result.payload.get("status"),
                    "message": result.payload.get("message"),
                },
                transitioned_at=utc_now(),
            )
            current_state = next_state

            if not result.passed:
                stage_failed = True
                final_status = "failed"
                for skipped_stage_name in ALL_STAGE_NAMES[STAGE_ORDER[stage.name] + 1 :]:
                    if skipped_stage_name in selected_stage_names:
                        self.store.upsert_run_stage(
                            run_id=run_id,
                            candidate_id=candidate_id,
                            stage_name=skipped_stage_name,
                            stage_order=STAGE_ORDER[skipped_stage_name],
                            status="skipped",
                            owner_token=owner_token,
                            details={"event": "skipped", "reason": "prior_stage_failed"},
                        )
                break

        scoring_payload: dict[str, Any] | None = None
        if SCORING_STAGE_NAME in selected_stage_names:
            scoring_started_at = utc_now()
            if stage_failed:
                self.store.upsert_run_stage(
                    run_id=run_id,
                    candidate_id=candidate_id,
                    stage_name=SCORING_STAGE_NAME,
                    stage_order=STAGE_ORDER[SCORING_STAGE_NAME],
                    status="skipped",
                    owner_token=owner_token,
                    details={"event": "skipped", "reason": "prior_stage_failed"},
                )
            else:
                self.store.upsert_run_stage(
                    run_id=run_id,
                    candidate_id=candidate_id,
                    stage_name=SCORING_STAGE_NAME,
                    stage_order=STAGE_ORDER[SCORING_STAGE_NAME],
                    status="running",
                    owner_token=owner_token,
                    started_at=scoring_started_at,
                    details={"event": "scoring_running"},
                )
                scoring_payload = self._score_run(stage_outputs, stage_failed)
                self.store.record_score(
                    candidate_id=candidate_id,
                    run_id=run_id,
                    total_score=scoring_payload["total_score"],
                    breakdown=scoring_payload["breakdown"],
                    metrics=scoring_payload["metrics"],
                    created_at=utc_now(),
                )
                self.store.upsert_run_stage(
                    run_id=run_id,
                    candidate_id=candidate_id,
                    stage_name=SCORING_STAGE_NAME,
                    stage_order=STAGE_ORDER[SCORING_STAGE_NAME],
                    status="passed",
                    owner_token=owner_token,
                    started_at=scoring_started_at,
                    ended_at=utc_now(),
                    details={"event": "scored", "total_score": scoring_payload["total_score"]},
                )
                self.store.transition_state(
                    candidate_id=candidate_id,
                    run_id=run_id,
                    stage=SCORING_STAGE_NAME,
                    from_state=current_state,
                    to_state=SCORED,
                    details={"event": "scored", "total_score": scoring_payload["total_score"]},
                    transitioned_at=utc_now(),
                )
                current_state = SCORED
        elif not stage_failed:
            final_status = "partial"

        if stage_failed and scoring_payload is None:
            # Preserve v1 behavior: even failed runs get a score entry when possible.
            scoring_payload = self._score_run(stage_outputs, stage_failed)
            self.store.record_score(
                candidate_id=candidate_id,
                run_id=run_id,
                total_score=scoring_payload["total_score"],
                breakdown=scoring_payload["breakdown"],
                metrics=scoring_payload["metrics"],
                created_at=utc_now(),
            )

        self.store.complete_run(run_id, final_status, utc_now())
        run_stages = [dict(row) for row in self.store.list_run_stages(run_id)]
        return {
            "candidate_id": candidate_id,
            "run_id": run_id,
            "attempt_index": attempt_index,
            "owner_token": owner_token,
            "run_dir": str(run_dir),
            "requested_start_stage": resolved_start_stage,
            "requested_end_stage": resolved_end_stage,
            "current_state": current_state,
            "stage_failed": stage_failed,
            "executed_stages": executed_stage_names,
            "run_stages": run_stages,
            "score": scoring_payload,
        }

    def run_pending(self, limit: int) -> list[dict[str, Any]]:
        self.store.init_db()
        rows = self.store.list_pending_candidates(limit)
        return [self.run_candidate(row["candidate_id"]) for row in rows]

    def get_status(self, candidate_id: str, *, include_lineage: bool = False, include_runs: bool = False) -> dict[str, Any]:
        self.store.init_db()
        candidate = self.store.get_candidate(candidate_id)
        if candidate is None:
            raise ValidationError(f"Candidate {candidate_id!r} is not registered")
        run = self.store.latest_run(candidate_id)
        history = self.store.state_history(candidate_id)
        score = self.store.latest_score(candidate_id)
        result: dict[str, Any] = {
            "candidate": dict(candidate),
            "latest_run": dict(run) if run else None,
            "state_history": [dict(row) for row in history],
            "latest_score": dict(score) if score else None,
        }
        if run is not None:
            result["latest_run_stages"] = [dict(row) for row in self.store.list_run_stages(run["run_id"])]
        if include_lineage:
            parent = None
            if candidate["parent_candidate_id"] is not None:
                parent_row = self.store.get_candidate(candidate["parent_candidate_id"])
                parent = dict(parent_row) if parent_row else None
            children = [dict(row) for row in self.store.list_children(candidate_id)]
            result["lineage"] = {
                "parent": parent,
                "lineage_root_candidate_id": candidate["lineage_root_candidate_id"],
                "revision_kind": candidate["revision_kind"],
                "derived_from_run_id": candidate["derived_from_run_id"],
                "supersedes_candidate_id": candidate["supersedes_candidate_id"],
                "children": children,
            }
        if include_runs:
            runs = [dict(row) for row in self.store.list_runs(candidate_id)]
            for run_row in runs:
                run_row["run_stages"] = [dict(stage) for stage in self.store.list_run_stages(run_row["run_id"])]
            result["runs"] = runs
        return result

    def list_candidates(
        self,
        *,
        parent_candidate_id: str | None = None,
        lineage_root_candidate_id: str | None = None,
        leaf_only: bool = False,
    ) -> list[dict[str, Any]]:
        self.store.init_db()
        return [
            dict(row)
            for row in self.store.list_candidates(
                parent_candidate_id=parent_candidate_id,
                lineage_root_candidate_id=lineage_root_candidate_id,
                leaf_only=leaf_only,
            )
        ]

    def compute_candidate_score(self, candidate_id: str, run_dir: Path | None = None) -> dict[str, Any]:
        self.store.init_db()
        candidate = self.store.get_candidate(candidate_id)
        if candidate is None:
            raise ValidationError(f"Candidate {candidate_id!r} is not registered")

        resolved_run_dir = run_dir
        if resolved_run_dir is None:
            latest_run = self.store.latest_run(candidate_id)
            if latest_run is None:
                raise ValidationError(f"Candidate {candidate_id!r} has no recorded runs")
            resolved_run_dir = Path(latest_run["run_dir"])

        vivado_result_path = resolved_run_dir / "vivado" / "vivado_result.json"
        perf_result_path = resolved_run_dir / "verilator_perf" / "verilator_result.json"
        vivado_payload = load_json(vivado_result_path) if vivado_result_path.exists() else {}
        perf_payload = load_json(perf_result_path) if perf_result_path.exists() else {}

        stage_failed = any(
            payload and payload.get("status") != "passed"
            for payload in (vivado_payload, perf_payload)
        )
        score = score_candidate(
            self.score_weights,
            vivado_payload.get("metrics"),
            perf_payload.get("metrics"),
            stage_failed=stage_failed,
        )
        return {
            "candidate_id": candidate_id,
            "run_dir": str(resolved_run_dir),
            "vivado_result_path": str(vivado_result_path) if vivado_result_path.exists() else None,
            "perf_result_path": str(perf_result_path) if perf_result_path.exists() else None,
            "stage_failed": stage_failed,
            "score": score,
        }

    def rank_candidates(
        self,
        *,
        markdown_out: Path | None = None,
        lineage_root_candidate_id: str | None = None,
        latest_only_per_root: bool = False,
        leaf_only: bool = False,
    ) -> dict[str, Any]:
        self.store.init_db()
        candidates = [
            dict(row)
            for row in self.store.list_candidates(
                lineage_root_candidate_id=lineage_root_candidate_id,
                leaf_only=leaf_only,
            )
        ]
        if latest_only_per_root:
            candidates = list(self._latest_candidate_per_root(candidates).values())

        ranked: list[dict[str, Any]] = []
        disqualified: list[dict[str, Any]] = []

        for candidate in candidates:
            candidate_id = candidate["candidate_id"]
            latest_run = self.store.latest_run(candidate_id)
            if latest_run is None:
                disqualified.append(
                    {
                        "candidate_id": candidate_id,
                        "current_state": candidate["current_state"],
                        "parent_candidate_id": candidate["parent_candidate_id"],
                        "lineage_root_candidate_id": candidate["lineage_root_candidate_id"],
                        "revision_kind": candidate["revision_kind"],
                        "reason": "No recorded runs are available.",
                    }
                )
                continue

            run_dir = Path(latest_run["run_dir"])
            vivado_result_path = run_dir / "vivado" / "vivado_result.json"
            perf_result_path = run_dir / "verilator_perf" / "verilator_result.json"
            vivado_payload = load_json(vivado_result_path) if vivado_result_path.exists() else {}
            perf_payload = load_json(perf_result_path) if perf_result_path.exists() else {}
            vivado_metrics = vivado_payload.get("metrics")
            perf_metrics = perf_payload.get("metrics")

            if not vivado_metrics or not perf_metrics:
                missing_inputs: list[str] = []
                if not vivado_metrics:
                    missing_inputs.append("implementation_metrics")
                if not perf_metrics:
                    missing_inputs.append("performance_metrics")
                disqualified.append(
                    {
                        "candidate_id": candidate_id,
                        "current_state": candidate["current_state"],
                        "parent_candidate_id": candidate["parent_candidate_id"],
                        "lineage_root_candidate_id": candidate["lineage_root_candidate_id"],
                        "revision_kind": candidate["revision_kind"],
                        "run_dir": str(run_dir),
                        "reason": "Missing measured artifacts required for ranking.",
                        "missing_inputs": missing_inputs,
                        "vivado_result_path": str(vivado_result_path) if vivado_result_path.exists() else None,
                        "perf_result_path": str(perf_result_path) if perf_result_path.exists() else None,
                    }
                )
                continue

            stage_failed = any(
                payload and payload.get("status") != "passed"
                for payload in (vivado_payload, perf_payload)
            )
            score = score_candidate(self.score_weights, vivado_metrics, perf_metrics, stage_failed=stage_failed)
            wns_value = score["metrics"].get("wns_ns")
            timing_status = "timing_unknown"
            if isinstance(wns_value, (int, float)):
                timing_status = "timing_clean" if float(wns_value) >= 0.0 else "timing_failed"

            ranked.append(
                {
                    "candidate_id": candidate_id,
                    "current_state": candidate["current_state"],
                    "parent_candidate_id": candidate["parent_candidate_id"],
                    "lineage_root_candidate_id": candidate["lineage_root_candidate_id"],
                    "revision_kind": candidate["revision_kind"],
                    "run_dir": str(run_dir),
                    "run_id": latest_run["run_id"],
                    "attempt_index": latest_run["attempt_index"],
                    "vivado_result_path": str(vivado_result_path),
                    "perf_result_path": str(perf_result_path),
                    "timing_status": timing_status,
                    "stage_failed": stage_failed,
                    "score": score,
                }
            )

        ranked.sort(key=lambda item: item["score"]["total_score"], reverse=True)
        for index, item in enumerate(ranked, start=1):
            item["rank"] = index

        best_numeric_score = ranked[0]["candidate_id"] if ranked else None
        best_timing_clean = next(
            (item["candidate_id"] for item in ranked if item["timing_status"] == "timing_clean"),
            None,
        )

        report = {
            "generated_at": utc_now(),
            "score_weights_path": str(DEFAULT_SCORE_WEIGHTS_PATH),
            "current_best_candidates": self.get_best_candidates(),
            "filters": {
                "lineage_root_candidate_id": lineage_root_candidate_id,
                "latest_only_per_root": latest_only_per_root,
                "leaf_only": leaf_only,
            },
            "best_under_numeric_score": best_numeric_score,
            "best_timing_clean": best_timing_clean,
            "ranked_candidates": ranked,
            "disqualified_candidates": disqualified,
            "markdown_report_path": None,
        }

        if markdown_out is not None:
            markdown_out.parent.mkdir(parents=True, exist_ok=True)
            markdown_out.write_text(self._render_ranking_markdown(report))
            report["markdown_report_path"] = str(markdown_out)

        return report

    def link_lineage(
        self,
        *,
        parent_candidate_id: str,
        child_candidate_id: str,
        revision_kind: str,
        derived_from_run_id: int | None = None,
    ) -> dict[str, Any]:
        self.store.init_db()
        if self.store.get_candidate(parent_candidate_id) is None:
            raise ValidationError(f"Parent candidate {parent_candidate_id!r} is not registered")
        if self.store.get_candidate(child_candidate_id) is None:
            raise ValidationError(f"Child candidate {child_candidate_id!r} is not registered")
        if derived_from_run_id is not None and self.store.get_run(derived_from_run_id) is None:
            raise ValidationError(f"Derived-from run {derived_from_run_id!r} does not exist")

        self.store.link_lineage(
            parent_candidate_id=parent_candidate_id,
            child_candidate_id=child_candidate_id,
            revision_kind=revision_kind,
            derived_from_run_id=derived_from_run_id,
        )
        return {
            "parent_candidate_id": parent_candidate_id,
            "child_candidate_id": child_candidate_id,
            "revision_kind": revision_kind,
            "derived_from_run_id": derived_from_run_id,
        }

    def set_best_candidates(
        self,
        best_numeric_score: str,
        best_timing_clean: str,
    ) -> dict[str, Any]:
        self.store.init_db()
        for candidate_id in (best_numeric_score, best_timing_clean):
            if self.store.get_candidate(candidate_id) is None:
                raise ValidationError(f"Candidate {candidate_id!r} is not registered")

        payload = {
            "updated_at": utc_now(),
            "best_numeric_score": {
                "candidate_id": best_numeric_score,
            },
            "best_timing_clean": {
                "candidate_id": best_timing_clean,
            },
        }
        VAR_DIR.mkdir(parents=True, exist_ok=True)
        BEST_CANDIDATES_PATH.write_text(json.dumps(payload, indent=2) + "\n")
        return payload

    def get_best_candidates(self) -> dict[str, Any]:
        if not BEST_CANDIDATES_PATH.exists():
            return {
                "updated_at": None,
                "best_numeric_score": None,
                "best_timing_clean": None,
                "note": "No best-candidate pointer has been recorded yet.",
            }
        return load_json(BEST_CANDIDATES_PATH)

    def _run_stage(self, stage_name: str, manifest_path: Path, run_dir: Path, result_relpath: str) -> StageResult:
        script_map = {
            "fast_verify": SCRIPTS_DIR / "fast_verify.sh",
            "vivado": SCRIPTS_DIR / "run_vivado_batch.sh",
            "verilator_perf": SCRIPTS_DIR / "collect_verilator_perf.sh",
        }
        script_path = script_map[stage_name]
        controller_log = run_dir / stage_name / "controller_command.log"
        command = [str(script_path), "--candidate-manifest", str(manifest_path), "--run-dir", str(run_dir)]
        completed = run_command(command, cwd=Path(script_path).parent.parent, log_path=controller_log)
        result_path = run_dir / result_relpath
        if not result_path.exists():
            payload = {
                "stage": stage_name,
                "status": "failed",
                "message": f"{stage_name} did not produce expected result file",
                "command": shell_join(command),
                "returncode": completed.returncode,
                "log_path": str(controller_log.relative_to(run_dir)),
            }
            result_path.parent.mkdir(parents=True, exist_ok=True)
            result_path.write_text(json.dumps(payload, indent=2) + "\n")
            return StageResult(stage=stage_name, passed=False, result_path=result_path, payload=payload)

        payload = load_json(result_path)
        if "controller_log_path" not in payload:
            payload["controller_log_path"] = str(controller_log.relative_to(run_dir))
            result_path.write_text(json.dumps(payload, indent=2) + "\n")
        return StageResult(
            stage=stage_name,
            passed=completed.returncode == 0 and payload.get("status") == "passed",
            result_path=result_path,
            payload=payload,
        )

    def _score_run(self, stage_outputs: dict[str, dict[str, Any]], stage_failed: bool) -> dict[str, Any]:
        vivado_metrics = stage_outputs.get("vivado", {}).get("metrics")
        perf_metrics = stage_outputs.get("verilator_perf", {}).get("metrics")
        return score_candidate(self.score_weights, vivado_metrics, perf_metrics, stage_failed=stage_failed)

    def _selected_stage_names(self, start_stage: str, end_stage: str) -> tuple[str, ...]:
        start_index = STAGE_ORDER[start_stage]
        end_index = STAGE_ORDER[end_stage]
        return tuple(stage_name for stage_name in ALL_STAGE_NAMES if start_index <= STAGE_ORDER[stage_name] <= end_index)

    def _latest_candidate_per_root(self, candidates: list[dict[str, Any]]) -> dict[str, dict[str, Any]]:
        latest: dict[str, dict[str, Any]] = {}
        for candidate in candidates:
            root_id = candidate["lineage_root_candidate_id"] or candidate["candidate_id"]
            previous = latest.get(root_id)
            if previous is None or (candidate["registered_at"], candidate["candidate_id"]) > (
                previous["registered_at"],
                previous["candidate_id"],
            ):
                latest[root_id] = candidate
        return latest

    def _render_ranking_markdown(self, report: dict[str, Any]) -> str:
        lines = [
            "# Candidate Ranking",
            "",
            f"Generated at: `{report['generated_at']}`",
            "",
            f"- Best under numeric score: `{report['best_under_numeric_score']}`",
            f"- Best timing-clean candidate: `{report['best_timing_clean']}`",
            "",
            "| Rank | Candidate | Timing | Score | Parent | Revision | WNS (ns) | Latency (cycles) | LUT | DSP |",
            "| --- | --- | --- | ---: | --- | --- | ---: | ---: | ---: | ---: |",
        ]

        for item in report["ranked_candidates"]:
            metrics = item["score"]["metrics"]
            lines.append(
                "| {rank} | `{candidate}` | {timing} | {score:.3f} | {parent} | {revision} | {wns} | {latency} | {lut} | {dsp} |".format(
                    rank=item["rank"],
                    candidate=item["candidate_id"],
                    timing=item["timing_status"],
                    score=item["score"]["total_score"],
                    parent=f"`{item['parent_candidate_id']}`" if item["parent_candidate_id"] else "N/A",
                    revision=item["revision_kind"] or "N/A",
                    wns=metrics.get("wns_ns", "N/A"),
                    latency=metrics.get("latency_cycles", "N/A"),
                    lut=metrics.get("lut", "N/A"),
                    dsp=metrics.get("dsp", "N/A"),
                )
            )

        if report["disqualified_candidates"]:
            lines.extend(
                [
                    "",
                    "## Disqualified",
                    "",
                    "| Candidate | Reason |",
                    "| --- | --- |",
                ]
            )
            for item in report["disqualified_candidates"]:
                lines.append(f"| `{item['candidate_id']}` | {item['reason']} |")

        lines.append("")
        return "\n".join(lines)
