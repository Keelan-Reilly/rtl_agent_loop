# Parallel Worktree Operations

This note defines the lightweight operational model for repeated parallel work on `rtl_agent_loop`.

## Core Rules

- One worktree owns one task at a time.
- Source manifests live in `candidates/` and are immutable once registered.
- Repaired or revised designs are new child candidates, not in-place edits of an existing candidate manifest.
- Canonical controller-owned runs live only under `runs/<candidate_id>/attempt_<n>/`.
- Manual stage runs and `/tmp/...` experiments are allowed, but they are not canonical controller runs unless explicitly documented as such.

## Artifact Ownership

Use these ownership rules consistently:

- Canonical runs:
  - launch with `python3 -m rtl_agent_loop run --candidate-id <id> --worktree-ref <label>`
  - artifacts land in `runs/<candidate_id>/attempt_<n>/`
  - SQLite `runs` and `run_stages` are the source of truth
- Manual stage checks:
  - launch through the stable `make` targets
  - always pass an explicit unique `RUN_DIR`
  - recommended pattern:
    - `/tmp/rtl_agent_loop/<worktree>/<candidate_id>/<stage>`
- Shared defaults to avoid in parallel work:
  - `runs/<candidate_id>/manual_verify`
  - `runs/<candidate_id>/manual_implement`
  - `runs/<candidate_id>/manual_perf`

Never reuse another worktree’s `RUN_DIR`. Never write into an existing `attempt_<n>/` path manually.

## Candidate Discipline

Use this candidate model:

- New exploration point:
  - create `candidates/<candidate_id>.json`
  - register with `python3 -m rtl_agent_loop register --manifest ...`
- Repaired or revised point:
  - create a new candidate ID
  - register with:
    - `python3 -m rtl_agent_loop register --manifest ... --parent-candidate-id <parent> --revision-kind <kind>`
- Historical repair already registered without lineage:
  - attach lineage with:
    - `python3 -m rtl_agent_loop link-lineage --parent-candidate-id <parent> --child-candidate-id <child> --revision-kind <kind>`

Do not mutate an existing candidate manifest to represent a new revision. Do not bypass lineage for repaired candidates.

## Recommended Parallel Launch Order

Use this queue shape:

1. Explorer worktrees
   - each Explorer proposes exactly one candidate at a time
   - register immediately so the candidate ID is reserved in SQLite
2. Verification gate
   - Verifier checks candidate manifest and runs fast verification
   - prefer controller-managed `run --start-stage fast_verify --end-stage fast_verify` for canonical history
3. Implementation gate
   - Implementer runs Vivado only for verified candidates
4. Timing-repair queue
   - TimingDoctor acts only on timing-limited candidates with measured evidence
   - repaired designs must become child candidates
5. Performance and scoring
   - collect Verilator performance
   - compute scores
   - rank and update the best-candidate pointer if appropriate

## Role-to-Command Map

- Explorer:
  - `python3 -m rtl_agent_loop register --manifest ...`
- Verifier:
  - `python3 -m rtl_agent_loop run --candidate-id <id> --start-stage fast_verify --end-stage fast_verify --worktree-ref <label>`
  - or `make verify_candidate CANDIDATE_ID=<id> RUN_DIR=/tmp/...`
- Implementer:
  - `python3 -m rtl_agent_loop run --candidate-id <id> --start-stage vivado --end-stage vivado --worktree-ref <label>`
  - or `make implement_candidate CANDIDATE_ID=<id> RUN_DIR=/tmp/...`
- TimingDoctor:
  - create a child candidate and register it with lineage
- Scorer:
  - `python3 -m rtl_agent_loop score --candidate-id <id> [--run-dir <dir>]`
  - `python3 -m rtl_agent_loop rank-candidates ...`
  - `python3 -m rtl_agent_loop set-best-candidates ...`

## Handoff Requirements

Each handoff should state:

- candidate ID
- whether the run was canonical controller-owned or manual
- exact run directory
- whether lineage was created or updated
- which command was used
- next recommended gate

If `/tmp/...` was used, say so explicitly.
