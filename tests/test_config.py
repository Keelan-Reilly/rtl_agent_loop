import json
from pathlib import Path
import unittest

from rtl_agent_loop.config import ValidationError, detect_parameter_family, validate_manifest
from rtl_agent_loop.paths import DEFAULT_SEARCH_SPACE_PATH


class ConfigTests(unittest.TestCase):
    def test_detects_mac_array_family(self) -> None:
        family = detect_parameter_family(
            {
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
            }
        )
        self.assertEqual(family, "mac_array_v1")

    def test_detects_legacy_cnn_family(self) -> None:
        family = detect_parameter_family(
            {
                "DENSE_OUT_PAR": 2,
                "DATA_WIDTH": 16,
                "FRAC_BITS": 7,
                "CONV_CHANNEL_PAR": 1,
                "CONV_VARIANT": "baseline",
            }
        )
        self.assertEqual(family, "cnn_legacy")

    def test_legacy_manifest_gets_clear_error(self) -> None:
        search_space = json.loads(DEFAULT_SEARCH_SPACE_PATH.read_text())
        manifest = {
            "candidate_id": "legacy_dense",
            "source": "legacy",
            "created_at": "2026-03-16T00:00:00Z",
            "parameters": {
                "DENSE_OUT_PAR": 2,
                "DATA_WIDTH": 16,
                "FRAC_BITS": 7,
                "CONV_CHANNEL_PAR": 1,
                "CONV_VARIANT": "baseline",
            },
            "notes": "legacy",
            "tags": ["legacy"],
        }
        with self.assertRaisesRegex(ValidationError, "legacy CNN-era"):
            validate_manifest(manifest, Path("legacy.json"), search_space)


if __name__ == "__main__":
    unittest.main()
