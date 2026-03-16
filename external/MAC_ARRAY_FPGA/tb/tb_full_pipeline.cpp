#include <verilated.h>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "Vtop_level.h"

namespace {

std::vector<long long> load_hex_file(const std::string& path) {
  std::ifstream input(path);
  if (!input) {
    std::cerr << "failed to open " << path << std::endl;
    return {};
  }
  std::vector<long long> values;
  std::string token;
  while (input >> token) {
    const auto parsed = std::stoll(token, nullptr, 16);
    values.push_back(parsed);
  }
  return values;
}

bool compare_mem_files(const std::string& actual_path, const std::string& expected_path) {
  const auto actual = load_hex_file(actual_path);
  const auto expected = load_hex_file(expected_path);
  if (actual.size() < expected.size()) {
    std::cerr << "size mismatch: actual=" << actual.size()
              << " expected_at_least=" << expected.size() << std::endl;
    return false;
  }
  for (size_t idx = 0; idx < expected.size(); ++idx) {
    if (actual[idx] != expected[idx]) {
      std::cerr << "mismatch at index " << idx
                << " actual=0x" << std::hex << actual[idx]
                << " expected=0x" << expected[idx] << std::dec << std::endl;
      return false;
    }
  }
  for (size_t idx = expected.size(); idx < actual.size(); ++idx) {
    if (actual[idx] != 0) {
      std::cerr << "non-zero tail entry at index " << idx
                << " actual=0x" << std::hex << actual[idx] << std::dec << std::endl;
      return false;
    }
  }
  return true;
}

void tick(Vtop_level& dut, vluint64_t& sim_time) {
  dut.clk = 0;
  dut.eval();
  ++sim_time;
  dut.clk = 1;
  dut.eval();
  ++sim_time;
}

}  // namespace

int main(int argc, char** argv) {
  Verilated::commandArgs(argc, argv);

  std::string expected_path = "data/expected_output.mem";
  std::string output_path = "sim_output.mem";
  int max_cycles = 512;
  bool verbose = false;

  for (int idx = 1; idx < argc; ++idx) {
    const std::string arg(argv[idx]);
    if (arg == "--expected" && idx + 1 < argc) {
      expected_path = argv[++idx];
    } else if (arg == "--output" && idx + 1 < argc) {
      output_path = argv[++idx];
    } else if (arg == "--max-cycles" && idx + 1 < argc) {
      max_cycles = std::stoi(argv[++idx]);
    } else if (arg == "--verbose") {
      verbose = true;
    }
  }

  Vtop_level dut;
  vluint64_t sim_time = 0;

  dut.rst = 1;
  dut.start = 0;
  for (int i = 0; i < 5; ++i) {
    tick(dut, sim_time);
  }

  dut.rst = 0;
  dut.start = 1;
  tick(dut, sim_time);
  dut.start = 0;

  int observed_cycles = 0;
  while (!dut.done && observed_cycles < max_cycles) {
    if (verbose) {
      std::cout << "cycle=" << observed_cycles
                << " busy=" << static_cast<int>(dut.busy)
                << " done=" << static_cast<int>(dut.done)
                << std::endl;
    }
    tick(dut, sim_time);
    ++observed_cycles;
  }

  if (!dut.done) {
    std::cerr << "timeout waiting for done after " << observed_cycles << " cycles" << std::endl;
    return 2;
  }

  tick(dut, sim_time);

  const bool match = compare_mem_files(output_path, expected_path);
  std::cout << "DONE=1" << std::endl;
  std::cout << "OBSERVED_CYCLES=" << observed_cycles << std::endl;
  std::cout << "LATENCY_CYCLES=" << dut.debug_cycle_count << std::endl;
  std::cout << "COMPARE_OK=" << (match ? 1 : 0) << std::endl;
  return match ? 0 : 3;
}
