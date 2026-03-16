# Sweep Summary

Perf only: no

| candidate | variant | ARRAY_M | ARRAY_N | CLUSTER_SIZE | SHARE_FACTOR | physical_pe_count | shadow_pe_count | total_compute_steps | latency_cycles | latency_time_ms | lut | ff | dsp | bram | wns_ns | fmax_mhz_est | status | ranking_note |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
| baseline_4x4 | baseline | 4 | 4 | 4 | 1 | 16 | 0 | 4 | 22 | 0.00022 | None | 1068.0 | 16.0 | 0.0 | 3.028 | 143.4308663224326 | passed_all | fastest, area-light, timing-clean best |
| baseline_8x4 | baseline | 8 | 4 | 4 | 1 | 32 | 0 | 4 | 38 | 0.00038 | None | 2152.0 | 32.0 | 0.0 | 2.851 | 139.87970345502868 | passed_all |  |
| baseline_8x8 | baseline | 8 | 8 | 4 | 1 | 64 | 0 | 4 | 70 | 0.0007 | None | 4206.0 | 64.0 | 0.0 | 1.49 | 117.50881316098707 | passed_all |  |
| shared_4x4_sf2 | shared | 4 | 4 | 4 | 2 | 8 | 0 | 8 | 26 | 0.00026 | None | 1069.0 | 8.0 | 0.0 | 2.024 | 125.37612838515547 | passed_all |  |
| shared_8x4_sf2 | shared | 8 | 4 | 4 | 2 | 16 | 0 | 8 | 42 | 0.00042 | None | 2152.0 | 16.0 | 0.0 | 1.477 | 117.32957878681216 | passed_all |  |
| replicated_4x4_c2 | replicated | 4 | 4 | 2 | 1 | 16 | 16 | 4 | 22 | 0.00022 | None | 1068.0 | 32.0 | 0.0 | 4.034 | 167.61649346295675 | passed_all |  |
| replicated_8x4_c2 | replicated | 8 | 4 | 2 | 1 | 32 | 32 | 4 | 38 | 0.00038 | None | 2152.0 | 64.0 | 0.0 | 2.435 | 132.18770654329148 | passed_all |  |
| replicated_8x8_c2 | replicated | 8 | 8 | 2 | 1 | 64 | 64 | 4 | 70 | 0.0007 | None | 40.0 | 0.0 | 0.0 | 6.263 | 267.5943270002676 | passed_perf_synth_only | most replicated |
