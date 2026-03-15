# rtl_agent_loop

`rtl_agent_loop` is a deterministic orchestration layer for FPGA design-space exploration on top of the external [`CNN_FPGA`](./external/CNN_FPGA) accelerator repo.

The baseline architecture is useful without AI agents:

- register candidate manifests
- run explicit verification and implementation gates
- collect artifacts and metrics
- score and rank candidates
- log experiments and state transitions in SQLite

Future agent workflows can sit on top of this controller by generating manifests, proposing new candidates, or interpreting results. The controller remains the source of truth for execution.

## v1 Scope

The v1 skeleton supports a safe search space over:

- `DENSE_OUT_PAR`
- `DATA_WIDTH`
- `FRAC_BITS`
- `CONV_VARIANT`

Execution is single-process and fail-fast. Each candidate moves through:

1. `registered`
2. `fast_verify_pending`
3. `fast_verify_passed` or `fast_verify_failed`
4. `vivado_pending`
5. `vivado_passed` or `vivado_failed`
6. `perf_pending`
7. `perf_passed` or `perf_failed`
8. `scored`

## Repository Layout

```text
.
├─ config/
│  ├─ score_weights.json
│  └─ search_space.json
├─ docs/
│  └─ integration_notes.md
├─ logs/
├─ runs/
├─ schemas/
│  └─ candidate_manifest.example.json
├─ scripts/
│  ├─ collect_verilator_perf.sh
│  ├─ fast_verify.sh
│  └─ run_vivado_batch.sh
├─ rtl_agent_loop/
│  ├─ __init__.py
│  ├─ __main__.py
│  ├─ cli.py
│  ├─ config.py
│  ├─ controller.py
│  ├─ models.py
│  ├─ paths.py
│  ├─ scoring.py
│  ├─ sqlite_store.py
│  ├─ state_machine.py
│  └─ subprocess_utils.py
└─ external/
   └─ CNN_FPGA/
```

## Architecture

### Deterministic controller

The Python controller owns:

- manifest validation
- candidate state transitions
- subprocess orchestration
- artifact registration
- metrics aggregation
- scoring
- SQLite persistence

### Thin integration wrappers

Shell wrappers in [`scripts/`](./scripts) provide a stable contract to external tools. Each wrapper:

- accepts `--candidate-id <id>` or `--candidate-manifest <path>`
- accepts `--run-dir <dir>`
- accepts `--external-repo <path>` to override the default external checkout
- writes a stage-specific JSON file
- writes a stage-specific log file
- exits non-zero on failure

The wrappers currently target the existing `external/CNN_FPGA` scripts where available.

### External dependency boundary

`external/CNN_FPGA` is treated as an external repo. This project does not copy its RTL or experiment logic. Integration points are intentionally explicit in config and wrapper TODOs.

## Candidate Manifest

Candidate manifests are JSON files with this shape:

```json
{
  "candidate_id": "dense2_dw16_fb7_base",
  "source": "manual",
  "created_at": "2026-03-15T00:00:00Z",
  "parameters": {
    "DENSE_OUT_PAR": 2,
    "DATA_WIDTH": 16,
    "FRAC_BITS": 7,
    "CONV_VARIANT": "baseline"
  },
  "notes": "Baseline architecture point for bring-up.",
  "tags": ["baseline", "manual"]
}
```

See [`schemas/candidate_manifest.example.json`](./schemas/candidate_manifest.example.json).

## SQLite Layout

The controller stores state in `var/rtl_agent_loop.db`.

Tables:

- `candidates`
- `candidate_params`
- `runs`
- `state_transitions`
- `artifacts`
- `scores`

This keeps candidate registration separate from per-run execution history.

## Local Setup

Bootstrap a local worktree and validate the environment:

```bash
make setup
```

Override the environment explicitly when needed:

```bash
RTL_AGENT_LOOP_PYTHON=python3.12 \
RTL_AGENT_LOOP_EXTERNAL_REPO=/abs/path/to/CNN_FPGA \
VIVADO_BIN=/tool/Xilinx/2025.2/Vivado/bin/vivado \
make setup
```

Expected environment variables:

- `RTL_AGENT_LOOP_PYTHON`: Python interpreter for controller and task commands.
- `RTL_AGENT_LOOP_EXTERNAL_REPO`: path to the underlying `CNN_FPGA` checkout. Defaults to `external/CNN_FPGA`.
- `VIVADO_BIN`: Vivado executable used by the external batch flow. Defaults to `vivado`.

The bootstrap script is [`scripts/bootstrap_env.sh`](./scripts/bootstrap_env.sh).

## Quickstart

Initialize the database directly:

```bash
python3 -m rtl_agent_loop init-db
```

Register a candidate:

```bash
python3 -m rtl_agent_loop register --manifest schemas/candidate_manifest.example.json
```

Inspect candidates:

```bash
python3 -m rtl_agent_loop list-candidates
python3 -m rtl_agent_loop status --candidate-id dense2_dw16_fb7_base
```

Run one candidate:

```bash
python3 -m rtl_agent_loop run --candidate-id dense2_dw16_fb7_base
```

Run pending candidates:

```bash
python3 -m rtl_agent_loop run-pending --limit 5
```

Compute a candidate score from its latest run:

```bash
python3 -m rtl_agent_loop score --candidate-id dense2_dw16_fb7_base
```

## Stable Task Commands

These `make` targets are intended to be the stable automation interface for Codex worktrees.

Validate Python dependencies and initialize the local database:

```bash
make setup
```

Run fast verification on a candidate:

```bash
make verify_candidate CANDIDATE_ID=dense2_dw16_fb7_base
```

Run Vivado batch for a candidate:

```bash
make implement_candidate CANDIDATE_ID=dense2_dw16_fb7_base
```

Run Verilator performance collection for a candidate:

```bash
make perf_candidate CANDIDATE_ID=dense2_dw16_fb7_base
```

Compute and print a candidate score:

```bash
make score_candidate CANDIDATE_ID=dense2_dw16_fb7_base
```

All task commands also accept explicit path overrides:

```bash
make verify_candidate \
  CANDIDATE_ID=dense2_dw16_fb7_base \
  MANIFEST_PATH=/abs/path/to/candidate_manifest.json \
  RUN_DIR=/abs/path/to/run_dir \
  EXTERNAL_REPO=/abs/path/to/CNN_FPGA
```

## Wrapper Workflow

### `fast_verify.sh`

This is intentionally lightweight but real in v1. It validates the external repo prerequisites, checks that the searched generics exist on the real `top_level` module, and runs a candidate-aware `verilator --lint-only` pass across the external HDL. `CONV_VARIANT` is still orchestration-only until the external RTL exposes a concrete hook.

### `run_vivado_batch.sh`

This wrapper translates manifest parameters into `--generic KEY=VALUE` flags and calls the existing `external/CNN_FPGA/fpga/vivado/run_batch.sh`. It then parses reports using the external report parser.

### `collect_verilator_perf.sh`

This wrapper calls `external/CNN_FPGA/experiments/collect_verilator_perf.py` and captures `performance.json` into the run directory.

## Scoring

Scoring is explicit and config-driven. The controller combines:

- latency and throughput from Verilator performance results
- LUT, FF, DSP, BRAM, and timing metrics from Vivado results
- penalties for timing failure or missing metrics

Weights live in [`config/score_weights.json`](./config/score_weights.json).

## TODO Integration Points

See [`docs/integration_notes.md`](./docs/integration_notes.md) for the unresolved repo-specific details:

- final fast verification command
- any `CONV_VARIANT` generic or patch hook
- Verilator dataset paths
- Vivado environment assumptions

## Agent Layer Later

When you add agents later, they should:

- propose manifests or parameter sweeps
- trigger the deterministic controller
- read SQLite state and artifacts
- use controller outputs as grounded evidence

That keeps the orchestration layer stable whether an experiment is launched by a script, a human, or an agent.
