// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Primary design header
//
// This header should be included by all source files instantiating the design.
// The class here is then constructed to instantiate the design.
// See the Verilator manual for examples.

#ifndef _VTOP_LEVEL_H_
#define _VTOP_LEVEL_H_  // guard

#include "verilated_heavy.h"

//==========

class Vtop_level__Syms;
class Vtop_level_cluster__pi4;


//----------

VL_MODULE(Vtop_level) {
  public:
    // CELLS
    // Public to allow access to /*verilator_public*/ items;
    // otherwise the application code can consider these internals.
    Vtop_level_cluster__pi4* __PVT__top_level__DOT__gen_clusters__BRA__0__KET____DOT__u_cluster;
    Vtop_level_cluster__pi4* __PVT__top_level__DOT__gen_clusters__BRA__1__KET____DOT__u_cluster;
    Vtop_level_cluster__pi4* __PVT__top_level__DOT__gen_clusters__BRA__2__KET____DOT__u_cluster;
    Vtop_level_cluster__pi4* __PVT__top_level__DOT__gen_clusters__BRA__3__KET____DOT__u_cluster;
    Vtop_level_cluster__pi4* __PVT__top_level__DOT__gen_clusters__BRA__4__KET____DOT__u_cluster;
    Vtop_level_cluster__pi4* __PVT__top_level__DOT__gen_clusters__BRA__5__KET____DOT__u_cluster;
    Vtop_level_cluster__pi4* __PVT__top_level__DOT__gen_clusters__BRA__6__KET____DOT__u_cluster;
    Vtop_level_cluster__pi4* __PVT__top_level__DOT__gen_clusters__BRA__7__KET____DOT__u_cluster;
    
    // PORTS
    // The application code writes and reads these signals to
    // propagate new values into/out from the Verilated model.
    VL_IN8(clk,0,0);
    VL_IN8(rst,0,0);
    VL_IN8(start,0,0);
    VL_OUT8(done,0,0);
    VL_OUT8(busy,0,0);
    VL_OUT(debug_cycle_count,31,0);
    VL_OUT(debug_output_count,31,0);
    VL_OUT(debug_total_compute_steps,31,0);
    VL_OUT(debug_primary_checksum,31,0);
    VL_OUT(debug_shadow_checksum,31,0);
    
    // LOCAL SIGNALS
    // Internals; generally not touched by application code
    CData/*0:0*/ top_level__DOT__clear_acc;
    CData/*0:0*/ top_level__DOT__compute_en;
    CData/*0:0*/ top_level__DOT__write_en;
    CData/*1:0*/ top_level__DOT__current_k;
    CData/*2:0*/ top_level__DOT__u_control__DOT__state_q;
    CData/*2:0*/ top_level__DOT__u_control__DOT__state_d;
    IData/*31:0*/ top_level__DOT__cycle_count;
    IData/*31:0*/ top_level__DOT__shadow_checksum_q;
    IData/*31:0*/ top_level__DOT__u_control__DOT__compute_iter_q;
    IData/*31:0*/ top_level__DOT__u_control__DOT__compute_iter_d;
    IData/*31:0*/ top_level__DOT__u_control__DOT__drain_iter_q;
    IData/*31:0*/ top_level__DOT__u_control__DOT__drain_iter_d;
    IData/*31:0*/ top_level__DOT__u_control__DOT__write_iter_q;
    IData/*31:0*/ top_level__DOT__u_control__DOT__write_iter_d;
    IData/*31:0*/ top_level__DOT__u_control__DOT__cycle_count_d;
    IData/*31:0*/ top_level__DOT__u_interconnect__DOT__a_addr_calc;
    IData/*31:0*/ top_level__DOT__u_interconnect__DOT__b_addr_calc;
    CData/*5:0*/ top_level__DOT__a_read_addr[4];
    CData/*5:0*/ top_level__DOT__b_read_addr[4];
    SData/*15:0*/ top_level__DOT__a_row_data[4];
    SData/*15:0*/ top_level__DOT__b_col_data[4];
    SData/*15:0*/ top_level__DOT__lane_a[16];
    SData/*15:0*/ top_level__DOT__lane_b[16];
    IData/*31:0*/ top_level__DOT__cluster_accum[8][2];
    IData/*31:0*/ top_level__DOT__cluster_shadow_accum[8][2];
    IData/*31:0*/ top_level__DOT__logical_accum[16];
    IData/*31:0*/ top_level__DOT__logical_shadow_accum[16];
    IData/*31:0*/ top_level__DOT__output_mem[64];
    SData/*15:0*/ top_level__DOT__gen_clusters__BRA__0__KET____DOT__cluster_lane_a[2];
    SData/*15:0*/ top_level__DOT__gen_clusters__BRA__0__KET____DOT__cluster_lane_b[2];
    SData/*15:0*/ top_level__DOT__gen_clusters__BRA__1__KET____DOT__cluster_lane_a[2];
    SData/*15:0*/ top_level__DOT__gen_clusters__BRA__1__KET____DOT__cluster_lane_b[2];
    SData/*15:0*/ top_level__DOT__gen_clusters__BRA__2__KET____DOT__cluster_lane_a[2];
    SData/*15:0*/ top_level__DOT__gen_clusters__BRA__2__KET____DOT__cluster_lane_b[2];
    SData/*15:0*/ top_level__DOT__gen_clusters__BRA__3__KET____DOT__cluster_lane_a[2];
    SData/*15:0*/ top_level__DOT__gen_clusters__BRA__3__KET____DOT__cluster_lane_b[2];
    SData/*15:0*/ top_level__DOT__gen_clusters__BRA__4__KET____DOT__cluster_lane_a[2];
    SData/*15:0*/ top_level__DOT__gen_clusters__BRA__4__KET____DOT__cluster_lane_b[2];
    SData/*15:0*/ top_level__DOT__gen_clusters__BRA__5__KET____DOT__cluster_lane_a[2];
    SData/*15:0*/ top_level__DOT__gen_clusters__BRA__5__KET____DOT__cluster_lane_b[2];
    SData/*15:0*/ top_level__DOT__gen_clusters__BRA__6__KET____DOT__cluster_lane_a[2];
    SData/*15:0*/ top_level__DOT__gen_clusters__BRA__6__KET____DOT__cluster_lane_b[2];
    SData/*15:0*/ top_level__DOT__gen_clusters__BRA__7__KET____DOT__cluster_lane_a[2];
    SData/*15:0*/ top_level__DOT__gen_clusters__BRA__7__KET____DOT__cluster_lane_b[2];
    SData/*15:0*/ top_level__DOT__u_a_buffer__DOT__mem[64];
    SData/*15:0*/ top_level__DOT__u_b_buffer__DOT__mem[64];
    
    // LOCAL VARIABLES
    // Internals; generally not touched by application code
    CData/*0:0*/ __Vclklast__TOP__clk;
    SData/*15:0*/ top_level__DOT____Vcellout__u_a_buffer__read_data[4];
    CData/*5:0*/ top_level__DOT____Vcellinp__u_a_buffer__read_addr[4];
    SData/*15:0*/ top_level__DOT____Vcellout__u_b_buffer__read_data[4];
    CData/*5:0*/ top_level__DOT____Vcellinp__u_b_buffer__read_addr[4];
    SData/*15:0*/ top_level__DOT____Vcellout__u_interconnect__lane_b[16];
    SData/*15:0*/ top_level__DOT____Vcellout__u_interconnect__lane_a[16];
    SData/*15:0*/ top_level__DOT____Vcellinp__u_interconnect__b_col_data[4];
    SData/*15:0*/ top_level__DOT____Vcellinp__u_interconnect__a_row_data[4];
    CData/*5:0*/ top_level__DOT____Vcellout__u_interconnect__b_read_addr[4];
    CData/*5:0*/ top_level__DOT____Vcellout__u_interconnect__a_read_addr[4];
    IData/*31:0*/ top_level__DOT____Vcellout__gen_clusters__BRA__0__KET____DOT__u_cluster__shadow_accum_out[2];
    IData/*31:0*/ top_level__DOT____Vcellout__gen_clusters__BRA__0__KET____DOT__u_cluster__accum_out[2];
    SData/*15:0*/ top_level__DOT____Vcellinp__gen_clusters__BRA__0__KET____DOT__u_cluster__lane_b[2];
    SData/*15:0*/ top_level__DOT____Vcellinp__gen_clusters__BRA__0__KET____DOT__u_cluster__lane_a[2];
    IData/*31:0*/ top_level__DOT____Vcellout__gen_clusters__BRA__1__KET____DOT__u_cluster__shadow_accum_out[2];
    IData/*31:0*/ top_level__DOT____Vcellout__gen_clusters__BRA__1__KET____DOT__u_cluster__accum_out[2];
    SData/*15:0*/ top_level__DOT____Vcellinp__gen_clusters__BRA__1__KET____DOT__u_cluster__lane_b[2];
    SData/*15:0*/ top_level__DOT____Vcellinp__gen_clusters__BRA__1__KET____DOT__u_cluster__lane_a[2];
    IData/*31:0*/ top_level__DOT____Vcellout__gen_clusters__BRA__2__KET____DOT__u_cluster__shadow_accum_out[2];
    IData/*31:0*/ top_level__DOT____Vcellout__gen_clusters__BRA__2__KET____DOT__u_cluster__accum_out[2];
    SData/*15:0*/ top_level__DOT____Vcellinp__gen_clusters__BRA__2__KET____DOT__u_cluster__lane_b[2];
    SData/*15:0*/ top_level__DOT____Vcellinp__gen_clusters__BRA__2__KET____DOT__u_cluster__lane_a[2];
    IData/*31:0*/ top_level__DOT____Vcellout__gen_clusters__BRA__3__KET____DOT__u_cluster__shadow_accum_out[2];
    IData/*31:0*/ top_level__DOT____Vcellout__gen_clusters__BRA__3__KET____DOT__u_cluster__accum_out[2];
    SData/*15:0*/ top_level__DOT____Vcellinp__gen_clusters__BRA__3__KET____DOT__u_cluster__lane_b[2];
    SData/*15:0*/ top_level__DOT____Vcellinp__gen_clusters__BRA__3__KET____DOT__u_cluster__lane_a[2];
    IData/*31:0*/ top_level__DOT____Vcellout__gen_clusters__BRA__4__KET____DOT__u_cluster__shadow_accum_out[2];
    IData/*31:0*/ top_level__DOT____Vcellout__gen_clusters__BRA__4__KET____DOT__u_cluster__accum_out[2];
    SData/*15:0*/ top_level__DOT____Vcellinp__gen_clusters__BRA__4__KET____DOT__u_cluster__lane_b[2];
    SData/*15:0*/ top_level__DOT____Vcellinp__gen_clusters__BRA__4__KET____DOT__u_cluster__lane_a[2];
    IData/*31:0*/ top_level__DOT____Vcellout__gen_clusters__BRA__5__KET____DOT__u_cluster__shadow_accum_out[2];
    IData/*31:0*/ top_level__DOT____Vcellout__gen_clusters__BRA__5__KET____DOT__u_cluster__accum_out[2];
    SData/*15:0*/ top_level__DOT____Vcellinp__gen_clusters__BRA__5__KET____DOT__u_cluster__lane_b[2];
    SData/*15:0*/ top_level__DOT____Vcellinp__gen_clusters__BRA__5__KET____DOT__u_cluster__lane_a[2];
    IData/*31:0*/ top_level__DOT____Vcellout__gen_clusters__BRA__6__KET____DOT__u_cluster__shadow_accum_out[2];
    IData/*31:0*/ top_level__DOT____Vcellout__gen_clusters__BRA__6__KET____DOT__u_cluster__accum_out[2];
    SData/*15:0*/ top_level__DOT____Vcellinp__gen_clusters__BRA__6__KET____DOT__u_cluster__lane_b[2];
    SData/*15:0*/ top_level__DOT____Vcellinp__gen_clusters__BRA__6__KET____DOT__u_cluster__lane_a[2];
    IData/*31:0*/ top_level__DOT____Vcellout__gen_clusters__BRA__7__KET____DOT__u_cluster__shadow_accum_out[2];
    IData/*31:0*/ top_level__DOT____Vcellout__gen_clusters__BRA__7__KET____DOT__u_cluster__accum_out[2];
    SData/*15:0*/ top_level__DOT____Vcellinp__gen_clusters__BRA__7__KET____DOT__u_cluster__lane_b[2];
    SData/*15:0*/ top_level__DOT____Vcellinp__gen_clusters__BRA__7__KET____DOT__u_cluster__lane_a[2];
    
    // INTERNAL VARIABLES
    // Internals; generally not touched by application code
    Vtop_level__Syms* __VlSymsp;  // Symbol table
    
    // CONSTRUCTORS
  private:
    VL_UNCOPYABLE(Vtop_level);  ///< Copying not allowed
  public:
    /// Construct the model; called by application code
    /// The special name  may be used to make a wrapper with a
    /// single model invisible with respect to DPI scope names.
    Vtop_level(const char* name = "TOP");
    /// Destroy the model; called (often implicitly) by application code
    ~Vtop_level();
    
    // API METHODS
    /// Evaluate the model.  Application must call when inputs change.
    void eval() { eval_step(); }
    /// Evaluate when calling multiple units/models per time step.
    void eval_step();
    /// Evaluate at end of a timestep for tracing, when using eval_step().
    /// Application must call after all eval() and before time changes.
    void eval_end_step() {}
    /// Simulation complete, run final blocks.  Application must call on completion.
    void final();
    
    // INTERNAL METHODS
  private:
    static void _eval_initial_loop(Vtop_level__Syms* __restrict vlSymsp);
  public:
    void __Vconfigure(Vtop_level__Syms* symsp, bool first);
  private:
    static QData _change_request(Vtop_level__Syms* __restrict vlSymsp);
    static QData _change_request_1(Vtop_level__Syms* __restrict vlSymsp);
  public:
    static void _combo__TOP__6(Vtop_level__Syms* __restrict vlSymsp);
  private:
    void _ctor_var_reset() VL_ATTR_COLD;
  public:
    static void _eval(Vtop_level__Syms* __restrict vlSymsp);
  private:
#ifdef VL_DEBUG
    void _eval_debug_assertions();
#endif  // VL_DEBUG
  public:
    static void _eval_initial(Vtop_level__Syms* __restrict vlSymsp) VL_ATTR_COLD;
    static void _eval_settle(Vtop_level__Syms* __restrict vlSymsp) VL_ATTR_COLD;
    static void _initial__TOP__1(Vtop_level__Syms* __restrict vlSymsp) VL_ATTR_COLD;
    static void _sequent__TOP__4(Vtop_level__Syms* __restrict vlSymsp);
    static void _sequent__TOP__5(Vtop_level__Syms* __restrict vlSymsp);
    static void _settle__TOP__2(Vtop_level__Syms* __restrict vlSymsp) VL_ATTR_COLD;
    static void _settle__TOP__3(Vtop_level__Syms* __restrict vlSymsp) VL_ATTR_COLD;
} VL_ATTR_ALIGNED(VL_CACHE_LINE_BYTES);

//----------


#endif  // guard
