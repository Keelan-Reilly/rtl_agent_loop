from __future__ import annotations

import argparse
import json
from pathlib import Path

from .config import ValidationError
from .controller import Controller


def build_parser() -> argparse.ArgumentParser:
    parser = argparse.ArgumentParser(description="Deterministic FPGA DSE controller for external accelerator studies")
    subparsers = parser.add_subparsers(dest="command", required=True)

    subparsers.add_parser("init-db", help="Initialize the SQLite database")

    register_parser = subparsers.add_parser("register", help="Register a candidate manifest")
    register_parser.add_argument("--manifest", required=True, type=Path)
    register_parser.add_argument("--parent-candidate-id")
    register_parser.add_argument("--revision-kind")
    register_parser.add_argument("--derived-from-run-id", type=int)
    register_parser.add_argument("--supersedes-candidate-id")

    run_parser = subparsers.add_parser("run", help="Run one registered candidate")
    run_parser.add_argument("--candidate-id", required=True)
    run_parser.add_argument("--start-stage")
    run_parser.add_argument("--end-stage")
    run_parser.add_argument("--worktree-ref")

    pending_parser = subparsers.add_parser("run-pending", help="Run registered candidates in order")
    pending_parser.add_argument("--limit", type=int, default=1)

    status_parser = subparsers.add_parser("status", help="Show candidate status")
    status_parser.add_argument("--candidate-id", required=True)
    status_parser.add_argument("--lineage", action="store_true")
    status_parser.add_argument("--runs", action="store_true")

    score_parser = subparsers.add_parser("score", help="Compute and print a candidate score")
    score_parser.add_argument("--candidate-id", required=True)
    score_parser.add_argument("--run-dir", type=Path)

    rank_parser = subparsers.add_parser("rank-candidates", help="Rank candidates with measured implementation and performance data")
    rank_parser.add_argument("--markdown-out", type=Path)
    rank_parser.add_argument("--lineage-root")
    rank_parser.add_argument("--latest-only-per-root", action="store_true")
    rank_parser.add_argument("--leaf-only", action="store_true")
    rank_parser.add_argument("--active-schema-only", action="store_true")

    lineage_parser = subparsers.add_parser("link-lineage", help="Attach an existing child candidate to a parent lineage")
    lineage_parser.add_argument("--parent-candidate-id", required=True)
    lineage_parser.add_argument("--child-candidate-id", required=True)
    lineage_parser.add_argument("--revision-kind", required=True)
    lineage_parser.add_argument("--derived-from-run-id", type=int)

    set_best_parser = subparsers.add_parser("set-best-candidates", help="Record the current preferred candidates")
    set_best_parser.add_argument("--best-numeric-score", required=True)
    set_best_parser.add_argument("--best-timing-clean", required=True)

    subparsers.add_parser("show-best-candidates", help="Show the current best-candidate pointer")

    list_parser = subparsers.add_parser("list-candidates", help="List registered candidates")
    list_parser.add_argument("--parent-candidate-id")
    list_parser.add_argument("--lineage-root")
    list_parser.add_argument("--leaf-only", action="store_true")
    list_parser.add_argument("--active-schema-only", action="store_true")
    return parser


def main() -> int:
    parser = build_parser()
    args = parser.parse_args()
    controller = Controller()

    try:
        if args.command == "init-db":
            controller.init_db()
            print("Initialized database at var/rtl_agent_loop.db")
            return 0
        if args.command == "register":
            result = controller.register_candidate(
                args.manifest,
                parent_candidate_id=args.parent_candidate_id,
                revision_kind=args.revision_kind,
                derived_from_run_id=args.derived_from_run_id,
                supersedes_candidate_id=args.supersedes_candidate_id,
            )
            print(json.dumps(result, indent=2))
            return 0
        if args.command == "run":
            result = controller.run_candidate(
                args.candidate_id,
                start_stage=args.start_stage,
                end_stage=args.end_stage,
                worktree_ref=args.worktree_ref,
            )
            print(json.dumps(result, indent=2))
            return 0
        if args.command == "run-pending":
            result = controller.run_pending(args.limit)
            print(json.dumps(result, indent=2))
            return 0
        if args.command == "status":
            result = controller.get_status(args.candidate_id, include_lineage=args.lineage, include_runs=args.runs)
            print(json.dumps(result, indent=2))
            return 0
        if args.command == "score":
            result = controller.compute_candidate_score(args.candidate_id, run_dir=args.run_dir)
            print(json.dumps(result, indent=2))
            return 0
        if args.command == "rank-candidates":
            result = controller.rank_candidates(
                markdown_out=args.markdown_out,
                lineage_root_candidate_id=args.lineage_root,
                latest_only_per_root=args.latest_only_per_root,
                leaf_only=args.leaf_only,
                active_schema_only=args.active_schema_only,
            )
            print(json.dumps(result, indent=2))
            return 0
        if args.command == "link-lineage":
            result = controller.link_lineage(
                parent_candidate_id=args.parent_candidate_id,
                child_candidate_id=args.child_candidate_id,
                revision_kind=args.revision_kind,
                derived_from_run_id=args.derived_from_run_id,
            )
            print(json.dumps(result, indent=2))
            return 0
        if args.command == "set-best-candidates":
            result = controller.set_best_candidates(
                best_numeric_score=args.best_numeric_score,
                best_timing_clean=args.best_timing_clean,
            )
            print(json.dumps(result, indent=2))
            return 0
        if args.command == "show-best-candidates":
            result = controller.get_best_candidates()
            print(json.dumps(result, indent=2))
            return 0
        if args.command == "list-candidates":
            result = controller.list_candidates(
                parent_candidate_id=args.parent_candidate_id,
                lineage_root_candidate_id=args.lineage_root,
                leaf_only=args.leaf_only,
                active_schema_only=args.active_schema_only,
            )
            print(json.dumps(result, indent=2))
            return 0
    except ValidationError as exc:
        parser.exit(status=2, message=f"ERROR: {exc}\n")

    parser.exit(status=2, message=f"ERROR: unknown command {args.command!r}\n")
    return 2
