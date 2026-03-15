#!/usr/bin/env bash
set -euo pipefail

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
REPO_ROOT="$(cd "${SCRIPT_DIR}/.." && pwd)"

PYTHON_BIN="${RTL_AGENT_LOOP_PYTHON:-python3}"
EXTERNAL_REPO="${RTL_AGENT_LOOP_EXTERNAL_REPO:-${REPO_ROOT}/external/CNN_FPGA}"
INIT_DB="1"

usage() {
  cat <<'EOF'
Usage:
  scripts/bootstrap_env.sh [--python <bin>] [--external-repo <path>] [--no-init-db]

Environment:
  RTL_AGENT_LOOP_PYTHON             Python interpreter to use for this repo
  RTL_AGENT_LOOP_EXTERNAL_REPO      Path to the underlying CNN_FPGA checkout
  VIVADO_BIN                        Vivado executable used by the external batch flow
EOF
}

while [[ $# -gt 0 ]]; do
  case "$1" in
    --python)
      PYTHON_BIN="$2"
      shift 2
      ;;
    --external-repo)
      EXTERNAL_REPO="$2"
      shift 2
      ;;
    --no-init-db)
      INIT_DB="0"
      shift
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

if ! command -v "${PYTHON_BIN}" >/dev/null 2>&1; then
  echo "ERROR: Python interpreter not found: ${PYTHON_BIN}" >&2
  exit 1
fi

if [[ ! -d "${EXTERNAL_REPO}" ]]; then
  echo "ERROR: external CNN_FPGA repo not found: ${EXTERNAL_REPO}" >&2
  exit 1
fi

if [[ ! -f "${EXTERNAL_REPO}/Makefile" ]]; then
  echo "ERROR: expected Makefile missing under ${EXTERNAL_REPO}" >&2
  exit 1
fi

export RTL_AGENT_LOOP_PYTHON="${PYTHON_BIN}"
export RTL_AGENT_LOOP_EXTERNAL_REPO="${EXTERNAL_REPO}"
export VIVADO_BIN="${VIVADO_BIN:-vivado}"

echo "repo_root=${REPO_ROOT}"
echo "python=${RTL_AGENT_LOOP_PYTHON}"
echo "external_repo=${RTL_AGENT_LOOP_EXTERNAL_REPO}"
echo "vivado_bin=${VIVADO_BIN}"

"${RTL_AGENT_LOOP_PYTHON}" - <<'PY'
import importlib
import sys

print(f"python_version={sys.version.split()[0]}")
if sys.version_info < (3, 12):
    print("WARNING: Python 3.12 is the target version for this repo.")
for module_name in ["argparse", "json", "sqlite3", "subprocess"]:
    importlib.import_module(module_name)
print("stdlib_dependency_check=ok")
PY

"${RTL_AGENT_LOOP_PYTHON}" -m compileall "${REPO_ROOT}/rtl_agent_loop" >/dev/null

if [[ "${INIT_DB}" == "1" ]]; then
  "${RTL_AGENT_LOOP_PYTHON}" -m rtl_agent_loop init-db >/dev/null
fi

echo "bootstrap_status=ok"

