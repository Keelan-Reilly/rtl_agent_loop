module control #(
  parameter int ARCH_VARIANT = 0,
  parameter int ARRAY_M      = 4,
  parameter int ARRAY_N      = 4,
  parameter int TILE_K       = 4,
  parameter int SHARE_FACTOR = 2,
  parameter int PIPE_STAGES  = 1
) (
  input  logic clk,
  input  logic rst,
  input  logic start,
  output logic busy,
  output logic done,
  output logic clear_acc,
  output logic compute_en,
  output logic write_en,
  output logic [types_pkg::safe_clog2((TILE_K < 1) ? 1 : TILE_K)-1:0] k_index,
  output logic [types_pkg::safe_clog2((SHARE_FACTOR < 1) ? 1 : SHARE_FACTOR)-1:0] shared_phase,
  output logic [31:0] cycle_count
);
  import types_pkg::*;

  typedef enum logic [2:0] {
    ST_IDLE,
    ST_CLEAR,
    ST_COMPUTE,
    ST_DRAIN,
    ST_WRITE,
    ST_DONE
  } state_t;

  localparam int SAFE_SHARE_FACTOR = max_int(1, SHARE_FACTOR);
  localparam int SHARED_MULTIPLIER = (ARCH_VARIANT == 1) ? SAFE_SHARE_FACTOR : 1;
  localparam int TOTAL_COMPUTE_STEPS = TILE_K * SHARED_MULTIPLIER;
  // PIPE_STAGES currently stretches drain latency instead of inserting a fully
  // retimed MAC datapath. That keeps the semantics deterministic and honest.
  localparam int DRAIN_STEPS = max_int(1, PIPE_STAGES);
  localparam int K_W = safe_clog2(TILE_K);
  localparam int SHARE_W = safe_clog2(SAFE_SHARE_FACTOR);

  state_t state_q, state_d;
  logic [31:0] compute_iter_q, compute_iter_d;
  logic [31:0] drain_iter_q, drain_iter_d;
  logic [31:0] cycle_count_d;

  always_comb begin
    state_d        = state_q;
    compute_iter_d = compute_iter_q;
    drain_iter_d   = drain_iter_q;
    cycle_count_d  = cycle_count;

    busy      = 1'b1;
    done      = 1'b0;
    clear_acc = 1'b0;
    compute_en = 1'b0;
    write_en  = 1'b0;
    k_index   = '0;
    shared_phase = '0;

    case (state_q)
      ST_IDLE: begin
        busy = 1'b0;
        cycle_count_d = 32'd0;
        if (start) begin
          state_d = ST_CLEAR;
        end
      end
      ST_CLEAR: begin
        clear_acc = 1'b1;
        cycle_count_d = cycle_count + 1;
        compute_iter_d = 32'd0;
        drain_iter_d = 32'd0;
        state_d = ST_COMPUTE;
      end
      ST_COMPUTE: begin
        compute_en = 1'b1;
        cycle_count_d = cycle_count + 1;
        k_index = K_W'(compute_iter_q / SHARED_MULTIPLIER);
        shared_phase = SHARE_W'(compute_iter_q % SHARED_MULTIPLIER);
        if (compute_iter_q + 1 >= TOTAL_COMPUTE_STEPS) begin
          compute_iter_d = 32'd0;
          state_d = ST_DRAIN;
        end else begin
          compute_iter_d = compute_iter_q + 1;
        end
      end
      ST_DRAIN: begin
        cycle_count_d = cycle_count + 1;
        if (drain_iter_q + 1 >= DRAIN_STEPS) begin
          drain_iter_d = 32'd0;
          state_d = ST_WRITE;
        end else begin
          drain_iter_d = drain_iter_q + 1;
        end
      end
      ST_WRITE: begin
        write_en = 1'b1;
        cycle_count_d = cycle_count + 1;
        state_d = ST_DONE;
      end
      ST_DONE: begin
        done = 1'b1;
        cycle_count_d = cycle_count;
        if (!start) begin
          state_d = ST_IDLE;
        end
      end
      default: begin
        state_d = ST_IDLE;
      end
    endcase
  end

  always_ff @(posedge clk) begin
    if (rst) begin
      state_q       <= ST_IDLE;
      compute_iter_q <= 32'd0;
      drain_iter_q  <= 32'd0;
      cycle_count   <= 32'd0;
    end else begin
      state_q       <= state_d;
      compute_iter_q <= compute_iter_d;
      drain_iter_q  <= drain_iter_d;
      cycle_count   <= cycle_count_d;
    end
  end
endmodule
