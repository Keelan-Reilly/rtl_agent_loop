# rtl_agent_loop

`rtl_agent_loop` is a deterministic, local-first FPGA accelerator exploration controller centered on the external [`MAC_ARRAY_FPGA`](./external/MAC_ARRAY_FPGA) repo.

It is designed for bounded architecture studies where we want:

- explicit candidate manifests
- deterministic controller-owned run directories
- fast verification, Vivado, and Verilator perf collection
- SQLite-backed provenance
- transparent scoring and ranking
- reproducible study artifacts rather than ad hoc one-off runs

The hardware implementation boundary stays outside this repo in `external/MAC_ARRAY_FPGA`. This repo is the control plane, experiment ledger, and reporting layer.

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

Bootstrap the checked-in MAC candidates into SQLite before running canonical studies:

```bash
./scripts/bootstrap_active_mac_candidates.sh
```

External bounded sweep:

```bash
make -C external/MAC_ARRAY_FPGA sweep_perf_only
make -C external/MAC_ARRAY_FPGA sweep
```

## Artifact Model

Source manifests:

- `candidates/<candidate_id>.json`

Canonical registered manifest copy:

- `runs/<candidate_id>/candidate_manifest.json`

Controller-owned run directories:

- `runs/<candidate_id>/attempt_<n>/`

Generated stage result files:

- `fast_verify/fast_verify.json`
- `vivado/vivado_result.json`
- `verilator_perf/verilator_result.json`

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
