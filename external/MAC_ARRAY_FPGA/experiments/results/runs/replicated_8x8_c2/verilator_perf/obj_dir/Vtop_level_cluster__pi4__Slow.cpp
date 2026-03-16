// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vtop_level.h for the primary calling header

#include "Vtop_level_cluster__pi4.h"
#include "Vtop_level__Syms.h"

//==========

VL_CTOR_IMP(Vtop_level_cluster__pi4) {
    // Reset internal values
    // Reset structure values
    _ctor_var_reset();
}

void Vtop_level_cluster__pi4::__Vconfigure(Vtop_level__Syms* vlSymsp, bool first) {
    if (false && first) {}  // Prevent unused
    this->__VlSymsp = vlSymsp;
    if (false && this->__VlSymsp) {}  // Prevent unused
}

Vtop_level_cluster__pi4::~Vtop_level_cluster__pi4() {
}

void Vtop_level_cluster__pi4::_settle__TOP__top_level__DOT__gen_clusters__BRA__0__KET____DOT__u_cluster__1(Vtop_level__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+        Vtop_level_cluster__pi4::_settle__TOP__top_level__DOT__gen_clusters__BRA__0__KET____DOT__u_cluster__1\n"); );
    Vtop_level* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    this->__PVT__shadow_pe_valid[0U] = 1U;
    this->__PVT__shadow_pe_valid[1U] = 1U;
    this->__PVT__pe_valid[0U] = 1U;
    this->__PVT__pe_valid[1U] = 1U;
    this->accum_out[0U] = this->__PVT__accum_bank[0U];
    this->accum_out[1U] = this->__PVT__accum_bank[1U];
    this->shadow_accum_out[0U] = this->__PVT__shadow_accum_bank
        [0U];
    this->shadow_accum_out[1U] = this->__PVT__shadow_accum_bank
        [1U];
    this->__PVT__shadow_pe_a[0U] = this->lane_a[1U];
    this->__PVT__shadow_pe_b[0U] = this->lane_b[1U];
    this->__PVT__shadow_pe_seed[0U] = this->__PVT__shadow_accum_bank
        [1U];
    this->__PVT__shadow_pe_a[1U] = this->lane_a[0U];
    this->__PVT__shadow_pe_b[1U] = this->lane_b[0U];
    this->__PVT__shadow_pe_seed[1U] = this->__PVT__shadow_accum_bank
        [0U];
    this->__Vlvbound1 = this->lane_a[0U];
    this->__PVT__shared_lane_a[0U][0U] = this->__Vlvbound1;
    this->__Vlvbound2 = this->lane_b[0U];
    this->__PVT__shared_lane_b[0U][0U] = this->__Vlvbound2;
    this->__PVT__pe_seed[0U] = this->__PVT__accum_bank
        [0U];
    this->__PVT__pe_a[0U] = this->lane_a[0U];
    this->__PVT__pe_b[0U] = this->lane_b[0U];
    this->__Vlvbound1 = this->lane_a[1U];
    this->__PVT__shared_lane_a[1U][0U] = this->__Vlvbound1;
    this->__Vlvbound2 = this->lane_b[1U];
    this->__PVT__shared_lane_b[1U][0U] = this->__Vlvbound2;
    this->__PVT__pe_seed[1U] = this->__PVT__accum_bank
        [1U];
    this->__PVT__pe_a[1U] = this->lane_a[1U];
    this->__PVT__pe_b[1U] = this->lane_b[1U];
    this->__PVT__shadow_done[0U] = ((IData)(vlTOPp->top_level__DOT__compute_en) 
                                    & this->__PVT__shadow_pe_valid
                                    [0U]);
    this->__PVT__shadow_done[1U] = ((IData)(vlTOPp->top_level__DOT__compute_en) 
                                    & this->__PVT__shadow_pe_valid
                                    [1U]);
    this->__PVT__pe_done[0U] = ((IData)(vlTOPp->top_level__DOT__compute_en) 
                                & this->__PVT__pe_valid
                                [0U]);
    this->__PVT__pe_done[1U] = ((IData)(vlTOPp->top_level__DOT__compute_en) 
                                & this->__PVT__pe_valid
                                [1U]);
    this->__PVT__gen_main_pes__BRA__0__KET____DOT__gen_shadow_replicas__DOT__u_shadow_pe__DOT__product_full 
        = VL_MULS_III(32,32,32, VL_EXTENDS_II(32,16, 
                                              this->__PVT__shadow_pe_a
                                              [0U]), 
                      VL_EXTENDS_II(32,16, this->__PVT__shadow_pe_b
                                    [0U]));
    this->__PVT__gen_main_pes__BRA__0__KET____DOT__gen_shadow_replicas__DOT__u_shadow_pe__DOT__product_scaled 
        = VL_SHIFTRS_III(32,32,32, this->__PVT__gen_main_pes__BRA__0__KET____DOT__gen_shadow_replicas__DOT__u_shadow_pe__DOT__product_full, 8U);
    this->__Vcellout__gen_main_pes__BRA__0__KET____DOT__gen_shadow_replicas__DOT__u_shadow_pe__acc_result 
        = (this->__PVT__shadow_pe_seed[0U] + this->__PVT__gen_main_pes__BRA__0__KET____DOT__gen_shadow_replicas__DOT__u_shadow_pe__DOT__product_scaled);
    this->__PVT__gen_main_pes__BRA__1__KET____DOT__gen_shadow_replicas__DOT__u_shadow_pe__DOT__product_full 
        = VL_MULS_III(32,32,32, VL_EXTENDS_II(32,16, 
                                              this->__PVT__shadow_pe_a
                                              [1U]), 
                      VL_EXTENDS_II(32,16, this->__PVT__shadow_pe_b
                                    [1U]));
    this->__PVT__gen_main_pes__BRA__1__KET____DOT__gen_shadow_replicas__DOT__u_shadow_pe__DOT__product_scaled 
        = VL_SHIFTRS_III(32,32,32, this->__PVT__gen_main_pes__BRA__1__KET____DOT__gen_shadow_replicas__DOT__u_shadow_pe__DOT__product_full, 8U);
    this->__Vcellout__gen_main_pes__BRA__1__KET____DOT__gen_shadow_replicas__DOT__u_shadow_pe__acc_result 
        = (this->__PVT__shadow_pe_seed[1U] + this->__PVT__gen_main_pes__BRA__1__KET____DOT__gen_shadow_replicas__DOT__u_shadow_pe__DOT__product_scaled);
    this->__PVT__gen_main_pes__BRA__0__KET____DOT__u_pe__DOT__product_full 
        = VL_MULS_III(32,32,32, VL_EXTENDS_II(32,16, 
                                              this->__PVT__pe_a
                                              [0U]), 
                      VL_EXTENDS_II(32,16, this->__PVT__pe_b
                                    [0U]));
    this->__PVT__gen_main_pes__BRA__0__KET____DOT__u_pe__DOT__product_scaled 
        = VL_SHIFTRS_III(32,32,32, this->__PVT__gen_main_pes__BRA__0__KET____DOT__u_pe__DOT__product_full, 8U);
    this->__Vcellout__gen_main_pes__BRA__0__KET____DOT__u_pe__acc_result 
        = (this->__PVT__pe_seed[0U] + this->__PVT__gen_main_pes__BRA__0__KET____DOT__u_pe__DOT__product_scaled);
    this->__PVT__gen_main_pes__BRA__1__KET____DOT__u_pe__DOT__product_full 
        = VL_MULS_III(32,32,32, VL_EXTENDS_II(32,16, 
                                              this->__PVT__pe_a
                                              [1U]), 
                      VL_EXTENDS_II(32,16, this->__PVT__pe_b
                                    [1U]));
    this->__PVT__gen_main_pes__BRA__1__KET____DOT__u_pe__DOT__product_scaled 
        = VL_SHIFTRS_III(32,32,32, this->__PVT__gen_main_pes__BRA__1__KET____DOT__u_pe__DOT__product_full, 8U);
    this->__Vcellout__gen_main_pes__BRA__1__KET____DOT__u_pe__acc_result 
        = (this->__PVT__pe_seed[1U] + this->__PVT__gen_main_pes__BRA__1__KET____DOT__u_pe__DOT__product_scaled);
    this->__PVT__shadow_result[0U] = this->__Vcellout__gen_main_pes__BRA__0__KET____DOT__gen_shadow_replicas__DOT__u_shadow_pe__acc_result;
    this->__PVT__shadow_result[1U] = this->__Vcellout__gen_main_pes__BRA__1__KET____DOT__gen_shadow_replicas__DOT__u_shadow_pe__acc_result;
    this->__PVT__pe_result[0U] = this->__Vcellout__gen_main_pes__BRA__0__KET____DOT__u_pe__acc_result;
    this->__PVT__pe_result[1U] = this->__Vcellout__gen_main_pes__BRA__1__KET____DOT__u_pe__acc_result;
    this->__PVT__shadow_accum_next[0U] = this->__PVT__shadow_accum_bank
        [0U];
    this->__PVT__shadow_accum_next[1U] = this->__PVT__shadow_accum_bank
        [1U];
    this->__PVT__shadow_lane = 1U;
    if (this->__PVT__shadow_done[0U]) {
        this->__PVT__shadow_accum_next[(1U & this->__PVT__shadow_lane)] 
            = this->__PVT__shadow_result[0U];
    }
    this->__PVT__shadow_lane = 0U;
    if (this->__PVT__shadow_done[1U]) {
        this->__PVT__shadow_accum_next[(1U & this->__PVT__shadow_lane)] 
            = this->__PVT__shadow_result[1U];
    }
    this->__PVT__accum_next[0U] = this->__PVT__accum_bank
        [0U];
    this->__PVT__accum_next[1U] = this->__PVT__accum_bank
        [1U];
    this->__PVT__logical_lane = 0U;
    if (this->__PVT__pe_done[0U]) {
        this->__PVT__accum_next[(1U & this->__PVT__logical_lane)] 
            = this->__PVT__pe_result[0U];
    }
    this->__PVT__logical_lane = 1U;
    if (this->__PVT__pe_done[1U]) {
        this->__PVT__accum_next[(1U & this->__PVT__logical_lane)] 
            = this->__PVT__pe_result[1U];
    }
}

void Vtop_level_cluster__pi4::_ctor_var_reset() {
    VL_DEBUG_IF(VL_DBG_MSGF("+        Vtop_level_cluster__pi4::_ctor_var_reset\n"); );
    // Body
    clk = VL_RAND_RESET_I(1);
    rst = VL_RAND_RESET_I(1);
    clear_acc = VL_RAND_RESET_I(1);
    compute_en = VL_RAND_RESET_I(1);
    shared_phase = VL_RAND_RESET_I(1);
    { int __Vi0=0; for (; __Vi0<2; ++__Vi0) {
            lane_a[__Vi0] = VL_RAND_RESET_I(16);
    }}
    { int __Vi0=0; for (; __Vi0<2; ++__Vi0) {
            lane_b[__Vi0] = VL_RAND_RESET_I(16);
    }}
    { int __Vi0=0; for (; __Vi0<2; ++__Vi0) {
            accum_out[__Vi0] = VL_RAND_RESET_I(32);
    }}
    { int __Vi0=0; for (; __Vi0<2; ++__Vi0) {
            shadow_accum_out[__Vi0] = VL_RAND_RESET_I(32);
    }}
    { int __Vi0=0; for (; __Vi0<2; ++__Vi0) {
            __PVT__accum_bank[__Vi0] = VL_RAND_RESET_I(32);
    }}
    { int __Vi0=0; for (; __Vi0<2; ++__Vi0) {
            __PVT__shadow_accum_bank[__Vi0] = VL_RAND_RESET_I(32);
    }}
    { int __Vi0=0; for (; __Vi0<2; ++__Vi0) {
            __PVT__pe_a[__Vi0] = VL_RAND_RESET_I(16);
    }}
    { int __Vi0=0; for (; __Vi0<2; ++__Vi0) {
            __PVT__pe_b[__Vi0] = VL_RAND_RESET_I(16);
    }}
    { int __Vi0=0; for (; __Vi0<2; ++__Vi0) {
            __PVT__shadow_pe_a[__Vi0] = VL_RAND_RESET_I(16);
    }}
    { int __Vi0=0; for (; __Vi0<2; ++__Vi0) {
            __PVT__shadow_pe_b[__Vi0] = VL_RAND_RESET_I(16);
    }}
    { int __Vi0=0; for (; __Vi0<2; ++__Vi0) {
            __PVT__pe_seed[__Vi0] = VL_RAND_RESET_I(32);
    }}
    { int __Vi0=0; for (; __Vi0<2; ++__Vi0) {
            __PVT__shadow_pe_seed[__Vi0] = VL_RAND_RESET_I(32);
    }}
    { int __Vi0=0; for (; __Vi0<2; ++__Vi0) {
            __PVT__pe_valid[__Vi0] = VL_RAND_RESET_I(1);
    }}
    { int __Vi0=0; for (; __Vi0<2; ++__Vi0) {
            __PVT__shadow_pe_valid[__Vi0] = VL_RAND_RESET_I(1);
    }}
    { int __Vi0=0; for (; __Vi0<2; ++__Vi0) {
            __PVT__pe_done[__Vi0] = VL_RAND_RESET_I(1);
    }}
    { int __Vi0=0; for (; __Vi0<2; ++__Vi0) {
            __PVT__pe_result[__Vi0] = VL_RAND_RESET_I(32);
    }}
    { int __Vi0=0; for (; __Vi0<2; ++__Vi0) {
            __PVT__shadow_done[__Vi0] = VL_RAND_RESET_I(1);
    }}
    { int __Vi0=0; for (; __Vi0<2; ++__Vi0) {
            __PVT__shadow_result[__Vi0] = VL_RAND_RESET_I(32);
    }}
    { int __Vi0=0; for (; __Vi0<2; ++__Vi0) {
            __PVT__accum_next[__Vi0] = VL_RAND_RESET_I(32);
    }}
    { int __Vi0=0; for (; __Vi0<2; ++__Vi0) {
            __PVT__shadow_accum_next[__Vi0] = VL_RAND_RESET_I(32);
    }}
    { int __Vi0=0; for (; __Vi0<2; ++__Vi0) {
            { int __Vi1=0; for (; __Vi1<1; ++__Vi1) {
                    __PVT__shared_lane_a[__Vi0][__Vi1] = VL_RAND_RESET_I(16);
            }}
    }}
    { int __Vi0=0; for (; __Vi0<2; ++__Vi0) {
            { int __Vi1=0; for (; __Vi1<1; ++__Vi1) {
                    __PVT__shared_lane_b[__Vi0][__Vi1] = VL_RAND_RESET_I(16);
            }}
    }}
    __PVT__logical_lane = VL_RAND_RESET_I(32);
    __PVT__shadow_lane = VL_RAND_RESET_I(32);
    __Vcellout__gen_main_pes__BRA__0__KET____DOT__u_pe__acc_result = VL_RAND_RESET_I(32);
    __Vcellout__gen_main_pes__BRA__0__KET____DOT__gen_shadow_replicas__DOT__u_shadow_pe__acc_result = VL_RAND_RESET_I(32);
    __Vcellout__gen_main_pes__BRA__1__KET____DOT__u_pe__acc_result = VL_RAND_RESET_I(32);
    __Vcellout__gen_main_pes__BRA__1__KET____DOT__gen_shadow_replicas__DOT__u_shadow_pe__acc_result = VL_RAND_RESET_I(32);
    __Vlvbound1 = VL_RAND_RESET_I(16);
    __Vlvbound2 = VL_RAND_RESET_I(16);
    __PVT__gen_main_pes__BRA__0__KET____DOT__u_pe__DOT__product_full = VL_RAND_RESET_I(32);
    __PVT__gen_main_pes__BRA__0__KET____DOT__u_pe__DOT__product_scaled = VL_RAND_RESET_I(32);
    __PVT__gen_main_pes__BRA__0__KET____DOT__gen_shadow_replicas__DOT__u_shadow_pe__DOT__product_full = VL_RAND_RESET_I(32);
    __PVT__gen_main_pes__BRA__0__KET____DOT__gen_shadow_replicas__DOT__u_shadow_pe__DOT__product_scaled = VL_RAND_RESET_I(32);
    __PVT__gen_main_pes__BRA__1__KET____DOT__u_pe__DOT__product_full = VL_RAND_RESET_I(32);
    __PVT__gen_main_pes__BRA__1__KET____DOT__u_pe__DOT__product_scaled = VL_RAND_RESET_I(32);
    __PVT__gen_main_pes__BRA__1__KET____DOT__gen_shadow_replicas__DOT__u_shadow_pe__DOT__product_full = VL_RAND_RESET_I(32);
    __PVT__gen_main_pes__BRA__1__KET____DOT__gen_shadow_replicas__DOT__u_shadow_pe__DOT__product_scaled = VL_RAND_RESET_I(32);
    __Vdlyvset__accum_bank__v0 = 0;
    __Vdlyvval__accum_bank__v2 = VL_RAND_RESET_I(32);
    __Vdlyvset__accum_bank__v2 = 0;
    __Vdlyvval__accum_bank__v3 = VL_RAND_RESET_I(32);
    __Vdlyvset__shadow_accum_bank__v0 = 0;
    __Vdlyvval__shadow_accum_bank__v2 = VL_RAND_RESET_I(32);
    __Vdlyvset__shadow_accum_bank__v2 = 0;
    __Vdlyvval__shadow_accum_bank__v3 = VL_RAND_RESET_I(32);
}
