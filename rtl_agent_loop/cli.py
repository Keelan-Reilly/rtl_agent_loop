from __future__ import annotations

import argparse
import json
from pathlib import Path

from .config import ValidationError
from .controller import Controller


def build_parser() -> argparse.ArgumentParser:
    parser = argparse.ArgumentParser(description="Deterministic FPGA DSE controller for CNN_FPGA")
    subparsers = parser.add_subparsers(dest="command", required=True)

    subparsers.add_parser("init-db", help="Initialize the SQLite database")

    register_parser = subparsers.add_parser("register", help="Register a candidate manifest")
    register_parser.add_argument("--manifest", required=True, type=Path)

    run_parser = subparsers.add_parser("run", help="Run one registered candidate")
    run_parser.add_argument("--candidate-id", required=True)

    pending_parser = subparsers.add_parser("run-pending", help="Run registered candidates in order")
    pending_parser.add_argument("--limit", type=int, default=1)

    status_parser = subparsers.add_parser("status", help="Show candidate status")
    status_parser.add_argument("--candidate-id", required=True)

    score_parser = subparsers.add_parser("score", help="Compute and print a candidate score")
    score_parser.add_argument("--candidate-id", required=True)
    score_parser.add_argument("--run-dir", type=Path)

    rank_parser = subparsers.add_parser("rank-candidates", help="Rank candidates with measured implementation and performance data")
    rank_parser.add_argument("--markdown-out", type=Path)

    set_best_parser = subparsers.add_parser("set-best-candidates", help="Record the current preferred candidates")
    set_best_parser.add_argument("--best-numeric-score", required=True)
    set_best_parser.add_argument("--best-timing-clean", required=True)

    subparsers.add_parser("show-best-candidates", help="Show the current best-candidate pointer")

    subparsers.add_parser("list-candidates", help="List registered candidates")
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
            result = controller.register_candidate(args.manifest)
            print(json.dumps(result, indent=2))
            return 0
        if args.command == "run":
            result = controller.run_candidate(args.candidate_id)
            print(json.dumps(result, indent=2))
            return 0
        if args.command == "run-pending":
            result = controller.run_pending(args.limit)
            print(json.dumps(result, indent=2))
            return 0
        if args.command == "status":
            result = controller.get_status(args.candidate_id)
            print(json.dumps(result, indent=2))
            return 0
        if args.command == "score":
            result = controller.compute_candidate_score(args.candidate_id, run_dir=args.run_dir)
            print(json.dumps(result, indent=2))
            return 0
        if args.command == "rank-candidates":
            result = controller.rank_candidates(markdown_out=args.markdown_out)
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
            result = controller.list_candidates()
            print(json.dumps(result, indent=2))
            return 0
    except ValidationError as exc:
        parser.exit(status=2, message=f"ERROR: {exc}\n")

    parser.exit(status=2, message=f"ERROR: unknown command {args.command!r}\n")
    return 2
