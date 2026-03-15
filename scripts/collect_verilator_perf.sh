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
  scripts/collect_verilator_perf.sh (--candidate-id <id> | --candidate-manifest <path>) --run-dir <dir> [--external-repo <path>]
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

mkdir -p "${RUN_DIR}/verilator_perf"
LOG_PATH="${RUN_DIR}/verilator_perf/verilator_wrapper.log"
RESULT_PATH="${RUN_DIR}/verilator_perf/verilator_result.json"

"${PYTHON_BIN}" - "${REPO_ROOT}" "${CANDIDATE_ID}" "${CANDIDATE_MANIFEST}" "${RUN_DIR}" "${LOG_PATH}" "${RESULT_PATH}" "${EXTERNAL_REPO}" <<'PY'
import json
import os
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
defaults = config["defaults"]
verilator_cfg = defaults["verilator"]
perf_script = external_root / "experiments" / "collect_verilator_perf.py"
perf_root = run_dir / "verilator_perf" / "perf_run"
perf_json = perf_root / "verilator_perf" / "performance.json"
weights_input_path = external_root / "weights" / "input_image.mem"
tb_full_path = external_root / "tb" / "tb_full_pipeline.cpp"

params = dict(manifest.get("parameters", {}))
conv_variant = params.pop("CONV_VARIANT", None)

command = [
    sys.executable,
    str(perf_script),
    "--run-dir",
    str(perf_root),
    "--clock-hz",
    str(defaults["clock_hz"]),
    "--top",
    str(verilator_cfg["top"]),
]
for key in sorted(params):
    command.extend(["--generic", f"{key}={params[key]}"])

status = "passed"
message = "Verilator performance collection completed successfully."
returncode = 0
parsed_metrics = {}
checks = {
    "external_root_exists": external_root.exists(),
    "perf_script_exists": perf_script.exists(),
    "weights_input_exists": weights_input_path.exists(),
    "tb_full_exists": tb_full_path.exists(),
}

if conv_variant is not None:
    message = (
        "Verilator performance collection completed. CONV_VARIANT is recorded but not yet mapped into external RTL; "
        "see docs/integration_notes.md."
    )

with log_path.open("w") as logf:
    logf.write(f"candidate_id={manifest.get('candidate_id')}\n")
    logf.write(f"manifest_path={manifest_path}\n")
    logf.write(f"external_root={external_root}\n")
    logf.write("checks:\n")
    for key, value in checks.items():
        logf.write(f"  {key}={value}\n")
    if not all(checks.values()):
        status = "failed"
        message = "Verilator wrapper preflight failed."
        returncode = 2
    else:
        proc = subprocess.run(command, cwd=external_root, stdout=logf, stderr=subprocess.STDOUT)
        returncode = proc.returncode
        if returncode != 0:
            status = "failed"
            message = f"Verilator performance collection failed with exit code {returncode}"
        elif perf_json.exists():
            parsed_metrics = json.loads(perf_json.read_text())
        else:
            status = "failed"
            message = "Verilator performance collection completed but performance.json was not found."
            returncode = 3

payload = {
    "stage": "verilator_perf",
    "status": status,
    "message": message,
    "candidate_id": manifest.get("candidate_id"),
    "parameters": manifest.get("parameters", {}),
    "command": command,
    "returncode": returncode,
    "checks": checks,
    "performance_path": str(perf_json.relative_to(run_dir)) if perf_json.exists() else None,
    "metrics": parsed_metrics,
    "todo": "TODO: confirm Verilator data and weight prerequisites in the external CNN_FPGA repo.",
    "log_path": str(log_path.relative_to(run_dir)),
}
result_path.write_text(json.dumps(payload, indent=2) + "\n")
sys.exit(0 if status == "passed" else returncode or 1)
PY
