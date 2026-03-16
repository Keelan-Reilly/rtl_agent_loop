#!/usr/bin/env bash
set -euo pipefail

RUN_DIR=""
REPO_ROOT=""
PART=""
TOP=""
XDC=""
CLOCK_PERIOD_NS=""
JOBS="4"
declare -a GENERICS=()

usage() {
  cat <<'EOF'
Usage:
  run_batch.sh --run-dir <dir> --repo-root <dir> --part <part> --top <top> --xdc <file> --clock-period-ns <ns> [--jobs <n>] [--generic KEY=VALUE ...]
EOF
}

while [[ $# -gt 0 ]]; do
  case "$1" in
    --run-dir)
      RUN_DIR="$2"
      shift 2
      ;;
    --repo-root)
      REPO_ROOT="$2"
      shift 2
      ;;
    --part)
      PART="$2"
      shift 2
      ;;
    --top)
      TOP="$2"
      shift 2
      ;;
    --xdc)
      XDC="$2"
      shift 2
      ;;
    --clock-period-ns)
      CLOCK_PERIOD_NS="$2"
      shift 2
      ;;
    --jobs)
      JOBS="$2"
      shift 2
      ;;
    --generic)
      GENERICS+=("$2")
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

if [[ -z "${RUN_DIR}" || -z "${REPO_ROOT}" || -z "${PART}" || -z "${TOP}" || -z "${XDC}" || -z "${CLOCK_PERIOD_NS}" ]]; then
  echo "ERROR: missing required arguments" >&2
  usage
  exit 1
fi

VIVADO_BIN="${VIVADO_BIN:-vivado}"
if ! command -v "${VIVADO_BIN}" >/dev/null 2>&1; then
  echo "ERROR: Vivado binary '${VIVADO_BIN}' not found in PATH" >&2
  exit 2
fi

mkdir -p "${RUN_DIR}/reports" "${RUN_DIR}/logs" "${RUN_DIR}/project"
LOG_PATH="${RUN_DIR}/logs/vivado_batch.log"
TCL_SCRIPT="${REPO_ROOT}/fpga/vivado/run_project.tcl"

GENERIC_CSV=""
if [[ ${#GENERICS[@]} -gt 0 ]]; then
  GENERIC_CSV="$(IFS=, ; echo "${GENERICS[*]}")"
fi

{
  echo "repo_root=${REPO_ROOT}"
  echo "run_dir=${RUN_DIR}"
  echo "top=${TOP}"
  echo "part=${PART}"
  echo "xdc=${XDC}"
  echo "clock_period_ns=${CLOCK_PERIOD_NS}"
  echo "jobs=${JOBS}"
  echo "generics=${GENERIC_CSV}"
} > "${LOG_PATH}"

"${VIVADO_BIN}" \
  -mode batch \
  -source "${TCL_SCRIPT}" \
  -notrace \
  -tclargs "${REPO_ROOT}" "${RUN_DIR}" "${TOP}" "${PART}" "${XDC}" "${CLOCK_PERIOD_NS}" "${JOBS}" "${GENERIC_CSV}" \
  >> "${LOG_PATH}" 2>&1
