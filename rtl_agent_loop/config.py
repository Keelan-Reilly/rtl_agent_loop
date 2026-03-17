from __future__ import annotations

import json
from pathlib import Path
from typing import Any

from .models import ALLOWED_ARCH_VARIANTS, CandidateManifest, OPTIONAL_PARAMETER_KEYS, REQUIRED_PARAMETER_KEYS
from .paths import DEFAULT_SCORE_WEIGHTS_PATH, DEFAULT_SEARCH_SPACE_PATH


class ValidationError(ValueError):
    """Raised when config or manifest validation fails."""


LEGACY_CNN_PARAMETER_KEYS = {
    "DENSE_OUT_PAR",
    "CONV_CHANNEL_PAR",
    "CONV_VARIANT",
    "DENSE_SPLIT_MAC_PIPELINE",
}


def load_json(path: Path) -> dict[str, Any]:
    return json.loads(path.read_text())


def load_search_space(path: Path | None = None) -> dict[str, Any]:
    return load_json(path or DEFAULT_SEARCH_SPACE_PATH)


def load_score_weights(path: Path | None = None) -> dict[str, Any]:
    return load_json(path or DEFAULT_SCORE_WEIGHTS_PATH)


def detect_parameter_family(parameters: dict[str, Any]) -> str:
    keys = set(parameters)
    required = set(REQUIRED_PARAMETER_KEYS)
    if required.issubset(keys):
        return "mac_array_v1"
    if keys & LEGACY_CNN_PARAMETER_KEYS:
        return "cnn_legacy"
    return "unknown"


def validate_manifest(manifest_data: dict[str, Any], manifest_path: Path, search_space: dict[str, Any]) -> CandidateManifest:
    required_keys = {"candidate_id", "source", "created_at", "parameters", "notes", "tags"}
    missing = sorted(required_keys - manifest_data.keys())
    if missing:
        raise ValidationError(f"Manifest missing required fields: {', '.join(missing)}")

    candidate_id = manifest_data["candidate_id"]
    if not isinstance(candidate_id, str) or not candidate_id.strip():
        raise ValidationError("candidate_id must be a non-empty string")

    parameters = manifest_data["parameters"]
    if not isinstance(parameters, dict):
        raise ValidationError("parameters must be an object")

    parameter_family = detect_parameter_family(parameters)

    missing_params = [key for key in REQUIRED_PARAMETER_KEYS if key not in parameters]
    if missing_params:
        if parameter_family == "cnn_legacy":
            raise ValidationError(
                "Manifest uses the legacy CNN-era parameter family. "
                "The active schema now targets MAC-array candidates and requires: "
                + ", ".join(REQUIRED_PARAMETER_KEYS)
            )
        raise ValidationError(f"Manifest missing required parameters: {', '.join(missing_params)}")

    allowed_parameter_keys = set(REQUIRED_PARAMETER_KEYS) | set(OPTIONAL_PARAMETER_KEYS)
    unsupported = sorted(set(parameters) - allowed_parameter_keys)
    if unsupported:
        if parameter_family == "cnn_legacy":
            raise ValidationError(
                "Manifest uses legacy CNN-era parameters that are no longer part of the active MAC-array schema: "
                + ", ".join(unsupported)
            )
        raise ValidationError(f"Unsupported parameters in manifest: {', '.join(unsupported)}")

    search_space_def = search_space["search_space"]
    for key in REQUIRED_PARAMETER_KEYS:
        value = parameters[key]
        if not isinstance(value, int):
            raise ValidationError(f"{key} must be an integer")
        allowed = search_space_def[key]["allowed"]
        if value not in allowed:
            raise ValidationError(f"{key}={value} is outside allowed set {allowed}")

    arch_variant = parameters["ARCH_VARIANT"]
    if arch_variant not in ALLOWED_ARCH_VARIANTS:
        raise ValidationError(f"ARCH_VARIANT must be one of {sorted(ALLOWED_ARCH_VARIANTS)}, got {arch_variant!r}")

    if parameters["FRAC_BITS"] >= parameters["DATA_WIDTH"]:
        raise ValidationError("FRAC_BITS must be strictly less than DATA_WIDTH")

    if parameters["ACC_WIDTH"] <= parameters["DATA_WIDTH"]:
        raise ValidationError("ACC_WIDTH must be strictly greater than DATA_WIDTH")

    if parameters["ARCH_VARIANT"] != 1 and parameters["SHARE_FACTOR"] != 1:
        raise ValidationError("SHARE_FACTOR must be 1 for baseline and replicated variants")

    if parameters["ARCH_VARIANT"] == 1 and parameters["SHARE_FACTOR"] < 2:
        raise ValidationError("Shared variants require SHARE_FACTOR >= 2")

    if parameters["CLUSTER_SIZE"] > max(parameters["ARRAY_M"], parameters["ARRAY_N"]):
        raise ValidationError("CLUSTER_SIZE must be <= max(ARRAY_M, ARRAY_N)")

    required_input_depth = max(
        parameters["ARRAY_M"] * parameters["TILE_K"],
        parameters["ARRAY_N"] * parameters["TILE_K"],
    )
    if parameters["INPUT_MEM_DEPTH"] < required_input_depth:
        raise ValidationError(
            f"INPUT_MEM_DEPTH must be >= {required_input_depth} for the selected ARRAY_M/ARRAY_N/TILE_K"
        )

    required_output_depth = parameters["ARRAY_M"] * parameters["ARRAY_N"]
    if parameters["OUTPUT_MEM_DEPTH"] < required_output_depth:
        raise ValidationError(f"OUTPUT_MEM_DEPTH must be >= {required_output_depth} for the selected output tile")

    if not isinstance(manifest_data["tags"], list) or not all(isinstance(tag, str) for tag in manifest_data["tags"]):
        raise ValidationError("tags must be a list of strings")

    for key in ("source", "created_at", "notes"):
        if not isinstance(manifest_data[key], str):
            raise ValidationError(f"{key} must be a string")

    return CandidateManifest(
        candidate_id=candidate_id,
        source=manifest_data["source"],
        created_at=manifest_data["created_at"],
        parameters=dict(parameters),
        notes=manifest_data["notes"],
        tags=list(manifest_data["tags"]),
        manifest_path=manifest_path,
        raw=dict(manifest_data),
    )
