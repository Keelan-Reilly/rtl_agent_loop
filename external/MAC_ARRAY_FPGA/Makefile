PYTHON ?= python3
VERILATOR ?= verilator
VIVADO_BIN ?= vivado

REPO_ROOT := $(abspath .)
RUN_DIR ?= $(REPO_ROOT)/build/default_run
PART ?= xc7a35tcpg236-1
TOP ?= top_level
CLOCK_PERIOD_NS ?= 10.0

ARCH_VARIANT ?= 0
ARRAY_M ?= 4
ARRAY_N ?= 4
CLUSTER_SIZE ?= 4
SHARE_FACTOR ?= 2
DATA_WIDTH ?= 16
FRAC_BITS ?= 8
ACC_WIDTH ?= 32
PIPE_STAGES ?= 1
TILE_K ?= 4
INPUT_MEM_DEPTH ?= 16
OUTPUT_MEM_DEPTH ?= 16

.PHONY: test_vectors verilator_tb perf vivado sweep sweep_perf_only clean

test_vectors:
	$(PYTHON) python/generate_test_vectors.py \
		--array-m $(ARRAY_M) \
		--array-n $(ARRAY_N) \
		--tile-k $(TILE_K) \
		--data-width $(DATA_WIDTH) \
		--frac-bits $(FRAC_BITS) \
		--acc-width $(ACC_WIDTH) \
		--input-mem-depth $(INPUT_MEM_DEPTH) \
		--output-mem-depth $(OUTPUT_MEM_DEPTH) \
		--output-dir data

verilator_tb:
	$(PYTHON) experiments/collect_verilator_perf.py \
		--run-dir $(RUN_DIR) \
		--top $(TOP) \
		--clock-hz 100000000 \
		--build-only \
		--parameter ARCH_VARIANT=$(ARCH_VARIANT) \
		--parameter ARRAY_M=$(ARRAY_M) \
		--parameter ARRAY_N=$(ARRAY_N) \
		--parameter CLUSTER_SIZE=$(CLUSTER_SIZE) \
		--parameter SHARE_FACTOR=$(SHARE_FACTOR) \
		--parameter DATA_WIDTH=$(DATA_WIDTH) \
		--parameter FRAC_BITS=$(FRAC_BITS) \
		--parameter ACC_WIDTH=$(ACC_WIDTH) \
		--parameter PIPE_STAGES=$(PIPE_STAGES) \
		--parameter TILE_K=$(TILE_K) \
		--parameter INPUT_MEM_DEPTH=$(INPUT_MEM_DEPTH) \
		--parameter OUTPUT_MEM_DEPTH=$(OUTPUT_MEM_DEPTH)

perf:
	$(PYTHON) experiments/collect_verilator_perf.py \
		--run-dir $(RUN_DIR) \
		--top $(TOP) \
		--clock-hz 100000000 \
		--parameter ARCH_VARIANT=$(ARCH_VARIANT) \
		--parameter ARRAY_M=$(ARRAY_M) \
		--parameter ARRAY_N=$(ARRAY_N) \
		--parameter CLUSTER_SIZE=$(CLUSTER_SIZE) \
		--parameter SHARE_FACTOR=$(SHARE_FACTOR) \
		--parameter DATA_WIDTH=$(DATA_WIDTH) \
		--parameter FRAC_BITS=$(FRAC_BITS) \
		--parameter ACC_WIDTH=$(ACC_WIDTH) \
		--parameter PIPE_STAGES=$(PIPE_STAGES) \
		--parameter TILE_K=$(TILE_K) \
		--parameter INPUT_MEM_DEPTH=$(INPUT_MEM_DEPTH) \
		--parameter OUTPUT_MEM_DEPTH=$(OUTPUT_MEM_DEPTH)

sweep:
	$(PYTHON) experiments/sweep_variants.py

sweep_perf_only:
	$(PYTHON) experiments/sweep_variants.py --perf-only

vivado:
	fpga/vivado/run_batch.sh \
		--run-dir $(RUN_DIR)/vivado \
		--repo-root $(REPO_ROOT) \
		--part $(PART) \
		--top $(TOP) \
		--xdc $(REPO_ROOT)/fpga/vivado/constraints/mac_array_constraints.xdc \
		--clock-period-ns $(CLOCK_PERIOD_NS) \
		--generic ARCH_VARIANT=$(ARCH_VARIANT) \
		--generic ARRAY_M=$(ARRAY_M) \
		--generic ARRAY_N=$(ARRAY_N) \
		--generic CLUSTER_SIZE=$(CLUSTER_SIZE) \
		--generic SHARE_FACTOR=$(SHARE_FACTOR) \
		--generic DATA_WIDTH=$(DATA_WIDTH) \
		--generic FRAC_BITS=$(FRAC_BITS) \
		--generic ACC_WIDTH=$(ACC_WIDTH) \
		--generic PIPE_STAGES=$(PIPE_STAGES) \
		--generic TILE_K=$(TILE_K) \
		--generic INPUT_MEM_DEPTH=$(INPUT_MEM_DEPTH) \
		--generic OUTPUT_MEM_DEPTH=$(OUTPUT_MEM_DEPTH)
	$(PYTHON) fpga/vivado/parse_reports.py \
		--reports-dir $(RUN_DIR)/vivado/reports \
		--clock-period-ns $(CLOCK_PERIOD_NS) \
		--output $(RUN_DIR)/vivado/reports/metrics.json

clean:
	rm -rf build obj_dir sim_output.mem
