module operand_interconnect #(
  parameter int ARRAY_M      = 4,
  parameter int ARRAY_N      = 4,
  parameter int TILE_K       = 4,
  parameter int DATA_WIDTH   = 16,
  parameter int INPUT_ADDR_W = 8,
  parameter int K_W          = 2
) (
  input  logic [K_W-1:0] current_k,
  output logic [INPUT_ADDR_W-1:0] a_read_addr [0:ARRAY_M-1],
  output logic [INPUT_ADDR_W-1:0] b_read_addr [0:ARRAY_N-1],
  input  logic signed [DATA_WIDTH-1:0] a_row_data [0:ARRAY_M-1],
  input  logic signed [DATA_WIDTH-1:0] b_col_data [0:ARRAY_N-1],
  output logic signed [DATA_WIDTH-1:0] lane_a [0:(ARRAY_M*ARRAY_N)-1],
  output logic signed [DATA_WIDTH-1:0] lane_b [0:(ARRAY_M*ARRAY_N)-1]
);
  integer row_idx;
  integer col_idx;
  integer lane_idx;
  integer a_addr_calc;
  integer b_addr_calc;

  always_comb begin
    for (row_idx = 0; row_idx < ARRAY_M; row_idx++) begin
      a_addr_calc = (row_idx * TILE_K) + int'(current_k);
      a_read_addr[row_idx] = INPUT_ADDR_W'(a_addr_calc);
    end
    for (col_idx = 0; col_idx < ARRAY_N; col_idx++) begin
      b_addr_calc = (int'(current_k) * ARRAY_N) + col_idx;
      b_read_addr[col_idx] = INPUT_ADDR_W'(b_addr_calc);
    end

    lane_idx = 0;
    for (row_idx = 0; row_idx < ARRAY_M; row_idx++) begin
      for (col_idx = 0; col_idx < ARRAY_N; col_idx++) begin
        lane_a[lane_idx] = a_row_data[row_idx];
        lane_b[lane_idx] = b_col_data[col_idx];
        lane_idx = lane_idx + 1;
      end
    end
  end
endmodule
