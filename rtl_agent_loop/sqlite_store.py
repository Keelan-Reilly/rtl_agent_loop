from __future__ import annotations

import json
import sqlite3
from contextlib import contextmanager
from pathlib import Path
from typing import Any, Iterator

from .models import CandidateManifest
from .paths import DB_PATH, VAR_DIR


SCHEMA_STATEMENTS = (
    """
    CREATE TABLE IF NOT EXISTS candidates (
      candidate_id TEXT PRIMARY KEY,
      current_state TEXT NOT NULL,
      manifest_path TEXT NOT NULL,
      candidate_dir TEXT NOT NULL,
      source TEXT NOT NULL,
      created_at TEXT NOT NULL,
      notes TEXT NOT NULL,
      tags_json TEXT NOT NULL,
      manifest_json TEXT NOT NULL,
      registered_at TEXT NOT NULL
    )
    """,
    """
    CREATE TABLE IF NOT EXISTS candidate_params (
      candidate_id TEXT NOT NULL,
      param_key TEXT NOT NULL,
      param_value TEXT NOT NULL,
      PRIMARY KEY (candidate_id, param_key),
      FOREIGN KEY(candidate_id) REFERENCES candidates(candidate_id)
    )
    """,
    """
    CREATE TABLE IF NOT EXISTS runs (
      run_id INTEGER PRIMARY KEY AUTOINCREMENT,
      candidate_id TEXT NOT NULL,
      attempt_index INTEGER NOT NULL,
      status TEXT NOT NULL,
      started_at TEXT NOT NULL,
      ended_at TEXT,
      run_dir TEXT NOT NULL,
      FOREIGN KEY(candidate_id) REFERENCES candidates(candidate_id)
    )
    """,
    """
    CREATE TABLE IF NOT EXISTS state_transitions (
      transition_id INTEGER PRIMARY KEY AUTOINCREMENT,
      candidate_id TEXT NOT NULL,
      run_id INTEGER,
      stage TEXT,
      from_state TEXT,
      to_state TEXT NOT NULL,
      details_json TEXT NOT NULL,
      transitioned_at TEXT NOT NULL,
      FOREIGN KEY(candidate_id) REFERENCES candidates(candidate_id),
      FOREIGN KEY(run_id) REFERENCES runs(run_id)
    )
    """,
    """
    CREATE TABLE IF NOT EXISTS artifacts (
      artifact_id INTEGER PRIMARY KEY AUTOINCREMENT,
      candidate_id TEXT NOT NULL,
      run_id INTEGER,
      stage TEXT NOT NULL,
      artifact_type TEXT NOT NULL,
      path TEXT NOT NULL,
      metadata_json TEXT NOT NULL,
      recorded_at TEXT NOT NULL,
      FOREIGN KEY(candidate_id) REFERENCES candidates(candidate_id),
      FOREIGN KEY(run_id) REFERENCES runs(run_id)
    )
    """,
    """
    CREATE TABLE IF NOT EXISTS scores (
      score_id INTEGER PRIMARY KEY AUTOINCREMENT,
      candidate_id TEXT NOT NULL,
      run_id INTEGER NOT NULL,
      total_score REAL NOT NULL,
      breakdown_json TEXT NOT NULL,
      metrics_json TEXT NOT NULL,
      created_at TEXT NOT NULL,
      FOREIGN KEY(candidate_id) REFERENCES candidates(candidate_id),
      FOREIGN KEY(run_id) REFERENCES runs(run_id)
    )
    """,
)


class SQLiteStore:
    def __init__(self, db_path: Path | None = None) -> None:
        self.db_path = db_path or DB_PATH

    @contextmanager
    def connect(self) -> Iterator[sqlite3.Connection]:
        VAR_DIR.mkdir(parents=True, exist_ok=True)
        conn = sqlite3.connect(self.db_path)
        conn.row_factory = sqlite3.Row
        try:
            yield conn
            conn.commit()
        except Exception:
            conn.rollback()
            raise
        finally:
            conn.close()

    def init_db(self) -> None:
        with self.connect() as conn:
            for stmt in SCHEMA_STATEMENTS:
                conn.execute(stmt)

    def candidate_exists(self, candidate_id: str) -> bool:
        with self.connect() as conn:
            row = conn.execute(
                "SELECT 1 FROM candidates WHERE candidate_id = ?",
                (candidate_id,),
            ).fetchone()
        return row is not None

    def register_candidate(self, manifest: CandidateManifest, candidate_dir: Path, registered_at: str) -> None:
        with self.connect() as conn:
            conn.execute(
                """
                INSERT INTO candidates (
                  candidate_id, current_state, manifest_path, candidate_dir, source, created_at,
                  notes, tags_json, manifest_json, registered_at
                ) VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?)
                """,
                (
                    manifest.candidate_id,
                    "registered",
                    str(manifest.manifest_path),
                    str(candidate_dir),
                    manifest.source,
                    manifest.created_at,
                    manifest.notes,
                    json.dumps(manifest.tags),
                    json.dumps(manifest.raw, sort_keys=True),
                    registered_at,
                ),
            )
            for key, value in sorted(manifest.parameters.items()):
                conn.execute(
                    "INSERT INTO candidate_params (candidate_id, param_key, param_value) VALUES (?, ?, ?)",
                    (manifest.candidate_id, key, json.dumps(value)),
                )
            conn.execute(
                """
                INSERT INTO state_transitions (
                  candidate_id, run_id, stage, from_state, to_state, details_json, transitioned_at
                ) VALUES (?, NULL, NULL, NULL, ?, ?, ?)
                """,
                (manifest.candidate_id, "registered", json.dumps({"event": "register"}), registered_at),
            )

    def get_candidate(self, candidate_id: str) -> sqlite3.Row | None:
        with self.connect() as conn:
            return conn.execute(
                "SELECT * FROM candidates WHERE candidate_id = ?",
                (candidate_id,),
            ).fetchone()

    def list_candidates(self) -> list[sqlite3.Row]:
        with self.connect() as conn:
            return conn.execute(
                "SELECT * FROM candidates ORDER BY candidate_id"
            ).fetchall()

    def list_pending_candidates(self, limit: int) -> list[sqlite3.Row]:
        with self.connect() as conn:
            return conn.execute(
                """
                SELECT * FROM candidates
                WHERE current_state = 'registered'
                ORDER BY registered_at, candidate_id
                LIMIT ?
                """,
                (limit,),
            ).fetchall()

    def next_attempt_index(self, candidate_id: str) -> int:
        with self.connect() as conn:
            row = conn.execute(
                "SELECT COALESCE(MAX(attempt_index), 0) AS max_idx FROM runs WHERE candidate_id = ?",
                (candidate_id,),
            ).fetchone()
        return int(row["max_idx"]) + 1

    def create_run(self, candidate_id: str, attempt_index: int, started_at: str, run_dir: Path) -> int:
        with self.connect() as conn:
            cursor = conn.execute(
                """
                INSERT INTO runs (candidate_id, attempt_index, status, started_at, ended_at, run_dir)
                VALUES (?, ?, ?, ?, NULL, ?)
                """,
                (candidate_id, attempt_index, "running", started_at, str(run_dir)),
            )
            return int(cursor.lastrowid)

    def complete_run(self, run_id: int, status: str, ended_at: str) -> None:
        with self.connect() as conn:
            conn.execute(
                "UPDATE runs SET status = ?, ended_at = ? WHERE run_id = ?",
                (status, ended_at, run_id),
            )

    def transition_state(
        self,
        candidate_id: str,
        run_id: int | None,
        stage: str | None,
        from_state: str | None,
        to_state: str,
        details: dict[str, Any],
        transitioned_at: str,
    ) -> None:
        with self.connect() as conn:
            conn.execute(
                "UPDATE candidates SET current_state = ? WHERE candidate_id = ?",
                (to_state, candidate_id),
            )
            conn.execute(
                """
                INSERT INTO state_transitions (
                  candidate_id, run_id, stage, from_state, to_state, details_json, transitioned_at
                ) VALUES (?, ?, ?, ?, ?, ?, ?)
                """,
                (
                    candidate_id,
                    run_id,
                    stage,
                    from_state,
                    to_state,
                    json.dumps(details, sort_keys=True),
                    transitioned_at,
                ),
            )

    def record_artifact(
        self,
        candidate_id: str,
        run_id: int | None,
        stage: str,
        artifact_type: str,
        path: str,
        metadata: dict[str, Any],
        recorded_at: str,
    ) -> None:
        with self.connect() as conn:
            conn.execute(
                """
                INSERT INTO artifacts (
                  candidate_id, run_id, stage, artifact_type, path, metadata_json, recorded_at
                ) VALUES (?, ?, ?, ?, ?, ?, ?)
                """,
                (
                    candidate_id,
                    run_id,
                    stage,
                    artifact_type,
                    path,
                    json.dumps(metadata, sort_keys=True),
                    recorded_at,
                ),
            )

    def record_score(
        self,
        candidate_id: str,
        run_id: int,
        total_score: float,
        breakdown: dict[str, Any],
        metrics: dict[str, Any],
        created_at: str,
    ) -> None:
        with self.connect() as conn:
            conn.execute(
                """
                INSERT INTO scores (
                  candidate_id, run_id, total_score, breakdown_json, metrics_json, created_at
                ) VALUES (?, ?, ?, ?, ?, ?)
                """,
                (
                    candidate_id,
                    run_id,
                    total_score,
                    json.dumps(breakdown, sort_keys=True),
                    json.dumps(metrics, sort_keys=True),
                    created_at,
                ),
            )

    def latest_run(self, candidate_id: str) -> sqlite3.Row | None:
        with self.connect() as conn:
            return conn.execute(
                """
                SELECT * FROM runs
                WHERE candidate_id = ?
                ORDER BY attempt_index DESC
                LIMIT 1
                """,
                (candidate_id,),
            ).fetchone()

    def state_history(self, candidate_id: str) -> list[sqlite3.Row]:
        with self.connect() as conn:
            return conn.execute(
                """
                SELECT * FROM state_transitions
                WHERE candidate_id = ?
                ORDER BY transition_id
                """,
                (candidate_id,),
            ).fetchall()

    def latest_score(self, candidate_id: str) -> sqlite3.Row | None:
        with self.connect() as conn:
            return conn.execute(
                """
                SELECT * FROM scores
                WHERE candidate_id = ?
                ORDER BY score_id DESC
                LIMIT 1
                """,
                (candidate_id,),
            ).fetchone()

