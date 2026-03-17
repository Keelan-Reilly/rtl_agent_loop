# MAC Array Tradeoff Study

This note summarizes the current bounded MAC-array study attached to `rtl_agent_loop`.

## Study Question

When does structural sharing or flexibility outperform brute-force replication in bounded spatial MAC accelerators under FPGA implementation constraints?

## Variants

- `baseline`: one active PE per logical lane, simple schedule, no sharing
- `shared`: fewer physical PEs with phased operand sharing and extra mux/control logic
- `replicated`: baseline-style active datapath plus preserved shadow replication for implementation-cost study

## Measurement Flow

Two evidence tiers are used deliberately:

1. Canonical controller-owned runs under `runs/<candidate_id>/attempt_<n>/`
2. External bounded sweep evidence under `external/MAC_ARRAY_FPGA/experiments/results/`

Canonical runs are the strongest evidence tier in this repo because they are owned by the controller, recorded in SQLite, and resolved through the same ranking logic used for candidate comparison. External sweep results provide broader context across more study points.

## Canonical Candidate Set

The first canonical MAC study now includes these active-schema candidates:

- `mac_baseline_4x4_dw16`
- `mac_baseline_8x4_dw16`
- `mac_shared_4x4_sf2_dw16`
- `mac_replicated_4x4_c2_dw16`

## Canonical Results

### 4x4 architecture comparison

| Candidate | Variant | Latency (cycles) | LUT | DSP | WNS (ns) | Score |
| --- | --- | ---: | ---: | ---: | ---: | ---: |
| `mac_baseline_4x4_dw16` | baseline | 22 | 689 | 16 | 3.028 | -10.992 |
| `mac_shared_4x4_sf2_dw16` | shared | 26 | 695 | 8 | 2.024 | -9.066 |
| `mac_replicated_4x4_c2_dw16` | replicated | 22 | 1212 | 32 | 4.034 | -22.210 |

Interpretation:

- Shared mode pays a real scheduling penalty at 4x4: `26` cycles versus the baseline `22`.
- Shared mode does not materially reduce LUT relative to baseline at this point, but it does halve DSP usage from `16` to `8`.
- Replication preserves baseline-like latency at `22` cycles, but its area cost is obvious: `1212` LUT and `32` DSP versus `689` LUT and `16` DSP for baseline.
- Replication also improves timing slack at this point, with `4.034 ns` WNS versus `3.028 ns` for baseline and `2.024 ns` for shared.

### Baseline scaling

| Candidate | ARRAY_M x ARRAY_N | Latency (cycles) | LUT | DSP | WNS (ns) | Score |
| --- | --- | ---: | ---: | ---: | ---: | ---: |
| `mac_baseline_4x4_dw16` | 4x4 | 22 | 689 | 16 | 3.028 | -10.992 |
| `mac_baseline_8x4_dw16` | 8x4 | 38 | 1408 | 32 | 2.851 | -28.720 |

Interpretation:

- Moving from `4x4` to `8x4` materially increases both latency and implementation cost in the canonical flow.
- The current MAC platform is therefore no longer “flat” with respect to array size; the bounded study points now express real schedule and structural scaling.

## Active Ranking

The current active-schema controller ranking is published at [active_mac_ranking.md](/home/keelan/rtl_agent_loop/docs/results/active_mac_ranking.md).

Under the current score weights, `mac_shared_4x4_sf2_dw16` ranks first among the canonical MAC candidates. That ranking is driven mainly by the current DSP weight and the shared design’s lower DSP count, not by lower latency.

This matters for interpretation:

- the controller score is a transparent weighted heuristic, not an oracle
- the architecture conclusion should still be read alongside the raw latency/LUT/DSP numbers

## Score Policy Sensitivity

The current ranking is not fully policy-robust. A dedicated sensitivity report is published at [score_policy_sensitivity.md](/home/keelan/rtl_agent_loop/docs/results/score_policy_sensitivity.md).

Policy outcomes over the current canonical MAC evidence:

| Policy family | Winner |
| --- | --- |
| default current | `mac_shared_4x4_sf2_dw16` |
| latency-priority | `mac_shared_4x4_sf2_dw16` |
| area-priority | `mac_shared_4x4_sf2_dw16` |
| timing-priority | `mac_replicated_4x4_c2_dw16` |
| balanced no-throughput | `mac_shared_4x4_sf2_dw16` |

Interpretation:

- `mac_shared_4x4_sf2_dw16` remains best under four of the five tested policy variants.
- The winner flips under timing-priority scoring because the replicated point has the strongest measured WNS at `4.034 ns`.
- That means “shared is the best candidate” is a score-policy result, not a policy-free architectural fact.

Robust measured findings are stronger than the winner label:

- shared reduces DSP materially while adding scheduling latency
- replicated preserves baseline-like latency while increasing area
- baseline scaling from `4x4` to `8x4` increases both latency and implementation cost

For a fast visual comparison of the canonical points, see [canonical_latency_vs_lut.svg](/home/keelan/rtl_agent_loop/docs/results/canonical_latency_vs_lut.svg).

## Broader Sweep Context

The external bounded sweep broadens the view beyond the canonical controller set:

- [sweep_summary.md](/home/keelan/rtl_agent_loop/external/MAC_ARRAY_FPGA/experiments/results/sweep_summary.md)
- [sweep_results.csv](/home/keelan/rtl_agent_loop/external/MAC_ARRAY_FPGA/experiments/results/sweep_results.csv)

Current sweep-backed conclusions:

- baseline latency scales monotonically from `4x4` to `8x4` to `8x8`
- shared mode adds measurable schedule overhead relative to the matching baseline points
- preserved replication can keep latency near baseline while driving area sharply upward

Current sweep caveat:

- the broader sweep is still the weaker evidence tier than the canonical controller-owned runs
- the checked-in sweep summary continues to flag `replicated_8x8_c2` as stale-looking until a fresh full sweep replaces it

## Evidence Quality Notes

- Canonical controller-owned runs are the primary evidence tier for candidate comparison.
- External sweep rows are useful for broader trend analysis.
- Synth-only Vivado outcomes are preserved as provisional evidence rather than discarded, but they should not be treated as full implementation passes.
- The current external sweep summary already flags any rows that look stale relative to the current preserved-replication design.
- The strongest conclusions in this note are taken from canonical controller-owned runs, not from the partially stale broad sweep table.

## Limitations

- `PIPE_STAGES` is still a bounded latency-modeling knob, not full arithmetic retiming.
- The canonical controller set is still small; it is representative, not exhaustive.
- The controller’s “best candidate” result depends on the configured weights. For architecture interpretation, raw latency/area/timing tables remain essential.
- The broader sweep packet is still mixed-quality until the currently running full sweep finishes and replaces the flagged stale row.

## Next Experiments

- add canonical `8x8` and larger shared/replicated study points if budget allows
- rerun the full external sweep after any meaningful RTL change to keep the broad trend plots fresh
- test whether a different score weighting or a Pareto-first report better matches the intended architecture question
