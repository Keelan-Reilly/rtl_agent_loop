#!/usr/bin/env python3
"""Generate deterministic .mem files for bounded MAC-array studies."""

from __future__ import annotations

import argparse
import json
from pathlib import Path

from golden_model import GemmConfig, fixed_point_gemm, flatten, mem_lines, quantize_signed


NONZERO_LEVELS = [-0.875, -0.75, -0.625, -0.5, -0.375, -0.25, 0.25, 0.375, 0.5, 0.625, 0.75, 0.875]


def deterministic_level(row_idx: int, col_idx: int, stride_a: int, stride_b: int) -> float:
    return NONZERO_LEVELS[(row_idx * stride_a + col_idx * stride_b) % len(NONZERO_LEVELS)]


def build_study_matrices(cfg: GemmConfig) -> tuple[list[list[int]], list[list[int]]]:
    if cfg.tile_k != 4:
        raise ValueError("The bounded study vector generator currently supports TILE_K=4.")

    matrix_a = []
    for row_idx in range(cfg.array_m):
        row = []
        for k_idx in range(cfg.tile_k):
            value = deterministic_level(row_idx, k_idx, 5, 3)
            row.append(quantize_signed(value, cfg.frac_bits, cfg.data_width))
        matrix_a.append(row)

    matrix_b = []
    for k_idx in range(cfg.tile_k):
        row = []
        for col_idx in range(cfg.array_n):
            value = deterministic_level(k_idx, col_idx + 1, 7, 4)
            row.append(quantize_signed(value, cfg.frac_bits, cfg.data_width))
        matrix_b.append(row)

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
        "note": "The active ARRAY_M x TILE_K and TILE_K x ARRAY_N regions are fully populated with deterministic nonzero values. Padding is applied only after generating the full active workload.",
    }
    (output_dir / "metadata.json").write_text(json.dumps(metadata, indent=2) + "\n")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
