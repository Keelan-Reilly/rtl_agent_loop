# Integration Notes

This repo intentionally stops short of inventing `CNN_FPGA`-specific details that are not yet fixed. The current v1 skeleton is runnable, but these integration points still need to be finalized for a production flow.

## External repo path

- Default path: `external/CNN_FPGA`
- Source of truth: `config/search_space.json`
- TODO: decide whether this remains a submodule path or becomes a user-supplied checkout path in CI and multi-machine setups.

## Fast verification gate

- Current wrapper now performs a real candidate-aware Verilator lint pass against `external/CNN_FPGA/hdl/*.sv`.
- It also checks:
  - `top_level.sv`
  - `tb/tb_full_pipeline.cpp`
  - `weights/input_image.mem`
  - Vivado and Verilator helper scripts
- The lint gate validates the actual searched generics currently exposed by `top_level`: `DATA_WIDTH`, `FRAC_BITS`, and `DENSE_OUT_PAR`.
- TODO: decide whether to keep lint-only as the v1 gate or replace it with a lightweight compile/regression target later.

## `CONV_VARIANT`

- `CONV_VARIANT` is accepted, validated, stored, and passed through the orchestration layer.
- The current external repo does not expose a visible synthesis generic for this flag.
- TODO: decide whether this becomes:
  - a synthesis generic
  - a generated include/config file
  - a branch/patch selection hook

Until then, wrappers record the selected value but do not mutate external RTL.

## Vivado batch flow

- Current wrapper targets `external/CNN_FPGA/fpga/vivado/run_batch.sh`
- Report parsing targets `external/CNN_FPGA/fpga/vivado/parse_reports.py`
- Defaults in config assume:
  - part: `xc7a35tcpg236-1`
  - top: `top_level`
  - xdc: `CNN_constraints.xdc`
  - target clock: `10.0ns`
- TODO: confirm these remain valid for your intended board and branch.

## Verilator performance flow

- Current wrapper targets `external/CNN_FPGA/experiments/collect_verilator_perf.py`
- That flow depends on dataset files and any external weight/image prerequisites expected by `CNN_FPGA`.
- The current external script does not accept dataset path CLI flags; it reads `weights/input_image.mem` directly.
- `config/search_space.json` still carries `images_path` and `labels_path` placeholders for future wiring, but they are not active in v1.
- TODO: confirm data path strategy:
  - checked into external repo
  - generated on demand
  - configured through environment or local machine path

## Logging and artifacts

- All controller-owned metadata goes into `var/rtl_agent_loop.db`
- Candidate-owned artifacts live under `runs/<candidate_id>/`
- TODO: define your preferred artifact retention policy once real sweeps start producing many runs.
