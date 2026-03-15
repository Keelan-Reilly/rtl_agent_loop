#!/usr/bin/env bash
set -euo pipefail

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
REPO_ROOT="$(cd "${SCRIPT_DIR}/.." && pwd)"
PYTHON_BIN="${RTL_AGENT_LOOP_PYTHON:-python3}"

CANDIDATE_MANIFEST=""
CANDIDATE_ID=""
RUN_DIR=""
EXTERNAL_REPO=""

usage() {
  cat <<'EOF'
Usage:
  scripts/fast_verify.sh (--candidate-id <id> | --candidate-manifest <path>) --run-dir <dir> [--external-repo <path>]
EOF
}

while [[ $# -gt 0 ]]; do
  case "$1" in
    --candidate-id)
      CANDIDATE_ID="$2"
      shift 2
      ;;
    --candidate-manifest)
      CANDIDATE_MANIFEST="$2"
      shift 2
      ;;
    --run-dir)
      RUN_DIR="$2"
      shift 2
      ;;
    --external-repo)
      EXTERNAL_REPO="$2"
      shift 2
      ;;
    -h|--help)
      usage
      exit 0
      ;;
    *)
      echo "ERROR: unknown argument '$1'" >&2
      usage
      exit 1
      ;;
  esac
done

if [[ -z "${CANDIDATE_ID}" && -z "${CANDIDATE_MANIFEST}" ]]; then
  echo "ERROR: either --candidate-id or --candidate-manifest is required" >&2
  usage
  exit 1
fi

if [[ -z "${RUN_DIR}" ]]; then
  echo "ERROR: --run-dir is required" >&2
  usage
  exit 1
fi

mkdir -p "${RUN_DIR}/fast_verify"
LOG_PATH="${RUN_DIR}/fast_verify/fast_verify.log"
RESULT_PATH="${RUN_DIR}/fast_verify/fast_verify.json"

"${PYTHON_BIN}" - "${REPO_ROOT}" "${CANDIDATE_ID}" "${CANDIDATE_MANIFEST}" "${RUN_DIR}" "${LOG_PATH}" "${RESULT_PATH}" "${EXTERNAL_REPO}" <<'PY'
import json
import os
import re
import shutil
import subprocess
import sys
from pathlib import Path

repo_root = Path(sys.argv[1])
candidate_id_arg = sys.argv[2]
manifest_arg = sys.argv[3]
run_dir = Path(sys.argv[4])
log_path = Path(sys.argv[5])
result_path = Path(sys.argv[6])
external_repo_arg = sys.argv[7]

config = json.loads((repo_root / "config" / "search_space.json").read_text())
if manifest_arg:
    manifest_path = Path(manifest_arg)
else:
    source_manifest = repo_root / "candidates" / f"{candidate_id_arg}.json"
    copied_manifest = repo_root / "runs" / candidate_id_arg / "candidate_manifest.json"
    manifest_path = source_manifest if source_manifest.exists() else copied_manifest
manifest = json.loads(manifest_path.read_text())
external_root = Path(
    external_repo_arg
    or os.environ.get("RTL_AGENT_LOOP_EXTERNAL_REPO")
    or (repo_root / config["external_repo"]["path"])
)
makefile_path = external_root / "Makefile"
top_level_path = external_root / "hdl" / "top_level.sv"
tb_full_path = external_root / "tb" / "tb_full_pipeline.cpp"
weights_input_path = external_root / "weights" / "input_image.mem"
hdl_dir = external_root / "hdl"
mode = config["defaults"]["fast_verify"]["mode"]

def parse_top_level_parameters(top_level_text: str) -> set[str]:
    module_match = re.search(r"module\s+top_level\s*#\((.*?)\)\s*\(", top_level_text, flags=re.S)
    if not module_match:
        return set()
    body = module_match.group(1)
    names = set()
    for match in re.finditer(r"parameter(?:\s+\w+)?(?:\s+\w+)?\s+([A-Za-z_][A-Za-z0-9_]*)\s*=", body):
        names.add(match.group(1))
    return names

top_level_text = top_level_path.read_text() if top_level_path.exists() else ""
top_level_parameters = parse_top_level_parameters(top_level_text)
candidate_parameters = manifest.get("parameters", {})
lint_generics = {
    key: candidate_parameters[key]
    for key in ("DATA_WIDTH", "DENSE_OUT_PAR", "FRAC_BITS")
    if key in candidate_parameters
}

checks = {
    "manifest_exists": manifest_path.exists(),
    "external_repo_exists": external_root.exists(),
    "makefile_exists": makefile_path.exists(),
    "top_level_exists": top_level_path.exists(),
    "tb_full_exists": tb_full_path.exists(),
    "weights_input_exists": weights_input_path.exists(),
    "hdl_dir_exists": hdl_dir.exists(),
    "vivado_wrapper_exists": (external_root / "fpga" / "vivado" / "run_batch.sh").exists(),
    "verilator_perf_exists": (external_root / "experiments" / "collect_verilator_perf.py").exists(),
    "verilator_available": shutil.which("verilator") is not None,
    "make_available": shutil.which("make") is not None,
}
checks["required_generics_present_in_top_level"] = all(key in top_level_parameters for key in lint_generics)

log_lines = [
    f"candidate_id={manifest.get('candidate_id', '<unknown>')}",
    f"manifest_path={manifest_path}",
    f"mode={mode}",
    f"external_root={external_root}",
    f"top_level_parameters={sorted(top_level_parameters)}",
    f"lint_generics={lint_generics}",
    "checks:",
]
for key, value in checks.items():
    log_lines.append(f"  {key}={value}")

status = "passed"
message = "Fast verification completed successfully."
command = None
returncode = 0
warnings = []

required_check_keys = [
    "manifest_exists",
    "external_repo_exists",
    "makefile_exists",
    "top_level_exists",
    "tb_full_exists",
    "weights_input_exists",
    "hdl_dir_exists",
    "vivado_wrapper_exists",
    "verilator_perf_exists",
    "required_generics_present_in_top_level",
]
if not all(checks[k] for k in required_check_keys):
    status = "failed"
    message = "Required external repo integration points are missing."
    returncode = 1
elif mode == "verilator_lint":
    if not checks["verilator_available"]:
        status = "failed"
        message = "Fast verification requires 'verilator' in PATH."
        returncode = 2
    else:
        hdl_files = sorted(hdl_dir.glob("*.sv"))
        if not hdl_files:
            status = "failed"
            message = "No HDL files found under external/CNN_FPGA/hdl."
            returncode = 3
        else:
            command = [
                "verilator",
                "-sv",
                "--lint-only",
                "-Wall",
                "-Wno-fatal",
            ]
            for key in sorted(lint_generics):
                command.append(f"-G{key}={lint_generics[key]}")
            command.extend(str(path) for path in hdl_files)
            command.extend(["--top-module", "top_level"])
            if candidate_parameters.get("CONV_VARIANT") != "baseline":
                warnings.append(
                    "CONV_VARIANT is recorded for orchestration but is not yet mapped into the external RTL fast gate."
                )
            log_lines.append(f"running={' '.join(command)}")
            with log_path.open("w") as logf:
                logf.write("\n".join(log_lines) + "\n")
                if warnings:
                    logf.write("warnings:\n")
                    for warning in warnings:
                        logf.write(f"  {warning}\n")
                logf.flush()
                proc = subprocess.run(command, cwd=external_root, stdout=logf, stderr=subprocess.STDOUT)
            returncode = proc.returncode
            if returncode != 0:
                status = "failed"
                message = f"Verilator lint failed with exit code {returncode}"
            else:
                message = "Candidate-aware Verilator lint passed."
else:
    status = "failed"
    message = f"Unsupported fast_verify mode: {mode}"
    returncode = 4

if command is None:
    with log_path.open("w") as logf:
        logf.write("\n".join(log_lines) + "\n")
        if warnings:
            logf.write("warnings:\n")
            for warning in warnings:
                logf.write(f"  {warning}\n")

payload = {
    "stage": "fast_verify",
    "status": status,
    "message": message,
    "mode": mode,
    "candidate_id": manifest.get("candidate_id"),
    "parameters": manifest.get("parameters", {}),
    "checks": checks,
    "top_level_parameters": sorted(top_level_parameters),
    "warnings": warnings,
    "command": command,
    "returncode": returncode,
    "todo": config["defaults"]["fast_verify"]["todo"],
    "log_path": str(log_path.relative_to(run_dir)),
}
result_path.write_text(json.dumps(payload, indent=2) + "\n")
sys.exit(0 if status == "passed" else returncode or 1)
PY
