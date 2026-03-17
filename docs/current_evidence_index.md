# Current Evidence Index

This is the fastest path through the active MAC-array study artifacts.

## Canonical Controller-Owned Evidence

- [mac_baseline_4x4 attempt_0001](/home/keelan/rtl_agent_loop/runs/mac_baseline_4x4_dw16/attempt_0001)
- [mac_baseline_8x4 attempt_0001](/home/keelan/rtl_agent_loop/runs/mac_baseline_8x4_dw16/attempt_0001)
- [mac_shared_4x4 attempt_0001](/home/keelan/rtl_agent_loop/runs/mac_shared_4x4_sf2_dw16/attempt_0001)
- [mac_replicated_4x4 attempt_0001](/home/keelan/rtl_agent_loop/runs/mac_replicated_4x4_c2_dw16/attempt_0001)

## Controller Reports

- [Active MAC ranking](/home/keelan/rtl_agent_loop/docs/results/active_mac_ranking.md)
- [Best-candidate pointer](/home/keelan/rtl_agent_loop/var/best_candidates.json)
- [Score policy sensitivity](/home/keelan/rtl_agent_loop/docs/results/score_policy_sensitivity.md)
- [Canonical latency vs LUT plot](/home/keelan/rtl_agent_loop/docs/results/canonical_latency_vs_lut.svg)

## Study Notes

- [MAC array tradeoff study](/home/keelan/rtl_agent_loop/docs/mac_array_tradeoff_study.md)
- [Repository design](/home/keelan/rtl_agent_loop/docs/repository_design.md)

## External Sweep Evidence

- [Sweep summary](/home/keelan/rtl_agent_loop/external/MAC_ARRAY_FPGA/experiments/results/sweep_summary.md)
- [Sweep CSV](/home/keelan/rtl_agent_loop/external/MAC_ARRAY_FPGA/experiments/results/sweep_results.csv)
- [Sweep plots](/home/keelan/rtl_agent_loop/external/MAC_ARRAY_FPGA/experiments/results/plots)

Current caveat:

- the canonical controller-owned runs are the strongest evidence tier
- the broad sweep still contains a flagged stale-looking replicated `8x8` row until the fresh full sweep completes

## Evidence Tiers

- `runs/<candidate>/attempt_<n>/`: canonical controller-owned evidence
- `external/MAC_ARRAY_FPGA/experiments/results/`: broader external sweep context
- synth-only Vivado rows: provisional implementation evidence, not full implementation passes
