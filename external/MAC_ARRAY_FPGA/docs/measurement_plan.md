# Measurement Plan

This platform is meant for controlled comparisons across architecture variants and parameter settings.

## Primary Metrics

- `latency_cycles`
  - direct indicator of control complexity and time-multiplexing cost
- `latency_time_ms`
  - cycle count interpreted through the requested clock frequency
- `throughput_ops_per_sec`
  - coarse throughput proxy for bounded GEMM workloads
- `lut`
  - logic growth from control, muxing, and replication
- `ff`
  - pipeline and state overhead
- `dsp`
  - MAC resource scaling across variants
- `bram`
  - storage cost of buffering and future tiling changes
- `wns_ns`
  - timing sensitivity to mux depth, fanout, and replication
- `fmax_mhz_est`
  - frequency estimate derived from WNS and requested clock period

## Expected Hypotheses

- shared mode should reduce active DSP count but worsen latency and often timing
- replicated mode should preserve straightforward control while increasing LUT/DSP/FF use
- baseline should remain the best reference for functional equivalence and implementation sanity

## First-Pass Study Shape

Suggested bounded sweeps:

- vary `ARCH_VARIANT` across baseline/shared/replicated
- vary `ARRAY_M` and `ARRAY_N` together to scale total lanes
- vary `CLUSTER_SIZE` to study aggregation overhead
- vary `SHARE_FACTOR` only in shared mode
- vary `PIPE_STAGES` to observe timing versus cycle tradeoff
- vary `DATA_WIDTH` and `FRAC_BITS` to study arithmetic width cost

## Caveats

- current vectors are fixed to a compact deterministic workload
- current throughput metric is a controlled proxy, not a system-level benchmark
- shared mode models datapath sharing within a cluster rather than a global crossbar design
- `PIPE_STAGES` is currently an honest latency-modeling knob, not a complete MAC retiming implementation
- Vivado memory initialization still depends on repository-local `.mem` files rather than board/software loaders
