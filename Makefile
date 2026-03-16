PYTHON ?= $(if $(RTL_AGENT_LOOP_PYTHON),$(RTL_AGENT_LOOP_PYTHON),python3)
EXTERNAL_REPO ?= $(if $(RTL_AGENT_LOOP_EXTERNAL_REPO),$(RTL_AGENT_LOOP_EXTERNAL_REPO),$(CURDIR)/external/MAC_ARRAY_FPGA)
CANDIDATE_ID ?=
MANIFEST_PATH ?=
RUN_DIR ?=
VIVADO_BIN ?= vivado

ifeq ($(strip $(MANIFEST_PATH)),)
ifneq ($(wildcard $(CURDIR)/candidates/$(CANDIDATE_ID).json),)
RESOLVED_MANIFEST_PATH = $(CURDIR)/candidates/$(CANDIDATE_ID).json
else
RESOLVED_MANIFEST_PATH = $(CURDIR)/runs/$(CANDIDATE_ID)/candidate_manifest.json
endif
else
RESOLVED_MANIFEST_PATH = $(MANIFEST_PATH)
endif

ifeq ($(strip $(RUN_DIR)),)
VERIFY_RUN_DIR = $(CURDIR)/runs/$(CANDIDATE_ID)/manual_verify
IMPLEMENT_RUN_DIR = $(CURDIR)/runs/$(CANDIDATE_ID)/manual_implement
PERF_RUN_DIR = $(CURDIR)/runs/$(CANDIDATE_ID)/manual_perf
SCORE_RUN_DIR =
else
VERIFY_RUN_DIR = $(RUN_DIR)
IMPLEMENT_RUN_DIR = $(RUN_DIR)
PERF_RUN_DIR = $(RUN_DIR)
SCORE_RUN_DIR = --run-dir $(RUN_DIR)
endif

.PHONY: setup verify_candidate implement_candidate perf_candidate score_candidate

setup:
	@RTL_AGENT_LOOP_PYTHON="$(PYTHON)" RTL_AGENT_LOOP_EXTERNAL_REPO="$(EXTERNAL_REPO)" VIVADO_BIN="$(VIVADO_BIN)" \
		bash scripts/bootstrap_env.sh

verify_candidate:
	@test -n "$(CANDIDATE_ID)" || { echo "ERROR: set CANDIDATE_ID=<id>"; exit 2; }
	@RTL_AGENT_LOOP_EXTERNAL_REPO="$(EXTERNAL_REPO)" \
		bash scripts/fast_verify.sh \
		--candidate-id "$(CANDIDATE_ID)" \
		--candidate-manifest "$(RESOLVED_MANIFEST_PATH)" \
		--run-dir "$(VERIFY_RUN_DIR)" \
		--external-repo "$(EXTERNAL_REPO)"

implement_candidate:
	@test -n "$(CANDIDATE_ID)" || { echo "ERROR: set CANDIDATE_ID=<id>"; exit 2; }
	@RTL_AGENT_LOOP_EXTERNAL_REPO="$(EXTERNAL_REPO)" VIVADO_BIN="$(VIVADO_BIN)" \
		bash scripts/run_vivado_batch.sh \
		--candidate-id "$(CANDIDATE_ID)" \
		--candidate-manifest "$(RESOLVED_MANIFEST_PATH)" \
		--run-dir "$(IMPLEMENT_RUN_DIR)" \
		--external-repo "$(EXTERNAL_REPO)"

perf_candidate:
	@test -n "$(CANDIDATE_ID)" || { echo "ERROR: set CANDIDATE_ID=<id>"; exit 2; }
	@RTL_AGENT_LOOP_EXTERNAL_REPO="$(EXTERNAL_REPO)" \
		bash scripts/collect_verilator_perf.sh \
		--candidate-id "$(CANDIDATE_ID)" \
		--candidate-manifest "$(RESOLVED_MANIFEST_PATH)" \
		--run-dir "$(PERF_RUN_DIR)" \
		--external-repo "$(EXTERNAL_REPO)"

score_candidate:
	@test -n "$(CANDIDATE_ID)" || { echo "ERROR: set CANDIDATE_ID=<id>"; exit 2; }
	@"$(PYTHON)" -m rtl_agent_loop score --candidate-id "$(CANDIDATE_ID)" $(SCORE_RUN_DIR)
