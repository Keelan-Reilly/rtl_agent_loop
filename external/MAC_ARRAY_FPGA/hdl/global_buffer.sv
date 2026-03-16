module global_buffer #(
  parameter int WIDTH          = 16,
  parameter int DEPTH          = 16,
  parameter int NUM_READ_PORTS = 1,
  parameter string INIT_FILE   = ""
) (
  input  logic clk,
  input  logic [($clog2((DEPTH < 2) ? 2 : DEPTH))-1:0] read_addr [0:NUM_READ_PORTS-1],
  output logic signed [WIDTH-1:0] read_data [0:NUM_READ_PORTS-1],
  input  logic write_en,
  input  logic [($clog2((DEPTH < 2) ? 2 : DEPTH))-1:0] write_addr,
  input  logic signed [WIDTH-1:0] write_data
);
  logic signed [WIDTH-1:0] mem [0:DEPTH-1];
  integer idx;

  initial begin
    for (idx = 0; idx < DEPTH; idx++) begin
      mem[idx] = '0;
    end
    if (INIT_FILE != "") begin
      $readmemh(INIT_FILE, mem);
    end
  end

  always_ff @(posedge clk) begin
    if (write_en) begin
      mem[write_addr] <= write_data;
    end
  end

  always_comb begin
    for (idx = 0; idx < NUM_READ_PORTS; idx++) begin
      read_data[idx] = mem[read_addr[idx]];
    end
  end
endmodule
