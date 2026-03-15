from __future__ import annotations

from dataclasses import dataclass
from pathlib import Path
from typing import Any


ALLOWED_CONV_VARIANTS = {"baseline", "pipelined"}
REQUIRED_PARAMETER_KEYS = ("DENSE_OUT_PAR", "DATA_WIDTH", "FRAC_BITS", "CONV_VARIANT")


@dataclass(slots=True)
class CandidateManifest:
    candidate_id: str
    source: str
    created_at: str
    parameters: dict[str, Any]
    notes: str
    tags: list[str]
    manifest_path: Path
    raw: dict[str, Any]


@dataclass(slots=True)
class CandidateRecord:
    candidate_id: str
    current_state: str
    manifest_path: str
    candidate_dir: str
    source: str
    created_at: str
    notes: str
    tags_json: str
    manifest_json: str


@dataclass(slots=True)
class StageResult:
    stage: str
    passed: bool
    result_path: Path
    payload: dict[str, Any]

