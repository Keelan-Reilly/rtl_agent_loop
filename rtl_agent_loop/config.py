from __future__ import annotations

import json
from pathlib import Path
from typing import Any

from .models import ALLOWED_CONV_VARIANTS, CandidateManifest, OPTIONAL_PARAMETER_KEYS, REQUIRED_PARAMETER_KEYS
from .paths import DEFAULT_SCORE_WEIGHTS_PATH, DEFAULT_SEARCH_SPACE_PATH


class ValidationError(ValueError):
    """Raised when config or manifest validation fails."""


def load_json(path: Path) -> dict[str, Any]:
    return json.loads(path.read_text())


def load_search_space(path: Path | None = None) -> dict[str, Any]:
    return load_json(path or DEFAULT_SEARCH_SPACE_PATH)


def load_score_weights(path: Path | None = None) -> dict[str, Any]:
    return load_json(path or DEFAULT_SCORE_WEIGHTS_PATH)


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

    missing_params = [key for key in REQUIRED_PARAMETER_KEYS if key not in parameters]
    if missing_params:
        raise ValidationError(f"Manifest missing required parameters: {', '.join(missing_params)}")

    allowed_parameter_keys = set(REQUIRED_PARAMETER_KEYS) | set(OPTIONAL_PARAMETER_KEYS)
    unsupported = sorted(set(parameters) - allowed_parameter_keys)
    if unsupported:
        raise ValidationError(f"Unsupported parameters in manifest: {', '.join(unsupported)}")

    search_space_def = search_space["search_space"]
    for key in ("DENSE_OUT_PAR", "DATA_WIDTH", "FRAC_BITS", "CONV_CHANNEL_PAR"):
        value = parameters[key]
        if not isinstance(value, int):
            raise ValidationError(f"{key} must be an integer")
        allowed = search_space_def[key]["allowed"]
        if value not in allowed:
            raise ValidationError(f"{key}={value} is outside allowed set {allowed}")

    if "DENSE_SPLIT_MAC_PIPELINE" in parameters:
        value = parameters["DENSE_SPLIT_MAC_PIPELINE"]
        if not isinstance(value, int):
            raise ValidationError("DENSE_SPLIT_MAC_PIPELINE must be an integer")
        allowed = search_space_def["DENSE_SPLIT_MAC_PIPELINE"]["allowed"]
        if value not in allowed:
            raise ValidationError(f"DENSE_SPLIT_MAC_PIPELINE={value} is outside allowed set {allowed}")

    conv_variant = parameters["CONV_VARIANT"]
    if conv_variant not in ALLOWED_CONV_VARIANTS:
        raise ValidationError(
            f"CONV_VARIANT must be one of {sorted(ALLOWED_CONV_VARIANTS)}, got {conv_variant!r}"
        )
    allowed_variants = search_space_def["CONV_VARIANT"]["allowed"]
    if conv_variant not in allowed_variants:
        raise ValidationError(f"CONV_VARIANT={conv_variant!r} is outside allowed set {allowed_variants}")

    if parameters["FRAC_BITS"] >= parameters["DATA_WIDTH"]:
        raise ValidationError("FRAC_BITS must be strictly less than DATA_WIDTH")

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
