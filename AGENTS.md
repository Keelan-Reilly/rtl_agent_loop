# AGENTS.md

## Purpose

`rtl_agent_loop` is a deterministic FPGA design-space exploration controller for the external `CNN_FPGA` accelerator repository.

This repository is responsible for:

- candidate manifest validation
- deterministic stage execution
- fast verification
- Vivado batch orchestration
- Verilator performance collection
- score computation
- SQLite-backed experiment logging

This repository is not the source of truth for the accelerator RTL itself. The accelerator implementation remains in the external `CNN_FPGA` repository.

## Source Of Truth

Treat the following as authoritative:

- `Makefile`: stable automation interface for worktrees and agents
- `candidates/`: source candidate manifests
- `scripts/bootstrap_env.sh`: local environment/bootstrap contract
- `scripts/fast_verify.sh`: fast verification contract
- `scripts/run_vivado_batch.sh`: Vivado batch contract
- `scripts/collect_verilator_perf.sh`: Verilator performance contract
- `rtl_agent_loop/cli.py`: supported controller CLI subcommands
- `rtl_agent_loop/controller.py`: controller behavior and score computation behavior
- `config/search_space.json`: allowed search space and default external integration values
- `config/score_weights.json`: score weights and penalties
- `schemas/candidate_manifest.example.json`: manifest shape example
- `docs/integration_notes.md`: explicit unresolved integration points
- `runs/`: candidate manifests and generated run artifacts
- `var/rtl_agent_loop.db`: SQLite experiment state

Treat the following as external dependency state, not local ownership:

- `external/CNN_FPGA/`

Do not silently override the behavior of any source-of-truth file through undocumented ad hoc scripts.

## Agent Roles And Allowed Scope

### 1. Controller Agent

Allowed modifications:

- `rtl_agent_loop/*.py`
- `config/*.json`
- `schemas/*.json`
- `Makefile`
- `README.md`
- `docs/*.md`

Responsibilities:

- manifest validation
- state transitions
- score computation
- database schema and logging behavior
- stable CLI behavior

Must not:

- edit `external/CNN_FPGA/*` unless explicitly instructed
- invent new execution stages that are not implemented

### 2. Wrapper Agent

Allowed modifications:

- `scripts/*.sh`
- `Makefile`
- `README.md`
- `docs/*.md`
- `config/search_space.json`

Responsibilities:

- keep wrapper argument contracts stable
- align wrapper behavior with the actual external `CNN_FPGA` interfaces
- fail fast with explicit logs and result JSON

Must not:

- reimplement external Vivado or Verilator flows locally without explicit instruction
- add hidden environment assumptions

### 3. Documentation Agent

Allowed modifications:

- `README.md`
- `docs/*.md`
- `AGENTS.md`
- `schemas/*.json`

Responsibilities:

- document only workflows that exist in the current repo
- keep setup, task commands, and environment variables accurate

Must not:

- document speculative commands or future agent workflows as if they are implemented
- change code behavior to match documentation without explicit implementation work

### 4. Experiment Operator

Allowed actions:

- run `make setup`
- run `make verify_candidate`
- run `make implement_candidate`
- run `make perf_candidate`
- run `make score_candidate`
- run `python -m rtl_agent_loop ...` supported CLI commands
- register manifests
- inspect `runs/` artifacts and SQLite state

Must not:

- hand-edit generated stage result JSON
- hand-edit SQLite tables
- rename candidate directories after registration

## Forbidden Actions

The following actions are forbidden unless explicitly requested by the project owner:

- modifying files under `external/CNN_FPGA/`
- copying RTL or scripts from `external/CNN_FPGA/` into this repo
- deleting `runs/` or `var/rtl_agent_loop.db` to hide failures
- editing generated files under `runs/<candidate_id>/...` except to remove disposable local test artifacts you created yourself
- changing wrapper interfaces without updating `Makefile`, `README.md`, and this file in the same change
- inventing unimplemented pipeline stages, agent loops, schedulers, or mutation workflows
- bypassing `config/search_space.json` validation for v1 parameters
- changing candidate IDs after a candidate has been registered
- force-passing validation by suppressing non-zero wrapper exit codes

Do not represent incomplete or speculative integration as complete.

## Required Validation Before Handoff

Before handoff, run the validation that matches the files you changed.

Minimum required validation for any code or script change:

- `make setup`
- `python3 -m compileall rtl_agent_loop`

If you changed wrapper scripts or `Makefile`:

- run the relevant `make` target(s) using an explicit `CANDIDATE_ID`
- capture whether the command passed or failed
- if a command fails because of missing external tools or configuration, state that explicitly

If you changed scoring or controller behavior:

- run `python3 -m rtl_agent_loop score --candidate-id <id>` for a real candidate with existing artifacts, or explain why no suitable candidate exists

If you changed documentation only:

- verify that every command named in the docs exists in `Makefile`, `scripts/`, or `rtl_agent_loop/cli.py`

Never claim validation you did not run.

## Stable Command Surface

Use these commands as the stable v1 interface:

- `make setup`
- `make verify_candidate CANDIDATE_ID=<id>`
- `make implement_candidate CANDIDATE_ID=<id>`
- `make perf_candidate CANDIDATE_ID=<id>`
- `make score_candidate CANDIDATE_ID=<id>`

Supported explicit overrides:

- `PYTHON=...`
- `EXTERNAL_REPO=...`
- `MANIFEST_PATH=...`
- `RUN_DIR=...`
- `VIVADO_BIN=...`

Supported direct wrapper arguments:

- `--candidate-id <id>` or `--candidate-manifest <path>`
- `--run-dir <dir>`
- `--external-repo <path>`

Supported controller CLI subcommands:

- `init-db`
- `register --manifest <path>`
- `run --candidate-id <id>`
- `run-pending --limit <n>`
- `status --candidate-id <id>`
- `score --candidate-id <id> [--run-dir <dir>]`
- `rank-candidates [--markdown-out <path>]`
- `list-candidates`

Do not invent additional public commands without updating all source-of-truth references.

## File Naming Conventions

Use these conventions consistently:

- Python modules: `snake_case.py`
- shell scripts: `snake_case.sh`
- config files: descriptive `snake_case.json`
- docs: `snake_case.md` except top-level `README.md` and `AGENTS.md`
- source candidate manifests: `candidates/<candidate_id>.json`
- copied registered manifests: `runs/<candidate_id>/candidate_manifest.json`
- generated stage result files:
  - `fast_verify/fast_verify.json`
  - `vivado/vivado_result.json`
  - `verilator_perf/verilator_result.json`

Do not create alternate names for the same artifact type.

## Candidate ID Conventions

Candidate IDs must be:

- lowercase
- ASCII
- deterministic and human-readable
- safe for directory names

Preferred pattern:

- `<dense>_<width>_<frac>_<variant>`

Concrete example:

- `dense2_dw16_fb7_base`

Recommended tokens:

- `dense<N>` for `DENSE_OUT_PAR`
- `dw<N>` for `DATA_WIDTH`
- `fb<N>` for `FRAC_BITS`
- `base` or `pipe` for `CONV_VARIANT`

Rules:

- use only letters, numbers, and underscores
- do not include spaces
- do not reuse a candidate ID for a different parameter set
- once registered, a candidate ID is immutable

## Recording Hypotheses And Outcomes

Record hypotheses at candidate creation time:

- put the intended rationale in manifest field `notes`
- put lightweight classification labels in manifest field `tags`
- store the source manifest under `candidates/<candidate_id>.json`

Examples of valid hypothesis recording:

- expected resource tradeoff
- expected timing impact
- expected throughput impact

Record measured outcomes through the implemented system only:

- run stage commands or controller commands
- inspect generated artifacts under `runs/<candidate_id>/...`
- inspect `var/rtl_agent_loop.db`

Measured outcomes must be taken from:

- `fast_verify.json`
- `vivado_result.json`
- `metrics.json`
- `verilator_result.json`
- `performance.json`
- `python -m rtl_agent_loop score ...`
- SQLite entries in `var/rtl_agent_loop.db`

Do not record measured outcomes by manually editing manifest notes after execution. Post-run interpretation belongs in commit messages, PR text, or external analysis notes, not by mutating generated result files.

## Manifest And Artifact Hygiene

Use these locations consistently:

- `candidates/<candidate_id>.json`:
  - source manifest owned by contributors and agents
- `runs/<candidate_id>/candidate_manifest.json`:
  - controller-owned copy captured at registration time
- `runs/<candidate_id>/attempt_XXXX/`:
  - repo-managed run artifacts
- `/tmp/...`:
  - temporary external run directories for local execution only

Do not treat `/tmp/...` artifacts as the canonical presentation location when an equivalent repo-managed run directory exists.

## Handoff Requirements

Every handoff must state:

- which source-of-truth files were changed
- which stable commands were run
- which commands passed
- which commands failed
- which failures are expected environment limitations versus code defects
- any remaining explicit TODOs, with paths

Be precise. If an integration point remains unresolved, name the exact file and TODO rather than describing it vaguely.
