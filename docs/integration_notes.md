# Integration Notes

This repo now actively targets [`external/MAC_ARRAY_FPGA`](/home/keelan/rtl_agent_loop/external/MAC_ARRAY_FPGA), not the older CNN-oriented flow.

## Active External Boundary

The controller and wrappers currently depend on these external files:

- `hdl/top_level.sv`
- `tb/tb_full_pipeline.cpp`
- `experiments/collect_verilator_perf.py`
- `fpga/vivado/run_batch.sh`
- `fpga/vivado/parse_reports.py`
- `data/input_a.mem`
- `data/input_b.mem`
- `data/expected_output.mem`

## Real Top-Level Parameters

The active searched generics are:

- `ARCH_VARIANT`
- `ARRAY_M`
- `ARRAY_N`
- `CLUSTER_SIZE`
- `SHARE_FACTOR`
- `DATA_WIDTH`
- `FRAC_BITS`
- `ACC_WIDTH`
- `PIPE_STAGES`
- `TILE_K`
- `INPUT_MEM_DEPTH`
- `OUTPUT_MEM_DEPTH`

All three wrapper stages now treat `ARCH_VARIANT` as a real hardware control, not orchestration-only metadata.

## Partial Vivado Outcomes

The external study flow can preserve synth-stage metrics even when implementation fails.

Current behavior split:

- the external bounded sweep records synth-only rows such as `passed_perf_synth_only`
- the controller Vivado wrapper now preserves synth-stage metrics in `vivado_result.json`
- controller stage success still requires a true full pass; synth-only outcomes remain explicitly non-passing
- controller ranking/status prefers the newest measurement-usable Vivado evidence, even if that newest evidence is synth-only rather than a stale older full implementation run

This is intentional. Useful evidence is preserved, but partial outcomes are not mislabeled as full implementation success.

Practical consequence:

- synth-only Vivado evidence is treated as provisional measurement evidence
- it remains scoreable and rankable
- it carries the stage-failed penalty so reports do not blur it with full implementation passes

## `PIPE_STAGES`

`PIPE_STAGES` is a real searched/configured knob and is forwarded through lint, synthesis, and simulation.

Current limitation:

- it still acts more like deterministic drain-latency modeling than a full arithmetic retiming framework

That limitation should be documented honestly in study writeups and candidate notes.

## Legacy Candidate State

Legacy CNN-era manifests remain in `candidates/` for historical context.

Practical consequence:

- they are no longer valid under the active MAC-array schema
- `list-candidates --active-schema-only` and `rank-candidates --active-schema-only` should be preferred for current studies
- `./scripts/bootstrap_active_mac_candidates.sh` provides a deterministic way to register the checked-in MAC manifests before controller-owned runs are created
