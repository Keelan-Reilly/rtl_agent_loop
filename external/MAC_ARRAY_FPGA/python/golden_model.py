#!/usr/bin/env python3
"""Deterministic fixed-point GEMM reference model."""

from __future__ import annotations

from dataclasses import dataclass
from typing import Iterable, Sequence


@dataclass(frozen=True)
class GemmConfig:
    array_m: int = 4
    array_n: int = 4
    tile_k: int = 4
    data_width: int = 16
    frac_bits: int = 8
    acc_width: int = 32


def sign_extend(value: int, bits: int) -> int:
    mask = (1 << bits) - 1
    value &= mask
    sign_bit = 1 << (bits - 1)
    return (value ^ sign_bit) - sign_bit


def quantize_signed(value: float, frac_bits: int, width: int) -> int:
    scaled = int(round(value * (1 << frac_bits)))
    return sign_extend(scaled, width)


def to_twos_hex(value: int, width: int) -> str:
    mask = (1 << width) - 1
    return f"{value & mask:0{width // 4}x}"


def reshape(flat_values: Sequence[int], rows: int, cols: int) -> list[list[int]]:
    if len(flat_values) != rows * cols:
      raise ValueError(f"expected {rows * cols} values, got {len(flat_values)}")
    return [list(flat_values[row * cols:(row + 1) * cols]) for row in range(rows)]


def fixed_point_gemm(a: Sequence[Sequence[int]], b: Sequence[Sequence[int]], cfg: GemmConfig) -> list[list[int]]:
    outputs = [[0 for _ in range(cfg.array_n)] for _ in range(cfg.array_m)]
    for row in range(cfg.array_m):
        for col in range(cfg.array_n):
            accum = 0
            for k_idx in range(cfg.tile_k):
                product = a[row][k_idx] * b[k_idx][col]
                accum += product >> cfg.frac_bits
            outputs[row][col] = sign_extend(accum, cfg.acc_width)
    return outputs


def flatten(matrix: Sequence[Sequence[int]]) -> list[int]:
    return [value for row in matrix for value in row]


def mem_lines(values: Iterable[int], width: int) -> list[str]:
    return [to_twos_hex(value, width) for value in values]


if __name__ == "__main__":
    cfg = GemmConfig()
    example_a = [
        [quantize_signed(0.5, cfg.frac_bits, cfg.data_width), quantize_signed(-0.25, cfg.frac_bits, cfg.data_width), quantize_signed(0.75, cfg.frac_bits, cfg.data_width), quantize_signed(0.125, cfg.frac_bits, cfg.data_width)],
        [quantize_signed(-0.5, cfg.frac_bits, cfg.data_width), quantize_signed(0.5, cfg.frac_bits, cfg.data_width), quantize_signed(0.25, cfg.frac_bits, cfg.data_width), quantize_signed(-0.125, cfg.frac_bits, cfg.data_width)],
        [quantize_signed(0.25, cfg.frac_bits, cfg.data_width), quantize_signed(0.75, cfg.frac_bits, cfg.data_width), quantize_signed(-0.5, cfg.frac_bits, cfg.data_width), quantize_signed(0.5, cfg.frac_bits, cfg.data_width)],
        [quantize_signed(1.0, cfg.frac_bits, cfg.data_width), quantize_signed(-0.5, cfg.frac_bits, cfg.data_width), quantize_signed(0.25, cfg.frac_bits, cfg.data_width), quantize_signed(-0.25, cfg.frac_bits, cfg.data_width)],
    ]
    example_b = [
        [quantize_signed(0.5, cfg.frac_bits, cfg.data_width), quantize_signed(0.25, cfg.frac_bits, cfg.data_width), quantize_signed(-0.5, cfg.frac_bits, cfg.data_width), quantize_signed(1.0, cfg.frac_bits, cfg.data_width)],
        [quantize_signed(-0.75, cfg.frac_bits, cfg.data_width), quantize_signed(0.5, cfg.frac_bits, cfg.data_width), quantize_signed(0.125, cfg.frac_bits, cfg.data_width), quantize_signed(-0.25, cfg.frac_bits, cfg.data_width)],
        [quantize_signed(0.25, cfg.frac_bits, cfg.data_width), quantize_signed(-0.5, cfg.frac_bits, cfg.data_width), quantize_signed(0.75, cfg.frac_bits, cfg.data_width), quantize_signed(0.5, cfg.frac_bits, cfg.data_width)],
        [quantize_signed(0.125, cfg.frac_bits, cfg.data_width), quantize_signed(0.25, cfg.frac_bits, cfg.data_width), quantize_signed(-0.25, cfg.frac_bits, cfg.data_width), quantize_signed(0.5, cfg.frac_bits, cfg.data_width)],
    ]
    expected = fixed_point_gemm(example_a, example_b, cfg)
    print("\n".join(mem_lines(flatten(expected), cfg.acc_width)))
