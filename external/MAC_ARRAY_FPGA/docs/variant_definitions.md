# Variant Definitions

This note records the intended interpretation of the three architecture variants.

## Baseline

`ARCH_VARIANT = 0`

- each logical output lane owns a physical PE
- control advances one `k` step per compute cycle
- minimal operand muxing
- intended as the cleanest timing/control reference

## Shared

`ARCH_VARIANT = 1`

- each cluster instantiates fewer physical PEs than logical lanes
- logical lanes are scheduled onto physical PEs over `SHARE_FACTOR` sub-steps
- cluster logic tracks which logical accumulator each PE result belongs to
- intended hypothesis:
  - lower physical compute footprint
  - higher control and mux cost
  - longer latency
  - potentially worse timing

## Replicated

`ARCH_VARIANT = 2`

- active datapaths follow the baseline mapping
- extra shadow compute is instantiated to increase pressure on resources and routing
- architectural results are still taken from the primary datapaths
- intended hypothesis:
  - similar cycle behavior to baseline
  - higher area
  - timing may improve or worsen depending on clustering and placement effects

## Current Boundaries

- all variants execute the same fixed-point GEMM workload
- all variants use the same input memories and expected output data
- differences are structural and scheduling-related, not algorithmic
- shared mode is currently modeled at cluster scope
- replicated mode duplicates compute structurally but only commits the primary bank
- `PIPE_STAGES` affects deterministic schedule/drain timing, not full arithmetic retiming yet
