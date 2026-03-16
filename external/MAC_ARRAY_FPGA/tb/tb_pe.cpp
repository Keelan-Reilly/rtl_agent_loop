#include <verilated.h>
#include <cstdlib>
#include <iostream>

#include "Vpe.h"

int main(int argc, char** argv) {
  Verilated::commandArgs(argc, argv);
  Vpe dut;

  dut.compute_en = 0;
  dut.lane_valid = 0;
  dut.op_a = 0;
  dut.op_b = 0;
  dut.acc_seed = 0;
  dut.eval();

  dut.compute_en = 1;
  dut.lane_valid = 1;
  dut.op_a = 0x0100;
  dut.op_b = 0x0200;
  dut.acc_seed = 0;
  dut.eval();

  if (!dut.result_valid) {
    std::cerr << "expected valid PE result" << std::endl;
    return 2;
  }
  if (dut.acc_result != 0x00000200) {
    std::cerr << "unexpected PE result: " << dut.acc_result << std::endl;
    return 3;
  }

  std::cout << "PE_RESULT_VALID=" << static_cast<int>(dut.result_valid) << std::endl;
  std::cout << "PE_ACC_RESULT=" << dut.acc_result << std::endl;
  return 0;
}
