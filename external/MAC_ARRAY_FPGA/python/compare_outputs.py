#!/usr/bin/env python3
"""Compare a hardware output .mem file against the expected golden output."""

from __future__ import annotations

import argparse
from pathlib import Path


def load_tokens(path: Path) -> list[str]:
    return [line.strip().lower() for line in path.read_text().splitlines() if line.strip()]


def main() -> int:
    parser = argparse.ArgumentParser()
    parser.add_argument("--actual", type=Path, required=True)
    parser.add_argument("--expected", type=Path, required=True)
    args = parser.parse_args()

    actual = load_tokens(args.actual)
    expected = load_tokens(args.expected)

    if len(actual) != len(expected):
        print(f"size mismatch: actual={len(actual)} expected={len(expected)}")
        return 2

    for idx, (lhs, rhs) in enumerate(zip(actual, expected)):
        if lhs != rhs:
            print(f"mismatch at index {idx}: actual={lhs} expected={rhs}")
            return 3

    print("outputs_match=1")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
