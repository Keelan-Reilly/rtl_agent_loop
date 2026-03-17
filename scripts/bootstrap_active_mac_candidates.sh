#!/usr/bin/env bash
set -euo pipefail

repo_root="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
python_bin="${PYTHON:-python3}"

shopt -s nullglob
manifests=("${repo_root}"/candidates/mac_*.json)

if [[ "${#manifests[@]}" -eq 0 ]]; then
  echo "No MAC-array manifests found under ${repo_root}/candidates" >&2
  exit 1
fi

for manifest in "${manifests[@]}"; do
  candidate_id="$("${python_bin}" - <<'PY' "$manifest"
import json, sys
print(json.loads(open(sys.argv[1]).read())["candidate_id"])
PY
)"
  if "${python_bin}" -m rtl_agent_loop status --candidate-id "${candidate_id}" >/dev/null 2>&1; then
    echo "already registered: ${candidate_id}"
    continue
  fi
  echo "registering: ${candidate_id}"
  "${python_bin}" -m rtl_agent_loop register --manifest "${manifest}"
done
