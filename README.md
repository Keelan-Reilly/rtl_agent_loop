# rtl_agent_loop

`rtl_agent_loop` is a deterministic orchestration layer for FPGA design-space exploration on top of the external [`CNN_FPGA`](./external/CNN_FPGA) accelerator repo.

The baseline architecture is useful without AI agents:

- register candidate manifests
- run explicit verification and implementation gates
- collect artifacts and metrics
- score and rank candidates
- track candidate lineage and per-run stage ownership
- log experiments and state transitions in SQLite

Future agent workflows can sit on top of this controller by generating manifests, proposing new candidates, or interpreting results. The controller remains the source of truth for execution.

## v2 Orchestrator Extensions

The current controller extends the original v1 flow with a minimal v2 orchestration layer:

- revised designs are modeled as child candidates linked to a parent candidate
- every controller invocation creates a fresh owned run under `runs/<candidate_id>/attempt_XXXX/`
- per-run stage status is tracked explicitly in SQLite through `run_stages`
- partial stage execution is supported without mutating older run artifacts

This remains a local deterministic orchestrator. It does not add a scheduler, dashboard, or distributed execution model.

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

## First Case Study

The current measured results already show a useful timing/performance boundary for the dense stage search space.

| candidate_id | DENSE_OUT_PAR | DATA_WIDTH | FRAC_BITS | LUT | FF | DSP | BRAM | WNS (ns) | est. Fmax (MHz) | latency_cycles | throughput_inf_per_sec |
| --- | ---: | ---: | ---: | ---: | ---: | ---: | ---: | ---: | ---: | ---: | ---: |
| `dense1_dw12_fb6_base` | 1 | 12 | 6 | 2654 | 907 | 5 | 5.0 | 0.076 | 100.766 | 465732 | 214.716 |
| `dense2_dw12_fb6_base` | 2 | 12 | 6 | 4397 | 981 | 7 | 5 | -1.431 | 87.481 | 434367 | 230.220 |
| `dense2_dw12_fb6_base_r1` | 2 | 12 | 6 | 4418 | 955 | 9 | 5 | -1.805 | 84.710 | 442207 | 226.138 |
| `dense2_dw16_fb7_base` | 2 | 16 | 7 | 4467 | 1093 | 7 | 6.0 | -1.146 | 89.718 | N/A | N/A |

- `dense1_dw12_fb6_base` is the best timing-clean baseline. It is the only measured point here with positive post-route slack at the 100 MHz target, and it also has the smallest measured area footprint.
- `dense2_dw12_fb6_base` is the best raw performance point in the measured set. It improves latency and throughput over `dense1_dw12_fb6_base`, but it is timing-limited with `WNS = -1.431 ns`.
- `dense2_dw12_fb6_base_r1` was a localized dense MAC split repair attempt. It was not successful: timing worsened, latency increased, throughput dropped, and DSP usage increased relative to the unrepaired `dense2_dw12_fb6_base`.
- This is already a useful outcome for the framework: it separates deployable points from attractive-but-non-closing points, preserves failed repair attempts as evidence, and makes the tradeoff visible from measured artifacts instead of intuition.

## Repository Layout

```text
.
├─ candidates/
├─ config/
│  ├─ score_weights.json
│  └─ search_space.json
├─ docs/
│  └─ integration_notes.md
├─ logs/
├─ prompts/
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

Source candidate manifests should live under [`candidates/`](./candidates) and use the naming convention:

- `candidates/<candidate_id>.json`

Example:

- [`dense1_dw12_fb6_base.json`](./candidates/dense1_dw12_fb6_base.json)

## Manifest And Artifact Conventions

There are three different manifest/artifact locations in the v1 flow:

- Source manifests:
  - human-authored candidate definitions under `candidates/<candidate_id>.json`
- Copied manifests:
  - immutable copies stored under `runs/<candidate_id>/candidate_manifest.json` at registration time
- Run artifacts:
  - stage outputs, logs, and parsed metrics under a run directory such as `runs/<candidate_id>/attempt_0001/`

Temporary external run directories under `/tmp/...` are still supported for bounded local execution and experimentation, but repo-managed `runs/` paths are preferred for long-term project presentation and inspection.

## SQLite Layout

The controller stores state in `var/rtl_agent_loop.db`.

Tables:

- `candidates`
- `candidate_params`
- `runs`
- `run_stages`
- `state_transitions`
- `artifacts`
- `scores`

`candidates` now also stores lineage metadata such as `parent_candidate_id`, `lineage_root_candidate_id`, and `revision_kind`. `run_stages` is the authoritative per-run stage snapshot; `candidates.current_state` remains a backward-compatible summary of the latest run.

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
python3 -m rtl_agent_loop register --manifest candidates/dense1_dw12_fb6_base.json
```

Register a child candidate revision:

```bash
python3 -m rtl_agent_loop register \
  --manifest candidates/dense2_dw12_fb6_base_r1.json \
  --parent-candidate-id dense2_dw12_fb6_base \
  --revision-kind timing_repair
```

Inspect candidates:

```bash
python3 -m rtl_agent_loop list-candidates
python3 -m rtl_agent_loop status --candidate-id dense2_dw16_fb7_base
```

Inspect lineage and run-stage history:

```bash
python3 -m rtl_agent_loop status --candidate-id dense2_dw12_fb6_base_r1 --lineage --runs
python3 -m rtl_agent_loop list-candidates --lineage-root dense2_dw12_fb6_base
```

Run one candidate:

```bash
python3 -m rtl_agent_loop run --candidate-id dense2_dw16_fb7_base
```

Run only one stage range as a fresh owned run:

```bash
python3 -m rtl_agent_loop run \
  --candidate-id dense1_dw12_fb6_base \
  --start-stage fast_verify \
  --end-stage fast_verify \
  --worktree-ref local_debug
```

Run pending candidates:

```bash
python3 -m rtl_agent_loop run-pending --limit 5
```

Compute a candidate score from its latest run:

```bash
python3 -m rtl_agent_loop score --candidate-id dense2_dw16_fb7_base
```

Rank all candidates that have measured implementation and performance artifacts:

```bash
python3 -m rtl_agent_loop rank-candidates
python3 -m rtl_agent_loop rank-candidates --markdown-out docs/latest_ranking.md
python3 -m rtl_agent_loop rank-candidates --lineage-root dense2_dw12_fb6_base --leaf-only
```

Attach known historical lineage without re-registering:

```bash
python3 -m rtl_agent_loop link-lineage \
  --parent-candidate-id dense2_dw12_fb6_base \
  --child-candidate-id dense2_dw12_fb6_base_r1 \
  --revision-kind timing_repair
```

Record and inspect the current preferred candidates:

```bash
python3 -m rtl_agent_loop set-best-candidates \
  --best-numeric-score dense2_dw12_fb6_base \
  --best-timing-clean dense1_dw12_fb6_base

python3 -m rtl_agent_loop show-best-candidates
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

The current preferred-candidate pointer is stored in `var/best_candidates.json` and can distinguish:

- best candidate under the configured numeric score
- best timing-clean candidate

`rank-candidates` recomputes scores from the latest measured artifacts for each registered candidate, ranks only candidates with both implementation and performance data, and marks each ranked entry as `timing_clean` or `timing_failed`.

All task commands also accept explicit path overrides:

```bash
make verify_candidate \
  CANDIDATE_ID=dense2_dw16_fb7_base \
  MANIFEST_PATH=/abs/path/to/candidate_manifest.json \
  RUN_DIR=/abs/path/to/run_dir \
  EXTERNAL_REPO=/abs/path/to/CNN_FPGA
```

If `MANIFEST_PATH` is not provided, `make` now prefers:

1. `candidates/<candidate_id>.json`
2. `runs/<candidate_id>/candidate_manifest.json` as a backward-compatible fallback

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

For canonical controller use, `score` and `rank-candidates` resolve the latest successful candidate-level `vivado` and `verilator_perf` artifacts, even if those artifacts came from different runs.

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

For disciplined parallel worktree usage, see [worktree_operations.md](./docs/worktree_operations.md) and the role prompts under [`prompts/`](./prompts).
