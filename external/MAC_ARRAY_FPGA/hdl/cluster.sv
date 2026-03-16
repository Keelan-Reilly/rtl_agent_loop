module cluster #(
  parameter int ARCH_VARIANT = 0,
  parameter int NUM_PES      = 4,
  parameter int SHARE_FACTOR = 2,
  parameter int DATA_WIDTH   = 16,
  parameter int FRAC_BITS    = 8,
  parameter int ACC_WIDTH    = 32,
  parameter int PIPE_STAGES  = 1,
  parameter int LANE_ID_W    = 8
) (
  input  logic                         clk,
  input  logic                         rst,
  input  logic                         clear_acc,
  input  logic                         compute_en,
  input  logic [types_pkg::safe_clog2((SHARE_FACTOR < 1) ? 1 : SHARE_FACTOR)-1:0] shared_phase,
  input  logic signed [DATA_WIDTH-1:0] lane_a [0:NUM_PES-1],
  input  logic signed [DATA_WIDTH-1:0] lane_b [0:NUM_PES-1],
  output logic signed [ACC_WIDTH-1:0]  accum_out [0:NUM_PES-1]
);
  import types_pkg::*;

  localparam int SAFE_SHARE_FACTOR = max_int(1, SHARE_FACTOR);
  localparam int PHYSICAL_PES = (ARCH_VARIANT == 1) ? ((NUM_PES + SAFE_SHARE_FACTOR - 1) / SAFE_SHARE_FACTOR) : NUM_PES;

  logic signed [ACC_WIDTH-1:0] accum_bank [0:NUM_PES-1];
  logic signed [DATA_WIDTH-1:0] pe_a      [0:PHYSICAL_PES-1];
  logic signed [DATA_WIDTH-1:0] pe_b      [0:PHYSICAL_PES-1];
  logic signed [ACC_WIDTH-1:0]  pe_seed   [0:PHYSICAL_PES-1];
  logic                         pe_valid  [0:PHYSICAL_PES-1];
  logic                         pe_done   [0:PHYSICAL_PES-1];
  logic signed [ACC_WIDTH-1:0]  pe_result [0:PHYSICAL_PES-1];
  logic signed [ACC_WIDTH-1:0] accum_next [0:NUM_PES-1];
  integer logical_lane;
  integer phys_idx;

  genvar g;
  generate
    for (g = 0; g < PHYSICAL_PES; g++) begin : gen_main_pes
      pe #(
        .ARCH_VARIANT(ARCH_VARIANT),
        .DATA_WIDTH(DATA_WIDTH),
        .FRAC_BITS(FRAC_BITS),
        .ACC_WIDTH(ACC_WIDTH),
        .PIPE_STAGES(PIPE_STAGES)
      ) u_pe (
        .compute_en(compute_en),
        .lane_valid(pe_valid[g]),
        .op_a(pe_a[g]),
        .op_b(pe_b[g]),
        .acc_seed(pe_seed[g]),
        .result_valid(pe_done[g]),
        .acc_result(pe_result[g])
      );

      if (ARCH_VARIANT == 2) begin : gen_shadow_replicas
        // Replicated mode instantiates extra compute that sees the same traffic
        // as the primary cluster. The architectural result still comes from the
        // main PE bank, so functionality matches baseline while area/routing grow.
        logic shadow_valid;
        logic signed [ACC_WIDTH-1:0] shadow_result;
        pe #(
          .ARCH_VARIANT(ARCH_VARIANT),
          .DATA_WIDTH(DATA_WIDTH),
          .FRAC_BITS(FRAC_BITS),
          .ACC_WIDTH(ACC_WIDTH),
          .PIPE_STAGES(PIPE_STAGES)
        ) u_shadow_pe (
          .compute_en(compute_en),
          .lane_valid(pe_valid[g]),
          .op_a(pe_a[g]),
          .op_b(pe_b[g]),
          .acc_seed(pe_seed[g]),
          .result_valid(shadow_valid),
          .acc_result(shadow_result)
        );
      end
    end
  endgenerate

  always_comb begin
    for (phys_idx = 0; phys_idx < PHYSICAL_PES; phys_idx++) begin
      // Shared mode time-multiplexes a smaller physical PE bank across logical
      // lanes. Baseline and replicated modes keep one active PE per logical lane.
      logical_lane = (ARCH_VARIANT == 1) ? (phys_idx + (shared_phase * PHYSICAL_PES)) : phys_idx;
      if (logical_lane < NUM_PES) begin
        pe_valid[phys_idx] = 1'b1;
        pe_a[phys_idx]     = lane_a[logical_lane];
        pe_b[phys_idx]     = lane_b[logical_lane];
        pe_seed[phys_idx]  = accum_bank[logical_lane];
      end else begin
        pe_valid[phys_idx] = 1'b0;
        pe_a[phys_idx]     = '0;
        pe_b[phys_idx]     = '0;
        pe_seed[phys_idx]  = '0;
      end
    end
  end

  always_ff @(posedge clk) begin
    if (rst || clear_acc) begin
      for (logical_lane = 0; logical_lane < NUM_PES; logical_lane++) begin
        accum_bank[logical_lane] <= '0;
      end
    end else begin
      for (logical_lane = 0; logical_lane < NUM_PES; logical_lane++) begin
        accum_bank[logical_lane] <= accum_next[logical_lane];
      end
    end
  end

  always_comb begin
    for (logical_lane = 0; logical_lane < NUM_PES; logical_lane++) begin
      accum_next[logical_lane] = accum_bank[logical_lane];
    end
    for (phys_idx = 0; phys_idx < PHYSICAL_PES; phys_idx++) begin
      logical_lane = (ARCH_VARIANT == 1) ? (phys_idx + (shared_phase * PHYSICAL_PES)) : phys_idx;
      if (pe_done[phys_idx] && logical_lane < NUM_PES) begin
        accum_next[logical_lane] = pe_result[phys_idx];
      end
    end
  end

  always_comb begin
    for (logical_lane = 0; logical_lane < NUM_PES; logical_lane++) begin
      accum_out[logical_lane] = accum_bank[logical_lane];
    end
  end
endmodule
