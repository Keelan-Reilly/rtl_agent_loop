from __future__ import annotations

import json
import sqlite3
import uuid
from contextlib import contextmanager
from pathlib import Path
from typing import Any, Iterator

from .models import CandidateManifest
from .paths import DB_PATH, VAR_DIR
from .state_machine import STAGES


BASE_SCHEMA_STATEMENTS = (
    """
    CREATE TABLE IF NOT EXISTS schema_migrations (
      migration_key TEXT PRIMARY KEY,
      applied_at TEXT NOT NULL
    )
    """,
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
            for stmt in BASE_SCHEMA_STATEMENTS:
                conn.execute(stmt)
            self._apply_migrations(conn)
            self._backfill_run_stages(conn)

    def candidate_exists(self, candidate_id: str) -> bool:
        with self.connect() as conn:
            row = conn.execute(
                "SELECT 1 FROM candidates WHERE candidate_id = ?",
                (candidate_id,),
            ).fetchone()
        return row is not None

    def register_candidate(
        self,
        manifest: CandidateManifest,
        candidate_dir: Path,
        registered_at: str,
        *,
        parent_candidate_id: str | None = None,
        lineage_root_candidate_id: str | None = None,
        revision_kind: str | None = None,
        derived_from_run_id: int | None = None,
        supersedes_candidate_id: str | None = None,
    ) -> None:
        resolved_root = lineage_root_candidate_id or manifest.candidate_id
        with self.connect() as conn:
            conn.execute(
                """
                INSERT INTO candidates (
                  candidate_id, current_state, manifest_path, candidate_dir, source, created_at,
                  notes, tags_json, manifest_json, registered_at, parent_candidate_id,
                  lineage_root_candidate_id, revision_kind, derived_from_run_id, supersedes_candidate_id
                ) VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?)
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
                    parent_candidate_id,
                    resolved_root,
                    revision_kind,
                    derived_from_run_id,
                    supersedes_candidate_id,
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

    def list_candidates(
        self,
        *,
        parent_candidate_id: str | None = None,
        lineage_root_candidate_id: str | None = None,
        leaf_only: bool = False,
    ) -> list[sqlite3.Row]:
        clauses: list[str] = []
        params: list[Any] = []
        if parent_candidate_id is not None:
            clauses.append("parent_candidate_id = ?")
            params.append(parent_candidate_id)
        if lineage_root_candidate_id is not None:
            clauses.append("lineage_root_candidate_id = ?")
            params.append(lineage_root_candidate_id)
        if leaf_only:
            clauses.append(
                "NOT EXISTS (SELECT 1 FROM candidates child WHERE child.parent_candidate_id = candidates.candidate_id)"
            )

        sql = "SELECT * FROM candidates"
        if clauses:
            sql += " WHERE " + " AND ".join(clauses)
        sql += " ORDER BY candidate_id"

        with self.connect() as conn:
            return conn.execute(sql, params).fetchall()

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

    def link_lineage(
        self,
        *,
        parent_candidate_id: str,
        child_candidate_id: str,
        revision_kind: str,
        derived_from_run_id: int | None,
    ) -> None:
        with self.connect() as conn:
            parent = conn.execute(
                "SELECT candidate_id, lineage_root_candidate_id FROM candidates WHERE candidate_id = ?",
                (parent_candidate_id,),
            ).fetchone()
            if parent is None:
                raise ValueError(f"Unknown parent candidate {parent_candidate_id!r}")
            child = conn.execute(
                "SELECT candidate_id FROM candidates WHERE candidate_id = ?",
                (child_candidate_id,),
            ).fetchone()
            if child is None:
                raise ValueError(f"Unknown child candidate {child_candidate_id!r}")
            conn.execute(
                """
                UPDATE candidates
                SET parent_candidate_id = ?,
                    lineage_root_candidate_id = ?,
                    revision_kind = ?,
                    derived_from_run_id = ?
                WHERE candidate_id = ?
                """,
                (
                    parent_candidate_id,
                    parent["lineage_root_candidate_id"],
                    revision_kind,
                    derived_from_run_id,
                    child_candidate_id,
                ),
            )

    def next_attempt_index(self, candidate_id: str) -> int:
        with self.connect() as conn:
            row = conn.execute(
                "SELECT COALESCE(MAX(attempt_index), 0) AS max_idx FROM runs WHERE candidate_id = ?",
                (candidate_id,),
            ).fetchone()
        return int(row["max_idx"]) + 1

    def create_run(
        self,
        candidate_id: str,
        started_at: str,
        candidate_dir: Path,
        *,
        requested_start_stage: str,
        requested_end_stage: str,
        worktree_ref: str | None = None,
    ) -> tuple[int, int, str, Path]:
        owner_token = uuid.uuid4().hex
        with self.connect() as conn:
            conn.execute("BEGIN IMMEDIATE")
            row = conn.execute(
                "SELECT COALESCE(MAX(attempt_index), 0) AS max_idx FROM runs WHERE candidate_id = ?",
                (candidate_id,),
            ).fetchone()
            attempt_index = int(row["max_idx"]) + 1
            run_dir = candidate_dir / f"attempt_{attempt_index:04d}"
            cursor = conn.execute(
                """
                INSERT INTO runs (
                  candidate_id, attempt_index, status, started_at, ended_at, run_dir, owner_token,
                  requested_start_stage, requested_end_stage, worktree_ref
                ) VALUES (?, ?, ?, ?, NULL, ?, ?, ?, ?, ?)
                """,
                (
                    candidate_id,
                    attempt_index,
                    "running",
                    started_at,
                    str(run_dir),
                    owner_token,
                    requested_start_stage,
                    requested_end_stage,
                    worktree_ref,
                ),
            )
            return int(cursor.lastrowid), attempt_index, owner_token, run_dir

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

    def upsert_run_stage(
        self,
        *,
        run_id: int,
        candidate_id: str,
        stage_name: str,
        stage_order: int,
        status: str,
        details: dict[str, Any],
        owner_token: str | None = None,
        started_at: str | None = None,
        ended_at: str | None = None,
        result_path: str | None = None,
        log_path: str | None = None,
    ) -> None:
        with self.connect() as conn:
            existing = conn.execute(
                "SELECT run_stage_id, started_at FROM run_stages WHERE run_id = ? AND stage_name = ?",
                (run_id, stage_name),
            ).fetchone()
            if existing is None:
                conn.execute(
                    """
                    INSERT INTO run_stages (
                      run_id, candidate_id, stage_name, stage_order, status, started_at, ended_at,
                      owner_token, result_path, log_path, details_json
                    ) VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?)
                    """,
                    (
                        run_id,
                        candidate_id,
                        stage_name,
                        stage_order,
                        status,
                        started_at,
                        ended_at,
                        owner_token,
                        result_path,
                        log_path,
                        json.dumps(details, sort_keys=True),
                    ),
                )
                return

            resolved_started = started_at if started_at is not None else existing["started_at"]
            conn.execute(
                """
                UPDATE run_stages
                SET status = ?,
                    started_at = ?,
                    ended_at = ?,
                    owner_token = COALESCE(?, owner_token),
                    result_path = COALESCE(?, result_path),
                    log_path = COALESCE(?, log_path),
                    details_json = ?
                WHERE run_id = ? AND stage_name = ?
                """,
                (
                    status,
                    resolved_started,
                    ended_at,
                    owner_token,
                    result_path,
                    log_path,
                    json.dumps(details, sort_keys=True),
                    run_id,
                    stage_name,
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

    def list_runs(self, candidate_id: str) -> list[sqlite3.Row]:
        with self.connect() as conn:
            return conn.execute(
                """
                SELECT * FROM runs
                WHERE candidate_id = ?
                ORDER BY attempt_index DESC
                """,
                (candidate_id,),
            ).fetchall()

    def get_run(self, run_id: int) -> sqlite3.Row | None:
        with self.connect() as conn:
            return conn.execute(
                "SELECT * FROM runs WHERE run_id = ?",
                (run_id,),
            ).fetchone()

    def list_run_stages(self, run_id: int) -> list[sqlite3.Row]:
        with self.connect() as conn:
            return conn.execute(
                """
                SELECT * FROM run_stages
                WHERE run_id = ?
                ORDER BY stage_order
                """,
                (run_id,),
            ).fetchall()

    def latest_successful_run_stage(self, candidate_id: str, stage_name: str) -> sqlite3.Row | None:
        with self.connect() as conn:
            return conn.execute(
                """
                SELECT * FROM run_stages
                WHERE candidate_id = ?
                  AND stage_name = ?
                  AND status = 'passed'
                  AND result_path IS NOT NULL
                ORDER BY COALESCE(ended_at, '') DESC, run_id DESC
                LIMIT 1
                """,
                (candidate_id, stage_name),
            ).fetchone()

    def list_run_stages_with_results(self, candidate_id: str, stage_name: str) -> list[sqlite3.Row]:
        with self.connect() as conn:
            return conn.execute(
                """
                SELECT * FROM run_stages
                WHERE candidate_id = ?
                  AND stage_name = ?
                  AND result_path IS NOT NULL
                ORDER BY COALESCE(ended_at, '') DESC, run_id DESC
                """,
                (candidate_id, stage_name),
            ).fetchall()

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

    def list_children(self, candidate_id: str) -> list[sqlite3.Row]:
        with self.connect() as conn:
            return conn.execute(
                "SELECT * FROM candidates WHERE parent_candidate_id = ? ORDER BY candidate_id",
                (candidate_id,),
            ).fetchall()

    def _apply_migrations(self, conn: sqlite3.Connection) -> None:
        self._ensure_columns(
            conn,
            "candidates",
            {
                "parent_candidate_id": "TEXT",
                "lineage_root_candidate_id": "TEXT",
                "revision_kind": "TEXT",
                "derived_from_run_id": "INTEGER",
                "supersedes_candidate_id": "TEXT",
            },
        )
        self._ensure_columns(
            conn,
            "runs",
            {
                "owner_token": "TEXT",
                "requested_start_stage": "TEXT",
                "requested_end_stage": "TEXT",
                "worktree_ref": "TEXT",
            },
        )
        conn.execute(
            """
            CREATE TABLE IF NOT EXISTS run_stages (
              run_stage_id INTEGER PRIMARY KEY AUTOINCREMENT,
              run_id INTEGER NOT NULL,
              candidate_id TEXT NOT NULL,
              stage_name TEXT NOT NULL,
              stage_order INTEGER NOT NULL,
              status TEXT NOT NULL,
              started_at TEXT,
              ended_at TEXT,
              owner_token TEXT,
              result_path TEXT,
              log_path TEXT,
              details_json TEXT NOT NULL,
              UNIQUE(run_id, stage_name),
              FOREIGN KEY(candidate_id) REFERENCES candidates(candidate_id),
              FOREIGN KEY(run_id) REFERENCES runs(run_id)
            )
            """
        )
        conn.execute(
            "CREATE UNIQUE INDEX IF NOT EXISTS idx_runs_candidate_attempt ON runs(candidate_id, attempt_index)"
        )
        conn.execute(
            "CREATE INDEX IF NOT EXISTS idx_candidates_parent ON candidates(parent_candidate_id)"
        )
        conn.execute(
            "CREATE INDEX IF NOT EXISTS idx_candidates_root ON candidates(lineage_root_candidate_id)"
        )
        conn.execute(
            "CREATE INDEX IF NOT EXISTS idx_run_stages_run_order ON run_stages(run_id, stage_order)"
        )
        conn.execute(
            "UPDATE candidates SET lineage_root_candidate_id = candidate_id WHERE lineage_root_candidate_id IS NULL"
        )
        conn.execute(
            """
            INSERT OR IGNORE INTO schema_migrations (migration_key, applied_at)
            VALUES ('v2_lineage_and_run_stages', datetime('now'))
            """
        )

    def _ensure_columns(self, conn: sqlite3.Connection, table_name: str, columns: dict[str, str]) -> None:
        existing_columns = {
            row["name"] for row in conn.execute(f"PRAGMA table_info({table_name})").fetchall()
        }
        for column_name, column_type in columns.items():
            if column_name not in existing_columns:
                conn.execute(f"ALTER TABLE {table_name} ADD COLUMN {column_name} {column_type}")

    def _backfill_run_stages(self, conn: sqlite3.Connection) -> None:
        rows = conn.execute("SELECT run_id, candidate_id, status, ended_at FROM runs ORDER BY run_id").fetchall()
        stage_order = {stage.name: index for index, stage in enumerate(STAGES)}
        for run in rows:
            existing = conn.execute(
                "SELECT COUNT(*) AS count FROM run_stages WHERE run_id = ?",
                (run["run_id"],),
            ).fetchone()
            if int(existing["count"]) > 0:
                continue

            for stage in STAGES:
                transitions = conn.execute(
                    """
                    SELECT * FROM state_transitions
                    WHERE run_id = ? AND stage = ?
                    ORDER BY transition_id
                    """,
                    (run["run_id"], stage.name),
                ).fetchall()
                artifacts = conn.execute(
                    """
                    SELECT * FROM artifacts
                    WHERE run_id = ? AND stage = ?
                    ORDER BY artifact_id
                    """,
                    (run["run_id"], stage.name),
                ).fetchall()
                if not transitions and not artifacts:
                    continue

                started_at = None
                ended_at = None
                status = "running"
                details: dict[str, Any] = {"migrated_from_v1": True}

                if transitions:
                    started_at = transitions[0]["transitioned_at"]
                    terminal = transitions[-1]
                    to_state = terminal["to_state"]
                    if to_state == stage.success_state:
                        status = "passed"
                        ended_at = terminal["transitioned_at"]
                    elif to_state == stage.failure_state:
                        status = "failed"
                        ended_at = terminal["transitioned_at"]
                    else:
                        status = "failed" if run["status"] == "failed" else "running"
                        ended_at = run["ended_at"]
                        details["migrated_incomplete"] = True
                elif artifacts:
                    metadata = json.loads(artifacts[0]["metadata_json"])
                    status = "passed" if metadata.get("passed") else "failed"
                    details["migrated_from_artifact_only"] = True
                    ended_at = artifacts[-1]["recorded_at"]

                result_path = None
                log_path = None
                for artifact in artifacts:
                    if artifact["artifact_type"] == "stage_result":
                        result_path = artifact["path"]
                    if artifact["artifact_type"] == "log":
                        log_path = artifact["path"]

                conn.execute(
                    """
                    INSERT OR IGNORE INTO run_stages (
                      run_id, candidate_id, stage_name, stage_order, status, started_at, ended_at,
                      owner_token, result_path, log_path, details_json
                    ) VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?)
                    """,
                    (
                        run["run_id"],
                        run["candidate_id"],
                        stage.name,
                        stage_order[stage.name],
                        status,
                        started_at,
                        ended_at,
                        None,
                        result_path,
                        log_path,
                        json.dumps(details, sort_keys=True),
                    ),
                )
