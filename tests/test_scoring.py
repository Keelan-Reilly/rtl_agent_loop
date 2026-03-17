import json
import unittest

from rtl_agent_loop.paths import DEFAULT_SCORE_WEIGHTS_PATH
from rtl_agent_loop.scoring import flatten_metrics, score_candidate


class ScoringTests(unittest.TestCase):
    def test_flatten_metrics_supports_flat_vivado_payloads(self) -> None:
        flattened = flatten_metrics(
            {
                "lut": 689,
                "ff": 1068,
                "dsp": 16,
                "bram": 0,
                "wns_ns": 3.028,
                "fmax_mhz_est": 143.43,
            },
            None,
        )
        self.assertEqual(flattened["lut"], 689.0)
        self.assertEqual(flattened["ff"], 1068.0)
        self.assertEqual(flattened["dsp"], 16.0)
        self.assertEqual(flattened["wns_ns"], 3.028)

    def test_flatten_metrics_supports_throughput_ops(self) -> None:
        flattened = flatten_metrics(
            None,
            {
                "latency_cycles": 22,
                "latency_time_ms": 0.00022,
                "throughput_ops_per_sec": 290_909_090.9,
            },
        )
        self.assertEqual(flattened["latency_cycles"], 22.0)
        self.assertEqual(flattened["throughput_ops_per_sec"], 290_909_090.9)
        self.assertEqual(flattened["throughput_inferences_per_sec"], 290_909_090.9)

    def test_flatten_metrics_supports_nested_vivado_payloads(self) -> None:
        flattened = flatten_metrics(
            {
                "utilization": {"lut": 512, "ff": 1024, "dsp": 4, "bram": 1},
                "timing": {"wns_ns": 0.75, "fmax_mhz_est": 115.0},
            },
            None,
        )
        self.assertEqual(flattened["lut"], 512.0)
        self.assertEqual(flattened["ff"], 1024.0)
        self.assertEqual(flattened["wns_ns"], 0.75)

    def test_flatten_metrics_supports_legacy_throughput_name(self) -> None:
        flattened = flatten_metrics(
            None,
            {
                "latency_cycles": 18,
                "latency_time_ms": 0.00018,
                "throughput_inferences_per_sec": 42_000.0,
            },
        )
        self.assertEqual(flattened["throughput_ops_per_sec"], 42_000.0)
        self.assertEqual(flattened["throughput_inferences_per_sec"], 42_000.0)

    def test_score_candidate_applies_stage_failed_penalty_to_provisional_measurements(self) -> None:
        weights = json.loads(DEFAULT_SCORE_WEIGHTS_PATH.read_text())
        score = score_candidate(
            weights,
            {"lut": 100, "ff": 200, "dsp": 2, "bram": 0, "wns_ns": 0.5, "fmax_mhz_est": 101.0},
            {"latency_cycles": 20, "latency_time_ms": 0.0002, "throughput_ops_per_sec": 50_000.0},
            stage_failed=True,
        )
        self.assertIn("penalty:stage_failed", score["breakdown"])
        self.assertEqual(score["breakdown"]["penalty:stage_failed"], weights["penalties"]["stage_failed"])

    def test_score_candidate_tracks_missing_metrics(self) -> None:
        weights = json.loads(DEFAULT_SCORE_WEIGHTS_PATH.read_text())
        score = score_candidate(
            weights,
            {"lut": 100, "ff": 200},
            {"latency_cycles": 20},
            stage_failed=False,
        )
        self.assertIn("dsp", score["missing_metrics"])
        self.assertIn("bram", score["missing_metrics"])
        self.assertIn("wns_ns", score["missing_metrics"])


if __name__ == "__main__":
    unittest.main()
