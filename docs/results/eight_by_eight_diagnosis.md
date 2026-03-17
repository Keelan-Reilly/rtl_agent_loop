# 8x8 Diagnosis

## Manifest Check

| candidate_id | source manifest | active schema compatible | note |
| --- | --- | --- | --- |
| `mac_baseline_8x8_dw16` | `candidates/mac_baseline_8x8_dw16.json` | `true` | Existing manifest was valid as-is. |
| `mac_shared_8x8_sf2_dw16` | `candidates/mac_shared_8x8_sf2_dw16.json` | `true` | Added during this diagnosis to complete the bounded 8x8 family. |
| `mac_replicated_8x8_c2_dw16` | `candidates/mac_replicated_8x8_c2_dw16.json` | `true` | Existing manifest was valid as-is. |

## Canonical Outcomes

| candidate_id | canonical run dir | outcome tier | latency_cycles | LUT | DSP | WNS ns | total_score |
| --- | --- | --- | ---: | ---: | ---: | ---: | ---: |
| `mac_baseline_8x8_dw16` | `/home/keelan/rtl_agent_loop/runs/mac_baseline_8x8_dw16/attempt_0001` | `full_pass` | 70 | 2730 | 64 | 1.49 | -64.802 |
| `mac_shared_8x8_sf2_dw16` | `/home/keelan/rtl_agent_loop/runs/mac_shared_8x8_sf2_dw16/attempt_0001` | `full_pass` | 74 | 2749 | 32 | 1.571 | -48.834 |
| `mac_replicated_8x8_c2_dw16` | `/home/keelan/rtl_agent_loop/runs/mac_replicated_8x8_c2_dw16/attempt_0001` | `synth_only` |  | 41892 | 0 | 2.935 | -526.462 |

## What Failed And Why

- `mac_baseline_8x8_dw16`: controller-owned path was already fresh and trustworthy; no rerun was needed.
- `mac_shared_8x8_sf2_dw16`: fast verify, Vivado implementation, Verilator perf, and scoring all passed on the first canonical run.
- `mac_replicated_8x8_c2_dw16`: fast verify passed, synthesis metrics were parsed, then Vivado implementation stopped before placement. The decisive log is in `/home/keelan/rtl_agent_loop/runs/mac_replicated_8x8_c2_dw16/attempt_0001/vivado/batch_run/project/mac_array_project/mac_array_project.runs/impl_1/runme.log` with `DRC UTLZ-1` reporting LUT over-utilization: 39844 required vs 20800 available.
- That replicated 8x8 result is therefore a real target-device implementation limit, not a manifest bug, parser bug, run-dir collision, or controller misclassification.

## Controller Vs Sweep

- `baseline_8x8`: canonical and current sweep row agree exactly on the overlapping measured metrics.
- `shared_8x8_sf2`: there is no current sweep row, so sweep-side comparison is not yet possible.
- `replicated_8x8_c2`: the checked-in sweep row is stale and inconsistent. It still claims `passed_all` with LUT `37.0`, which conflicts with the fresh canonical synth-only evidence and with the sweep summary's own stale-row warning.
- I updated the external sweep matrix definition in `/home/keelan/rtl_agent_loop/external/MAC_ARRAY_FPGA/experiments/sweep_variants.py` so future sweep refreshes include `shared_8x8_sf2`.

## 8x8 Takeaway

- The repo can run the full 8x8 study path across all three architecture families.
- `baseline 8x8` is a clean full-pass reference point.
- `shared 8x8 sf2` is also a clean full-pass point and is the strongest 8x8 measured design under the current score policy because it cuts DSP from 64 to 32 while keeping LUT and timing near baseline.
- `replicated 8x8 c2` is not a hidden repo defect; it hits a real Artix-7 LUT utilization wall during implementation.
- The only repo/tooling gap I found was evidence coverage: `shared 8x8` was missing as a canonical manifest and missing from the external sweep matrix.
