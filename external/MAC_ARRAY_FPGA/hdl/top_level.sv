module top_level #(
  parameter int ARCH_VARIANT     = 0,
  parameter int ARRAY_M          = 4,
  parameter int ARRAY_N          = 4,
  parameter int CLUSTER_SIZE     = 4,
  parameter int SHARE_FACTOR     = 2,
  parameter int DATA_WIDTH       = 16,
  parameter int FRAC_BITS        = 8,
  parameter int ACC_WIDTH        = 32,
  parameter int PIPE_STAGES      = 1,
  parameter int TILE_K           = 4,
  parameter int INPUT_MEM_DEPTH  = 16,
  parameter int OUTPUT_MEM_DEPTH = 16
) (
  input  logic clk,
  input  logic rst,
  input  logic start,
  output logic done,
  output logic busy,
  output logic [31:0] debug_cycle_count
);
  import types_pkg::*;

  localparam int NUM_LANES     = ARRAY_M * ARRAY_N;
  localparam int NUM_CLUSTERS  = ceil_div(NUM_LANES, CLUSTER_SIZE);
  localparam int A_ADDR_W      = $clog2((INPUT_MEM_DEPTH < 2) ? 2 : INPUT_MEM_DEPTH);
  localparam int OUT_ADDR_W    = $clog2((OUTPUT_MEM_DEPTH < 2) ? 2 : OUTPUT_MEM_DEPTH);
  localparam int SHARE_W       = safe_clog2(SHARE_FACTOR);
  localparam int K_W           = safe_clog2(TILE_K);
  localparam int LANE_ID_W     = $clog2((CLUSTER_SIZE < 2) ? 2 : CLUSTER_SIZE);

  logic clear_acc;
  logic compute_en;
  logic write_en;
  logic [K_W-1:0] current_k;
  logic [SHARE_W-1:0] shared_phase;
  logic [31:0] cycle_count;

  logic [A_ADDR_W-1:0] a_read_addr [0:ARRAY_M-1];
  logic [A_ADDR_W-1:0] b_read_addr [0:ARRAY_N-1];
  logic signed [DATA_WIDTH-1:0] a_row_data [0:ARRAY_M-1];
  logic signed [DATA_WIDTH-1:0] b_col_data [0:ARRAY_N-1];
  logic signed [DATA_WIDTH-1:0] lane_a [0:NUM_LANES-1];
  logic signed [DATA_WIDTH-1:0] lane_b [0:NUM_LANES-1];
  logic signed [ACC_WIDTH-1:0]  cluster_accum [0:NUM_CLUSTERS-1][0:CLUSTER_SIZE-1];
  logic signed [ACC_WIDTH-1:0]  output_mem [0:OUTPUT_MEM_DEPTH-1];
  integer lane_idx;
  integer cluster_idx;
  integer local_idx;

  control #(
    .ARCH_VARIANT(ARCH_VARIANT),
    .ARRAY_M(ARRAY_M),
    .ARRAY_N(ARRAY_N),
    .TILE_K(TILE_K),
    .SHARE_FACTOR(SHARE_FACTOR),
    .PIPE_STAGES(PIPE_STAGES)
  ) u_control (
    .clk(clk),
    .rst(rst),
    .start(start),
    .busy(busy),
    .done(done),
    .clear_acc(clear_acc),
    .compute_en(compute_en),
    .write_en(write_en),
    .k_index(current_k),
    .shared_phase(shared_phase),
    .cycle_count(cycle_count)
  );

  global_buffer #(
    .WIDTH(DATA_WIDTH),
    .DEPTH(INPUT_MEM_DEPTH),
    .NUM_READ_PORTS(ARRAY_M),
    .INIT_FILE("data/input_a.mem")
  ) u_a_buffer (
    .clk(clk),
    .read_addr(a_read_addr),
    .read_data(a_row_data),
    .write_en(1'b0),
    .write_addr('0),
    .write_data('0)
  );

  global_buffer #(
    .WIDTH(DATA_WIDTH),
    .DEPTH(INPUT_MEM_DEPTH),
    .NUM_READ_PORTS(ARRAY_N),
    .INIT_FILE("data/input_b.mem")
  ) u_b_buffer (
    .clk(clk),
    .read_addr(b_read_addr),
    .read_data(b_col_data),
    .write_en(1'b0),
    .write_addr('0),
    .write_data('0)
  );

  operand_interconnect #(
    .ARRAY_M(ARRAY_M),
    .ARRAY_N(ARRAY_N),
    .TILE_K(TILE_K),
    .DATA_WIDTH(DATA_WIDTH),
    .INPUT_ADDR_W(A_ADDR_W),
    .K_W(K_W)
  ) u_interconnect (
    .current_k(current_k),
    .a_read_addr(a_read_addr),
    .b_read_addr(b_read_addr),
    .a_row_data(a_row_data),
    .b_col_data(b_col_data),
    .lane_a(lane_a),
    .lane_b(lane_b)
  );

  genvar cg;
  genvar lg;
  generate
    for (cg = 0; cg < NUM_CLUSTERS; cg++) begin : gen_clusters
      logic signed [DATA_WIDTH-1:0] cluster_lane_a [0:CLUSTER_SIZE-1];
      logic signed [DATA_WIDTH-1:0] cluster_lane_b [0:CLUSTER_SIZE-1];
      for (lg = 0; lg < CLUSTER_SIZE; lg++) begin : gen_cluster_lanes
        localparam int GLOBAL_LANE = (cg * CLUSTER_SIZE) + lg;
        if (GLOBAL_LANE < NUM_LANES) begin
          always_comb begin
            cluster_lane_a[lg] = lane_a[GLOBAL_LANE];
            cluster_lane_b[lg] = lane_b[GLOBAL_LANE];
          end
        end else begin
          always_comb begin
            cluster_lane_a[lg] = '0;
            cluster_lane_b[lg] = '0;
          end
        end
      end

      cluster #(
        .ARCH_VARIANT(ARCH_VARIANT),
        .NUM_PES(CLUSTER_SIZE),
        .SHARE_FACTOR(SHARE_FACTOR),
        .DATA_WIDTH(DATA_WIDTH),
        .FRAC_BITS(FRAC_BITS),
        .ACC_WIDTH(ACC_WIDTH),
        .PIPE_STAGES(PIPE_STAGES),
        .LANE_ID_W(LANE_ID_W)
      ) u_cluster (
        .clk(clk),
        .rst(rst),
        .clear_acc(clear_acc),
        .compute_en(compute_en),
        .shared_phase(shared_phase),
        .lane_a(cluster_lane_a),
        .lane_b(cluster_lane_b),
        .accum_out(cluster_accum[cg])
      );
    end
  endgenerate

  always_ff @(posedge clk) begin
    if (rst) begin
      for (lane_idx = 0; lane_idx < OUTPUT_MEM_DEPTH; lane_idx++) begin
        output_mem[lane_idx] <= '0;
      end
    end else if (write_en) begin
      for (cluster_idx = 0; cluster_idx < NUM_CLUSTERS; cluster_idx++) begin
        for (local_idx = 0; local_idx < CLUSTER_SIZE; local_idx++) begin
          lane_idx = cluster_idx * CLUSTER_SIZE + local_idx;
          if (lane_idx < OUTPUT_MEM_DEPTH && lane_idx < NUM_LANES) begin
            output_mem[lane_idx] <= cluster_accum[cluster_idx][local_idx];
          end
        end
      end
    end
  end

`ifndef SYNTHESIS
  always_ff @(posedge clk) begin
    if (!rst && done) begin
      $writememh("sim_output.mem", output_mem);
    end
  end
`endif

  assign debug_cycle_count = cycle_count;
endmodule
