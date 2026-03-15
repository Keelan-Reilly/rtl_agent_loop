#!/usr/bin/env bash
set -euo pipefail

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
REPO_ROOT="$(cd "${SCRIPT_DIR}/.." && pwd)"

CANDIDATE_MANIFEST=""
RUN_DIR=""

usage() {
  cat <<'EOF'
Usage:
  scripts/run_vivado_batch.sh --candidate-manifest <path> --run-dir <dir>
EOF
}

while [[ $# -gt 0 ]]; do
  case "$1" in
    --candidate-manifest)
      CANDIDATE_MANIFEST="$2"
      shift 2
      ;;
    --run-dir)
      RUN_DIR="$2"
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

if [[ -z "${CANDIDATE_MANIFEST}" || -z "${RUN_DIR}" ]]; then
  echo "ERROR: --candidate-manifest and --run-dir are required" >&2
  usage
  exit 1
fi

mkdir -p "${RUN_DIR}/vivado"
LOG_PATH="${RUN_DIR}/vivado/vivado_wrapper.log"
RESULT_PATH="${RUN_DIR}/vivado/vivado_result.json"

python3 - "${REPO_ROOT}" "${CANDIDATE_MANIFEST}" "${RUN_DIR}" "${LOG_PATH}" "${RESULT_PATH}" <<'PY'
import json
import subprocess
import sys
from pathlib import Path

repo_root = Path(sys.argv[1])
manifest_path = Path(sys.argv[2])
run_dir = Path(sys.argv[3])
log_path = Path(sys.argv[4])
result_path = Path(sys.argv[5])

config = json.loads((repo_root / "config" / "search_space.json").read_text())
manifest = json.loads(manifest_path.read_text())
external_root = repo_root / config["external_repo"]["path"]
defaults = config["defaults"]
vivado_cfg = defaults["vivado"]
vivado_root = external_root / "fpga" / "vivado"
run_script = vivado_root / "run_batch.sh"
parse_script = vivado_root / "parse_reports.py"
xdc_path = external_root / vivado_cfg["xdc"]
wrapper_run_dir = run_dir / "vivado" / "batch_run"
wrapper_run_dir.mkdir(parents=True, exist_ok=True)
metrics_path = run_dir / "vivado" / "metrics.json"
reports_dir = wrapper_run_dir / "reports"

params = dict(manifest.get("parameters", {}))
conv_variant = params.pop("CONV_VARIANT", None)

command = [
    str(run_script),
    "--run-dir",
    str(wrapper_run_dir),
    "--repo-root",
    str(external_root),
    "--part",
    str(vivado_cfg["part"]),
    "--top",
    str(vivado_cfg["top"]),
    "--xdc",
    str(external_root / vivado_cfg["xdc"]),
    "--clock-period-ns",
    str(vivado_cfg["clock_period_ns"]),
    "--jobs",
    str(vivado_cfg["jobs"]),
]
for key in sorted(params):
    command.extend(["--generic", f"{key}={params[key]}"])

status = "passed"
message = "Vivado batch completed successfully."
returncode = 0
parsed_metrics = {}
checks = {
    "external_root_exists": external_root.exists(),
    "run_script_exists": run_script.exists(),
    "parse_script_exists": parse_script.exists(),
    "xdc_exists": xdc_path.exists(),
}

if conv_variant is not None:
    message = (
        "Vivado batch completed. CONV_VARIANT is recorded but not yet mapped into external RTL; "
        "see docs/integration_notes.md."
    )

with log_path.open("w") as logf:
    logf.write("checks:\n")
    for key, value in checks.items():
        logf.write(f"  {key}={value}\n")
    if not all(checks.values()):
        status = "failed"
        message = "Vivado wrapper preflight failed."
        returncode = 2
    else:
        proc = subprocess.run(command, cwd=wrapper_run_dir, stdout=logf, stderr=subprocess.STDOUT)
        returncode = proc.returncode
        if returncode != 0:
            status = "failed"
            message = f"Vivado batch failed with exit code {returncode}"
        else:
            parse_command = [
                sys.executable,
                str(parse_script),
                "--reports-dir",
                str(reports_dir),
                "--clock-period-ns",
                str(vivado_cfg["clock_period_ns"]),
                "--output",
                str(metrics_path),
            ]
            parse_proc = subprocess.run(parse_command, cwd=wrapper_run_dir, stdout=logf, stderr=subprocess.STDOUT)
            if parse_proc.returncode != 0:
                status = "failed"
                message = f"Vivado report parsing failed with exit code {parse_proc.returncode}"
                returncode = parse_proc.returncode
            elif metrics_path.exists():
                parsed_metrics = json.loads(metrics_path.read_text())

payload = {
    "stage": "vivado",
    "status": status,
    "message": message,
    "candidate_id": manifest.get("candidate_id"),
    "parameters": manifest.get("parameters", {}),
    "command": command,
    "returncode": returncode,
    "checks": checks,
    "reports_dir": str(reports_dir.relative_to(run_dir)) if reports_dir.exists() else None,
    "metrics_path": str(metrics_path.relative_to(run_dir)) if metrics_path.exists() else None,
    "metrics": parsed_metrics,
    "todo": "TODO: map CONV_VARIANT into CNN_FPGA once the external repo exposes the desired integration hook.",
    "log_path": str(log_path.relative_to(run_dir)),
}
result_path.write_text(json.dumps(payload, indent=2) + "\n")
sys.exit(0 if status == "passed" else returncode or 1)
PY
