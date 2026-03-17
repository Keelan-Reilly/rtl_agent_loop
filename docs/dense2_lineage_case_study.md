# Dense2 Canonical Lineage Case Study

Legacy note: this is a historical CNN-era case study, not the current active MAC-array exploration path.

This note summarizes the canonical parent/child experiment for `dense2_dw12_fb6_base` and `dense2_dw12_fb6_base_r1` using only measured canonical artifacts under `runs/`.

## Candidates

Parent candidate:

- `candidate_id`: `dense2_dw12_fb6_base`
- parameters:
  - `DENSE_OUT_PAR=2`
  - `DATA_WIDTH=12`
  - `FRAC_BITS=6`
  - `CONV_VARIANT=baseline`

Repair child candidate:

- `candidate_id`: `dense2_dw12_fb6_base_r1`
- lineage:
  - parent: `dense2_dw12_fb6_base`
  - revision kind: `timing_repair`
- source manifest parameters:
  - `DENSE_OUT_PAR=2`
  - `DATA_WIDTH=12`
  - `FRAC_BITS=6`
  - `DENSE_SPLIT_MAC_PIPELINE=1`
  - `CONV_VARIANT=baseline`

Repair intent:

- enable the dense split-MAC timing-repair mode through `DENSE_SPLIT_MAC_PIPELINE=1`

## Measured Canonical Comparison

Measured canonical implementation artifacts:

- parent:
  - [vivado_result.json](/home/keelan/rtl_agent_loop/runs/dense2_dw12_fb6_base/attempt_0002/vivado/vivado_result.json)
- child:
  - [vivado_result.json](/home/keelan/rtl_agent_loop/runs/dense2_dw12_fb6_base_r1/attempt_0002/vivado/vivado_result.json)

Measured canonical performance artifacts:

- parent:
  - [verilator_result.json](/home/keelan/rtl_agent_loop/runs/dense2_dw12_fb6_base/attempt_0003/verilator_perf/verilator_result.json)
- child:
  - [verilator_result.json](/home/keelan/rtl_agent_loop/runs/dense2_dw12_fb6_base_r1/attempt_0003/verilator_perf/verilator_result.json)

| candidate_id | LUT | FF | DSP | BRAM | WNS (ns) | est. Fmax (MHz) | latency_cycles | throughput_inf_per_sec |
| --- | ---: | ---: | ---: | ---: | ---: | ---: | ---: | ---: |
| `dense2_dw12_fb6_base` | 4458 | 1117 | 11 | 5.0 | -1.702 | 85.455 | 434367 | 230.220 |
| `dense2_dw12_fb6_base_r1` | 4458 | 1117 | 11 | 5.0 | -1.702 | 85.455 | 434367 | 230.220 |

## Why The Repair Did Not Help

On the measured canonical artifacts currently in the repo, the child candidate did not improve timing, area, or performance relative to the parent. The results are numerically identical.

The artifact record also shows why this happened:

- the measured child Vivado command did not include `DENSE_SPLIT_MAC_PIPELINE=1`
- the measured child Verilator command did not include `DENSE_SPLIT_MAC_PIPELINE=1`

So the canonical measured child runs were recorded before the repair-mode plumbing was connected through the top-level generic path. In other words, the child lineage existed, but the measured canonical implementation did not actually exercise a different dense mode.

## What This Demonstrates

This is still a useful framework result:

- the parent/child relationship was preserved explicitly in the controller and SQLite lineage model
- canonical artifacts remained separated by candidate and run
- ranking exposed that the child candidate was not meaningfully different in measured results
- artifact-level inspection made it possible to diagnose the issue as missing repair-mode plumbing, rather than assuming the repair itself was ineffective

The current canonical evidence therefore supports a narrow conclusion: the first measured `dense2_dw12_fb6_base_r1` lineage experiment did not test a distinct hardware mode, and it should be rerun after the repair-mode generic plumbing fix.
