# First Bounded Study

This repository is ready for a compact first study that compares the three MAC-array architecture variants under a deterministic workload and fixed-point arithmetic setup.

## Study Matrix

The default bounded sweep covers:

- `baseline_4x4`
- `baseline_8x4`
- `baseline_8x8`
- `shared_4x4_sf2`
- `shared_8x4_sf2`
- `replicated_4x4_c2`
- `replicated_8x4_c2`
- `replicated_8x8_c2`

Defaults:

- `DATA_WIDTH=16`
- `FRAC_BITS=8`
- `ACC_WIDTH=32`
- `TILE_K=4`
- `INPUT_MEM_DEPTH=64`
- `OUTPUT_MEM_DEPTH=64`

## Hypotheses

- baseline should be the cleanest reference for functional equivalence
- shared should reduce active compute duplication but increase latency and mux/control pressure
- replicated should preserve straightforward scheduling while increasing area and routing pressure

## Metrics

Primary metrics:

- `latency_cycles`
- `latency_time_ms`
- `throughput_ops_per_sec`
- `lut`
- `ff`
- `dsp`
- `bram`
- `wns_ns`
- `fmax_mhz_est`

## Running The Study

Perf-only:

```bash
make sweep_perf_only
```

Perf plus Vivado:

```bash
make sweep
```

Outputs:

- `experiments/results/sweep_results.csv`
- `experiments/results/sweep_summary.md`
- `experiments/results/runs/<case_name>/...`

## Remaining Limitations

- `PIPE_STAGES` is a bounded latency-modeling knob, not yet a fully retimed arithmetic pipeline
- shared mode models local cluster sharing rather than a larger fabric
- Vivado uses repository-local `.mem` files; no board-level load path is modeled
- the first sweep is intentionally small and deterministic, not an exhaustive DSE campaign
