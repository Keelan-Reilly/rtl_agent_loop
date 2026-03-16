#!/usr/bin/env python3
"""Generate deterministic .mem files for bounded MAC-array studies."""

from __future__ import annotations

import argparse
import json
from pathlib import Path

from golden_model import GemmConfig, fixed_point_gemm, flatten, mem_lines, quantize_signed


def base_4x4_operands(cfg: GemmConfig) -> tuple[list[list[int]], list[list[int]]]:
    # The values are hand-picked to exercise positive/negative products while
    # staying comfortably within the default fixed-point range.
    a = [
        [quantize_signed(0.5, cfg.frac_bits, cfg.data_width), quantize_signed(-0.25, cfg.frac_bits, cfg.data_width), quantize_signed(0.75, cfg.frac_bits, cfg.data_width), quantize_signed(0.125, cfg.frac_bits, cfg.data_width)],
        [quantize_signed(-0.5, cfg.frac_bits, cfg.data_width), quantize_signed(0.5, cfg.frac_bits, cfg.data_width), quantize_signed(0.25, cfg.frac_bits, cfg.data_width), quantize_signed(-0.125, cfg.frac_bits, cfg.data_width)],
        [quantize_signed(0.25, cfg.frac_bits, cfg.data_width), quantize_signed(0.75, cfg.frac_bits, cfg.data_width), quantize_signed(-0.5, cfg.frac_bits, cfg.data_width), quantize_signed(0.5, cfg.frac_bits, cfg.data_width)],
        [quantize_signed(1.0, cfg.frac_bits, cfg.data_width), quantize_signed(-0.5, cfg.frac_bits, cfg.data_width), quantize_signed(0.25, cfg.frac_bits, cfg.data_width), quantize_signed(-0.25, cfg.frac_bits, cfg.data_width)],
    ]
    b = [
        [quantize_signed(0.5, cfg.frac_bits, cfg.data_width), quantize_signed(0.25, cfg.frac_bits, cfg.data_width), quantize_signed(-0.5, cfg.frac_bits, cfg.data_width), quantize_signed(1.0, cfg.frac_bits, cfg.data_width)],
        [quantize_signed(-0.75, cfg.frac_bits, cfg.data_width), quantize_signed(0.5, cfg.frac_bits, cfg.data_width), quantize_signed(0.125, cfg.frac_bits, cfg.data_width), quantize_signed(-0.25, cfg.frac_bits, cfg.data_width)],
        [quantize_signed(0.25, cfg.frac_bits, cfg.data_width), quantize_signed(-0.5, cfg.frac_bits, cfg.data_width), quantize_signed(0.75, cfg.frac_bits, cfg.data_width), quantize_signed(0.5, cfg.frac_bits, cfg.data_width)],
        [quantize_signed(0.125, cfg.frac_bits, cfg.data_width), quantize_signed(0.25, cfg.frac_bits, cfg.data_width), quantize_signed(-0.25, cfg.frac_bits, cfg.data_width), quantize_signed(0.5, cfg.frac_bits, cfg.data_width)],
    ]
    return a, b


def build_study_matrices(cfg: GemmConfig) -> tuple[list[list[int]], list[list[int]]]:
    if cfg.tile_k != 4:
        raise ValueError("The bounded study vector generator currently supports TILE_K=4.")

    base_a, base_b = base_4x4_operands(cfg)
    matrix_a = [[0 for _ in range(cfg.tile_k)] for _ in range(cfg.array_m)]
    matrix_b = [[0 for _ in range(cfg.array_n)] for _ in range(cfg.tile_k)]

    for row in range(min(cfg.array_m, 4)):
        for col in range(cfg.tile_k):
            matrix_a[row][col] = base_a[row][col]

    for row in range(cfg.tile_k):
        for col in range(min(cfg.array_n, 4)):
            matrix_b[row][col] = base_b[row][col]

    return matrix_a, matrix_b


def main() -> int:
    parser = argparse.ArgumentParser()
    parser.add_argument("--array-m", type=int, default=4)
    parser.add_argument("--array-n", type=int, default=4)
    parser.add_argument("--tile-k", type=int, default=4)
    parser.add_argument("--data-width", type=int, default=16)
    parser.add_argument("--frac-bits", type=int, default=8)
    parser.add_argument("--acc-width", type=int, default=32)
    parser.add_argument("--input-mem-depth", type=int, default=None)
    parser.add_argument("--output-mem-depth", type=int, default=None)
    parser.add_argument("--output-dir", type=Path, default=Path("data"))
    args = parser.parse_args()

    cfg = GemmConfig(
        array_m=args.array_m,
        array_n=args.array_n,
        tile_k=args.tile_k,
        data_width=args.data_width,
        frac_bits=args.frac_bits,
        acc_width=args.acc_width,
    )
    output_dir = args.output_dir
    output_dir.mkdir(parents=True, exist_ok=True)

    input_mem_depth = args.input_mem_depth or max(cfg.array_m * cfg.tile_k, cfg.array_n * cfg.tile_k)
    output_mem_depth = args.output_mem_depth or (cfg.array_m * cfg.array_n)

    matrix_a, matrix_b = build_study_matrices(cfg)
    expected = fixed_point_gemm(matrix_a, matrix_b, cfg)

    flat_a = flatten(matrix_a)
    flat_b = flatten(matrix_b)
    flat_expected = flatten(expected)

    flat_a.extend([0] * max(0, input_mem_depth - len(flat_a)))
    flat_b.extend([0] * max(0, input_mem_depth - len(flat_b)))
    flat_expected.extend([0] * max(0, output_mem_depth - len(flat_expected)))

    (output_dir / "input_a.mem").write_text("\n".join(mem_lines(flat_a, cfg.data_width)) + "\n")
    (output_dir / "input_b.mem").write_text("\n".join(mem_lines(flat_b, cfg.data_width)) + "\n")
    (output_dir / "expected_output.mem").write_text("\n".join(mem_lines(flat_expected, cfg.acc_width)) + "\n")

    metadata = {
        "description": "Deterministic fixed-point bounded-study vectors for MAC_ARRAY_FPGA.",
        "array_m": cfg.array_m,
        "array_n": cfg.array_n,
        "tile_k": cfg.tile_k,
        "data_width": cfg.data_width,
        "frac_bits": cfg.frac_bits,
        "acc_width": cfg.acc_width,
        "input_mem_depth": input_mem_depth,
        "output_mem_depth": output_mem_depth,
        "note": "Rows and columns beyond the base 4x4 active study region are zero-padded deterministically.",
    }
    (output_dir / "metadata.json").write_text(json.dumps(metadata, indent=2) + "\n")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
