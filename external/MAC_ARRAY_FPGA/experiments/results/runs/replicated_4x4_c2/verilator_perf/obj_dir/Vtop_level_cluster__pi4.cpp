// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vtop_level.h for the primary calling header

#include "Vtop_level_cluster__pi4.h"
#include "Vtop_level__Syms.h"

//==========

VL_INLINE_OPT void Vtop_level_cluster__pi4::_sequent__TOP__top_level__DOT__gen_clusters__BRA__0__KET____DOT__u_cluster__9(Vtop_level__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+        Vtop_level_cluster__pi4::_sequent__TOP__top_level__DOT__gen_clusters__BRA__0__KET____DOT__u_cluster__9\n"); );
    Vtop_level* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
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
    this->__PVT__logical_lane = 2U;
    this->__Vdlyvset__shadow_accum_bank__v0 = 0U;
    this->__Vdlyvset__shadow_accum_bank__v2 = 0U;
    this->__Vdlyvset__accum_bank__v0 = 0U;
    this->__Vdlyvset__accum_bank__v2 = 0U;
    if (((IData)(vlTOPp->rst) | (IData)(vlTOPp->top_level__DOT__clear_acc))) {
        this->__Vdlyvset__shadow_accum_bank__v0 = 1U;
    } else {
        this->__Vdlyvval__shadow_accum_bank__v2 = this->__PVT__shadow_accum_next
            [0U];
        this->__Vdlyvset__shadow_accum_bank__v2 = 1U;
        this->__Vdlyvval__shadow_accum_bank__v3 = this->__PVT__shadow_accum_next
            [1U];
    }
    if (((IData)(vlTOPp->rst) | (IData)(vlTOPp->top_level__DOT__clear_acc))) {
        this->__Vdlyvset__accum_bank__v0 = 1U;
    } else {
        this->__Vdlyvval__accum_bank__v2 = this->__PVT__accum_next
            [0U];
        this->__Vdlyvset__accum_bank__v2 = 1U;
        this->__Vdlyvval__accum_bank__v3 = this->__PVT__accum_next
            [1U];
    }
    if (this->__Vdlyvset__shadow_accum_bank__v0) {
        this->__PVT__shadow_accum_bank[0U] = 0U;
        this->__PVT__shadow_accum_bank[1U] = 0U;
    }
    if (this->__Vdlyvset__shadow_accum_bank__v2) {
        this->__PVT__shadow_accum_bank[0U] = this->__Vdlyvval__shadow_accum_bank__v2;
        this->__PVT__shadow_accum_bank[1U] = this->__Vdlyvval__shadow_accum_bank__v3;
    }
    if (this->__Vdlyvset__accum_bank__v0) {
        this->__PVT__accum_bank[0U] = 0U;
        this->__PVT__accum_bank[1U] = 0U;
    }
    if (this->__Vdlyvset__accum_bank__v2) {
        this->__PVT__accum_bank[0U] = this->__Vdlyvval__accum_bank__v2;
        this->__PVT__accum_bank[1U] = this->__Vdlyvval__accum_bank__v3;
    }
    this->shadow_accum_out[0U] = this->__PVT__shadow_accum_bank
        [0U];
    this->shadow_accum_out[1U] = this->__PVT__shadow_accum_bank
        [1U];
    this->accum_out[0U] = this->__PVT__accum_bank[0U];
    this->accum_out[1U] = this->__PVT__accum_bank[1U];
}

VL_INLINE_OPT void Vtop_level_cluster__pi4::_combo__TOP__top_level__DOT__gen_clusters__BRA__0__KET____DOT__u_cluster__17(Vtop_level__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+        Vtop_level_cluster__pi4::_combo__TOP__top_level__DOT__gen_clusters__BRA__0__KET____DOT__u_cluster__17\n"); );
    Vtop_level* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
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
