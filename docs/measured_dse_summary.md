# Measured DSE Summary

This note summarizes the currently measured design-space exploration points available in `rtl_agent_loop` from existing implementation and Verilator performance artifacts.

Source of truth for the table below:

- candidate manifests under `runs/<candidate_id>/candidate_manifest.json`
- Vivado metrics JSON under each candidate's measured implementation artifact root
- Verilator result JSON under each candidate's measured performance artifact root

No values below are inferred where an artifact is missing.

## Comparison Table

| candidate_id | DENSE_OUT_PAR | DATA_WIDTH | FRAC_BITS | LUT | FF | DSP | BRAM | WNS (ns) | est. Fmax (MHz) | latency_cycles | throughput_inferences_per_sec |
|---|---:|---:|---:|---:|---:|---:|---:|---:|---:|---:|---:|
| `dense1_dw12_fb6_base` | 1 | 12 | 6 | 2654 | 907 | 5 | 5.0 | 0.076 | 100.766 | 465732 | 214.716 |
| `dense2_dw12_fb6_base` | 2 | 12 | 6 | 4397 | 981 | 7 | 5.0 | -1.431 | 87.481 | 434367 | 230.220 |
| `dense2_dw12_fb6_base_r1` | 2 | 12 | 6 | 4418 | 955 | 9 | 5.0 | -1.805 | 84.710 | 442207 | 226.138 |
| `dense2_dw16_fb7_base` | 2 | 16 | 7 | 4467 | 1093 | 7 | 6.0 | -1.146 | 89.718 | N/A | N/A |

## Interpretation

The current measured frontier is defined by a clear tradeoff between timing closure and throughput.

- `dense1_dw12_fb6_base` is the only measured timing-clean point in this set. It closes at the 100 MHz target with `WNS = +0.076 ns` and also has the smallest measured area footprint.
- `dense2_dw12_fb6_base` improves measured throughput and latency relative to `dense1_dw12_fb6_base`, but it does so at a substantial timing cost, failing timing with `WNS = -1.431 ns`.
- `dense2_dw12_fb6_base_r1` did not improve the measured dense2 tradeoff. It remains timing-failed and is both slower and slightly larger in critical resources than the unrepaired `dense2_dw12_fb6_base` point.
- `dense2_dw16_fb7_base` has implementation data only in the current repo state. It remains timing-failed and cannot be compared on end-to-end measured performance because no Verilator performance artifact is available.

## Candidate-Specific Conclusions

### Why `dense1_dw12_fb6_base` is the best timing-clean baseline

`dense1_dw12_fb6_base` is the best timing-clean baseline because it is the only candidate in this set with positive post-route slack at the 10.0 ns target. It also uses the least measured LUT, DSP, and BRAM among the fully measured points:

- `LUT = 2654`
- `DSP = 5`
- `BRAM = 5.0`
- `WNS = +0.076 ns`

Its drawback is lower measured throughput (`214.716 inf/s`) and higher latency (`465732 cycles`) than the faster dense2 points.

### Why `dense2_dw12_fb6_base` is the best performance point but timing-limited

`dense2_dw12_fb6_base` is the strongest measured performance point in the current set:

- `latency_cycles = 434367`
- `throughput_inferences_per_sec = 230.220`

That performance gain comes with a clear timing penalty:

- `WNS = -1.431 ns`
- `est. Fmax = 87.481 MHz`

It is therefore the best measured performance point under reduced precision, but it is not timing-clean at the current target clock.

### Why `dense2_dw12_fb6_base_r1` was not a successful repair

The `dense2_dw12_fb6_base_r1` repair attempt did not improve the measured result relative to `dense2_dw12_fb6_base`.

Measured comparison versus the unrepaired dense2 point:

- timing worsened: `WNS -1.805 ns` vs `-1.431 ns`
- estimated Fmax dropped: `84.710 MHz` vs `87.481 MHz`
- latency increased: `442207 cycles` vs `434367 cycles`
- throughput decreased: `226.138 inf/s` vs `230.220 inf/s`
- DSP use increased: `9` vs `7`

On the measured data currently available, this repair did not recover timing and also regressed the original dense2 performance/resource balance.

## Artifact Notes

- `dense1_dw12_fb6_base`, `dense2_dw12_fb6_base`, and `dense2_dw12_fb6_base_r1` each have both measured implementation and measured Verilator performance artifacts available in the current workspace.
- `dense2_dw16_fb7_base` currently has measured implementation artifacts only. Performance entries are marked `N/A` because no measured Verilator result artifact is present in the repo state used for this summary.
