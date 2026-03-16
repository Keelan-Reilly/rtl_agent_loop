# Convolution Parallelism Experiment

## Scope

This experiment adds a single architectural knob, `CONV_CHANNEL_PAR`, to the `CNN_FPGA` convolution stage and evaluates it through the canonical `rtl_agent_loop` flow for three candidates:

| candidate_id | DATA_WIDTH | FRAC_BITS | DENSE_OUT_PAR | CONV_VARIANT | CONV_CHANNEL_PAR |
|---|---:|---:|---:|---|---:|
| `conv1_dw12_fb6` | 12 | 6 | 1 | `baseline` | 1 |
| `conv2_dw12_fb6` | 12 | 6 | 1 | `baseline` | 2 |
| `conv4_dw12_fb6` | 12 | 6 | 1 | `baseline` | 4 |

All three candidates were registered under the lineage root `conv1_dw12_fb6` and run with:

```bash
python3 -m rtl_agent_loop run --candidate-id <candidate_id> --worktree-ref conv_parallelism_experiment
```

## Results

| candidate_id | latency_cycles | throughput_inferences_per_sec | conv_stage_cycles | LUT | DSP | WNS (ns) | est. Fmax (MHz) |
|---|---:|---:|---:|---:|---:|---:|---:|
| `conv1_dw12_fb6` | 465,732 | 214.716 | 344,962 | 2,770 | 8 | -0.664 | 93.77 |
| `conv2_dw12_fb6` | 465,732 | 214.716 | 344,962 | 2,863 | 9 | -0.322 | 96.88 |
| `conv4_dw12_fb6` | 465,732 | 214.716 | 344,962 | 3,083 | 11 | -0.482 | 95.40 |

Additional stage context from the Verilator performance runs was identical across all three points:

- `stage_cycles_conv = 344,962`
- `stage_cycles_relu = 25,090`
- `stage_cycles_pool = 32,930`
- `stage_cycles_dense = 62,732`

Convolution remains the dominant stage at about 74.1% of total measured frame latency (`344,962 / 465,732`), but the measured conv-stage cycle count did not change across the three architectural points.

## Interpretation

Latency vs parallelism:
Increasing `CONV_CHANNEL_PAR` from 1 to 2 to 4 did not improve measured accelerator latency or throughput. End-to-end latency stayed at `465,732` cycles and throughput stayed at `214.716` inferences/s for all three runs.

Area vs parallelism:
Area increased monotonically with wider convolution channel parallelism. Relative to `conv1_dw12_fb6`, `conv2_dw12_fb6` added 93 LUTs and 1 DSP, while `conv4_dw12_fb6` added 313 LUTs and 3 DSPs.

Timing closure:
None of the three candidates met timing at the 10.0 ns target. `conv2_dw12_fb6` had the best slack at `-0.322 ns`, improving on the baseline `-0.664 ns`. `conv4_dw12_fb6` regressed slightly versus `conv2_dw12_fb6` to `-0.482 ns`, though it still outperformed the baseline.

End-to-end latency impact:
In the checked-in accelerator, `top_level` still fixes `IN_CHANNELS=1`. That means the new `CONV_CHANNEL_PAR` hardware is structurally present and does affect area/timing, but the deployed network cannot feed more than one convolution input channel per tap group. As a result, the experiment shows no latency reduction despite convolution dominating runtime.

## Conclusion

For the current `CNN_FPGA` top-level design, widening `CONV_CHANNEL_PAR` is not a beneficial end-to-end optimization. The best-ranked point under the unchanged scoring policy is still `conv1_dw12_fb6`, because `conv2_dw12_fb6` and `conv4_dw12_fb6` spend extra LUT/DSP/BRAM budget without reducing latency. The results do show that `conv2_dw12_fb6` modestly improves timing margin, so this knob could become performance-relevant only after the accelerator is integrated with a convolution stage that actually exposes more than one input channel at runtime.
