# Sweep Summary

Perf only: no

## Key Findings

- Baseline scaling is monotonic across the bounded study: baseline_4x4=None cycles, baseline_8x4=None cycles, baseline_8x8=None cycles.

## Plots

- [LUT vs latency](./plots/lut_vs_latency_cycles.svg)
- [DSP vs latency](./plots/dsp_vs_latency_cycles.svg)
- [Latency vs physical PE count](./plots/latency_vs_physical_pe_count.svg)
- [Fmax vs LUT](./plots/fmax_vs_lut.svg)

## Detailed Table

| candidate | variant | ARRAY_M | ARRAY_N | CLUSTER_SIZE | SHARE_FACTOR | physical_pe_count | shadow_pe_count | total_compute_steps | latency_cycles | latency_time_ms | lut | ff | dsp | bram | wns_ns | fmax_mhz_est | status | pareto_latency_lut | ranking_note |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
| baseline_4x4 | baseline | 4 | 4 | 4 | 1 | None | None | None | None | None | None | None | None | None | None | None | failed_perf |  |  |
| baseline_8x4 | baseline | 8 | 4 | 4 | 1 | None | None | None | None | None | None | None | None | None | None | None | failed_perf |  |  |
| baseline_8x8 | baseline | 8 | 8 | 4 | 1 | None | None | None | None | None | None | None | None | None | None | None | failed_perf |  |  |
| shared_4x4_sf2 | shared | 4 | 4 | 4 | 2 | None | None | None | None | None | None | None | None | None | None | None | failed_perf |  |  |
| shared_8x4_sf2 | shared | 8 | 4 | 4 | 2 | None | None | None | None | None | None | None | None | None | None | None | failed_perf |  |  |
| replicated_4x4_c2 | replicated | 4 | 4 | 2 | 1 | None | None | None | None | None | None | None | None | None | None | None | failed_perf |  |  |
| replicated_8x4_c2 | replicated | 8 | 4 | 2 | 1 | None | None | None | None | None | None | None | None | None | None | None | failed_perf |  |  |
| replicated_8x8_c2 | replicated | 8 | 8 | 2 | 1 | None | None | None | None | None | None | None | None | None | None | None | failed_perf |  |  |
