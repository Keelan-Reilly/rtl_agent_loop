// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design internal header
// See Vtop_level.h for the primary calling header

#ifndef _VTOP_LEVEL_CLUSTER__PI4_H_
#define _VTOP_LEVEL_CLUSTER__PI4_H_  // guard

#include "verilated_heavy.h"

//==========

class Vtop_level__Syms;

//----------

VL_MODULE(Vtop_level_cluster__pi4) {
  public:
    
    // PORTS
    VL_IN8(clk,0,0);
    VL_IN8(rst,0,0);
    VL_IN8(clear_acc,0,0);
    VL_IN8(compute_en,0,0);
    VL_IN8(shared_phase,0,0);
    VL_IN16(lane_a[4],15,0);
    VL_IN16(lane_b[4],15,0);
    VL_OUT(accum_out[4],31,0);
    
    // LOCAL SIGNALS
    IData/*31:0*/ __PVT__logical_lane;
    IData/*31:0*/ __PVT__gen_main_pes__BRA__0__KET____DOT__u_pe__DOT__product_full;
    IData/*31:0*/ __PVT__gen_main_pes__BRA__0__KET____DOT__u_pe__DOT__product_scaled;
    IData/*31:0*/ __PVT__gen_main_pes__BRA__1__KET____DOT__u_pe__DOT__product_full;
    IData/*31:0*/ __PVT__gen_main_pes__BRA__1__KET____DOT__u_pe__DOT__product_scaled;
    IData/*31:0*/ __PVT__gen_main_pes__BRA__2__KET____DOT__u_pe__DOT__product_full;
    IData/*31:0*/ __PVT__gen_main_pes__BRA__2__KET____DOT__u_pe__DOT__product_scaled;
    IData/*31:0*/ __PVT__gen_main_pes__BRA__3__KET____DOT__u_pe__DOT__product_full;
    IData/*31:0*/ __PVT__gen_main_pes__BRA__3__KET____DOT__u_pe__DOT__product_scaled;
    IData/*31:0*/ __PVT__accum_bank[4];
    SData/*15:0*/ __PVT__pe_a[4];
    SData/*15:0*/ __PVT__pe_b[4];
    IData/*31:0*/ __PVT__pe_seed[4];
    CData/*0:0*/ __PVT__pe_valid[4];
    CData/*0:0*/ __PVT__pe_done[4];
    IData/*31:0*/ __PVT__pe_result[4];
    IData/*31:0*/ __PVT__accum_next[4];
    
    // LOCAL VARIABLES
    CData/*0:0*/ __Vdlyvset__accum_bank__v0;
    CData/*0:0*/ __Vdlyvset__accum_bank__v4;
    IData/*31:0*/ __Vcellout__gen_main_pes__BRA__0__KET____DOT__u_pe__acc_result;
    IData/*31:0*/ __Vcellout__gen_main_pes__BRA__1__KET____DOT__u_pe__acc_result;
    IData/*31:0*/ __Vcellout__gen_main_pes__BRA__2__KET____DOT__u_pe__acc_result;
    IData/*31:0*/ __Vcellout__gen_main_pes__BRA__3__KET____DOT__u_pe__acc_result;
    IData/*31:0*/ __Vdlyvval__accum_bank__v4;
    IData/*31:0*/ __Vdlyvval__accum_bank__v5;
    IData/*31:0*/ __Vdlyvval__accum_bank__v6;
    IData/*31:0*/ __Vdlyvval__accum_bank__v7;
    
    // INTERNAL VARIABLES
  private:
    Vtop_level__Syms* __VlSymsp;  // Symbol table
  public:
    
    // CONSTRUCTORS
  private:
    VL_UNCOPYABLE(Vtop_level_cluster__pi4);  ///< Copying not allowed
  public:
    Vtop_level_cluster__pi4(const char* name = "TOP");
    ~Vtop_level_cluster__pi4();
    
    // INTERNAL METHODS
    void __Vconfigure(Vtop_level__Syms* symsp, bool first);
  private:
    void _ctor_var_reset() VL_ATTR_COLD;
  public:
    void _sequent__TOP__top_level__DOT__gen_clusters__BRA__0__KET____DOT__u_cluster__33(Vtop_level__Syms* __restrict vlSymsp);
    void _settle__TOP__top_level__DOT__gen_clusters__BRA__0__KET____DOT__u_cluster__1(Vtop_level__Syms* __restrict vlSymsp) VL_ATTR_COLD;
    void _settle__TOP__top_level__DOT__gen_clusters__BRA__0__KET____DOT__u_cluster__17(Vtop_level__Syms* __restrict vlSymsp) VL_ATTR_COLD;
    void _settle__TOP__top_level__DOT__gen_clusters__BRA__0__KET____DOT__u_cluster__49(Vtop_level__Syms* __restrict vlSymsp);
} VL_ATTR_ALIGNED(VL_CACHE_LINE_BYTES);

//----------


#endif  // guard
