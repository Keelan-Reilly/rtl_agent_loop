#!/usr/bin/env python3
"""Parse Vivado utilization and timing reports into a stable metrics JSON."""

from __future__ import annotations

import argparse
import json
import re
from pathlib import Path


def find_number(pattern: str, text: str) -> float | None:
    match = re.search(pattern, text, flags=re.MULTILINE)
    if not match:
        return None
    return float(match.group(1).replace(",", ""))


def main() -> int:
    parser = argparse.ArgumentParser()
    parser.add_argument("--reports-dir", type=Path, required=True)
    parser.add_argument("--clock-period-ns", type=float, required=True)
    parser.add_argument("--output", type=Path, required=True)
    args = parser.parse_args()

    reports_dir = args.reports_dir
    util_path = reports_dir / "utilization_impl.rpt"
    timing_path = reports_dir / "timing_impl.rpt"
    if not util_path.exists():
        util_path = reports_dir / "utilization_synth.rpt"
    if not timing_path.exists():
        timing_path = reports_dir / "timing_synth.rpt"

    util_text = util_path.read_text() if util_path.exists() else ""
    timing_text = timing_path.read_text() if timing_path.exists() else ""

    lut = find_number(r"\|\s*Slice LUTs\s*\|\s*([\d,]+)\s*\|", util_text)
    ff = find_number(r"\|\s*Slice Registers\s*\|\s*([\d,]+)\s*\|", util_text)
    dsp = find_number(r"\|\s*DSPs\s*\|\s*([\d,]+)\s*\|", util_text)
    bram = find_number(r"\|\s*Block RAM Tile\s*\|\s*([\d,\.]+)\s*\|", util_text)

    wns = find_number(r"WNS\(ns\):\s*(-?[\d\.]+)", timing_text)
    if wns is None:
        wns = find_number(r"^\s*WNS\s*\(ns\)\s*[: ]\s*(-?[\d\.]+)", timing_text)
    if wns is None:
        wns = find_number(r"^\s*(-?[\d\.]+)\s+[-\d\.]+\s+\d+\s+\d+\s+[-\d\.]+\s+[-\d\.]+\s+\d+\s+\d+", timing_text)
    fmax = (1000.0 / (args.clock_period_ns - wns)) if wns is not None and (args.clock_period_ns - wns) > 0 else None

    payload = {
        "success": util_path.exists() and timing_path.exists(),
        "lut": lut,
        "ff": ff,
        "dsp": dsp,
        "bram": bram,
        "wns_ns": wns,
        "fmax_mhz_est": fmax,
        "utilization_report": str(util_path),
        "timing_report": str(timing_path),
    }
    args.output.write_text(json.dumps(payload, indent=2) + "\n")
    return 0 if payload["success"] else 2


if __name__ == "__main__":
    raise SystemExit(main())
