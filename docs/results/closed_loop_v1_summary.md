# Closed-Loop V1 Summary

## What This Repo Does Now

rtl_agent_loop is now a deterministic, lineage-preserving hardware exploration control plane for the external MAC_ARRAY_FPGA design, with a validated closed-loop optimize layer built on top of real FPGA implementation feedback.

In practical terms, it provides:

- explicit candidate manifests
- lineage-preserving candidate registration
- canonical controller-owned run artifacts under `runs/<candidate_id>/attempt_<n>/`
- deterministic execution through fast verify, Vivado, Verilator perf, and scoring
- SQLite-backed provenance
- a thin closed-loop `optimize` layer that turns implementation feedback into searchable evidence

This is not a speculative optimizer mockup. The closed-loop v1 path has been validated on the real Vivado server.

## What Was True Before Closed-Loop

Before `optimize`, the repo already had the core measured architecture story through canonical runs and manual study work:

- `mac_baseline_8x8_dw16`: `2730 LUT`, `64 DSP`, `70 cycles`, score `-64.802`
- `mac_shared_8x8_sf2_dw16`: `2749 LUT`, `32 DSP`, `74 cycles`, score `-48.834`
- `mac_baseline_4x4_dw16`: `689 LUT`, `16 DSP`, `22 cycles`, score `-10.992`
- `mac_shared_4x4_sf2_dw16`: `695 LUT`, `8 DSP`, `26 cycles`, score `-9.066`

That manual measured evidence already suggested the core rule:

> compute sharing is only worth its fixed cost when it relieves the genuinely limiting resource

At small points, sharing pays latency and control overhead and does not obviously help LUT. At wider points, sharing becomes more credible because it materially reduces DSP pressure while leaving LUT nearly flat.

## What Closed-Loop Adds

The closed-loop v1 layer adds a disciplined way to turn that architectural question into an evidence loop:

- generate deterministic child candidates
- register them through the same controller with lineage preserved
- run them through the same canonical flow
- keep successful and partial-failure evidence under controller ownership
- record rejected regions in persistent optimize session artifacts under `var/optimize/<session_id>/`

The important addition is not “automation” by itself. It is that architecture decisions can now be supported or rejected by controller-owned evidence rather than by ad hoc interpretation alone.

## What The Two Bounded Case Studies Showed

### Shared-Side Study

From shared seeds, the closed-loop system produced two useful rejections:

- a fully measured child that completed fast verify, Vivado, Verilator perf, and scoring, then was rejected as `perf_regressed`
- a wider shared-side mutation that failed to reach full implementation but was still rejected using preserved `synth_only` Vivado evidence

This showed that the system can reject bad architectural moves using both:

- full implementation plus performance evidence
- preserved partial implementation evidence

### Baseline-Side 8x8 Follow-Up

From the wide non-shared seed `mac_baseline_8x8_dw16`, the system did not invent a better wide non-shared answer.

Instead:

- the first useful child improved only by shrinking the design (`ARRAY_M:8->4`)
- the next replicated-style move from that lineage was rejected as `perf_regressed` with full measured evidence

This is important because it tests the same rule from the opposite direction:

- from the shared side, bad moves were rejected
- from the wide baseline side, the search still failed to find a better nearby non-shared alternative

## Supported Design Rule

The same design rule is now supported by both manual evidence and closed-loop evidence:

> compute sharing is worth its fixed latency and control cost only when it relieves the resource that is actually constraining the design

The combined evidence says:

- sharing is not “free”; it adds schedule/control overhead
- sharing is not automatically better at small points
- at wider points, the meaningful benefit is DSP relief
- moving away from that relief either regresses score under full measurement or fails to close implementation cleanly

## Why This Matters

This is the repo’s strongest current story:

- it is a real hardware result-generation system, not just a workflow wrapper
- it preserves provenance while exploring architecture mutations
- it can learn from both successful runs and incomplete implementation outcomes
- it makes hardware iteration faster by turning implementation feedback into reusable search evidence

For a technically strong reader, the main point is simple:

the repo now demonstrates that a thin, deterministic closed-loop layer can produce credible architecture conclusions without abandoning artifact ownership, reproducibility, or measured hardware reality.

## Out Of Scope For V1

The current v1 intentionally does not include:

- richer search methods
- scheduler or worker infrastructure
- SQLite-backed optimize memory
- Bayesian or RL policies
- GUI layers

The value of v1 is narrower and more concrete:

- deterministic candidate generation
- controller-owned evidence capture
- lineage-aware search bookkeeping
- credible rejection and support of architecture moves using real implementation feedback

## Key Source Notes

- [mac_array_tradeoff_study.md](docs/mac_array_tradeoff_study.md)
- [closed_loop_v1_case_study.md](docs/results/closed_loop_v1_case_study.md)
- [closed_loop_v1_baseline8x8_followup.md](docs/results/closed_loop_v1_baseline8x8_followup.md)
- [canonical_mac_results.md](docs/results/canonical_mac_results.md)
