# Architecture Insight Extract

## Baseline Findings

- `mac_baseline_4x4_dw16` to `mac_baseline_8x4_dw16` increases latency from 22 to 38 cycles and LUT from 689 to 1408.
- `mac_baseline_8x8_dw16` extends the same trend to 70 cycles and 2730 LUT.

## Shared Findings

- `mac_shared_4x4_sf2_dw16` lowers DSP from 16 to 8 versus baseline 4x4, but raises latency from 22 to 26 cycles.
- `mac_shared_8x4_sf2_dw16` keeps the same pattern at larger size: DSP 32 to 16, latency 38 to 42 cycles.
- `mac_shared_8x8_sf2_dw16` extends the same tradeoff at the widest bounded point: DSP 64 to 32, latency 70 to 74 cycles, and LUT stays near baseline at 2749.

## Replicated Findings

- `mac_replicated_4x4_c2_dw16` preserves baseline-like latency at 22 cycles but raises LUT to 1212 and DSP to 32.
- `mac_replicated_8x4_c2_dw16` does the same at larger scale: latency stays at 38 cycles while LUT rises to 2453.

## Ranking Robustness Findings

- Official policy order over fully measured canonical candidates: `mac_shared_4x4_sf2_dw16` > `mac_baseline_4x4_dw16` > `mac_replicated_4x4_c2_dw16` > `mac_shared_8x4_sf2_dw16` > `mac_baseline_8x4_dw16` > `mac_shared_8x8_sf2_dw16` > `mac_replicated_8x4_c2_dw16` > `mac_baseline_8x8_dw16`.
- Official ranking disqualifies: `mac_replicated_8x8_c2_dw16`.
- Policy winners: default=`mac_shared_4x4_sf2_dw16`, latency=`mac_shared_4x4_sf2_dw16`, area=`mac_shared_4x4_sf2_dw16`, timing=`mac_replicated_4x4_c2_dw16`, balanced=`mac_shared_4x4_sf2_dw16`.
- The official best candidate is robust across most tested policies, but not all of them.

## Canonical vs Sweep Consistency Findings

- `mac_baseline_4x4_dw16`: Canonical and sweep agree on the overlapping measured metrics.
- `mac_baseline_8x4_dw16`: Canonical and sweep agree on the overlapping measured metrics.
- `mac_baseline_8x8_dw16`: Canonical and sweep agree on the overlapping measured metrics.
- `mac_shared_4x4_sf2_dw16`: Canonical and sweep agree on the overlapping measured metrics.
- `mac_shared_8x4_sf2_dw16`: Canonical and sweep agree on the overlapping measured metrics.
- `mac_shared_8x8_sf2_dw16`: No sweep row present.
- `mac_replicated_4x4_c2_dw16`: Canonical and sweep agree on the overlapping measured metrics.
- `mac_replicated_8x4_c2_dw16`: Canonical and sweep agree on the overlapping measured metrics.
- `mac_replicated_8x8_c2_dw16`: Canonical run preserved synth-only Vivado evidence; stored sweep row should not be treated as equally trustworthy.

## Provisional / Synth-Only Findings

- `mac_replicated_8x8_c2_dw16` produced canonical `synth_only` evidence with implementation_evidence=`synth_only` and score_provisional=`true`.
- The preserved synth-only result still records LUT=41892 and WNS=2.935, which is useful as an implementation-limit signal even though it does not enter the full ranking.

## Current Unknowns / Unresolved Questions

- A fresh full external sweep is still needed to replace the stale-looking `replicated_8x8_c2` implementation row in the sweep table.
- `shared_8x8_sf2` is now a canonical point, but it is still missing from the external bounded sweep matrix and sweep CSV.
- The canonical controller flow still has only one synth-only stress point, so wider implementation-limit frontiers are not yet mapped.

## Single Highest-Value Next Experiment

- Refresh the external bounded sweep with `shared_8x8_sf2` included, then add one more canonical shared-vs-replicated stress pair at `8x8` or `PIPE_STAGES=2` to map where DSP savings stop justifying scheduling overhead.
