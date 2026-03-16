# Repository Design

This document describes the current implementation of `rtl_agent_loop` as it exists in this repository on 2026-03-16. It is intentionally implementation-first: where code, config, and docs disagree, this note calls that out explicitly instead of smoothing it over.

## 1. System Purpose

`rtl_agent_loop` is a deterministic orchestration layer for bounded FPGA design-space exploration over an external accelerator repository, [`external/CNN_FPGA`](/home/keelan/rtl_agent_loop/external/CNN_FPGA/README.md).

This repository owns:

- candidate manifest validation
- candidate registration and lineage tracking
- deterministic stage execution
- wrapper contracts for fast verification, Vivado, and Verilator performance collection
- run artifact ownership under `runs/`
- score computation and ranking
- SQLite-backed experiment state
- role prompts and operator-facing documentation

This repository does not own the accelerator RTL implementation as a product surface. The external repo remains the hardware implementation boundary.

## 2. Top-Level Repository Layout

The repo is organized into a few clear ownership zones:

- [`rtl_agent_loop/`](/home/keelan/rtl_agent_loop/rtl_agent_loop): Python controller package
- [`scripts/`](/home/keelan/rtl_agent_loop/scripts): stable wrapper entrypoints used by the controller and `Makefile`
- [`config/`](/home/keelan/rtl_agent_loop/config): search-space and scoring policy JSON
- [`candidates/`](/home/keelan/rtl_agent_loop/candidates): contributor-authored source manifests
- [`runs/`](/home/keelan/rtl_agent_loop/runs): controller-owned manifest copies and per-run artifacts
- [`var/`](/home/keelan/rtl_agent_loop/var): SQLite state and best-candidate pointer JSON
- [`docs/`](/home/keelan/rtl_agent_loop/docs): operator notes, scoring policy, measured summaries, and this design note
- [`prompts/`](/home/keelan/rtl_agent_loop/prompts): role-specific operating prompts
- [`external/CNN_FPGA/`](/home/keelan/rtl_agent_loop/external/CNN_FPGA): external accelerator dependency

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
- `scoring` is defined as a name but the candidate summary state written after scoring is `scored`

Important implementation detail:

- `candidates.current_state` is only a summary of the latest transition.
- `run_stages` is the authoritative per-run stage snapshot.
- Partial runs mark unrequested stages as `skipped`.
- A failed executable stage causes remaining selected stages to be marked `skipped`.
- A run with only a bounded stage window, such as `fast_verify` only, ends with run status `partial` rather than `completed`.

Stage range handling is implemented by `normalize_stage_range()`. If the caller omits both bounds, the controller runs the full range from `fast_verify` through `scoring`.

## 5. Python Package Design

### 5.1 Package entrypoints

[`rtl_agent_loop/__main__.py`](/home/keelan/rtl_agent_loop/rtl_agent_loop/__main__.py) is the module entrypoint and simply dispatches to CLI `main()`.

[`rtl_agent_loop/__init__.py`](/home/keelan/rtl_agent_loop/rtl_agent_loop/__init__.py) only exposes `__version__ = "0.1.0"`.

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

### 5.4 Config and validation

[`rtl_agent_loop/config.py`](/home/keelan/rtl_agent_loop/rtl_agent_loop/config.py) does three things:

- generic JSON loading
- config loading for search space and weights
- manifest validation against the active search-space schema

`validate_manifest()` currently accepts only:

- required parameters:
  - `DENSE_OUT_PAR`
  - `DATA_WIDTH`
  - `FRAC_BITS`
  - `CONV_CHANNEL_PAR`
  - `CONV_VARIANT`
- optional parameters:
  - `DENSE_SPLIT_MAC_PIPELINE`

Validation rules include:

- top-level required fields must exist
- `candidate_id` must be a non-empty string
- `parameters` must be an object
- unsupported parameter keys are rejected
- integer parameters must fall inside the allowed sets in `config/search_space.json`
- `CONV_VARIANT` must be both logically allowed and present in the configured allowed set
- `FRAC_BITS` must be strictly less than `DATA_WIDTH`
- `tags` must be a list of strings

This validator returns a `CandidateManifest` dataclass, not a raw dict.

### 5.5 Models

[`rtl_agent_loop/models.py`](/home/keelan/rtl_agent_loop/rtl_agent_loop/models.py) contains lightweight dataclasses and parameter-key constants.

Important constants:

- `ALLOWED_CONV_VARIANTS = {"baseline", "pipelined"}`
- `REQUIRED_PARAMETER_KEYS`
- `OPTIONAL_PARAMETER_KEYS`

Important dataclasses:

- `CandidateManifest`
- `CandidateRecord`
- `StageResult`

These dataclasses are data containers; they do not implement behavior.

### 5.6 Paths

[`rtl_agent_loop/paths.py`](/home/keelan/rtl_agent_loop/rtl_agent_loop/paths.py) centralizes filesystem roots:

- repo root
- config paths
- `runs/`
- `logs/`
- `var/`
- database path
- best-candidate JSON path
- scripts dir

This keeps path logic out of the controller and wrappers.

### 5.7 Scoring

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

Only a subset contributes to the weighted score. The current weights JSON uses:

- `latency_cycles`
- `lut`
- `ff`
- `dsp`
- `bram`
- `wns_ns`

Penalty rules are explicit:

- each missing weighted metric adds `missing_metric`
- missing timing adds `timing_missing`
- negative `wns_ns` adds `timing_negative_wns`
- failed stage runs add `stage_failed`

This module is intentionally simple and transparent rather than statistically sophisticated.

### 5.8 SQLite store

[`rtl_agent_loop/sqlite_store.py`](/home/keelan/rtl_agent_loop/rtl_agent_loop/sqlite_store.py) is the persistence layer.

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

Base schema tables:

- `schema_migrations`
- `candidates`
- `candidate_params`
- `runs`
- `state_transitions`
- `artifacts`
- `scores`

Migration-added/maintained columns and tables:

- candidate lineage columns:
  - `parent_candidate_id`
  - `lineage_root_candidate_id`
  - `revision_kind`
  - `derived_from_run_id`
  - `supersedes_candidate_id`
- run ownership and request columns:
  - `owner_token`
  - `requested_start_stage`
  - `requested_end_stage`
  - `worktree_ref`
- `run_stages` table

`create_run()` is worth calling out:

- it uses `BEGIN IMMEDIATE`
- it computes the next `attempt_index` inside the transaction
- it allocates `runs/<candidate_id>/attempt_<n>`
- it generates a UUID-based `owner_token`

This is the core concurrency-safety mechanism for run numbering.

`_backfill_run_stages()` is the compatibility layer for older runs:

- if a run already has `run_stages`, nothing is changed
- otherwise the method reconstructs stage rows from `state_transitions` and `artifacts`
- missing-but-inferred data is annotated in `details_json`

### 5.9 Subprocess execution

[`rtl_agent_loop/subprocess_utils.py`](/home/keelan/rtl_agent_loop/rtl_agent_loop/subprocess_utils.py) is intentionally tiny.

It provides:

- `shell_join()` for readable logging
- `run_command()` for subprocess execution with stdout/stderr redirected into a file

The controller uses this to keep a `controller_command.log` per stage invocation.

## 6. Wrapper Script Design

The shell wrappers in [`scripts/`](/home/keelan/rtl_agent_loop/scripts) are part of the stable integration surface. Each wrapper:

- accepts `--candidate-id` or `--candidate-manifest`
- requires `--run-dir`
- optionally accepts `--external-repo`
- writes a stage log
- writes a stage result JSON
- exits non-zero on failure

The heavy logic in each wrapper actually lives in an embedded Python block. Bash is mainly used for argument parsing and directory setup.

### 6.1 `bootstrap_env.sh`

[`scripts/bootstrap_env.sh`](/home/keelan/rtl_agent_loop/scripts/bootstrap_env.sh) is the environment bootstrap contract.

It:

- resolves the Python interpreter and external repo path
- checks that Python exists
- checks that the external repo and its `Makefile` exist
- exports `RTL_AGENT_LOOP_PYTHON`
- exports `RTL_AGENT_LOOP_EXTERNAL_REPO`
- exports `VIVADO_BIN` with a default of `vivado`
- prints basic environment facts
- runs a lightweight stdlib import check
- runs `python -m compileall rtl_agent_loop`
- optionally runs `python -m rtl_agent_loop init-db`

This is the minimum validation gate required by the repo instructions before handoff for code/script changes.

### 6.2 `fast_verify.sh`

[`scripts/fast_verify.sh`](/home/keelan/rtl_agent_loop/scripts/fast_verify.sh) is the fast verification gate.

Implementation details:

- loads `config/search_space.json`
- resolves the manifest path from the CLI args or canonical locations
- resolves the external repo path from args, env, or config default
- reads `external/CNN_FPGA/hdl/top_level.sv`
- parses the `top_level` parameter block with a regex
- collects searched generics from the manifest for:
  - `CONV_CHANNEL_PAR`
  - `DATA_WIDTH`
  - `DENSE_OUT_PAR`
  - `FRAC_BITS`
  - `DENSE_SPLIT_MAC_PIPELINE`
- performs preflight checks for:
  - external repo existence
  - external `Makefile`
  - `top_level.sv`
  - `tb/tb_full_pipeline.cpp`
  - `weights/input_image.mem`
  - HDL directory
  - Vivado batch wrapper
  - Verilator perf script
  - local `verilator`
  - local `make`
  - searched generic presence in `top_level`

In `verilator_lint` mode, it builds and runs:

- `verilator -sv --lint-only -Wall -Wno-fatal ... --top-module top_level`

Important current limitation:

- `CONV_VARIANT` is recorded and warned about, but not mapped into the external RTL for this gate.

The output JSON includes:

- `checks`
- `top_level_parameters`
- `warnings`
- `command`
- `returncode`
- config `todo`
- relative `log_path`

### 6.3 `run_vivado_batch.sh`

[`scripts/run_vivado_batch.sh`](/home/keelan/rtl_agent_loop/scripts/run_vivado_batch.sh) is the implementation wrapper.

Implementation details:

- loads the manifest
- resolves external repo and Vivado defaults from config
- targets:
  - `external/CNN_FPGA/fpga/vivado/run_batch.sh`
  - `external/CNN_FPGA/fpga/vivado/parse_reports.py`
- creates a nested wrapper-owned path:
  - `<run_dir>/vivado/batch_run`
- writes parsed metrics to:
  - `<run_dir>/vivado/metrics.json`

It strips `CONV_VARIANT` out of the generic set before building the external command because the current external repo does not expose that as a real synthesis generic.

The result JSON includes:

- preflight `checks`
- the exact command
- relative `reports_dir`
- relative `metrics_path`
- parsed `metrics`
- a `todo` string documenting the missing `CONV_VARIANT` integration hook

### 6.4 `collect_verilator_perf.sh`

[`scripts/collect_verilator_perf.sh`](/home/keelan/rtl_agent_loop/scripts/collect_verilator_perf.sh) is the performance wrapper.

Implementation details:

- targets `external/CNN_FPGA/experiments/collect_verilator_perf.py`
- creates:
  - `<run_dir>/verilator_perf/perf_run`
- expects external output at:
  - `<run_dir>/verilator_perf/perf_run/verilator_perf/performance.json`

As in the Vivado wrapper:

- searched generics other than `CONV_VARIANT` are passed through
- `CONV_VARIANT` is recorded but not wired into the external flow

The result JSON includes:

- preflight `checks`
- exact `command`
- relative `performance_path`
- parsed `metrics`
- a `todo` about external prerequisites

## 7. Makefile Surface

[`Makefile`](/home/keelan/rtl_agent_loop/Makefile) is the stable automation interface called out in repo policy.

Targets:

- `setup`
- `verify_candidate`
- `implement_candidate`
- `perf_candidate`
- `score_candidate`

Important behavior:

- `PYTHON` defaults from `RTL_AGENT_LOOP_PYTHON` or `python3`
- `EXTERNAL_REPO` defaults from `RTL_AGENT_LOOP_EXTERNAL_REPO` or `external/CNN_FPGA`
- `VIVADO_BIN` defaults to `vivado`
- if `MANIFEST_PATH` is not supplied, the Makefile resolves the manifest from:
  - `candidates/<candidate_id>.json` if it exists
  - otherwise `runs/<candidate_id>/candidate_manifest.json`
- if `RUN_DIR` is omitted, stage targets use repo-local manual paths such as:
  - `runs/<candidate_id>/manual_verify`
  - `runs/<candidate_id>/manual_implement`
  - `runs/<candidate_id>/manual_perf`

The docs and AGENTS file explicitly warn that these default manual paths are not safe for parallel worktrees. The controller-owned `attempt_<n>` model is the concurrency-safe canonical path.

## 8. Configuration Files

### 8.1 Search space

[`config/search_space.json`](/home/keelan/rtl_agent_loop/config/search_space.json) defines three things:

- default external repo location
- allowed search-space values
- default integration settings for Vivado, Verilator, and fast verify

Current active allowed parameters:

- `DENSE_OUT_PAR`: `[1, 2, 5, 10]`
- `DATA_WIDTH`: `[12, 16]`
- `FRAC_BITS`: `[6, 7]`
- `CONV_CHANNEL_PAR`: `[1, 2, 4]`
- `DENSE_SPLIT_MAC_PIPELINE`: `[0, 1]`
- `CONV_VARIANT`: `["baseline", "pipelined"]`

Current default integration settings:

- global clock:
  - `clock_hz = 100000000`
- Vivado:
  - part `xc7a35tcpg236-1`
  - top `top_level`
  - xdc `CNN_constraints.xdc`
  - jobs `4`
  - clock period `10.0 ns`
- Verilator:
  - top `top_level`
  - placeholder dataset/image paths for future use
- fast verify:
  - mode `verilator_lint`
  - TODO note about `CONV_VARIANT`

### 8.2 Score weights

[`config/score_weights.json`](/home/keelan/rtl_agent_loop/config/score_weights.json) defines the current ranking policy:

- negative weights for latency and area
- a positive weight for `wns_ns`
- fixed penalties for missing metrics, missing timing, negative WNS, and stage failure

The scoring policy is also described narratively in [`docs/scoring_policy.md`](/home/keelan/rtl_agent_loop/docs/scoring_policy.md).

## 9. Candidate, Run, and Artifact Model

### 9.1 Source manifests

Source manifests live in [`candidates/`](/home/keelan/rtl_agent_loop/candidates).

Examples:

- [`dense1_dw12_fb6_base.json`](/home/keelan/rtl_agent_loop/candidates/dense1_dw12_fb6_base.json)
- [`dense2_dw12_fb6_base_r1.json`](/home/keelan/rtl_agent_loop/candidates/dense2_dw12_fb6_base_r1.json)

These files store:

- the candidate ID
- provenance/source label
- creation timestamp
- searched parameters
- rationale/hypothesis in `notes`
- lightweight classification in `tags`

### 9.2 Canonical manifest copy

Registration writes an immutable canonical copy to:

- `runs/<candidate_id>/candidate_manifest.json`

This copy, not the original `candidates/` file, is what the controller records in SQLite as the manifest path.

### 9.3 Controller-owned run directories

Each controller-created run lives under:

- `runs/<candidate_id>/attempt_<n>/`

Stage result conventions:

- `fast_verify/fast_verify.json`
- `vivado/vivado_result.json`
- `verilator_perf/verilator_result.json`

The wrappers also create additional logs and nested working directories under those stage roots.

### 9.4 Artifact resolution strategy

When computing a candidate score without an explicit `--run-dir`, the controller resolves:

- the latest successful canonical Vivado result
- the latest successful canonical Verilator performance result

These can come from different attempts.

This is an important design choice: the system treats candidate scoring as an aggregate over the latest passing stage artifacts, not necessarily a single monolithic full-pipeline run.

## 10. Current SQLite Data Model

The live DB currently records:

- registered candidates
- candidate parameter key/value rows
- run ownership and requested stage windows
- per-stage snapshots in `run_stages`
- state history in `state_transitions`
- artifact registrations
- score history

Observed live behavior from the current DB:

- candidates can have old passing artifacts and a newer in-progress summary state
- `rank-candidates` still uses the passing artifacts
- `show-best-candidates` is stored outside SQLite in [`var/best_candidates.json`](/home/keelan/rtl_agent_loop/var/best_candidates.json)

## 11. Current Documented Operator Workflow

The implemented operator surfaces are split across CLI, Makefile, and docs.

Main lifecycle:

1. `make setup`
2. `python3 -m rtl_agent_loop register --manifest ...`
3. `python3 -m rtl_agent_loop run --candidate-id <id> ...`
4. `python3 -m rtl_agent_loop score --candidate-id <id>`
5. `python3 -m rtl_agent_loop rank-candidates`

Supporting notes:

- [`docs/worktree_operations.md`](/home/keelan/rtl_agent_loop/docs/worktree_operations.md): parallel worktree ownership rules
- [`docs/integration_notes.md`](/home/keelan/rtl_agent_loop/docs/integration_notes.md): known unresolved integration hooks
- [`docs/measured_dse_summary.md`](/home/keelan/rtl_agent_loop/docs/measured_dse_summary.md): measured results summary
- [`docs/dense2_lineage_case_study.md`](/home/keelan/rtl_agent_loop/docs/dense2_lineage_case_study.md): a concrete lineage analysis note
- [`docs/conv_parallelism_experiment.md`](/home/keelan/rtl_agent_loop/docs/conv_parallelism_experiment.md): bounded convolution-channel parallelism experiment summary

## 12. Prompt Files

The prompt set in [`prompts/`](/home/keelan/rtl_agent_loop/prompts) encodes disciplined role boundaries for:

- explorer
- verifier
- implementer
- timing doctor
- scorer

These files are not executable code, but they are part of the repository’s operating model. They reinforce current design assumptions:

- one bounded task at a time
- child candidates for repairs
- explicit canonical versus manual run ownership
- no artifact overwrites
- no inferred measurements

## 13. Real Repository State Observations

The current repo contains real measured state, not just scaffolding.

Examples visible through the live CLI:

- registered candidates exist in SQLite
- lineage exists for `dense2_dw12_fb6_base -> dense2_dw12_fb6_base_r1`
- canonical run attempts exist under `runs/`
- best-candidate pointers currently exist in `var/best_candidates.json`

One especially important observed behavior:

- a candidate can currently rank using older successful artifacts even while its latest run is in progress and its current summary state is pending

That is not a bug in the ranking code; it is how artifact resolution is intentionally implemented today.

## 14. Known Mismatches And Design Drift

This repo currently has a few important mismatches between files.

### 14.1 Candidate schema migration side effect

`CONV_CHANNEL_PAR` is now a real required searched parameter in:

- [`rtl_agent_loop/config.py`](/home/keelan/rtl_agent_loop/rtl_agent_loop/config.py)
- [`rtl_agent_loop/models.py`](/home/keelan/rtl_agent_loop/rtl_agent_loop/models.py)
- [`config/search_space.json`](/home/keelan/rtl_agent_loop/config/search_space.json)

Practical consequence:

- newly authored manifests must include `CONV_CHANNEL_PAR`
- existing source manifests in [`candidates/`](/home/keelan/rtl_agent_loop/candidates) were backfilled with `CONV_CHANNEL_PAR = 1` to preserve baseline semantics
- some older already-registered canonical manifest copies under `runs/<candidate_id>/candidate_manifest.json` may still reflect pre-migration parameter sets because registration captures an immutable copy at registration time

### 14.2 CLI surface drift

The CLI currently implements:

- `set-best-candidates`
- `show-best-candidates`

Those commands are real and working, but they are not consistently reflected in every project-level stable-surface note. The code is the reliable statement of current behavior here.

### 14.3 Timing-clean interpretation drift in docs versus current artifacts

The measured summaries in some docs describe earlier timing-clean results, but the current `rank-candidates` output in this workspace now resolves later canonical artifacts where all ranked candidates have negative WNS.

Practical consequence:

- historical docs may reflect earlier measured runs
- current ranking is driven by the newest passing canonical artifacts, not by those older summaries

### 14.4 `CONV_CHANNEL_PAR` is real, but currently network-limited

`CONV_CHANNEL_PAR` is now wired into the external RTL:

- [`external/CNN_FPGA/hdl/top_level.sv`](/home/keelan/rtl_agent_loop/external/CNN_FPGA/hdl/top_level.sv)
- [`external/CNN_FPGA/hdl/conv2d.sv`](/home/keelan/rtl_agent_loop/external/CNN_FPGA/hdl/conv2d.sv)

The current implementation mirrors IFMAP storage into `CONV_CHANNEL_PAR` read banks and performs grouped channel accumulation in `conv2d`.

Practical consequence:

- the knob is synthesis-real and affects LUT/DSP/BRAM/timing
- the current checked-in accelerator still fixes `IN_CHANNELS = 1` at top level
- the completed experiment in [`docs/conv_parallelism_experiment.md`](/home/keelan/rtl_agent_loop/docs/conv_parallelism_experiment.md) shows no end-to-end latency or throughput improvement for `CONV_CHANNEL_PAR = 1, 2, 4` in this network, even though convolution remains the dominant stage

### 14.5 `CONV_VARIANT` orchestration-only status

`CONV_VARIANT` is accepted and stored across the system, but both stage wrappers still treat it as an orchestration-level field, not as a real hardware control hook into the external repo.

This is documented honestly in:

- [`scripts/fast_verify.sh`](/home/keelan/rtl_agent_loop/scripts/fast_verify.sh)
- [`scripts/run_vivado_batch.sh`](/home/keelan/rtl_agent_loop/scripts/run_vivado_batch.sh)
- [`scripts/collect_verilator_perf.sh`](/home/keelan/rtl_agent_loop/scripts/collect_verilator_perf.sh)
- [`docs/integration_notes.md`](/home/keelan/rtl_agent_loop/docs/integration_notes.md)

## 15. What Is Not Implemented

This repo does not currently implement:

- a scheduler or job queue
- distributed workers
- a web UI or dashboard
- automatic candidate generation loops
- mutation engines
- external RTL patch management as a first-class controller feature
- artifact garbage collection
- a formal schema migration framework beyond additive SQL helpers
- direct DB-backed storage for best-candidate pointers
- any controller-managed abstraction for patching or versioning external RTL changes beyond direct repo edits

## 16. Recommended Mental Model

The cleanest way to think about this codebase is:

- `rtl_agent_loop/` is the deterministic control plane
- `scripts/` are the stable boundary adapters to external tooling
- `config/` defines the allowed parameter and scoring policy
- `candidates/` are human/agent proposals
- `runs/` are canonical evidence
- `var/rtl_agent_loop.db` is the authoritative execution ledger
- `external/CNN_FPGA/` is the hardware/toolflow dependency being orchestrated, not reimplemented

That mental model matches the code more closely than thinking of this repo as an RTL repo or as a general-purpose workflow engine.
