# Architecture

`MAC_ARRAY_FPGA` is organized around a small number of clearly separated modules so that structural tradeoffs are visible in synthesis and simulation artifacts.

## Dataflow

The default workload computes:

- `A[ARRAY_M x TILE_K]`
- `B[TILE_K x ARRAY_N]`
- `C = A x B`

for a deterministic fixed-point operand set loaded from `.mem` files.

At a high level:

1. `control.sv` resets the machine, sequences compute iterations, drains pipeline latency, and triggers the writeback phase.
2. `global_buffer.sv` exposes a simple inferred-memory abstraction for operand storage.
3. `interconnect.sv` maps the current `k` iteration into row/column reads and fans those operands out to logical output lanes.
4. `cluster.sv` groups logical lanes and decides how many physical PE instances exist for the chosen architecture variant.
5. `pe.sv` implements the fixed-point MAC primitive used by each physical datapath.
6. `top_level.sv` wires buffers, control, interconnect, and clusters into a synthesis-friendly top module.

## Variant Behavior

### Baseline

- one physical PE per logical output lane in each cluster
- one MAC update per logical lane per `k` step
- shortest control schedule

### Shared

- fewer physical PEs than logical lanes inside a cluster
- `SHARE_FACTOR` controls how many logical lanes are time-multiplexed onto each physical PE
- cluster-local muxing and lane bookkeeping make control and timing meaningfully more complex

### Replicated

- baseline-style active datapaths remain
- extra shadow PE instances are instantiated and exercised with the same operands
- shadow results are intentionally not committed architecturally, so functionality matches baseline while area and routing pressure increase

## Parameter Notes

- `ARCH_VARIANT` is a real structural control:
  - `0`: one active PE per logical lane
  - `1`: fewer physical PEs plus time-multiplexing
  - `2`: baseline-style active PEs plus extra replicated shadow compute
- `CLUSTER_SIZE` controls the grouping granularity of logical lanes.
- `SHARE_FACTOR` only changes active scheduling in shared mode; other modes can keep it at `1` as a neutral value.
- `PIPE_STAGES` currently increases deterministic control drain latency but does not yet insert a full arithmetic register pipeline.

## Notes

- This repo deliberately avoids DMA, buses, and runtime-programmable memory systems.
- The current implementation targets bounded, repeatable experiments rather than productization.
- The most likely future refinements are richer tiling, deeper pipeline modeling, and better output-buffer organization.
