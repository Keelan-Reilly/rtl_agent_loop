module pe #(
  parameter int ARCH_VARIANT = 0,
  parameter int DATA_WIDTH   = 16,
  parameter int FRAC_BITS    = 8,
  parameter int ACC_WIDTH    = 32,
  parameter int PIPE_STAGES  = 1
) (
  input  logic                         compute_en,
  input  logic                         lane_valid,
  input  logic signed [DATA_WIDTH-1:0] op_a,
  input  logic signed [DATA_WIDTH-1:0] op_b,
  input  logic signed [ACC_WIDTH-1:0]  acc_seed,
  output logic                         result_valid,
  output logic signed [ACC_WIDTH-1:0]  acc_result
);
  logic signed [(2*DATA_WIDTH)-1:0] product_full;
  logic signed [ACC_WIDTH-1:0] product_scaled;

  always_comb begin
    product_full   = op_a * op_b;
    product_scaled = $signed(product_full >>> FRAC_BITS);
    // PIPE_STAGES currently models an architectural latency knob rather than a
    // fully retimed MAC pipeline. Control logic stretches the drain window using
    // this parameter so bounded studies can observe a deterministic cycle cost.
    acc_result   = acc_seed + product_scaled;
    result_valid = compute_en && lane_valid;
  end
endmodule
