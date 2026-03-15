from __future__ import annotations

import shlex
import subprocess
from pathlib import Path
from typing import Sequence


def shell_join(command: Sequence[str]) -> str:
    return " ".join(shlex.quote(part) for part in command)


def run_command(command: Sequence[str], cwd: Path, log_path: Path) -> subprocess.CompletedProcess[str]:
    log_path.parent.mkdir(parents=True, exist_ok=True)
    with log_path.open("w") as logf:
        logf.write(f"$ {shell_join(command)}\n")
        logf.flush()
        return subprocess.run(
            list(command),
            cwd=cwd,
            stdout=logf,
            stderr=subprocess.STDOUT,
            text=True,
            check=False,
        )

