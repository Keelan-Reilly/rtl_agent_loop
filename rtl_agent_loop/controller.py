from __future__ import annotations

import json
from dataclasses import asdict
from datetime import datetime, timezone
from pathlib import Path
from typing import Any

from .config import ValidationError, load_json, load_score_weights, load_search_space, validate_manifest
from .models import CandidateManifest, StageResult
from .paths import RUNS_DIR, SCRIPTS_DIR
from .scoring import score_candidate
from .sqlite_store import SQLiteStore
from .state_machine import REGISTERED, SCORED, STAGES
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

    def register_candidate(self, manifest_path: Path) -> dict[str, Any]:
        manifest_data = load_json(manifest_path)
        manifest = validate_manifest(manifest_data, manifest_path.resolve(), self.search_space)
        self.store.init_db()
        if self.store.candidate_exists(manifest.candidate_id):
            raise ValidationError(f"Candidate {manifest.candidate_id!r} is already registered")

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
        self.store.register_candidate(manifest, candidate_root, utc_now())
        return {
            "candidate_id": manifest.candidate_id,
            "current_state": REGISTERED,
            "manifest_path": str(stored_manifest_path),
            "candidate_dir": str(candidate_root),
        }

    def run_candidate(self, candidate_id: str) -> dict[str, Any]:
        self.store.init_db()
        candidate = self.store.get_candidate(candidate_id)
        if candidate is None:
            raise ValidationError(f"Candidate {candidate_id!r} is not registered")
        if candidate["current_state"] == SCORED:
            raise ValidationError(
                f"Candidate {candidate_id!r} is already scored; v1 blocks reruns to keep behavior explicit"
            )

        attempt_index = self.store.next_attempt_index(candidate_id)
        run_dir = Path(candidate["candidate_dir"]) / f"attempt_{attempt_index:04d}"
        run_dir.mkdir(parents=True, exist_ok=True)
        run_id = self.store.create_run(candidate_id, attempt_index, utc_now(), run_dir)

        manifest_path = Path(candidate["manifest_path"])
        current_state = candidate["current_state"]
        stage_outputs: dict[str, dict[str, Any]] = {}
        final_status = "scored"
        stage_failed = False

        for stage in STAGES:
            self.store.transition_state(
                candidate_id=candidate_id,
                run_id=run_id,
                stage=stage.name,
                from_state=current_state,
                to_state=stage.pending_state,
                details={"event": "stage_pending", "run_dir": str(run_dir)},
                transitioned_at=utc_now(),
            )
            current_state = stage.pending_state

            result = self._run_stage(stage.name, manifest_path, run_dir, stage.result_relpath)
            stage_outputs[stage.name] = result.payload
            self.store.record_artifact(
                candidate_id=candidate_id,
                run_id=run_id,
                stage=stage.name,
                artifact_type="stage_result",
                path=str(result.result_path),
                metadata={"passed": result.passed},
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
                    metadata={},
                    recorded_at=utc_now(),
                )

            next_state = stage.success_state if result.passed else stage.failure_state
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
                break

        scoring = self._score_run(stage_outputs, stage_failed)
        self.store.record_score(
            candidate_id=candidate_id,
            run_id=run_id,
            total_score=scoring["total_score"],
            breakdown=scoring["breakdown"],
            metrics=scoring["metrics"],
            created_at=utc_now(),
        )

        if not stage_failed:
            self.store.transition_state(
                candidate_id=candidate_id,
                run_id=run_id,
                stage="scoring",
                from_state=current_state,
                to_state=SCORED,
                details={
                    "event": "scored",
                    "total_score": scoring["total_score"],
                },
                transitioned_at=utc_now(),
            )
            current_state = SCORED

        self.store.complete_run(run_id, final_status, utc_now())
        return {
            "candidate_id": candidate_id,
            "run_id": run_id,
            "attempt_index": attempt_index,
            "run_dir": str(run_dir),
            "current_state": current_state,
            "stage_failed": stage_failed,
            "score": scoring,
        }

    def run_pending(self, limit: int) -> list[dict[str, Any]]:
        self.store.init_db()
        rows = self.store.list_pending_candidates(limit)
        results = []
        for row in rows:
            results.append(self.run_candidate(row["candidate_id"]))
        return results

    def get_status(self, candidate_id: str) -> dict[str, Any]:
        self.store.init_db()
        candidate = self.store.get_candidate(candidate_id)
        if candidate is None:
            raise ValidationError(f"Candidate {candidate_id!r} is not registered")
        run = self.store.latest_run(candidate_id)
        history = self.store.state_history(candidate_id)
        score = self.store.latest_score(candidate_id)
        return {
            "candidate": dict(candidate),
            "latest_run": dict(run) if run else None,
            "state_history": [dict(row) for row in history],
            "latest_score": dict(score) if score else None,
        }

    def list_candidates(self) -> list[dict[str, Any]]:
        self.store.init_db()
        return [dict(row) for row in self.store.list_candidates()]

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

