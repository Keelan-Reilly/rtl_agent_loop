from __future__ import annotations

from dataclasses import dataclass
from pathlib import Path
from typing import Any


ALLOWED_ARCH_VARIANTS = {0, 1, 2}
REQUIRED_PARAMETER_KEYS = (
    "ARCH_VARIANT",
    "ARRAY_M",
    "ARRAY_N",
    "CLUSTER_SIZE",
    "SHARE_FACTOR",
    "DATA_WIDTH",
    "FRAC_BITS",
    "ACC_WIDTH",
    "PIPE_STAGES",
    "TILE_K",
    "INPUT_MEM_DEPTH",
    "OUTPUT_MEM_DEPTH",
)
OPTIONAL_PARAMETER_KEYS: tuple[str, ...] = ()


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
    parent_candidate_id: str | None = None
    lineage_root_candidate_id: str | None = None
    revision_kind: str | None = None
    derived_from_run_id: int | None = None
    supersedes_candidate_id: str | None = None


@dataclass(slots=True)
class StageResult:
    stage: str
    passed: bool
    result_path: Path
    payload: dict[str, Any]
