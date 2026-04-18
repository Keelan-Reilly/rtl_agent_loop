# rtl_agent_loop

`rtl_agent_loop` is a deterministic hardware exploration control plane centered on the external [`MAC_ARRAY_FPGA`](./external/MAC_ARRAY_FPGA) repo.

It is designed for bounded architecture studies where we want:

- explicit candidate manifests
- deterministic controller-owned run directories
- fast verification, Vivado, and Verilator perf collection
- SQLite-backed provenance
- transparent scoring and ranking
- thin closed-loop search with persistent JSON-backed search memory
- reproducible study artifacts rather than ad hoc one-off runs

The hardware implementation boundary stays outside this repo in `external/MAC_ARRAY_FPGA`. This repo is the control plane, experiment ledger, and reporting layer.

Strategically, this repo exists to make hardware teams iterate materially faster on real designs by turning implementation feedback into a continuously improving decision loop.

Technically, it is a closed-loop hardware optimization control plane that treats synthesis, implementation, timing, and performance feedback as searchable evidence for architecture decisions.

The closed-loop v1 layer is intentionally thin. It adds a deterministic `optimize` command on top of the existing controller rather than introducing a new workflow engine.

Parent selection is explicit:

- use ranked candidates from the current optimize pool when scoreable evidence exists
- otherwise fall back to the optimize candidate-pool order, which starts from sorted seed ids and then appends newly registered children deterministically

## Validated V1

The current repo state is not just aspirational. The closed-loop v1 path has been validated on a real Linux plus Vivado server.

Validated facts:

- `optimize` runs as a thin layer above the existing deterministic controller
- optimize-generated children register through the controller with lineage preserved
- canonical controller-owned run artifacts land under `runs/<candidate_id>/attempt_<n>/`
- optimize session state and reports land under `var/optimize/<session_id>/`
- full Vivado implementation evidence is parsed through the optimize path
- the validated child session ended in `perf_regressed` based on scored metrics versus its parent, not on fallback failure heuristics

Exact validated command:

```bash
python3 -m rtl_agent_loop optimize \
  --iterations 1 \
  --seed-candidate-id mac_baseline_4x4_dw16 \
  --top-k 1 \
  --mutations-per-parent 1 \
  --worktree-ref servercheck
```

That successful run proved the v1 loop can deterministically generate a child, register it with lineage, execute fast verify plus Vivado plus Verilator under controller ownership, resolve full implementation evidence, score the result, and emit a persistent optimize summary.

## Current Study Question

The active study asks:

> When does structural flexibility or sharing outperform brute-force replication in spatial MAC accelerators?

The external MAC-array platform compares three architecture families:

- `baseline`: one active PE per logical lane
- `shared`: fewer physical PEs plus explicit phased sharing and mux overhead
- `replicated`: baseline-style active compute plus preserved shadow replication for area/timing study

The current bounded sweep already shows useful trends:

- baseline latency scales with array size
- shared mode adds measurable scheduling overhead
- replicated mode can preserve baseline-like latency while causing dramatic LUT growth

See:

- [docs/mac_array_tradeoff_study.md](./docs/mac_array_tradeoff_study.md)
- [docs/current_evidence_index.md](./docs/current_evidence_index.md)
- [docs/results/active_mac_ranking.md](./docs/results/active_mac_ranking.md)
- [docs/results/score_policy_sensitivity.md](./docs/results/score_policy_sensitivity.md)
- [external/MAC_ARRAY_FPGA/docs/first_bounded_study.md](./external/MAC_ARRAY_FPGA/docs/first_bounded_study.md)
- [external/MAC_ARRAY_FPGA/experiments/results/sweep_summary.md](./external/MAC_ARRAY_FPGA/experiments/results/sweep_summary.md)

## What This Repo Owns

- candidate manifest validation
- candidate registration and lineage tracking
- deterministic stage execution
- controller-owned artifacts under `runs/<candidate_id>/attempt_<n>/`
- SQLite experiment state in `var/rtl_agent_loop.db`
- score computation and ranking
- stable wrapper contracts to the external repo
- JSON-backed optimize session memory and reports under `var/optimize/`

## What The External Repo Owns

The external repo at [`external/MAC_ARRAY_FPGA`](./external/MAC_ARRAY_FPGA) owns:

- SystemVerilog RTL
- Verilator testbenches
- fixed-point vector generation and golden model logic
- Vivado batch scripts and report parsing
- manual sweep tooling and study plots

## Active Candidate Schema

The active manifest schema is MAC-array specific. Required parameters are:

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

Starter candidate examples:

- [candidates/mac_baseline_4x4_dw16.json](./candidates/mac_baseline_4x4_dw16.json)
- [candidates/mac_baseline_8x4_dw16.json](./candidates/mac_baseline_8x4_dw16.json)
- [candidates/mac_shared_4x4_sf2_dw16.json](./candidates/mac_shared_4x4_sf2_dw16.json)
- [candidates/mac_replicated_4x4_c2_dw16.json](./candidates/mac_replicated_4x4_c2_dw16.json)

Legacy CNN-era manifests still exist in `candidates/` for historical context, but they are not valid under the active schema.

## Main Commands

Environment/bootstrap:

```bash
make setup
```

Register a candidate:

```bash
python3 -m rtl_agent_loop register --manifest candidates/mac_baseline_4x4_dw16.json
```

Run the full canonical controller flow:

```bash
python3 -m rtl_agent_loop run --candidate-id mac_baseline_4x4_dw16
```

Manual bounded stage checks:

```bash
make verify_candidate CANDIDATE_ID=mac_baseline_4x4_dw16 RUN_DIR=/tmp/rtl_agent_loop/mac_verify
make implement_candidate CANDIDATE_ID=mac_baseline_4x4_dw16 RUN_DIR=/tmp/rtl_agent_loop/mac_impl
make perf_candidate CANDIDATE_ID=mac_baseline_4x4_dw16 RUN_DIR=/tmp/rtl_agent_loop/mac_perf
make score_candidate CANDIDATE_ID=mac_baseline_4x4_dw16
```

Ranking and status:

```bash
python3 -m rtl_agent_loop status --candidate-id mac_baseline_4x4_dw16 --runs --lineage
python3 -m rtl_agent_loop rank-candidates --active-schema-only
```

Run the minimal closed-loop optimizer:

```bash
python3 -m rtl_agent_loop optimize \
  --iterations 1 \
  --seed-candidate-id mac_baseline_4x4_dw16 \
  --top-k 1 \
  --mutations-per-parent 1 \
  --worktree-ref localopt
```

The exact server-validated variant used:

```bash
python3 -m rtl_agent_loop optimize \
  --iterations 1 \
  --seed-candidate-id mac_baseline_4x4_dw16 \
  --top-k 1 \
  --mutations-per-parent 1 \
  --worktree-ref servercheck
```

Bootstrap the checked-in MAC candidates into SQLite before running canonical studies:

```bash
./scripts/bootstrap_active_mac_candidates.sh
```

That bootstrap intentionally skips optimize-generated manifests whose `source` is `rtl_agent_loop_optimize_v1`, so the starter seed set stays distinct from closed-loop children.

External bounded sweep:

```bash
make -C external/MAC_ARRAY_FPGA sweep_perf_only
make -C external/MAC_ARRAY_FPGA sweep
```

## Artifact Model

Source manifests:

- `candidates/<candidate_id>.json`

Optimize-generated child manifests:

- `candidates/<child_candidate_id>.json`

These remain contributor-visible source manifests, but optimize owns their creation and they should be treated as controller-generated inputs rather than hand-edited study notes.

Canonical registered manifest copy:

- `runs/<candidate_id>/candidate_manifest.json`

Controller-owned run directories:

- `runs/<candidate_id>/attempt_<n>/`

Generated stage result files:

- `fast_verify/fast_verify.json`
- `vivado/vivado_result.json`
- `verilator_perf/verilator_result.json`

Closed-loop optimize session artifacts:

- `var/optimize/<session_id>/search_state.json`
- `var/optimize/<session_id>/summary.json`
- `var/optimize/<session_id>/summary.md`

What a successful optimize session proves:

- the search layer generated or selected candidates deterministically
- candidate registration and lineage stayed inside the controller path
- canonical measured evidence was captured under controller-owned run directories
- scoring and ranking used the latest resolved Vivado and Verilator artifacts
- the session left behind reproducible search memory and a human-readable summary

The controller-owned run directories are the canonical presentation layer for measured evidence. Manual `RUN_DIR=/tmp/...` runs are still useful for exploratory work, but they should be treated as local scratch artifacts unless the same result is reproduced canonically.

Vivado evidence semantics are intentionally split:

- `full_pass`: full implementation evidence and stage success
- `synth_only`: preserved measurement evidence, but provisional and non-passing

When both exist, ranking prefers the newest measurement-usable Vivado artifact, including a newer `synth_only` result over an older full implementation result. That keeps ranking aligned with the latest architecture state while explicitly penalizing provisional implementation evidence.

## Current Design Notes

Useful repo docs:

- [docs/mac_array_tradeoff_study.md](./docs/mac_array_tradeoff_study.md)
- [docs/current_evidence_index.md](./docs/current_evidence_index.md)
- [docs/repository_design.md](./docs/repository_design.md)
- [external/MAC_ARRAY_FPGA/docs/architecture.md](./external/MAC_ARRAY_FPGA/docs/architecture.md)
- [external/MAC_ARRAY_FPGA/docs/measurement_plan.md](./external/MAC_ARRAY_FPGA/docs/measurement_plan.md)
- [external/MAC_ARRAY_FPGA/docs/variant_definitions.md](./external/MAC_ARRAY_FPGA/docs/variant_definitions.md)

## Research Signal

The strongest current signal in this repo is not “AI orchestration.” It is:

- deterministic experiment ownership
- measured architecture tradeoffs
- preserved partial-failure evidence such as synth-only Vivado outcomes
- transparent ranking and provenance
- a real external accelerator platform with bounded but meaningful microarchitectural variation
- a thin evidence-driven search layer rather than a generic scheduler

## V2 Gaps

The current `optimize` flow intentionally stops at:

- deterministic seed selection and one-parameter mutation
- JSON-backed learned exclusions
- session-local evidence summaries

It does not yet include richer mutation strategies, SQLite-backed search memory, or broader search policies.

## Next Small Fix

The highest-value next hardening step is narrow wrapper metadata, not a broader optimizer redesign:

- emit structured Vivado failure phase and reason fields in wrapper result JSON so failed implementation runs are less dependent on message-text heuristics when full implementation closure is unavailable
