import json
import tempfile
import unittest
from pathlib import Path

from rtl_agent_loop.config import load_search_space, validate_manifest
from rtl_agent_loop.optimizer import Optimizer


def make_manifest(candidate_id: str, *, parameters: dict[str, int] | None = None) -> dict[str, object]:
    return {
        "candidate_id": candidate_id,
        "source": "test",
        "created_at": "2026-04-18T00:00:00Z",
        "parameters": parameters
        or {
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
        "notes": "test candidate",
        "tags": ["mac-array", "test"],
    }


class FakeController:
    def __init__(self, base_dir: Path) -> None:
        self.base_dir = base_dir
        self.search_space = load_search_space()
        self.candidates: dict[str, dict[str, object]] = {}
        self.ranking_items: dict[str, dict[str, object]] = {}
        self.child_run_plans: list[dict[str, object]] = []
        self.best_updates: list[tuple[str, str]] = []
        self._time_counter = 0

    def utc_now(self) -> str:
        self._time_counter += 1
        return f"2026-04-18T00:00:{self._time_counter:02d}Z"

    def list_candidates(self, *, active_schema_only: bool = False, **_: object) -> list[dict[str, object]]:
        candidates = list(self.candidates.values())
        if active_schema_only:
            candidates = [item for item in candidates if item["active_schema_compatible"]]
        return sorted(candidates, key=lambda item: item["candidate_id"])

    def rank_candidates(self, *, active_schema_only: bool = False, **_: object) -> dict[str, object]:
        candidates = self.list_candidates(active_schema_only=active_schema_only)
        ranked = []
        for candidate in candidates:
            candidate_id = candidate["candidate_id"]
            item = self.ranking_items.get(candidate_id)
            if item is not None:
                ranked.append(dict(item))
        ranked.sort(key=lambda item: item["score"]["total_score"], reverse=True)
        for index, item in enumerate(ranked, start=1):
            item["rank"] = index
        best_numeric = ranked[0]["candidate_id"] if ranked else None
        best_timing = next((item["candidate_id"] for item in ranked if item["timing_status"] == "timing_clean"), None)
        return {
            "best_under_numeric_score": best_numeric,
            "best_timing_clean": best_timing,
            "ranked_candidates": ranked,
            "disqualified_candidates": [],
        }

    def register_candidate(
        self,
        manifest_path: Path,
        *,
        parent_candidate_id: str | None = None,
        revision_kind: str | None = None,
        **_: object,
    ) -> dict[str, object]:
        manifest = json.loads(manifest_path.read_text())
        candidate_id = manifest["candidate_id"]
        self.candidates[candidate_id] = self._candidate_view(
            manifest,
            parent_candidate_id=parent_candidate_id,
            revision_kind=revision_kind,
            manifest_path=manifest_path,
        )
        return {
            "candidate_id": candidate_id,
            "manifest_path": str(manifest_path),
            "candidate_dir": str(self.base_dir / "runs" / candidate_id),
        }

    def run_candidate(self, candidate_id: str, *, worktree_ref: str | None = None, **_: object) -> dict[str, object]:
        plan = self.child_run_plans.pop(0)
        run_dir = self.base_dir / "runs" / candidate_id / f"attempt_{plan['attempt_index']:04d}"
        run_dir.mkdir(parents=True, exist_ok=True)
        run_stages = []
        for stage_name, payload in plan["stage_payloads"].items():
            stage_dir = run_dir / stage_name
            stage_dir.mkdir(parents=True, exist_ok=True)
            result_path = stage_dir / f"{stage_name}.json"
            result_path.write_text(json.dumps(payload, indent=2) + "\n")
            run_stages.append(
                {
                    "stage_name": stage_name,
                    "status": "passed" if payload.get("passed") else "failed",
                    "result_path": str(result_path),
                }
            )
        ranking_item = plan.get("ranking_item")
        if ranking_item is not None:
            self.ranking_items[candidate_id] = dict(ranking_item)
        return {
            "candidate_id": candidate_id,
            "run_id": plan["run_id"],
            "attempt_index": plan["attempt_index"],
            "run_dir": str(run_dir),
            "current_state": plan.get("current_state", "scored"),
            "stage_failed": plan.get("stage_failed", False),
            "run_stages": run_stages,
            "score": plan.get("score"),
            "worktree_ref": worktree_ref,
        }

    def set_best_candidates(self, *, best_numeric_score: str, best_timing_clean: str) -> dict[str, object]:
        self.best_updates.append((best_numeric_score, best_timing_clean))
        return {
            "best_numeric_score": {"candidate_id": best_numeric_score},
            "best_timing_clean": {"candidate_id": best_timing_clean},
        }

    def _candidate_view(
        self,
        manifest: dict[str, object],
        *,
        parent_candidate_id: str | None = None,
        revision_kind: str | None = None,
        manifest_path: Path | None = None,
    ) -> dict[str, object]:
        return {
            "candidate_id": manifest["candidate_id"],
            "current_state": "registered",
            "manifest_json": json.dumps(manifest),
            "manifest_path": str(manifest_path or self.base_dir / "candidates" / f"{manifest['candidate_id']}.json"),
            "parent_candidate_id": parent_candidate_id,
            "lineage_root_candidate_id": parent_candidate_id or manifest["candidate_id"],
            "revision_kind": revision_kind,
            "registered_at": "2026-04-18T00:00:00Z",
            "manifest_parameter_family": "mac_array_v1",
            "active_schema_compatible": True,
        }


class OptimizerTests(unittest.TestCase):
    def setUp(self) -> None:
        self._tmp = tempfile.TemporaryDirectory()
        self.tmp_path = Path(self._tmp.name)
        self.candidates_dir = self.tmp_path / "candidates"
        self.optimize_dir = self.tmp_path / "var" / "optimize"
        self.candidates_dir.mkdir(parents=True, exist_ok=True)
        self.controller = FakeController(self.tmp_path)
        self.optimizer = Optimizer(
            self.controller,
            candidates_dir=self.candidates_dir,
            optimize_root=self.optimize_dir,
        )

    def tearDown(self) -> None:
        self._tmp.cleanup()

    def test_mutation_generation_stays_valid_and_skips_duplicate_parameter_sets(self) -> None:
        parent_manifest = make_manifest("mac_baseline_4x4_dw16")
        existing_params = dict(parent_manifest["parameters"])
        duplicate_params = dict(existing_params)
        duplicate_params["ARCH_VARIANT"] = 1
        duplicate_params["SHARE_FACTOR"] = 2

        proposals = self.optimizer._generate_mutations_for_parent(
            parent_manifest=parent_manifest,
            existing_parameter_sets={
                self.optimizer._parameter_key(existing_params): "mac_baseline_4x4_dw16",
                self.optimizer._parameter_key(duplicate_params): "existing_shared_variant",
            },
            existing_candidate_ids={"mac_baseline_4x4_dw16", "existing_shared_variant"},
            delta_exclusions={},
            limit=3,
        )

        self.assertTrue(proposals)
        for proposal in proposals:
            validate_manifest(proposal.manifest_data, proposal.manifest_path, self.controller.search_space)
            self.assertNotEqual(
                self.optimizer._parameter_key(proposal.manifest_data["parameters"]),
                self.optimizer._parameter_key(duplicate_params),
            )
            self.assertTrue(proposal.candidate_id.startswith("mac_baseline_4x4_dw16_opt_"))

    def test_arch_variant_mutation_allows_dependent_share_factor_repair(self) -> None:
        parent_manifest = make_manifest("mac_baseline_4x4_dw16")

        proposals = self.optimizer._generate_mutations_for_parent(
            parent_manifest=parent_manifest,
            existing_parameter_sets={
                self.optimizer._parameter_key(parent_manifest["parameters"]): "mac_baseline_4x4_dw16",
            },
            existing_candidate_ids={"mac_baseline_4x4_dw16"},
            delta_exclusions={},
            limit=4,
        )

        shared_variant = next(
            (
                proposal
                for proposal in proposals
                if proposal.manifest_data["parameters"]["ARCH_VARIANT"] == 1
            ),
            None,
        )
        self.assertIsNotNone(shared_variant)
        self.assertEqual(shared_variant.manifest_data["parameters"]["SHARE_FACTOR"], 2)
        self.assertEqual(
            shared_variant.delta_key,
            "ARCH_VARIANT:0->1|SHARE_FACTOR:1->2",
        )

    def test_optimize_persists_state_generates_manifest_and_updates_best_candidate(self) -> None:
        seed_manifest = make_manifest("mac_baseline_4x4_dw16")
        seed_path = self.candidates_dir / "mac_baseline_4x4_dw16.json"
        seed_path.write_text(json.dumps(seed_manifest, indent=2) + "\n")
        self.controller.candidates["mac_baseline_4x4_dw16"] = self.controller._candidate_view(seed_manifest, manifest_path=seed_path)
        self.controller.ranking_items["mac_baseline_4x4_dw16"] = self._ranking_item(
            "mac_baseline_4x4_dw16",
            total_score=-20.0,
            latency_cycles=24.0,
            lut=1000.0,
            wns_ns=1.0,
        )

        child_candidate_id = "mac_baseline_4x4_dw16_opt_arch_variant_1"
        child_ranking_item = self._ranking_item(
            child_candidate_id,
            total_score=-10.0,
            latency_cycles=20.0,
            lut=900.0,
            wns_ns=1.2,
        )
        self.controller.child_run_plans.append(
            {
                "run_id": 11,
                "attempt_index": 1,
                "stage_failed": False,
                "score": child_ranking_item["score"],
                "stage_payloads": {
                    "fast_verify": {"passed": True, "outcome_classification": "full_pass", "message": "ok"},
                    "vivado": {"passed": True, "outcome_classification": "full_pass", "message": "ok"},
                    "verilator_perf": {"passed": True, "outcome_classification": "full_pass", "message": "ok"},
                },
                "ranking_item": child_ranking_item,
            }
        )

        summary = self.optimizer.optimize(
            iterations=1,
            seed_candidate_ids=["mac_baseline_4x4_dw16"],
            top_k=1,
            mutations_per_parent=1,
            worktree_ref="unittest",
            active_schema_only=True,
        )

        session_dir = self.optimize_dir / summary["session_id"]
        self.assertTrue((session_dir / "search_state.json").exists())
        self.assertTrue((session_dir / "summary.json").exists())
        self.assertTrue((session_dir / "summary.md").exists())
        search_state = json.loads((session_dir / "search_state.json").read_text())
        generated_child_id = search_state["iterations"][0]["generated_children"][0]["candidate_id"]
        self.assertEqual(summary["best_candidate"]["candidate_id"], child_candidate_id)
        self.assertEqual(self.controller.best_updates[-1], (child_candidate_id, child_candidate_id))
        child_manifest_path = self.candidates_dir / f"{generated_child_id}.json"
        self.assertTrue(child_manifest_path.exists())
        child_manifest = json.loads(child_manifest_path.read_text())
        self.assertEqual(generated_child_id, child_manifest["candidate_id"])
        self.assertIn("Optimize v1 child derived from mac_baseline_4x4_dw16", child_manifest["notes"])
        self.assertIn("optimize_v1", child_manifest["tags"])

    def test_failure_classification_covers_closed_loop_categories(self) -> None:
        parent_rank_item = self._ranking_item("parent", total_score=-5.0, latency_cycles=20.0, lut=800.0, wns_ns=1.0)

        self.assertEqual(
            self.optimizer._classify_candidate_result(parent_rank_item=parent_rank_item, run_result={}, child_score=None)["failure_class"],
            "schema_invalid",
        )
        self.assertEqual(
            self.optimizer._classify_candidate_result(
                parent_rank_item=parent_rank_item,
                run_result=self._run_result_with_payloads(
                    {
                        "fast_verify": {"passed": False, "outcome_classification": "failed_tool", "message": "lint failed"},
                    }
                ),
                child_score=None,
            )["failure_class"],
            "verification_fail",
        )
        self.assertEqual(
            self.optimizer._classify_candidate_result(
                parent_rank_item=parent_rank_item,
                run_result=self._run_result_with_payloads(
                    {
                        "fast_verify": {"passed": True, "outcome_classification": "full_pass", "message": "ok"},
                        "vivado": {"passed": False, "outcome_classification": "synth_only", "message": "synthesis metrics only"},
                    }
                ),
                child_score=self._ranking_item("child", total_score=-4.0, latency_cycles=21.0, lut=900.0, wns_ns=0.5)["score"],
            )["failure_class"],
            "synth_only_measurement",
        )
        self.assertEqual(
            self.optimizer._classify_candidate_result(
                parent_rank_item=parent_rank_item,
                run_result=self._run_result_with_payloads(
                    {
                        "fast_verify": {"passed": True, "outcome_classification": "full_pass", "message": "ok"},
                        "vivado": {"passed": False, "outcome_classification": "failed_tool", "message": "device resources exceeded"},
                    }
                ),
                child_score=None,
            )["failure_class"],
            "resource_exceeded",
        )
        self.assertEqual(
            self.optimizer._classify_candidate_result(
                parent_rank_item=parent_rank_item,
                run_result=self._run_result_with_payloads(
                    {
                        "fast_verify": {"passed": True, "outcome_classification": "full_pass", "message": "ok"},
                        "vivado": {"passed": False, "outcome_classification": "failed_tool", "message": "implementation route failed"},
                    }
                ),
                child_score=None,
            )["failure_class"],
            "route_fail",
        )
        self.assertEqual(
            self.optimizer._classify_candidate_result(
                parent_rank_item=parent_rank_item,
                run_result=self._run_result_with_payloads(
                    {
                        "fast_verify": {"passed": True, "outcome_classification": "full_pass", "message": "ok"},
                        "vivado": {"passed": False, "outcome_classification": "failed_tool", "message": "synth crashed"},
                    }
                ),
                child_score=None,
            )["failure_class"],
            "synth_fail",
        )
        self.assertEqual(
            self.optimizer._classify_candidate_result(
                parent_rank_item=parent_rank_item,
                run_result=self._run_result_with_payloads(
                    {
                        "fast_verify": {"passed": True, "outcome_classification": "full_pass", "message": "ok"},
                        "vivado": {"passed": True, "outcome_classification": "full_pass", "message": "ok"},
                        "verilator_perf": {"passed": True, "outcome_classification": "full_pass", "message": "ok"},
                    }
                ),
                child_score=self._ranking_item("child", total_score=-4.0, latency_cycles=20.0, lut=900.0, wns_ns=-0.2)["score"],
            )["failure_class"],
            "timing_fail",
        )
        self.assertEqual(
            self.optimizer._classify_candidate_result(
                parent_rank_item=parent_rank_item,
                run_result=self._run_result_with_payloads(
                    {
                        "fast_verify": {"passed": True, "outcome_classification": "full_pass", "message": "ok"},
                        "vivado": {"passed": True, "outcome_classification": "full_pass", "message": "ok"},
                        "verilator_perf": {"passed": True, "outcome_classification": "full_pass", "message": "ok"},
                    }
                ),
                child_score=self._ranking_item("child", total_score=-6.0, latency_cycles=25.0, lut=850.0, wns_ns=1.0)["score"],
            )["failure_class"],
            "perf_regressed",
        )

    def test_optimize_bootstraps_from_seed_pool_when_no_ranked_candidates_exist(self) -> None:
        seed_manifest = make_manifest("mac_baseline_4x4_dw16")
        seed_path = self.candidates_dir / "mac_baseline_4x4_dw16.json"
        seed_path.write_text(json.dumps(seed_manifest, indent=2) + "\n")
        self.controller.candidates["mac_baseline_4x4_dw16"] = self.controller._candidate_view(seed_manifest, manifest_path=seed_path)
        self.controller.child_run_plans.extend(
            [
                {
                    "run_id": 1,
                    "attempt_index": 1,
                    "stage_failed": True,
                    "score": None,
                    "stage_payloads": {
                        "fast_verify": {"passed": False, "outcome_classification": "failed_tool", "message": "lint failed"},
                    },
                },
                {
                    "run_id": 2,
                    "attempt_index": 1,
                    "stage_failed": True,
                    "score": None,
                    "stage_payloads": {
                        "fast_verify": {"passed": False, "outcome_classification": "failed_tool", "message": "lint failed"},
                    },
                },
            ]
        )

        summary = self.optimizer.optimize(
            iterations=1,
            seed_candidate_ids=["mac_baseline_4x4_dw16"],
            top_k=1,
            mutations_per_parent=1,
            worktree_ref="bootstrap",
            active_schema_only=True,
        )

        self.assertEqual(summary["iteration_history"][0]["selected_parent_ids"], ["mac_baseline_4x4_dw16"])
        self.assertEqual(summary["iteration_history"][0]["parent_selection_strategy"], "seed_pool_fallback")
        self.assertEqual(len(summary["iteration_history"][0]["generated_children"]), 1)

    def _ranking_item(
        self,
        candidate_id: str,
        *,
        total_score: float,
        latency_cycles: float,
        lut: float,
        wns_ns: float,
    ) -> dict[str, object]:
        return {
            "candidate_id": candidate_id,
            "timing_status": "timing_clean" if wns_ns >= 0.0 else "timing_failed",
            "measurement_quality": "full",
            "implementation_evidence": "full_implementation",
            "score": {
                "total_score": total_score,
                "metrics": {
                    "latency_cycles": latency_cycles,
                    "lut": lut,
                    "dsp": 8.0,
                    "wns_ns": wns_ns,
                },
            },
        }

    def _run_result_with_payloads(self, payloads: dict[str, dict[str, object]]) -> dict[str, object]:
        run_dir = self.tmp_path / "classify"
        run_dir.mkdir(parents=True, exist_ok=True)
        run_stages = []
        for stage_name, payload in payloads.items():
            stage_dir = run_dir / stage_name
            stage_dir.mkdir(parents=True, exist_ok=True)
            result_path = stage_dir / f"{stage_name}.json"
            result_path.write_text(json.dumps(payload, indent=2) + "\n")
            run_stages.append(
                {
                    "stage_name": stage_name,
                    "status": "passed" if payload.get("passed") else "failed",
                    "result_path": str(result_path),
                }
            )
        return {
            "candidate_id": "child",
            "run_id": 99,
            "attempt_index": 1,
            "run_stages": run_stages,
        }


if __name__ == "__main__":
    unittest.main()
