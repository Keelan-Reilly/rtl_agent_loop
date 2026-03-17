# Canonical MAC Results

| candidate_id | canonical run dir | outcome tier | latency_cycles | lut | dsp | wns_ns | fmax_mhz_est | total_score | score_provisional | implementation_evidence | measurement_quality |
| --- | --- | --- | ---: | ---: | ---: | ---: | ---: | ---: | --- | --- | --- |
| `mac_baseline_4x4_dw16` | `/home/keelan/rtl_agent_loop/runs/mac_baseline_4x4_dw16/attempt_0001` | `full_pass` | 22 | 689 | 16 | 3.028 | 143.431 | -10.992 | `false` | `full_implementation` | `full` |
| `mac_baseline_8x4_dw16` | `/home/keelan/rtl_agent_loop/runs/mac_baseline_8x4_dw16/attempt_0001` | `full_pass` | 38 | 1408 | 32 | 2.851 | 139.88 | -28.72 | `false` | `full_implementation` | `full` |
| `mac_baseline_8x8_dw16` | `/home/keelan/rtl_agent_loop/runs/mac_baseline_8x8_dw16/attempt_0001` | `full_pass` | 70 | 2730 | 64 | 1.49 | 117.509 | -64.802 | `false` | `full_implementation` | `full` |
| `mac_shared_4x4_sf2_dw16` | `/home/keelan/rtl_agent_loop/runs/mac_shared_4x4_sf2_dw16/attempt_0002` | `full_pass` | 26 | 695 | 8 | 2.024 | 125.376 | -9.066 | `false` | `full_implementation` | `full` |
| `mac_shared_8x4_sf2_dw16` | `/home/keelan/rtl_agent_loop/runs/mac_shared_8x4_sf2_dw16/attempt_0001` | `full_pass` | 42 | 1415 | 16 | 1.477 | 117.33 | -23.542 | `false` | `full_implementation` | `full` |
| `mac_shared_8x8_sf2_dw16` | `/home/keelan/rtl_agent_loop/runs/mac_shared_8x8_sf2_dw16/attempt_0001` | `full_pass` | 74 | 2749 | 32 | 1.571 | 118.638 | -48.834 | `false` | `full_implementation` | `full` |
| `mac_replicated_4x4_c2_dw16` | `/home/keelan/rtl_agent_loop/runs/mac_replicated_4x4_c2_dw16/attempt_0001` | `full_pass` | 22 | 1212 | 32 | 4.034 | 167.616 | -22.21 | `false` | `full_implementation` | `full` |
| `mac_replicated_8x4_c2_dw16` | `/home/keelan/rtl_agent_loop/runs/mac_replicated_8x4_c2_dw16/attempt_0001` | `full_pass` | 38 | 2453 | 64 | 2.435 | 132.188 | -56.002 | `false` | `full_implementation` | `full` |
| `mac_replicated_8x8_c2_dw16` | `/home/keelan/rtl_agent_loop/runs/mac_replicated_8x8_c2_dw16/attempt_0001` | `synth_only` |  | 41892 | 0 | 2.935 | 141.543 | -526.462 | `true` | `synth_only` | `provisional_synth_only` |

## Notes

- `mac_baseline_4x4_dw16`: Ranking uses latest available resolved artifacts.
- `mac_baseline_8x4_dw16`: Ranking uses latest available resolved artifacts.
- `mac_baseline_8x8_dw16`: Ranking uses latest available resolved artifacts.
- `mac_shared_4x4_sf2_dw16`: Ranking uses latest available resolved artifacts.
- `mac_shared_8x4_sf2_dw16`: Ranking uses latest available resolved artifacts.
- `mac_shared_8x8_sf2_dw16`: Ranking uses latest available resolved artifacts.
- `mac_replicated_4x4_c2_dw16`: Ranking uses latest available resolved artifacts.
- `mac_replicated_8x4_c2_dw16`: Ranking uses latest available resolved artifacts.
- `mac_replicated_8x8_c2_dw16`: vivado uses synth-only metrics from latest run 37
