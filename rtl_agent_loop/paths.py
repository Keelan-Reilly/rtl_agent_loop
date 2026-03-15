from __future__ import annotations

from pathlib import Path


PACKAGE_ROOT = Path(__file__).resolve().parent
REPO_ROOT = PACKAGE_ROOT.parent
CONFIG_DIR = REPO_ROOT / "config"
DEFAULT_SEARCH_SPACE_PATH = CONFIG_DIR / "search_space.json"
DEFAULT_SCORE_WEIGHTS_PATH = CONFIG_DIR / "score_weights.json"
RUNS_DIR = REPO_ROOT / "runs"
LOGS_DIR = REPO_ROOT / "logs"
VAR_DIR = REPO_ROOT / "var"
DB_PATH = VAR_DIR / "rtl_agent_loop.db"
SCRIPTS_DIR = REPO_ROOT / "scripts"

