# Scoring Policy

The v1 score is intended to rank measured architecture points using explicit, inspectable rules rather than hidden heuristics.

## Current Policy

The score combines:

- latency cost from `latency_cycles`
- area costs from `lut`, `ff`, `dsp`, and `bram`
- a small direct timing contribution from `wns_ns`
- explicit penalties for missing timing data, negative timing slack, and stage failure

## Why The Policy Changed

Two practical issues were visible in the measured results:

1. `throughput_inferences_per_sec` and `latency_cycles` were both contributing to the score, even though they are largely redundant in the current flow because throughput is derived from the same measured latency and fixed clock rate.
2. The negative-slack penalty was too small, which allowed a timing-failed point to edge out a timing-clean point on raw performance alone.

## Minimal Policy Update

The updated policy makes two minimal changes:

1. Remove `throughput_inferences_per_sec` from the weighted sum.
2. Increase `timing_negative_wns` from `-25.0` to `-75.0`.

This keeps the scoring simple and explicit while making the ranking better reflect deployable FPGA engineering priorities:

- timing-clean designs are strongly preferred
- latency is counted once
- area tradeoffs remain visible
- timing-failed designs are still comparable, but they pay a much clearer engineering penalty

## Practical Effect

Under this policy, a design that closes timing with slightly worse latency can outrank a faster design that misses timing, which is the intended behavior for selecting the best deployable point.
