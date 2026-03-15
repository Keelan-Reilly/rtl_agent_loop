from __future__ import annotations

from dataclasses import dataclass


REGISTERED = "registered"
FAST_VERIFY_PENDING = "fast_verify_pending"
FAST_VERIFY_PASSED = "fast_verify_passed"
FAST_VERIFY_FAILED = "fast_verify_failed"
VIVADO_PENDING = "vivado_pending"
VIVADO_PASSED = "vivado_passed"
VIVADO_FAILED = "vivado_failed"
PERF_PENDING = "perf_pending"
PERF_PASSED = "perf_passed"
PERF_FAILED = "perf_failed"
SCORED = "scored"

TERMINAL_FAILURE_STATES = {FAST_VERIFY_FAILED, VIVADO_FAILED, PERF_FAILED}


@dataclass(frozen=True, slots=True)
class StageDefinition:
    name: str
    pending_state: str
    success_state: str
    failure_state: str
    result_relpath: str


STAGES = (
    StageDefinition(
        name="fast_verify",
        pending_state=FAST_VERIFY_PENDING,
        success_state=FAST_VERIFY_PASSED,
        failure_state=FAST_VERIFY_FAILED,
        result_relpath="fast_verify/fast_verify.json",
    ),
    StageDefinition(
        name="vivado",
        pending_state=VIVADO_PENDING,
        success_state=VIVADO_PASSED,
        failure_state=VIVADO_FAILED,
        result_relpath="vivado/vivado_result.json",
    ),
    StageDefinition(
        name="verilator_perf",
        pending_state=PERF_PENDING,
        success_state=PERF_PASSED,
        failure_state=PERF_FAILED,
        result_relpath="verilator_perf/verilator_result.json",
    ),
)

