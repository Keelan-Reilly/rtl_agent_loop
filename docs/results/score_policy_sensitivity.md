# Score Policy Sensitivity

This report recomputes rankings over the current canonical MAC candidates using alternative score policies.

## Evidence Set

- `mac_shared_4x4_sf2_dw16`
- `mac_baseline_4x4_dw16`
- `mac_replicated_4x4_c2_dw16`
- `mac_baseline_8x4_dw16`

## Policy Winners

| Policy | Winner | Ordering |
| --- | --- | --- |
| Default current policy | `mac_shared_4x4_sf2_dw16` | `mac_shared_4x4_sf2_dw16` > `mac_baseline_4x4_dw16` > `mac_replicated_4x4_c2_dw16` > `mac_baseline_8x4_dw16` |
| Latency-priority policy | `mac_shared_4x4_sf2_dw16` | `mac_shared_4x4_sf2_dw16` > `mac_baseline_4x4_dw16` > `mac_replicated_4x4_c2_dw16` > `mac_baseline_8x4_dw16` |
| Area-priority policy | `mac_shared_4x4_sf2_dw16` | `mac_shared_4x4_sf2_dw16` > `mac_baseline_4x4_dw16` > `mac_replicated_4x4_c2_dw16` > `mac_baseline_8x4_dw16` |
| Timing-priority policy | `mac_replicated_4x4_c2_dw16` | `mac_replicated_4x4_c2_dw16` > `mac_baseline_4x4_dw16` > `mac_shared_4x4_sf2_dw16` > `mac_baseline_8x4_dw16` |
| Balanced no-throughput policy | `mac_shared_4x4_sf2_dw16` | `mac_shared_4x4_sf2_dw16` > `mac_baseline_4x4_dw16` > `mac_replicated_4x4_c2_dw16` > `mac_baseline_8x4_dw16` |

## Interpretation

- The winner changes across policies, so the repo should treat the current best-candidate result as policy-sensitive rather than universally robust.
- Direct measured architecture findings remain stable across policies: shared cuts DSP materially at 4x4, replicated preserves baseline-like latency while increasing area, and baseline scaling raises both latency and cost.
- The official controller ranking remains useful, but it should be read as one explicit policy view rather than a policy-free architectural truth.

## Policy Details

| Policy | Candidate | Rank | Score | Latency | LUT | DSP | WNS |
| --- | --- | ---: | ---: | ---: | ---: | ---: | ---: |
| Default current policy | `mac_shared_4x4_sf2_dw16` | 1 | -9.066 | 26.0 | 695.0 | 8.0 | 2.024 |
| Default current policy | `mac_baseline_4x4_dw16` | 2 | -10.992 | 22.0 | 689.0 | 16.0 | 3.028 |
| Default current policy | `mac_replicated_4x4_c2_dw16` | 3 | -22.210 | 22.0 | 1212.0 | 32.0 | 4.034 |
| Default current policy | `mac_baseline_8x4_dw16` | 4 | -28.720 | 38.0 | 1408.0 | 32.0 | 2.851 |
| Latency-priority policy | `mac_shared_4x4_sf2_dw16` | 1 | -2.850 | 26.0 | 695.0 | 8.0 | 2.024 |
| Latency-priority policy | `mac_baseline_4x4_dw16` | 2 | -2.947 | 22.0 | 689.0 | 16.0 | 3.028 |
| Latency-priority policy | `mac_replicated_4x4_c2_dw16` | 3 | -5.910 | 22.0 | 1212.0 | 32.0 | 4.034 |
| Latency-priority policy | `mac_baseline_8x4_dw16` | 4 | -9.085 | 38.0 | 1408.0 | 32.0 | 2.851 |
| Area-priority policy | `mac_shared_4x4_sf2_dw16` | 1 | -23.096 | 26.0 | 695.0 | 8.0 | 2.024 |
| Area-priority policy | `mac_baseline_4x4_dw16` | 2 | -29.967 | 22.0 | 689.0 | 16.0 | 3.028 |
| Area-priority policy | `mac_replicated_4x4_c2_dw16` | 3 | -55.421 | 22.0 | 1212.0 | 32.0 | 4.034 |
| Area-priority policy | `mac_baseline_8x4_dw16` | 4 | -63.784 | 38.0 | 1408.0 | 32.0 | 2.851 |
| Timing-priority policy | `mac_replicated_4x4_c2_dw16` | 1 | 11.877 | 22.0 | 1212.0 | 32.0 | 4.034 |
| Timing-priority policy | `mac_baseline_4x4_dw16` | 2 | 11.133 | 22.0 | 689.0 | 16.0 | 3.028 |
| Timing-priority policy | `mac_shared_4x4_sf2_dw16` | 3 | 6.682 | 26.0 | 695.0 | 8.0 | 2.024 |
| Timing-priority policy | `mac_baseline_8x4_dw16` | 4 | 2.903 | 38.0 | 1408.0 | 32.0 | 2.851 |
| Balanced no-throughput policy | `mac_shared_4x4_sf2_dw16` | 1 | -7.566 | 26.0 | 695.0 | 8.0 | 2.024 |
| Balanced no-throughput policy | `mac_baseline_4x4_dw16` | 2 | -8.794 | 22.0 | 689.0 | 16.0 | 3.028 |
| Balanced no-throughput policy | `mac_replicated_4x4_c2_dw16` | 3 | -17.069 | 22.0 | 1212.0 | 32.0 | 4.034 |
| Balanced no-throughput policy | `mac_baseline_8x4_dw16` | 4 | -22.643 | 38.0 | 1408.0 | 32.0 | 2.851 |
