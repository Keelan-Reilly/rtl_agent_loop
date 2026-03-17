import json
import tempfile
import unittest
from pathlib import Path

from rtl_agent_loop.controller import Controller
from rtl_agent_loop.models import CandidateManifest
from rtl_agent_loop.sqlite_store import SQLiteStore


class ControllerResolutionTests(unittest.TestCase):
    def setUp(self) -> None:
        self._tmp = tempfile.TemporaryDirectory()
        self.tmp_path = Path(self._tmp.name)
        self.store = SQLiteStore(self.tmp_path / "test.db")
        self.store.init_db()
        self.controller = Controller(store=self.store)
        self.candidate_id = "mac_test_candidate"
        self._register_candidate(self.candidate_id)

    def tearDown(self) -> None:
        self._tmp.cleanup()

    def test_latest_full_pass_artifacts_resolve_as_full(self) -> None:
        self._create_stage_run(self.candidate_id, "vivado", self._vivado_payload("full_pass", lut=1000, wns_ns=1.5))
        self._create_stage_run(self.candidate_id, "verilator_perf", self._perf_payload(latency_cycles=24))

        resolved = self.controller._resolve_candidate_stage_artifacts(self.candidate_id)

        self.assertEqual(resolved["measurement_quality"], "full")
        self.assertEqual(resolved["implementation_evidence"], "full_implementation")
        self.assertFalse(resolved["score_provisional"])
        self.assertFalse(resolved["stage_failed"])
        self.assertEqual(resolved["sources"]["vivado"]["outcome_classification"], "full_pass")
        self.assertEqual(resolved["score"]["metrics"]["lut"], 1000.0)

    def test_latest_synth_only_vivado_is_used_and_marked_provisional(self) -> None:
        self._create_stage_run(self.candidate_id, "vivado", self._vivado_payload("synth_only", lut=1200, wns_ns=0.2))
        self._create_stage_run(self.candidate_id, "verilator_perf", self._perf_payload(latency_cycles=24))

        ranking = self.controller.rank_candidates()
        self.assertEqual(len(ranking["ranked_candidates"]), 1)
        item = ranking["ranked_candidates"][0]

        self.assertEqual(item["measurement_quality"], "provisional_synth_only")
        self.assertEqual(item["implementation_evidence"], "synth_only")
        self.assertTrue(item["score_provisional"])
        self.assertTrue(item["stage_failed"])
        self.assertIn("synth-only", item["artifact_provenance_note"])
        self.assertEqual(item["artifact_sources"]["vivado"]["outcome_classification"], "synth_only")

    def test_newer_failed_junk_does_not_override_older_full_pass_vivado(self) -> None:
        older_run = self._create_stage_run(
            self.candidate_id,
            "vivado",
            self._vivado_payload("full_pass", lut=1300, wns_ns=1.0),
        )
        self._create_stage_run(
            self.candidate_id,
            "vivado",
            {"status": "failed", "passed": False, "outcome_classification": "failed_tool", "message": "tool failed"},
        )
        self._create_stage_run(self.candidate_id, "verilator_perf", self._perf_payload(latency_cycles=26))

        status = self.controller.get_status(self.candidate_id)
        summary = status["resolved_artifact_summary"]

        self.assertEqual(summary["measurement_quality"], "full")
        self.assertEqual(summary["sources"]["vivado"]["run_id"], older_run["run_id"])
        self.assertIn("uses older run", summary["artifact_provenance_note"])

    def test_newer_synth_only_is_preferred_over_older_full_implementation(self) -> None:
        older_run = self._create_stage_run(
            self.candidate_id,
            "vivado",
            self._vivado_payload("full_pass", lut=900, wns_ns=1.8),
        )
        newer_run = self._create_stage_run(
            self.candidate_id,
            "vivado",
            self._vivado_payload("synth_only", lut=2100, wns_ns=-0.4),
        )
        self._create_stage_run(self.candidate_id, "verilator_perf", self._perf_payload(latency_cycles=30))

        resolved = self.controller._resolve_candidate_stage_artifacts(self.candidate_id)

        self.assertEqual(resolved["sources"]["vivado"]["run_id"], newer_run["run_id"])
        self.assertNotEqual(resolved["sources"]["vivado"]["run_id"], older_run["run_id"])
        self.assertEqual(resolved["measurement_quality"], "provisional_synth_only")
        self.assertEqual(resolved["implementation_evidence"], "synth_only")
        self.assertTrue(resolved["score_provisional"])

    def test_backward_compatible_minimal_payloads_still_score(self) -> None:
        self._create_stage_run(
            self.candidate_id,
            "vivado",
            {
                "status": "passed",
                "metrics": {
                    "utilization": {"lut": 500, "ff": 600, "dsp": 8, "bram": 0},
                    "timing": {"wns_ns": 0.8, "fmax_mhz_est": 120.0},
                },
            },
        )
        self._create_stage_run(
            self.candidate_id,
            "verilator_perf",
            {
                "status": "passed",
                "metrics": {
                    "latency_cycles": 32,
                    "latency_time_ms": 0.00032,
                    "throughput_inferences_per_sec": 12345.0,
                },
            },
        )

        score = self.controller.compute_candidate_score(self.candidate_id)

        self.assertEqual(score["score"]["metrics"]["lut"], 500.0)
        self.assertEqual(score["score"]["metrics"]["throughput_ops_per_sec"], 12345.0)

    def test_stage_payload_schema_classification_helpers(self) -> None:
        self.assertTrue(
            self.controller._is_stage_payload_full_pass(
                "vivado", self._vivado_payload("full_pass", lut=10, wns_ns=1.0)
            )
        )
        self.assertFalse(
            self.controller._is_stage_payload_full_pass(
                "vivado", self._vivado_payload("synth_only", lut=10, wns_ns=1.0)
            )
        )
        self.assertTrue(
            self.controller._is_stage_payload_measurement_usable(
                "vivado", self._vivado_payload("synth_only", lut=10, wns_ns=1.0)
            )
        )
        self.assertFalse(
            self.controller._is_stage_payload_measurement_usable(
                "verilator_perf",
                {
                    "status": "failed",
                    "passed": False,
                    "outcome_classification": "failed_tool",
                    "metrics": {"latency_cycles": 99},
                },
            )
        )
        self.assertEqual(
            self.controller._classify_stage_payload(
                "fast_verify",
                {"status": "failed", "passed": False, "outcome_classification": "failed_preflight"},
            ),
            "failed_preflight",
        )
        self.assertEqual(
            self.controller._classify_stage_payload("verilator_perf", {"status": "failed"}),
            "failed_tool",
        )

    def _register_candidate(self, candidate_id: str) -> None:
        candidate_dir = self.tmp_path / candidate_id
        candidate_dir.mkdir(parents=True, exist_ok=True)
        manifest_path = candidate_dir / "candidate_manifest.json"
        raw = {
            "candidate_id": candidate_id,
            "source": "test",
            "created_at": "2026-03-17T00:00:00Z",
            "parameters": {
                "ARCH_VARIANT": 0,
                "ARRAY_M": 4,
                "ARRAY_N": 4,
                "CLUSTER_SIZE": 4,
                "SHARE_FACTOR": 1,
                "DATA_WIDTH": 16,
                "FRAC_BITS": 8,
                "ACC_WIDTH": 32,
                "PIPE_STAGES": 1,
                "TILE_K": 4,
                "INPUT_MEM_DEPTH": 64,
                "OUTPUT_MEM_DEPTH": 64,
            },
            "notes": "test",
            "tags": ["test"],
        }
        manifest_path.write_text(json.dumps(raw, indent=2) + "\n")
        manifest = CandidateManifest(
            candidate_id=candidate_id,
            source="test",
            created_at="2026-03-17T00:00:00Z",
            parameters=dict(raw["parameters"]),
            notes="test",
            tags=["test"],
            manifest_path=manifest_path,
            raw=raw,
        )
        self.store.register_candidate(
            manifest,
            candidate_dir,
            "2026-03-17T00:00:00Z",
            lineage_root_candidate_id=candidate_id,
        )

    def _create_stage_run(self, candidate_id: str, stage_name: str, payload: dict[str, object]) -> dict[str, int]:
        run_id, attempt_index, owner_token, run_dir = self.store.create_run(
            candidate_id,
            f"2026-03-17T00:00:{10 + self.store.next_attempt_index(candidate_id):02d}Z",
            self.tmp_path / candidate_id,
            requested_start_stage=stage_name,
            requested_end_stage=stage_name,
            worktree_ref="test",
        )
        run_dir.mkdir(parents=True, exist_ok=True)
        stage_dir = run_dir / stage_name
        stage_dir.mkdir(parents=True, exist_ok=True)
        result_path = stage_dir / f"{stage_name}_result.json"
        payload = {"stage": stage_name, **payload}
        result_path.write_text(json.dumps(payload, indent=2) + "\n")
        stage_status = "passed" if payload.get("status") == "passed" else "failed"
        self.store.upsert_run_stage(
            run_id=run_id,
            candidate_id=candidate_id,
            stage_name=stage_name,
            stage_order=0,
            status=stage_status,
            owner_token=owner_token,
            started_at=f"2026-03-17T00:00:{attempt_index:02d}Z",
            ended_at=f"2026-03-17T00:01:{attempt_index:02d}Z",
            result_path=str(result_path),
            log_path=str(stage_dir / "stage.log"),
            details={"event": "stage_complete"},
        )
        self.store.complete_run(run_id, "completed", f"2026-03-17T00:02:{attempt_index:02d}Z")
        return {"run_id": run_id, "attempt_index": attempt_index}

    def _vivado_payload(self, outcome_classification: str, *, lut: int, wns_ns: float) -> dict[str, object]:
        passed = outcome_classification == "full_pass"
        return {
            "status": "passed" if passed else "failed",
            "passed": passed,
            "outcome_classification": outcome_classification,
            "metrics": {
                "lut": lut,
                "ff": lut // 2,
                "dsp": 8,
                "bram": 0,
                "wns_ns": wns_ns,
                "fmax_mhz_est": 100.0 + wns_ns,
            },
        }

    def _perf_payload(self, *, latency_cycles: int) -> dict[str, object]:
        return {
            "status": "passed",
            "passed": True,
            "outcome_classification": "full_pass",
            "metrics": {
                "latency_cycles": latency_cycles,
                "latency_time_ms": latency_cycles / 100000.0,
                "throughput_ops_per_sec": 1_000_000.0 / latency_cycles,
            },
        }


if __name__ == "__main__":
    unittest.main()
