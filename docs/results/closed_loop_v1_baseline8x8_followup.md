# Closed-Loop V1 Baseline 8x8 Follow-Up

## Question

Starting from the non-shared wide design `mac_baseline_8x8_dw16`, can the closed-loop v1 move toward the shared `8x8` region, or otherwise generate evidence consistent with the rule that sharing becomes worthwhile when DSP pressure is the real constraint?

## Study Plan

This was a deliberately small follow-up on the real Vivado server.

- Seed budget used: 1
- Optimize iteration budget used: 2
- Search policy: unchanged v1 optimizer
- Evidence standard: canonical controller-owned runs under `runs/<candidate_id>/attempt_<n>/`

Exact command run:

```bash
python3 -m rtl_agent_loop optimize \
  --iterations 2 \
  --seed-candidate-id mac_baseline_8x8_dw16 \
  --top-k 1 \
  --mutations-per-parent 1 \
  --worktree-ref clv1baseline8x8
```

Companion inspection commands:

```bash
python3 -m rtl_agent_loop rank-candidates --active-schema-only
python3 -m rtl_agent_loop status --candidate-id mac_baseline_8x8_dw16 --lineage --runs
python3 -m rtl_agent_loop status --candidate-id mac_shared_8x8_sf2_dw16 --lineage --runs
python3 -m rtl_agent_loop status --candidate-id mac_baseline_8x8_dw16_opt_array_m_4 --lineage --runs
python3 -m rtl_agent_loop status --candidate-id mac_baseline_8x8_dw16_opt_array_m_4_opt_arch_variant_2 --lineage --runs
```

Session artifacts:

- `var/optimize/20260418T011206Z_clv1baseline8x8/`

## Existing 8x8 Context

The measured pool already contains both wide endpoints of interest:

| Candidate | Variant | Latency | LUT | DSP | WNS | Score |
| --- | --- | ---: | ---: | ---: | ---: | ---: |
| `mac_baseline_8x8_dw16` | baseline | 70 | 2730 | 64 | 1.490 | -64.802 |
| `mac_shared_8x8_sf2_dw16` | shared | 74 | 2749 | 32 | 1.571 | -48.834 |

Important context:

- the shared `8x8` point is already present in the registered measured pool
- that means optimize will not generate a duplicate child with the same parameter set
- so the question is not “will it rediscover an already-known exact duplicate?”
- the real question is whether baseline-side nearby mutations produce evidence that is consistent with the existing measured advantage of the shared `8x8` point

## What The Optimizer Did

The deterministic mutation order did what the current v1 implementation says it should do.

At iteration 1:

- optimize considered the seed `mac_baseline_8x8_dw16`
- the exact shared `8x8` parameter point was already known in the candidate pool, so it was not regenerated
- optimize advanced to the next unseen deterministic mutation and generated:
  - `mac_baseline_8x8_dw16_opt_array_m_4`

At iteration 2:

- the first child was rankable and fully measured, so optimize followed that lineage
- it generated:
  - `mac_baseline_8x8_dw16_opt_array_m_4_opt_arch_variant_2`

Generated child candidates:

- `mac_baseline_8x8_dw16_opt_array_m_4`
- `mac_baseline_8x8_dw16_opt_array_m_4_opt_arch_variant_2`

## Measured Outcomes

### Child 1: `mac_baseline_8x8_dw16_opt_array_m_4`

Canonical run:

- `runs/mac_baseline_8x8_dw16_opt_array_m_4/attempt_0001/`

Outcome:

- full fast verify
- full Vivado implementation evidence
- full Verilator performance evidence
- classification: `full_pass`

Measured result:

| Candidate | Latency | LUT | DSP | WNS | Score |
| --- | ---: | ---: | ---: | ---: | ---: |
| `mac_baseline_8x8_dw16` | 70 | 2730 | 64 | 1.490 | -64.802 |
| `mac_baseline_8x8_dw16_opt_array_m_4` | 38 | 1408 | 32 | 2.851 | -28.720 |

Interpretation:

- this child is effectively a narrower baseline point, not a movement into the shared region
- it improved score materially by shrinking the design rather than by making the wide non-shared region better
- this does not weaken the sharing rule; it reinforces that the baseline `8x8` point itself is paying for width with very high DSP demand

### Child 2: `mac_baseline_8x8_dw16_opt_array_m_4_opt_arch_variant_2`

Canonical run:

- `runs/mac_baseline_8x8_dw16_opt_array_m_4_opt_arch_variant_2/attempt_0001/`

Outcome:

- full fast verify
- full Vivado implementation evidence
- full Verilator performance evidence
- classification: `perf_regressed`

Measured result:

| Candidate | Latency | LUT | DSP | WNS | Score | Outcome |
| --- | ---: | ---: | ---: | ---: | ---: | --- |
| `mac_baseline_8x8_dw16_opt_array_m_4` | 38 | 1408 | 32 | 2.851 | -28.720 | parent |
| `mac_baseline_8x8_dw16_opt_array_m_4_opt_arch_variant_2` | 38 | 2450 | 64 | 1.595 | -57.652 | `perf_regressed` |

Rejected region:

- `ARCH_VARIANT:0->2`

Interpretation:

- once the optimizer had a rankable narrowed baseline child, moving to the replicated architecture increased LUT sharply and doubled DSP from `32` to `64` without any latency benefit
- this was rejected by full measured evidence through scoring, not by a wrapper heuristic

## Best Candidates Considered

Within this bounded baseline-side session:

- best generated child: `mac_baseline_8x8_dw16_opt_array_m_4`
- rejected child: `mac_baseline_8x8_dw16_opt_array_m_4_opt_arch_variant_2`

In the broader measured pool, the known shared `8x8` point still remains better than the original baseline `8x8` point:

- `mac_shared_8x8_sf2_dw16`: `-48.834`
- `mac_baseline_8x8_dw16`: `-64.802`

## Supported And Rejected Regions

Supported region observed in this session:

- `ARRAY_M:8->4` from `mac_baseline_8x8_dw16` -> full measured improvement, but by shrinking the problem, not by making the wide non-shared architecture intrinsically better

Rejected region observed in this session:

- `ARCH_VARIANT:0->2` from `mac_baseline_8x8_dw16_opt_array_m_4` -> `perf_regressed`

Important non-event:

- the optimizer did not create a new shared `8x8` child because that exact parameter point already exists in the candidate pool and v1 intentionally avoids duplicate candidates

## Conclusion

This follow-up strengthens the design-rule story, but with one important nuance.

The closed-loop v1 did not generate a new shared `8x8` child from the baseline side, because the exact shared `8x8` point was already present and measured. That is expected v1 behavior, not a failure.

Even so, the result still strengthens the earlier conclusion:

- the optimizer could not find a better nearby wide non-shared direction from `mac_baseline_8x8_dw16`
- its first useful move was to shrink the design to a cheaper baseline point
- once it explored a replicated architectural move from that lineage, the child was rejected by full measured evidence
- the already-measured shared `8x8` point remains the better wide design relative to the original baseline `8x8`, mainly because it halves DSP from `64` to `32` with nearly flat LUT and only a modest latency increase

So from the non-shared side, the evidence remains consistent with the same rule:

> sharing becomes worthwhile when it relieves the genuinely limiting resource, and at the wide `8x8` point that resource pressure is visible in DSP demand

## What This Adds To The Repo Story

The repo’s intended purpose is now demonstrated from both directions:

- from shared seeds, closed-loop runs rejected bad moves using full and synth-only implementation evidence
- from the wide baseline seed, the optimizer failed to find a compelling nearby non-shared alternative and instead produced evidence that wide baseline pressure is real while replication-like moves regress

This is a good control-plane result:

- the system did not hallucinate a better answer
- it used the existing measured pool plus new controller-owned runs to reinforce a real hardware design rule

## Next Highest-Value Experiment

The clearest next small experiment is:

- one bounded session from `mac_baseline_8x4_dw16`

Why that one:

- unlike the `8x8` case, it gives a non-shared wide seed where the shared-side comparison is still meaningful but the exact “known duplicate shared target” issue is less likely to dominate the interpretation
- it would test whether the same resource-relief rule shows up at the intermediate width, not just the widest bounded point
