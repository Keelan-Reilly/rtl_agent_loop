# Closed-Loop V1 Case Study

## Question

Can the validated closed-loop v1 recover or support the earlier manual rule that compute sharing is only worth its fixed cost when it relieves the genuinely limiting resource, while rejecting bad architectural moves using real implementation feedback?

## Study Plan

This was a deliberately small closed-loop study on the real Vivado server.

- Seed budget: 2
- Optimize iteration budget used: 2 total
- Search policy: unchanged v1 optimizer
- Evidence standard: canonical controller-owned runs under `runs/<candidate_id>/attempt_<n>/`

The study used the existing measured candidate pool plus two single-iteration optimize sessions seeded from already-measured shared designs:

- `mac_shared_4x4_sf2_dw16`
- `mac_shared_8x8_sf2_dw16`

Those seeds were chosen because the earlier bounded study already showed the core tradeoff:

- sharing adds fixed schedule and control cost
- sharing can still be worth it when it materially relieves DSP pressure

## Commands Run

```bash
python3 -m rtl_agent_loop rank-candidates --active-schema-only

python3 -m rtl_agent_loop optimize \
  --iterations 1 \
  --seed-candidate-id mac_shared_4x4_sf2_dw16 \
  --top-k 1 \
  --mutations-per-parent 1 \
  --worktree-ref clv1shared4x4

python3 -m rtl_agent_loop optimize \
  --iterations 1 \
  --seed-candidate-id mac_shared_8x8_sf2_dw16 \
  --top-k 1 \
  --mutations-per-parent 1 \
  --worktree-ref clv1shared8x8

python3 -m rtl_agent_loop status --candidate-id mac_shared_4x4_sf2_dw16_opt_array_n_8 --lineage --runs
python3 -m rtl_agent_loop status --candidate-id mac_shared_8x8_sf2_dw16_opt_arch_variant_2_share_factor_1 --lineage --runs
```

Optimize session artifacts:

- `var/optimize/20260418T004501Z_clv1shared4x4/`
- `var/optimize/20260418T004719Z_clv1shared8x8/`

## Existing Measured Context

The current ranked pool already contains the key canonical comparison points:

| Candidate | Latency | LUT | DSP | WNS | Score |
| --- | ---: | ---: | ---: | ---: | ---: |
| `mac_shared_4x4_sf2_dw16` | 26 | 695 | 8 | 2.024 | -9.066 |
| `mac_baseline_4x4_dw16` | 22 | 689 | 16 | 3.028 | -10.992 |
| `mac_shared_8x8_sf2_dw16` | 74 | 2749 | 32 | 1.571 | -48.834 |
| `mac_baseline_8x8_dw16` | 70 | 2730 | 64 | 1.490 | -64.802 |

This is the manual-rule backdrop:

- At `4x4`, sharing does not buy LUT, and it costs latency, but it halves DSP from `16` to `8`.
- At `8x8`, sharing again costs some latency, but it halves DSP from `64` to `32` with nearly flat LUT (`2730` to `2749`).

So the pre-existing measured pool already suggests that sharing is only attractive when the DSP reduction matters enough to offset its fixed overhead.

## Closed-Loop Runs

### Session 1: `mac_shared_4x4_sf2_dw16`

Session:

- `var/optimize/20260418T004501Z_clv1shared4x4/`

Generated child:

- `mac_shared_4x4_sf2_dw16_opt_array_n_8`

Canonical run:

- `runs/mac_shared_4x4_sf2_dw16_opt_array_n_8/attempt_0001/`

Outcome:

- full controller-owned run completed through scoring
- Vivado evidence kind: `implementation`
- classification: `perf_regressed`

Measured child result:

| Candidate | Latency | LUT | DSP | WNS | Score | Outcome |
| --- | ---: | ---: | ---: | ---: | ---: | --- |
| `mac_shared_4x4_sf2_dw16` | 26 | 695 | 8 | 2.024 | -9.066 | parent |
| `mac_shared_4x4_sf2_dw16_opt_array_n_8` | 42 | 1415 | 16 | 1.477 | -23.542 | `perf_regressed` |

Rejected region:

- `ARRAY_N:4->8`

Interpretation:

- The optimizer widened the shared design, but the real implementation-backed child doubled LUT, doubled DSP, and increased latency from `26` to `42` cycles.
- This was not rejected by a heuristic log parser. It was rejected after a full fast verify plus Vivado plus Verilator plus scoring path.

### Session 2: `mac_shared_8x8_sf2_dw16`

Session:

- `var/optimize/20260418T004719Z_clv1shared8x8/`

Generated child:

- `mac_shared_8x8_sf2_dw16_opt_arch_variant_2_share_factor_1`

Canonical run:

- `runs/mac_shared_8x8_sf2_dw16_opt_arch_variant_2_share_factor_1/attempt_0001/`

Outcome:

- fast verify passed
- Vivado ended in `synth_only`
- classification: `synth_only_measurement`

Preserved synthesis evidence:

| Candidate | LUT | FF | DSP | WNS | Evidence |
| --- | ---: | ---: | ---: | ---: | --- |
| `mac_shared_8x8_sf2_dw16` | 2749 | 4206 | 32 | 1.571 | full implementation |
| `mac_shared_8x8_sf2_dw16_opt_arch_variant_2_share_factor_1` | 41876 | 4206 | 0 | 2.935 | synth-only |

Rejected region:

- `ARCH_VARIANT:1->2|SHARE_FACTOR:2->1`

Interpretation:

- This mutation explicitly removed sharing from the widest shared point and pushed the design toward brute-force replication.
- The controller preserved the failed implementation as reusable evidence instead of discarding it.
- Even without a completed performance run, the synth-only evidence was enough to show the move was not credible: LUT exploded to `41876`, implementation did not close, and the optimizer rejected the region.

## Best Candidates Found

No optimize-generated child displaced the existing best measured design.

Best candidates after the study:

- best numeric score: `mac_shared_4x4_sf2_dw16`
- best timing-clean candidate: `mac_shared_4x4_sf2_dw16`

That is useful in itself: the closed-loop runs spent real implementation budget, generated new children deterministically, and still concluded that the already-measured shared point remained the strongest candidate under the current score policy.

## Rejected Regions

From the two bounded optimize sessions:

- `ARRAY_N:4->8` from `mac_shared_4x4_sf2_dw16` -> rejected as `perf_regressed`
- `ARCH_VARIANT:1->2|SHARE_FACTOR:2->1` from `mac_shared_8x8_sf2_dw16` -> rejected as `synth_only_measurement`

These are different failure modes, and both are useful:

- one child was rejected after full implementation and performance evidence
- one child was rejected using preserved partial Vivado evidence when full implementation closure failed

## Evidence-Based Takeaways

1. The closed-loop v1 does not need a large sweep to reject obviously bad architectural moves.
   One optimize iteration from the `4x4` shared seed was enough to produce a fully measured child and classify it as a real scored regression.

2. The closed-loop v1 preserves failed implementation evidence in a way that is actually decision-useful.
   The `8x8` mutation away from sharing did not disappear into a failed job log; it became a controller-owned synth-only artifact and a rejected search region.

3. The new closed-loop evidence is consistent with the earlier manual design rule.
   Sharing pays a fixed latency/control cost, but at wider points it is still the move that relieves the meaningful resource pressure. Moving away from sharing at `8x8` immediately ran into implementation trouble, while widening the smaller shared point produced a full measured regression rather than a new winner.

## Conclusion

Yes. This small real-server study supports the earlier manual conclusion:

> compute sharing is only worth its fixed cost when it relieves the genuinely limiting resource

The existing measured pool already showed that shared points mainly earn their keep by reducing DSP demand, not by improving latency or LUT. The new closed-loop runs reinforced that rule:

- when sharing was widened in a way that increased both latency and implementation cost, the child was rejected as a scored regression
- when sharing was removed from a wide resource-stressed point, the child failed to reach full implementation and was rejected using preserved synth-only evidence

## What This Demonstrates About Repo Value

This is the value proposition of `rtl_agent_loop` in a compact form:

- it turns real synthesis, implementation, timing, and performance feedback into searchable evidence
- it preserves provenance through deterministic child generation, lineage registration, and controller-owned artifacts
- it can reject bad architectural regions quickly without pretending every experiment must complete perfectly to be useful

## Next Highest-Value Experiment

The next highest-value experiment is still small:

- run one bounded closed-loop session starting from `mac_baseline_8x8_dw16` to see whether the optimizer can rediscover the shared `8x8` region from the non-shared side using the existing measured pool plus one or two additional mutations

That would test the same design rule from the opposite direction without broadening the optimizer itself.
