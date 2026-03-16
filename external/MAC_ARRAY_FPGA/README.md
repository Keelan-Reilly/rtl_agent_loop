# MAC_ARRAY_FPGA

`MAC_ARRAY_FPGA` is a parameterized fixed-point matrix-multiply accelerator repo intended for bounded FPGA microarchitecture studies. It is designed to be used as an external hardware dependency for a control-plane repository such as `rtl_agent_loop`, while remaining understandable and usable on its own.

The platform implements a deterministic GEMM-style workload:

- multiply `A[ARRAY_M x TILE_K]` by `B[TILE_K x ARRAY_N]`
- accumulate into `C[ARRAY_M x ARRAY_N]`
- use fixed-point signed arithmetic
- expose a small, synthesis-friendly top-level interface

The architecture is intentionally bounded and research-oriented. It is not an SoC subsystem, not an AXI design, and not tied to CNN-specific logic.

## Architecture Variants

The same workload can be evaluated across three structural variants:

- `ARCH_BASELINE = 0`: one physical MAC datapath per logical output lane
- `ARCH_SHARED = 1`: fewer physical MAC datapaths per cluster, with explicit operand multiplexing and extra control sequencing
- `ARCH_REPLICATED = 2`: baseline-style active datapaths plus shadow replicated compute for area/timing tradeoff studies

Variant selection is a real synthesizable parameter in [`hdl/top_level.sv`](/home/keelan/rtl_agent_loop/external/MAC_ARRAY_FPGA/hdl/top_level.sv), not an orchestration-only metadata field.

## Top-Level Parameters

The accelerator exposes the following principal parameters:

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

These parameters propagate into subordinate modules and change either control sequencing, physical compute replication, or both.

## Repository Layout

- [`hdl/`](/home/keelan/rtl_agent_loop/external/MAC_ARRAY_FPGA/hdl): SystemVerilog RTL
- [`tb/`](/home/keelan/rtl_agent_loop/external/MAC_ARRAY_FPGA/tb): Verilator-oriented C++ testbenches
- [`python/`](/home/keelan/rtl_agent_loop/external/MAC_ARRAY_FPGA/python): vector generation, golden model, and comparison helpers
- [`experiments/`](/home/keelan/rtl_agent_loop/external/MAC_ARRAY_FPGA/experiments): scripted Verilator performance collection
- [`fpga/vivado/`](/home/keelan/rtl_agent_loop/external/MAC_ARRAY_FPGA/fpga/vivado): Vivado batch flow and report parsing
- [`data/`](/home/keelan/rtl_agent_loop/external/MAC_ARRAY_FPGA/data): deterministic default operand/output memories
- [`docs/`](/home/keelan/rtl_agent_loop/external/MAC_ARRAY_FPGA/docs): architecture and measurement notes

## Quick Start

Generate deterministic vectors:

```bash
make test_vectors
```

Run the end-to-end Verilator performance collection:

```bash
make perf
```

Build a simple Verilator executable without the perf wrapper:

```bash
make verilator_tb
```

Run a Vivado batch implementation:

```bash
make vivado
```

Run the first bounded study matrix:

```bash
make sweep_perf_only
make sweep
```

## Output Contracts

The repo keeps machine-readable outputs stable so an external experiment framework can consume them:

- Verilator perf JSON:
  - `<run_dir>/verilator_perf/performance.json`
- Vivado metrics JSON:
  - `<run_dir>/reports/metrics.json`

The sweep utility collates a study under:

- `experiments/results/sweep_results.csv`
- `experiments/results/sweep_summary.md`

The repository also provides the contract points commonly expected by external wrappers:

- `hdl/top_level.sv`
- `tb/tb_full_pipeline.cpp`
- `fpga/vivado/run_batch.sh`
- `fpga/vivado/parse_reports.py`
- `experiments/collect_verilator_perf.py`

## Study Notes

- Default vectors target a compact `4 x 4 x 4` GEMM workload for fast simulation.
- Shared-mode control intentionally stretches execution latency by `SHARE_FACTOR`.
- The replicated variant increases instantiated compute without changing the functional result.
- `PIPE_STAGES` currently acts as a deterministic latency/drain knob rather than a fully retimed MAC pipeline.
- Vivado flow is a serious first-pass wrapper, but still assumes a standard local `vivado` installation and a single-clock design.

See [`docs/variant_definitions.md`](/home/keelan/rtl_agent_loop/external/MAC_ARRAY_FPGA/docs/variant_definitions.md) and [`docs/measurement_plan.md`](/home/keelan/rtl_agent_loop/external/MAC_ARRAY_FPGA/docs/measurement_plan.md) for the research framing.
