# Repository Design

This document describes the current implementation of `rtl_agent_loop` as it exists in this repository on 2026-03-16. It is intentionally implementation-first: where code, config, generated artifacts, and docs disagree, this note names the mismatch instead of smoothing it over.

## 1. System Purpose

`rtl_agent_loop` is a deterministic orchestration layer for bounded FPGA design-space exploration over an external MAC-array accelerator repository, [`external/MAC_ARRAY_FPGA`](/home/keelan/rtl_agent_loop/external/MAC_ARRAY_FPGA/README.md).

This repository owns:

- candidate manifest validation
- candidate registration and lineage tracking
- deterministic stage execution
- wrapper contracts for fast verification, Vivado, and Verilator performance collection
- run artifact ownership under `runs/`
- score computation and ranking
- SQLite-backed experiment state
- role prompts and operator-facing documentation

This repository does not own the accelerator RTL implementation as a product surface. The external MAC-array repo is the hardware implementation boundary.

## 2. Top-Level Repository Layout

The repo is organized into a few clear ownership zones:

- [`rtl_agent_loop/`](/home/keelan/rtl_agent_loop/rtl_agent_loop): Python controller package
- [`scripts/`](/home/keelan/rtl_agent_loop/scripts): stable wrapper entrypoints used by the controller and [`Makefile`](/home/keelan/rtl_agent_loop/Makefile)
- [`config/`](/home/keelan/rtl_agent_loop/config): search-space and scoring policy JSON
- [`candidates/`](/home/keelan/rtl_agent_loop/candidates): contributor-authored source manifests
- [`runs/`](/home/keelan/rtl_agent_loop/runs): controller-owned manifest copies and per-run artifacts
- [`var/`](/home/keelan/rtl_agent_loop/var): SQLite state and best-candidate pointer JSON
- [`docs/`](/home/keelan/rtl_agent_loop/docs): operator notes, scoring policy, measured summaries, and this design note
- [`prompts/`](/home/keelan/rtl_agent_loop/prompts): role-specific operating prompts
- [`external/MAC_ARRAY_FPGA/`](/home/keelan/rtl_agent_loop/external/MAC_ARRAY_FPGA): active external accelerator dependency
- [`external/CNN_FPGA/`](/home/keelan/rtl_agent_loop/external/CNN_FPGA): historical dependency still present in the workspace, but no longer the default integration target

## 3. Core Execution Model

The implementation centers on a controller class, [`rtl_agent_loop/controller.py`](/home/keelan/rtl_agent_loop/rtl_agent_loop/controller.py), which coordinates five concerns:

1. Load and validate configuration and manifests.
2. Register candidates and copy their manifests into canonical repo-owned locations.
3. Create a fresh owned run directory for every controller execution.
4. Invoke stage wrappers in order and persist stage/run/state metadata.
5. Resolve measured artifacts into scores and rankings.

The system is deterministic in the sense that:

- stage names and order are fixed in code
- every controller-owned run gets a unique `attempt_<n>` directory
- every run gets a unique `owner_token`
- stage transitions are logged in SQLite
- canonical artifacts are never overwritten in-place by later runs

The controller is intentionally single-process and local. There is no queue service, scheduler, dashboard, or distributed worker model.

## 4. State Machine

The stage/state model is defined in [`rtl_agent_loop/state_machine.py`](/home/keelan/rtl_agent_loop/rtl_agent_loop/state_machine.py).

Executable stages:

- `fast_verify`
- `vivado`
- `verilator_perf`

Synthetic controller-only stage:

- `scoring`

Candidate summary states:

- `registered`
- `fast_verify_pending`
- `fast_verify_passed`
- `fast_verify_failed`
- `vivado_pending`
- `vivado_passed`
- `vivado_failed`
- `perf_pending`
- `perf_passed`
- `perf_failed`
- `scored`

Important implementation details:

- `candidates.current_state` is only a summary of the latest transition.
- `run_stages` is the authoritative per-run stage snapshot.
- Partial runs mark unrequested stages as `skipped`.
- A failed executable stage causes remaining selected stages to be marked `skipped`.
- A run with only a bounded stage window, such as `fast_verify` only, ends with run status `partial` rather than `completed`.

Stage range handling is implemented by `normalize_stage_range()`. If the caller omits both bounds, the controller runs the full range from `fast_verify` through `scoring`.

## 5. Python Package Design

### 5.1 Package entrypoints

[`rtl_agent_loop/__main__.py`](/home/keelan/rtl_agent_loop/rtl_agent_loop/__main__.py) is the module entrypoint and simply dispatches to CLI `main()`.

[`rtl_agent_loop/__init__.py`](/home/keelan/rtl_agent_loop/rtl_agent_loop/__init__.py) exposes `__version__ = "0.1.0"`.

[`pyproject.toml`](/home/keelan/rtl_agent_loop/pyproject.toml) defines a minimal setuptools package with `requires-python = ">=3.12"`.

### 5.2 CLI layer

[`rtl_agent_loop/cli.py`](/home/keelan/rtl_agent_loop/rtl_agent_loop/cli.py) uses `argparse` and exposes these implemented subcommands:

- `init-db`
- `register`
- `run`
- `run-pending`
- `status`
- `score`
- `rank-candidates`
- `link-lineage`
- `set-best-candidates`
- `show-best-candidates`
- `list-candidates`

CLI behavior is thin by design:

- parse arguments
- instantiate `Controller()`
- call the corresponding controller method
- print JSON to stdout
- convert `ValidationError` into exit status `2`

This module does not implement business logic itself.

### 5.3 Controller

[`rtl_agent_loop/controller.py`](/home/keelan/rtl_agent_loop/rtl_agent_loop/controller.py) is the orchestration core.

Its constructor loads:

- the SQLite store
- the active search-space config
- the active scoring config

Key public methods:

- `init_db()`: initializes the database and applies migrations/backfills
- `register_candidate()`: validates a manifest, writes the canonical manifest copy under `runs/<candidate_id>/candidate_manifest.json`, and inserts the candidate plus lineage metadata into SQLite
- `run_candidate()`: creates a new owned run and executes the selected stage window
- `run_pending()`: finds `registered` candidates and runs them
- `get_status()`: returns candidate, latest run, state history, optional lineage, and optional run details
- `list_candidates()`: filterable listing by parent/root/leaf status
- `compute_candidate_score()`: computes a score either from an explicit run dir or by resolving the latest successful canonical artifacts
- `rank_candidates()`: resolves scoreable artifacts for many candidates, disqualifies incomplete ones, sorts by numeric score, and optionally writes a Markdown report
- `link_lineage()`: attaches an already-registered child candidate to a parent
- `set_best_candidates()` and `get_best_candidates()`: maintain a small JSON pointer in `var/best_candidates.json`

The most important internal helpers are:

- `_run_stage()`: maps stage names to wrapper scripts, captures a controller command log, loads the stage JSON, and normalizes missing-result failures
- `_resolve_candidate_stage_artifacts()`: chooses the latest successful `vivado` and `verilator_perf` artifacts per candidate, unless the current run already produced a passing payload
- `_score_candidate_from_resolved_artifacts()`: scores from resolved artifacts and optionally applies the stage-failure penalty
- `_selected_stage_names()`: expands a stage range into concrete stage names
- `_latest_candidate_per_root()`: implements `--latest-only-per-root` ranking behavior

Important design choice:

- scoring is artifact-resolution based, not latest-run based

That means a candidate can currently be in a pending or failed summary state and still rank successfully if older passing canonical artifacts exist.

## 6. Active Search Space And Manifest Validation

[`rtl_agent_loop/config.py`](/home/keelan/rtl_agent_loop/rtl_agent_loop/config.py) handles:

- generic JSON loading
- config loading for search space and weights
- manifest validation against the active search-space schema

[`rtl_agent_loop/models.py`](/home/keelan/rtl_agent_loop/rtl_agent_loop/models.py) now defines MAC-array-era parameter constants rather than CNN-era ones.

Current required searched parameters are:

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

There are currently no optional searched parameters in the active schema.

Validation rules include:

- top-level required fields must exist
- `candidate_id` must be a non-empty string
- `parameters` must be an object
- unsupported parameter keys are rejected
- all required parameters must be integers inside the allowed sets in [`config/search_space.json`](/home/keelan/rtl_agent_loop/config/search_space.json)
- `ARCH_VARIANT` must be one of `{0, 1, 2}`
- `FRAC_BITS` must be strictly less than `DATA_WIDTH`
- `ACC_WIDTH` must be strictly greater than `DATA_WIDTH`
- `SHARE_FACTOR` must be `1` for baseline and replicated variants
- shared variants require `SHARE_FACTOR >= 2`
- `CLUSTER_SIZE` must be `<= max(ARRAY_M, ARRAY_N)`
- `INPUT_MEM_DEPTH` must cover the active `A` and `B` operand footprints implied by `ARRAY_M`, `ARRAY_N`, and `TILE_K`
- `OUTPUT_MEM_DEPTH` must cover the active `ARRAY_M * ARRAY_N` output tile
- `tags` must be a list of strings

The validator returns a [`CandidateManifest`](/home/keelan/rtl_agent_loop/rtl_agent_loop/models.py) dataclass, not a raw dict.

## 7. Active Configuration Files

### 7.1 Search space

[`config/search_space.json`](/home/keelan/rtl_agent_loop/config/search_space.json) now points to the MAC-array repo and defines the active bounded study space.

Current allowed parameter values are:

- `ARCH_VARIANT`: `[0, 1, 2]`
- `ARRAY_M`: `[4, 8]`
- `ARRAY_N`: `[4, 8]`
- `CLUSTER_SIZE`: `[1, 2, 4]`
- `SHARE_FACTOR`: `[1, 2]`
- `DATA_WIDTH`: `[12, 16]`
- `FRAC_BITS`: `[6, 8]`
- `ACC_WIDTH`: `[24, 32]`
- `PIPE_STAGES`: `[1, 2]`
- `TILE_K`: `[4]`
- `INPUT_MEM_DEPTH`: `[16, 64]`
- `OUTPUT_MEM_DEPTH`: `[16, 64]`

Current default integration settings are:

- external repo path: `external/MAC_ARRAY_FPGA`
- global clock: `100000000 Hz`
- Vivado top: `top_level`
- Vivado part: `xc7a35tcpg236-1`
- Vivado XDC: `fpga/vivado/constraints/mac_array_constraints.xdc`
- Verilator top: `top_level`
- fast verify mode: `verilator_lint`

The current fast-verify TODO explicitly documents that `PIPE_STAGES` is still a bounded latency-modeling knob rather than a fully retimed arithmetic pipeline.

### 7.2 Score weights

[`config/score_weights.json`](/home/keelan/rtl_agent_loop/config/score_weights.json) still defines the controller ranking policy. The active score remains primarily latency/area/timing driven rather than throughput driven.

## 8. Scoring

[`rtl_agent_loop/scoring.py`](/home/keelan/rtl_agent_loop/rtl_agent_loop/scoring.py) converts raw Vivado and Verilator payload metrics into:

- flattened numeric metrics
- a weighted numeric score
- a contribution breakdown
- missing-metric tracking

Flattened Vivado metrics:

- `lut`
- `ff`
- `dsp`
- `bram`
- `wns_ns`
- `fmax_mhz_est`

Flattened performance metrics:

- `latency_cycles`
- `latency_time_ms`
- `throughput_inferences_per_sec`

Important current mismatch:

- the MAC-array external repo emits `throughput_ops_per_sec`
- the controller scoring code still looks for `throughput_inferences_per_sec`
- the active weights do not currently depend on throughput, so this mismatch does not affect the numeric score today, but it is real drift

## 9. SQLite Store

[`rtl_agent_loop/sqlite_store.py`](/home/keelan/rtl_agent_loop/rtl_agent_loop/sqlite_store.py) remains the persistence layer.

It is responsible for:

- schema creation
- additive migrations
- transactional run creation
- candidate inserts
- candidate state transitions
- artifact registration
- score inserts
- per-run stage upserts
- backfilling `run_stages` for older runs

The database file is [`var/rtl_agent_loop.db`](/home/keelan/rtl_agent_loop/var/rtl_agent_loop.db).

`create_run()` still uses `BEGIN IMMEDIATE`, computes `attempt_index` transactionally, allocates `runs/<candidate_id>/attempt_<n>`, and generates a UUID-based `owner_token`.

## 10. Wrapper Script Design

The shell wrappers in [`scripts/`](/home/keelan/rtl_agent_loop/scripts) remain the stable integration surface used by both the controller and the repo-level [`Makefile`](/home/keelan/rtl_agent_loop/Makefile).

Each wrapper:

- accepts `--candidate-id` or `--candidate-manifest`
- requires `--run-dir`
- optionally accepts `--external-repo`
- writes a stage log
- writes a stage result JSON
- exits non-zero on failure

The heavy logic still lives in embedded Python blocks.

### 10.1 `bootstrap_env.sh`

[`scripts/bootstrap_env.sh`](/home/keelan/rtl_agent_loop/scripts/bootstrap_env.sh) now defaults the external repo path to `external/MAC_ARRAY_FPGA`.

It:

- resolves the Python interpreter and external repo path
- checks that Python exists
- checks that the external repo and its `Makefile` exist
- exports `RTL_AGENT_LOOP_PYTHON`
- exports `RTL_AGENT_LOOP_EXTERNAL_REPO`
- exports `VIVADO_BIN` with a default of `vivado`
- prints environment facts
- runs a lightweight stdlib import check
- runs `python -m compileall rtl_agent_loop`
- optionally runs `python -m rtl_agent_loop init-db`

### 10.2 `fast_verify.sh`

[`scripts/fast_verify.sh`](/home/keelan/rtl_agent_loop/scripts/fast_verify.sh) is the fast verification gate for MAC-array candidates.

Implementation details:

- loads [`config/search_space.json`](/home/keelan/rtl_agent_loop/config/search_space.json)
- resolves the manifest from CLI args or canonical controller-owned locations
- resolves the external repo path from args, env, or config default
- reads `external/MAC_ARRAY_FPGA/hdl/top_level.sv`
- parses the `top_level` parameter block with a regex
- checks that every searched generic from the manifest is present in the real top-level parameter list
- performs preflight checks for:
  - external repo existence
  - external `Makefile`
  - `hdl/top_level.sv`
  - `tb/tb_full_pipeline.cpp`
  - `data/input_a.mem`
  - `data/input_b.mem`
  - `data/expected_output.mem`
  - HDL directory
  - Vivado wrapper
  - Verilator perf script
  - local `verilator`
  - local `make`
- in `verilator_lint` mode, runs:
  - `verilator -sv --lint-only -Wall -Wno-fatal ... --top-module top_level`

Important current behavior:

- `ARCH_VARIANT` is a real hardware generic and is linted like the other searched parameters
- `PIPE_STAGES` is also forwarded and linted, but its hardware meaning is still limited compared with a full retiming framework

The output JSON includes:

- `checks`
- `top_level_parameters`
- `command`
- `returncode`
- config `todo`
- relative `log_path`

### 10.3 `run_vivado_batch.sh`

[`scripts/run_vivado_batch.sh`](/home/keelan/rtl_agent_loop/scripts/run_vivado_batch.sh) is the implementation wrapper.

Implementation details:

- loads the manifest
- resolves external repo and Vivado defaults from config
- targets:
  - `external/MAC_ARRAY_FPGA/fpga/vivado/run_batch.sh`
  - `external/MAC_ARRAY_FPGA/fpga/vivado/parse_reports.py`
- creates a wrapper-owned path:
  - `<run_dir>/vivado/batch_run`
- writes parsed metrics to:
  - `<run_dir>/vivado/metrics.json`
- forwards all searched parameters as real Vivado generics, including `ARCH_VARIANT`

Important current limitation:

- the controller wrapper only parses metrics if the external Vivado batch exits success
- by contrast, the external sweep utility can keep synth-stage metrics when implementation fails

The result JSON includes:

- preflight `checks`
- exact `command`
- relative `reports_dir`
- relative `metrics_path`
- parsed `metrics`
- a TODO noting the current `PIPE_STAGES` modeling limit

### 10.4 `collect_verilator_perf.sh`

[`scripts/collect_verilator_perf.sh`](/home/keelan/rtl_agent_loop/scripts/collect_verilator_perf.sh) is the performance wrapper.

Implementation details:

- targets `external/MAC_ARRAY_FPGA/experiments/collect_verilator_perf.py`
- creates:
  - `<run_dir>/verilator_perf/perf_run`
- expects machine-readable output at:
  - `<run_dir>/verilator_perf/perf_run/verilator_perf/performance.json`
- forwards all searched parameters as real simulation generics

The result JSON includes:

- preflight `checks`
- exact `command`
- relative `performance_path`
- parsed `metrics`
- a TODO noting the current `PIPE_STAGES` modeling limit

## 11. External MAC_ARRAY_FPGA Contract

The active external repo is designed as a bounded MAC-array / GEMM-style research platform rather than a CNN accelerator.

The controller and wrappers currently depend on these stable integration points:

- [`external/MAC_ARRAY_FPGA/hdl/top_level.sv`](/home/keelan/rtl_agent_loop/external/MAC_ARRAY_FPGA/hdl/top_level.sv)
- [`external/MAC_ARRAY_FPGA/tb/tb_full_pipeline.cpp`](/home/keelan/rtl_agent_loop/external/MAC_ARRAY_FPGA/tb/tb_full_pipeline.cpp)
- [`external/MAC_ARRAY_FPGA/experiments/collect_verilator_perf.py`](/home/keelan/rtl_agent_loop/external/MAC_ARRAY_FPGA/experiments/collect_verilator_perf.py)
- [`external/MAC_ARRAY_FPGA/fpga/vivado/run_batch.sh`](/home/keelan/rtl_agent_loop/external/MAC_ARRAY_FPGA/fpga/vivado/run_batch.sh)
- [`external/MAC_ARRAY_FPGA/fpga/vivado/parse_reports.py`](/home/keelan/rtl_agent_loop/external/MAC_ARRAY_FPGA/fpga/vivado/parse_reports.py)
- [`external/MAC_ARRAY_FPGA/data/input_a.mem`](/home/keelan/rtl_agent_loop/external/MAC_ARRAY_FPGA/data/input_a.mem)
- [`external/MAC_ARRAY_FPGA/data/input_b.mem`](/home/keelan/rtl_agent_loop/external/MAC_ARRAY_FPGA/data/input_b.mem)
- [`external/MAC_ARRAY_FPGA/data/expected_output.mem`](/home/keelan/rtl_agent_loop/external/MAC_ARRAY_FPGA/data/expected_output.mem)

The MAC-array top level exposes real synthesizable generics for:

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

The external implementation also includes a bounded manual sweep utility:

- [`external/MAC_ARRAY_FPGA/experiments/sweep_variants.py`](/home/keelan/rtl_agent_loop/external/MAC_ARRAY_FPGA/experiments/sweep_variants.py)

That script is not part of the controller execution path, but it is now part of the real repo state and the current study workflow.

## 12. Makefile Surface

[`Makefile`](/home/keelan/rtl_agent_loop/Makefile) remains the stable automation interface called out in repo policy.

Targets:

- `setup`
- `verify_candidate`
- `implement_candidate`
- `perf_candidate`
- `score_candidate`

Important behavior:

- `PYTHON` defaults from `RTL_AGENT_LOOP_PYTHON` or `python3`
- `EXTERNAL_REPO` defaults from `RTL_AGENT_LOOP_EXTERNAL_REPO` or `external/MAC_ARRAY_FPGA`
- `VIVADO_BIN` defaults to `vivado`
- if `MANIFEST_PATH` is not supplied, the Makefile resolves the manifest from:
  - `candidates/<candidate_id>.json` if it exists
  - otherwise `runs/<candidate_id>/candidate_manifest.json`
- if `RUN_DIR` is omitted, stage targets use repo-local manual paths such as:
  - `runs/<candidate_id>/manual_verify`
  - `runs/<candidate_id>/manual_implement`
  - `runs/<candidate_id>/manual_perf`

Those default manual paths remain unsafe for parallel worktrees. The controller-owned `attempt_<n>` model is still the concurrency-safe canonical path.

## 13. Candidate, Run, And Artifact Model

### 13.1 Source manifests

The active schema now supports MAC-array candidate manifests. Current starter examples include:

- [`candidates/mac_baseline_4x4_dw16.json`](/home/keelan/rtl_agent_loop/candidates/mac_baseline_4x4_dw16.json)
- [`candidates/mac_baseline_8x4_dw16.json`](/home/keelan/rtl_agent_loop/candidates/mac_baseline_8x4_dw16.json)
- [`candidates/mac_shared_4x4_sf2_dw16.json`](/home/keelan/rtl_agent_loop/candidates/mac_shared_4x4_sf2_dw16.json)
- [`candidates/mac_replicated_4x4_c2_dw16.json`](/home/keelan/rtl_agent_loop/candidates/mac_replicated_4x4_c2_dw16.json)

These files store:

- the candidate ID
- source label
- creation timestamp
- searched parameters
- rationale or hypothesis in `notes`
- lightweight classification in `tags`

### 13.2 Canonical manifest copy

Registration still writes an immutable canonical copy to:

- `runs/<candidate_id>/candidate_manifest.json`

### 13.3 Controller-owned run directories

Each controller-created run still lives under:

- `runs/<candidate_id>/attempt_<n>/`

Stage result conventions remain:

- `fast_verify/fast_verify.json`
- `vivado/vivado_result.json`
- `verilator_perf/verilator_result.json`

## 14. Current External Study Tooling

The external MAC-array repo now includes a real first bounded study flow.

Primary study files:

- [`external/MAC_ARRAY_FPGA/docs/first_bounded_study.md`](/home/keelan/rtl_agent_loop/external/MAC_ARRAY_FPGA/docs/first_bounded_study.md)
- [`external/MAC_ARRAY_FPGA/experiments/results/sweep_results.csv`](/home/keelan/rtl_agent_loop/external/MAC_ARRAY_FPGA/experiments/results/sweep_results.csv)
- [`external/MAC_ARRAY_FPGA/experiments/results/sweep_summary.md`](/home/keelan/rtl_agent_loop/external/MAC_ARRAY_FPGA/experiments/results/sweep_summary.md)

Current default sweep matrix:

- `baseline_4x4`
- `baseline_8x4`
- `baseline_8x8`
- `shared_4x4_sf2`
- `shared_8x4_sf2`
- `replicated_4x4_c2`
- `replicated_8x4_c2`
- `replicated_8x8_c2`

Observed current behavior from the checked-in summary:

- larger `ARRAY_M` / `ARRAY_N` points now produce genuinely larger active work and higher latency
- shared mode now shows explicit latency overhead relative to baseline
- replicated mode can produce synth-only study rows when implementation overflows or is otherwise not preserved through to full implementation

The checked-in summary currently shows:

- `baseline_4x4`: `22` cycles
- `baseline_8x4`: `38` cycles
- `baseline_8x8`: `70` cycles
- `shared_4x4_sf2`: `26` cycles
- `shared_8x4_sf2`: `42` cycles
- `replicated_8x8_c2`: currently `passed_perf_synth_only`

## 15. Real Repository State Observations

The repo contains real controller state and real external study artifacts, not just scaffolding.

Examples visible in the current workspace:

- registered candidates exist in SQLite
- legacy CNN-era candidates and MAC-array candidates both exist under [`candidates/`](/home/keelan/rtl_agent_loop/candidates)
- canonical run attempts exist under [`runs/`](/home/keelan/rtl_agent_loop/runs)
- best-candidate pointers currently exist in [`var/best_candidates.json`](/home/keelan/rtl_agent_loop/var/best_candidates.json)
- the external MAC-array repo includes real sweep outputs under [`external/MAC_ARRAY_FPGA/experiments/results/`](/home/keelan/rtl_agent_loop/external/MAC_ARRAY_FPGA/experiments/results)

One especially important implementation behavior remains unchanged:

- a candidate can still rank using older successful artifacts even while its latest run is pending or failed, because ranking resolves the latest successful artifacts rather than requiring the latest run to be clean

## 16. Known Mismatches And Design Drift

This repo currently has a few important mismatches between the active implementation and older repository surfaces.

### 16.1 Top-level docs and AGENTS drift

Several top-level source-of-truth documents still describe the old CNN-oriented system:

- [`README.md`](/home/keelan/rtl_agent_loop/README.md)
- [`AGENTS.md`](/home/keelan/rtl_agent_loop/AGENTS.md)
- [`docs/integration_notes.md`](/home/keelan/rtl_agent_loop/docs/integration_notes.md)

Those files still talk about `external/CNN_FPGA`, `DENSE_OUT_PAR`, `CONV_CHANNEL_PAR`, and `CONV_VARIANT`, while the active config, wrappers, and external default now target `external/MAC_ARRAY_FPGA`.

### 16.2 Mixed-era candidate manifests

[`candidates/`](/home/keelan/rtl_agent_loop/candidates) currently contains a mix of:

- legacy CNN-era manifests
- new MAC-array manifests

Practical consequence:

- old source manifests such as `dense*.json` and `conv*.json` do not satisfy the active MAC-array schema
- newly registered candidates must use the MAC-array parameter set described in Section 6

### 16.3 Throughput metric naming drift

As noted above, the external MAC-array perf flow emits `throughput_ops_per_sec`, but controller scoring still flattens `throughput_inferences_per_sec`.

Practical consequence:

- no current score breakage, because the active weights do not depend on throughput
- real naming drift remains and should be cleaned up if throughput becomes part of scoring

### 16.4 Controller Vivado stage versus sweep behavior

There is now a behavioral difference between:

- the controller Vivado wrapper
- the external manual sweep utility

The wrapper requires full external batch success before parsing metrics. The sweep utility can preserve synth-stage metrics and label the row `passed_perf_synth_only`.

Practical consequence:

- external study summaries may include synth-only rows
- controller-managed canonical Vivado stages currently still behave as all-or-nothing passes

### 16.5 `PIPE_STAGES` is real config, limited microarchitecture

`PIPE_STAGES` is accepted, validated, forwarded, and present in the external top-level generic list.

Practical consequence:

- it is not orchestration-only metadata
- but it still models deterministic drain latency more than a full arithmetic retiming framework

## 17. What Is Not Implemented

This repo still does not implement:

- a scheduler or job queue
- distributed workers
- a web UI or dashboard
- automatic candidate generation loops
- mutation engines
- artifact garbage collection
- a formal schema migration framework beyond additive SQL helpers
- DB-backed storage for best-candidate pointers
- controller-managed patch management for external RTL repos

The MAC-array external repo also intentionally avoids:

- CNN-specific functionality
- AXI or DMA stacks
- software runtime stacks
- sparse compute support
- partial reconfiguration flows

## 18. Recommended Mental Model

The cleanest current way to think about the codebase is:

- `rtl_agent_loop/` is the deterministic control plane
- `scripts/` are the stable boundary adapters to external tooling
- `config/` defines the allowed MAC-array parameter and scoring policy
- `candidates/` contains mixed historical manifests, but only MAC-array manifests match the active schema
- `runs/` are canonical controller-owned evidence
- `var/rtl_agent_loop.db` is the authoritative execution ledger
- `external/MAC_ARRAY_FPGA/` is the active hardware/toolflow dependency being orchestrated
- `external/CNN_FPGA/` remains historical workspace state, not the active default target

That mental model matches the code more closely than thinking of this repo as a CNN repo or as a general-purpose workflow engine.
