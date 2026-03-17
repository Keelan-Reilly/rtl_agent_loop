# Current Execution Status

## Completed Use Cases

- Canonical controller-owned single-candidate evaluation: completed for baseline 4x4, baseline 8x4, baseline 8x8, shared 4x4, shared 8x4, shared 8x8, replicated 4x4, replicated 8x4, and replicated 8x8 stress.
- Active-schema ranking and best-candidate flow: regenerated against the refreshed canonical set.
- Score-policy sensitivity analysis: regenerated.
- Canonical vs sweep reconciliation: completed for overlapping points using the current sweep CSV.

## Incomplete Or Compute-Bound Use Cases

- External full bounded sweep refresh may still be in progress; check the live `make -C external/MAC_ARRAY_FPGA sweep` job before treating the broader sweep as fully refreshed.

## Strongest Artifacts

- Canonical controller-owned full-pass runs under `runs/<candidate_id>/attempt_<n>/` are the strongest evidence tier.
- `mac_replicated_8x8_c2_dw16` synth-only canonical run is strong provisional evidence for an implementation limit.

## Stale Or Provisional Artifacts

- The current external sweep still contains a stale-looking `replicated_8x8_c2` implementation row until a fresh full sweep replaces it.
- The current external sweep does not yet include `shared_8x8_sf2`, so controller vs sweep comparison is not yet available for that point.
- Sweep CSV presence at generation time: `present`.
