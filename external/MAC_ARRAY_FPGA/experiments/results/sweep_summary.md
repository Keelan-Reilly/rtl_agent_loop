# Sweep Summary

Perf only: yes

| candidate | variant | ARRAY_M | ARRAY_N | CLUSTER_SIZE | SHARE_FACTOR | latency_cycles | latency_time_ms | lut | ff | dsp | bram | wns_ns | fmax_mhz_est | status | ranking_note |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
| baseline_4x4 | baseline | 4 | 4 | 4 | 1 | 7 | 7.000000000000001e-05 | None | None | None | None | None | None | passed_perf | fastest, area-light |
| baseline_8x4 | baseline | 8 | 4 | 4 | 1 | 7 | 7.000000000000001e-05 | None | None | None | None | None | None | passed_perf |  |
| baseline_8x8 | baseline | 8 | 8 | 4 | 1 | 7 | 7.000000000000001e-05 | None | None | None | None | None | None | passed_perf |  |
| shared_4x4_sf2 | shared | 4 | 4 | 4 | 2 | 11 | 0.00011 | None | None | None | None | None | None | passed_perf |  |
| shared_8x4_sf2 | shared | 8 | 4 | 4 | 2 | 11 | 0.00011 | None | None | None | None | None | None | passed_perf |  |
| replicated_4x4_c2 | replicated | 4 | 4 | 2 | 1 | 7 | 7.000000000000001e-05 | None | None | None | None | None | None | passed_perf |  |
| replicated_8x4_c2 | replicated | 8 | 4 | 2 | 1 | 7 | 7.000000000000001e-05 | None | None | None | None | None | None | passed_perf |  |
| replicated_8x8_c2 | replicated | 8 | 8 | 2 | 1 | 7 | 7.000000000000001e-05 | None | None | None | None | None | None | passed_perf |  |
