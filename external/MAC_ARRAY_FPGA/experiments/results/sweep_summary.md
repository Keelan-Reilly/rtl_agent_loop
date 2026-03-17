# Sweep Summary

Perf only: no

## Key Findings

- Baseline scaling is monotonic across the bounded study: baseline_4x4=22 cycles, baseline_8x4=38 cycles, baseline_8x8=70 cycles.
- Shared mode introduces measurable scheduling overhead: shared_4x4_sf2 adds 4 cycles over baseline_4x4; shared_8x4_sf2 adds 4 cycles over baseline_8x4.
- Some stored implementation rows look stale relative to the current preserved-replication design and should be regenerated with a fresh full sweep: replicated_8x8_c2.
- Latency/LUT Pareto-efficient points in the current table: baseline_4x4, replicated_8x8_c2.

## Data Quality Notes

- Stored implementation rows that look stale relative to the current preserved-replication design: replicated_8x8_c2. Regenerate them with `make -C external/MAC_ARRAY_FPGA sweep` before using the table for claims about implementation-area trends.

## Plots

- [LUT vs latency](./plots/lut_vs_latency_cycles.svg)
- [DSP vs latency](./plots/dsp_vs_latency_cycles.svg)
- [Latency vs physical PE count](./plots/latency_vs_physical_pe_count.svg)
- [Fmax vs LUT](./plots/fmax_vs_lut.svg)

## Detailed Table

| candidate | variant | ARRAY_M | ARRAY_N | CLUSTER_SIZE | SHARE_FACTOR | physical_pe_count | shadow_pe_count | total_compute_steps | latency_cycles | latency_time_ms | lut | ff | dsp | bram | wns_ns | fmax_mhz_est | vivado_report_kind | status | pareto_latency_lut | ranking_note |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
| baseline_4x4 | baseline | 4 | 4 | 4 | 1 | 16 | 0 | 4 | 22 | 0.00022 | 689.0 | 1068.0 | 16.0 | 0.0 | 3.028 | 143.4308663224326 | implementation | passed_all | yes | fastest, timing-clean best |
| baseline_8x4 | baseline | 8 | 4 | 4 | 1 | 32 | 0 | 4 | 38 | 0.00038 | 1408.0 | 2152.0 | 32.0 | 0.0 | 2.851 | 139.87970345502868 | implementation | passed_all | no |  |
| baseline_8x8 | baseline | 8 | 8 | 4 | 1 | 64 | 0 | 4 | 70 | 0.0007 | 2730.0 | 4206.0 | 64.0 | 0.0 | 1.49 | 117.50881316098707 | implementation | passed_all | no |  |
| shared_4x4_sf2 | shared | 4 | 4 | 4 | 2 | 8 | 0 | 8 | 26 | 0.00026 | 695.0 | 1069.0 | 8.0 | 0.0 | 2.024 | 125.37612838515547 | implementation | passed_all | no |  |
| shared_8x4_sf2 | shared | 8 | 4 | 4 | 2 | 16 | 0 | 8 | 42 | 0.00042 | 1415.0 | 2152.0 | 16.0 | 0.0 | 1.477 | 117.32957878681216 | implementation | passed_all | no |  |
| replicated_4x4_c2 | replicated | 4 | 4 | 2 | 1 | 16 | 16 | 4 | 22 | 0.00022 | 1212.0 | 1068.0 | 32.0 | 0.0 | 4.034 | 167.61649346295675 | implementation | passed_all | no |  |
| replicated_8x4_c2 | replicated | 8 | 4 | 2 | 1 | 32 | 32 | 4 | 38 | 0.00038 | 2453.0 | 2152.0 | 64.0 | 0.0 | 2.435 | 132.18770654329148 | implementation | passed_all | no |  |
| replicated_8x8_c2 | replicated | 8 | 8 | 2 | 1 | 64 | 64 | 4 | 70 | 0.0007 | 37.0 | 40.0 | 0.0 | 0.0 | 6.263 | 267.5943270002676 | implementation | passed_all | yes | area-light, most replicated |
