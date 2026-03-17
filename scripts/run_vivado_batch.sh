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
  scripts/run_vivado_batch.sh (--candidate-id <id> | --candidate-manifest <path>) --run-dir <dir> [--external-repo <path>]
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

mkdir -p "${RUN_DIR}/vivado"
LOG_PATH="${RUN_DIR}/vivado/vivado_wrapper.log"
RESULT_PATH="${RUN_DIR}/vivado/vivado_result.json"

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
outcome_classification = "full_pass"
message = "Vivado batch completed successfully."
returncode = 0
parsed_metrics = {}
checks = {
    "external_root_exists": external_root.exists(),
    "run_script_exists": run_script.exists(),
    "parse_script_exists": parse_script.exists(),
    "xdc_exists": xdc_path.exists(),
}

with log_path.open("w") as logf:
    logf.write(f"candidate_id={manifest.get('candidate_id')}\n")
    logf.write(f"manifest_path={manifest_path}\n")
    logf.write(f"external_root={external_root}\n")
    logf.write("checks:\n")
    for key, value in checks.items():
        logf.write(f"  {key}={value}\n")
    if not all(checks.values()):
        status = "failed"
        outcome_classification = "failed_preflight"
        message = "Vivado wrapper preflight failed."
        returncode = 2
    else:
        proc = subprocess.run(command, cwd=wrapper_run_dir, stdout=logf, stderr=subprocess.STDOUT)
        returncode = proc.returncode
        have_reports = any(
            path.exists()
            for path in (
                reports_dir / "utilization_impl.rpt",
                reports_dir / "timing_impl.rpt",
                reports_dir / "utilization_synth.rpt",
                reports_dir / "timing_synth.rpt",
            )
        )
        if have_reports:
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
            if metrics_path.exists():
                parsed_metrics = json.loads(metrics_path.read_text())
            if parse_proc.returncode != 0:
                status = "failed"
                outcome_classification = "missing_result"
                message = f"Vivado report parsing failed with exit code {parse_proc.returncode}"
                returncode = parse_proc.returncode
            elif parsed_metrics.get("report_kind") == "implementation" and proc.returncode == 0:
                status = "passed"
                outcome_classification = "full_pass"
                message = "Vivado batch completed successfully with implementation metrics."
            elif parsed_metrics.get("report_kind") == "synthesis":
                status = "failed"
                outcome_classification = "synth_only"
                message = "Vivado implementation did not complete, but synthesis-stage metrics were preserved."
            elif proc.returncode != 0:
                status = "failed"
                outcome_classification = "failed_tool"
                message = f"Vivado batch failed with exit code {proc.returncode}"
            else:
                status = "failed"
                outcome_classification = "missing_result"
                message = "Vivado batch completed but no machine-readable metrics were parsed."
        else:
            status = "failed"
            outcome_classification = "failed_tool"
            message = f"Vivado batch failed with exit code {returncode}"

payload = {
    "stage": "vivado",
    "status": status,
    "passed": status == "passed",
    "outcome_classification": outcome_classification,
    "message": message,
    "candidate_id": manifest.get("candidate_id"),
    "parameters": manifest.get("parameters", {}),
    "command": command,
    "returncode": returncode,
    "checks": checks,
    "reports_dir": str(reports_dir.relative_to(run_dir)) if reports_dir.exists() else None,
    "metrics_path": str(metrics_path.relative_to(run_dir)) if metrics_path.exists() else None,
    "metrics": parsed_metrics,
    "metrics_kind": parsed_metrics.get("report_kind") if parsed_metrics else None,
    "todo": "ARCH_VARIANT is forwarded as a real generic. PIPE_STAGES currently models deterministic drain latency rather than a fully retimed datapath.",
    "log_path": str(log_path.relative_to(run_dir)),
}
result_path.write_text(json.dumps(payload, indent=2) + "\n")
sys.exit(0 if status == "passed" else returncode or 1)
PY
