// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vtop_level.h for the primary calling header

#include "Vtop_level.h"
#include "Vtop_level__Syms.h"

//==========

void Vtop_level::eval_step() {
    VL_DEBUG_IF(VL_DBG_MSGF("+++++TOP Evaluate Vtop_level::eval\n"); );
    Vtop_level__Syms* __restrict vlSymsp = this->__VlSymsp;  // Setup global symbol table
    Vtop_level* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
#ifdef VL_DEBUG
    // Debug assertions
    _eval_debug_assertions();
#endif  // VL_DEBUG
    // Initialize
    if (VL_UNLIKELY(!vlSymsp->__Vm_didInit)) _eval_initial_loop(vlSymsp);
    // Evaluate till stable
    int __VclockLoop = 0;
    QData __Vchange = 1;
    do {
        VL_DEBUG_IF(VL_DBG_MSGF("+ Clock loop\n"););
        _eval(vlSymsp);
        if (VL_UNLIKELY(++__VclockLoop > 100)) {
            // About to fail, so enable debug to see what's not settling.
            // Note you must run make with OPT=-DVL_DEBUG for debug prints.
            int __Vsaved_debug = Verilated::debug();
            Verilated::debug(1);
            __Vchange = _change_request(vlSymsp);
            Verilated::debug(__Vsaved_debug);
            VL_FATAL_MT("/home/keelan/rtl_agent_loop/external/MAC_ARRAY_FPGA/hdl/top_level.sv", 1, "",
                "Verilated model didn't converge\n"
                "- See DIDNOTCONVERGE in the Verilator manual");
        } else {
            __Vchange = _change_request(vlSymsp);
        }
    } while (VL_UNLIKELY(__Vchange));
}

void Vtop_level::_eval_initial_loop(Vtop_level__Syms* __restrict vlSymsp) {
    vlSymsp->__Vm_didInit = true;
    _eval_initial(vlSymsp);
    // Evaluate till stable
    int __VclockLoop = 0;
    QData __Vchange = 1;
    do {
        _eval_settle(vlSymsp);
        _eval(vlSymsp);
        if (VL_UNLIKELY(++__VclockLoop > 100)) {
            // About to fail, so enable debug to see what's not settling.
            // Note you must run make with OPT=-DVL_DEBUG for debug prints.
            int __Vsaved_debug = Verilated::debug();
            Verilated::debug(1);
            __Vchange = _change_request(vlSymsp);
            Verilated::debug(__Vsaved_debug);
            VL_FATAL_MT("/home/keelan/rtl_agent_loop/external/MAC_ARRAY_FPGA/hdl/top_level.sv", 1, "",
                "Verilated model didn't DC converge\n"
                "- See DIDNOTCONVERGE in the Verilator manual");
        } else {
            __Vchange = _change_request(vlSymsp);
        }
    } while (VL_UNLIKELY(__Vchange));
}

VL_INLINE_OPT void Vtop_level::_sequent__TOP__3(Vtop_level__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop_level::_sequent__TOP__3\n"); );
    Vtop_level* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Variables
    CData/*0:0*/ __Vdlyvset__top_level__DOT__output_mem__v0;
    CData/*5:0*/ __Vdlyvdim0__top_level__DOT__output_mem__v64;
    CData/*0:0*/ __Vdlyvset__top_level__DOT__output_mem__v64;
    CData/*5:0*/ __Vdlyvdim0__top_level__DOT__output_mem__v65;
    CData/*0:0*/ __Vdlyvset__top_level__DOT__output_mem__v65;
    CData/*5:0*/ __Vdlyvdim0__top_level__DOT__output_mem__v66;
    CData/*0:0*/ __Vdlyvset__top_level__DOT__output_mem__v66;
    CData/*5:0*/ __Vdlyvdim0__top_level__DOT__output_mem__v67;
    CData/*0:0*/ __Vdlyvset__top_level__DOT__output_mem__v67;
    CData/*5:0*/ __Vdlyvdim0__top_level__DOT__output_mem__v68;
    CData/*0:0*/ __Vdlyvset__top_level__DOT__output_mem__v68;
    CData/*5:0*/ __Vdlyvdim0__top_level__DOT__output_mem__v69;
    CData/*0:0*/ __Vdlyvset__top_level__DOT__output_mem__v69;
    CData/*5:0*/ __Vdlyvdim0__top_level__DOT__output_mem__v70;
    CData/*0:0*/ __Vdlyvset__top_level__DOT__output_mem__v70;
    CData/*5:0*/ __Vdlyvdim0__top_level__DOT__output_mem__v71;
    CData/*0:0*/ __Vdlyvset__top_level__DOT__output_mem__v71;
    CData/*5:0*/ __Vdlyvdim0__top_level__DOT__output_mem__v72;
    CData/*0:0*/ __Vdlyvset__top_level__DOT__output_mem__v72;
    CData/*5:0*/ __Vdlyvdim0__top_level__DOT__output_mem__v73;
    CData/*0:0*/ __Vdlyvset__top_level__DOT__output_mem__v73;
    CData/*5:0*/ __Vdlyvdim0__top_level__DOT__output_mem__v74;
    CData/*0:0*/ __Vdlyvset__top_level__DOT__output_mem__v74;
    CData/*5:0*/ __Vdlyvdim0__top_level__DOT__output_mem__v75;
    CData/*0:0*/ __Vdlyvset__top_level__DOT__output_mem__v75;
    CData/*5:0*/ __Vdlyvdim0__top_level__DOT__output_mem__v76;
    CData/*0:0*/ __Vdlyvset__top_level__DOT__output_mem__v76;
    CData/*5:0*/ __Vdlyvdim0__top_level__DOT__output_mem__v77;
    CData/*0:0*/ __Vdlyvset__top_level__DOT__output_mem__v77;
    CData/*5:0*/ __Vdlyvdim0__top_level__DOT__output_mem__v78;
    CData/*0:0*/ __Vdlyvset__top_level__DOT__output_mem__v78;
    CData/*5:0*/ __Vdlyvdim0__top_level__DOT__output_mem__v79;
    CData/*0:0*/ __Vdlyvset__top_level__DOT__output_mem__v79;
    CData/*5:0*/ __Vdlyvdim0__top_level__DOT__output_mem__v80;
    CData/*0:0*/ __Vdlyvset__top_level__DOT__output_mem__v80;
    CData/*5:0*/ __Vdlyvdim0__top_level__DOT__output_mem__v81;
    CData/*0:0*/ __Vdlyvset__top_level__DOT__output_mem__v81;
    CData/*5:0*/ __Vdlyvdim0__top_level__DOT__output_mem__v82;
    CData/*0:0*/ __Vdlyvset__top_level__DOT__output_mem__v82;
    CData/*5:0*/ __Vdlyvdim0__top_level__DOT__output_mem__v83;
    CData/*0:0*/ __Vdlyvset__top_level__DOT__output_mem__v83;
    CData/*5:0*/ __Vdlyvdim0__top_level__DOT__output_mem__v84;
    CData/*0:0*/ __Vdlyvset__top_level__DOT__output_mem__v84;
    CData/*5:0*/ __Vdlyvdim0__top_level__DOT__output_mem__v85;
    CData/*0:0*/ __Vdlyvset__top_level__DOT__output_mem__v85;
    CData/*5:0*/ __Vdlyvdim0__top_level__DOT__output_mem__v86;
    CData/*0:0*/ __Vdlyvset__top_level__DOT__output_mem__v86;
    CData/*5:0*/ __Vdlyvdim0__top_level__DOT__output_mem__v87;
    CData/*0:0*/ __Vdlyvset__top_level__DOT__output_mem__v87;
    CData/*5:0*/ __Vdlyvdim0__top_level__DOT__output_mem__v88;
    CData/*0:0*/ __Vdlyvset__top_level__DOT__output_mem__v88;
    CData/*5:0*/ __Vdlyvdim0__top_level__DOT__output_mem__v89;
    CData/*0:0*/ __Vdlyvset__top_level__DOT__output_mem__v89;
    CData/*5:0*/ __Vdlyvdim0__top_level__DOT__output_mem__v90;
    CData/*0:0*/ __Vdlyvset__top_level__DOT__output_mem__v90;
    CData/*5:0*/ __Vdlyvdim0__top_level__DOT__output_mem__v91;
    CData/*0:0*/ __Vdlyvset__top_level__DOT__output_mem__v91;
    CData/*5:0*/ __Vdlyvdim0__top_level__DOT__output_mem__v92;
    CData/*0:0*/ __Vdlyvset__top_level__DOT__output_mem__v92;
    CData/*5:0*/ __Vdlyvdim0__top_level__DOT__output_mem__v93;
    CData/*0:0*/ __Vdlyvset__top_level__DOT__output_mem__v93;
    CData/*5:0*/ __Vdlyvdim0__top_level__DOT__output_mem__v94;
    CData/*0:0*/ __Vdlyvset__top_level__DOT__output_mem__v94;
    CData/*5:0*/ __Vdlyvdim0__top_level__DOT__output_mem__v95;
    CData/*0:0*/ __Vdlyvset__top_level__DOT__output_mem__v95;
    CData/*0:0*/ __Vdlyvset__top_level__DOT__gen_clusters__BRA__0__KET____DOT__u_cluster__DOT__accum_bank__v0;
    CData/*0:0*/ __Vdlyvset__top_level__DOT__gen_clusters__BRA__0__KET____DOT__u_cluster__DOT__accum_bank__v4;
    CData/*0:0*/ __Vdlyvset__top_level__DOT__gen_clusters__BRA__1__KET____DOT__u_cluster__DOT__accum_bank__v0;
    CData/*0:0*/ __Vdlyvset__top_level__DOT__gen_clusters__BRA__1__KET____DOT__u_cluster__DOT__accum_bank__v4;
    CData/*0:0*/ __Vdlyvset__top_level__DOT__gen_clusters__BRA__2__KET____DOT__u_cluster__DOT__accum_bank__v0;
    CData/*0:0*/ __Vdlyvset__top_level__DOT__gen_clusters__BRA__2__KET____DOT__u_cluster__DOT__accum_bank__v4;
    CData/*0:0*/ __Vdlyvset__top_level__DOT__gen_clusters__BRA__3__KET____DOT__u_cluster__DOT__accum_bank__v0;
    CData/*0:0*/ __Vdlyvset__top_level__DOT__gen_clusters__BRA__3__KET____DOT__u_cluster__DOT__accum_bank__v4;
    CData/*0:0*/ __Vdlyvset__top_level__DOT__gen_clusters__BRA__4__KET____DOT__u_cluster__DOT__accum_bank__v0;
    CData/*0:0*/ __Vdlyvset__top_level__DOT__gen_clusters__BRA__4__KET____DOT__u_cluster__DOT__accum_bank__v4;
    CData/*0:0*/ __Vdlyvset__top_level__DOT__gen_clusters__BRA__5__KET____DOT__u_cluster__DOT__accum_bank__v0;
    CData/*0:0*/ __Vdlyvset__top_level__DOT__gen_clusters__BRA__5__KET____DOT__u_cluster__DOT__accum_bank__v4;
    CData/*0:0*/ __Vdlyvset__top_level__DOT__gen_clusters__BRA__6__KET____DOT__u_cluster__DOT__accum_bank__v0;
    CData/*0:0*/ __Vdlyvset__top_level__DOT__gen_clusters__BRA__6__KET____DOT__u_cluster__DOT__accum_bank__v4;
    CData/*0:0*/ __Vdlyvset__top_level__DOT__gen_clusters__BRA__7__KET____DOT__u_cluster__DOT__accum_bank__v0;
    CData/*0:0*/ __Vdlyvset__top_level__DOT__gen_clusters__BRA__7__KET____DOT__u_cluster__DOT__accum_bank__v4;
    IData/*31:0*/ __Vdlyvval__top_level__DOT__output_mem__v64;
    IData/*31:0*/ __Vdlyvval__top_level__DOT__output_mem__v65;
    IData/*31:0*/ __Vdlyvval__top_level__DOT__output_mem__v66;
    IData/*31:0*/ __Vdlyvval__top_level__DOT__output_mem__v67;
    IData/*31:0*/ __Vdlyvval__top_level__DOT__output_mem__v68;
    IData/*31:0*/ __Vdlyvval__top_level__DOT__output_mem__v69;
    IData/*31:0*/ __Vdlyvval__top_level__DOT__output_mem__v70;
    IData/*31:0*/ __Vdlyvval__top_level__DOT__output_mem__v71;
    IData/*31:0*/ __Vdlyvval__top_level__DOT__output_mem__v72;
    IData/*31:0*/ __Vdlyvval__top_level__DOT__output_mem__v73;
    IData/*31:0*/ __Vdlyvval__top_level__DOT__output_mem__v74;
    IData/*31:0*/ __Vdlyvval__top_level__DOT__output_mem__v75;
    IData/*31:0*/ __Vdlyvval__top_level__DOT__output_mem__v76;
    IData/*31:0*/ __Vdlyvval__top_level__DOT__output_mem__v77;
    IData/*31:0*/ __Vdlyvval__top_level__DOT__output_mem__v78;
    IData/*31:0*/ __Vdlyvval__top_level__DOT__output_mem__v79;
    IData/*31:0*/ __Vdlyvval__top_level__DOT__output_mem__v80;
    IData/*31:0*/ __Vdlyvval__top_level__DOT__output_mem__v81;
    IData/*31:0*/ __Vdlyvval__top_level__DOT__output_mem__v82;
    IData/*31:0*/ __Vdlyvval__top_level__DOT__output_mem__v83;
    IData/*31:0*/ __Vdlyvval__top_level__DOT__output_mem__v84;
    IData/*31:0*/ __Vdlyvval__top_level__DOT__output_mem__v85;
    IData/*31:0*/ __Vdlyvval__top_level__DOT__output_mem__v86;
    IData/*31:0*/ __Vdlyvval__top_level__DOT__output_mem__v87;
    IData/*31:0*/ __Vdlyvval__top_level__DOT__output_mem__v88;
    IData/*31:0*/ __Vdlyvval__top_level__DOT__output_mem__v89;
    IData/*31:0*/ __Vdlyvval__top_level__DOT__output_mem__v90;
    IData/*31:0*/ __Vdlyvval__top_level__DOT__output_mem__v91;
    IData/*31:0*/ __Vdlyvval__top_level__DOT__output_mem__v92;
    IData/*31:0*/ __Vdlyvval__top_level__DOT__output_mem__v93;
    IData/*31:0*/ __Vdlyvval__top_level__DOT__output_mem__v94;
    IData/*31:0*/ __Vdlyvval__top_level__DOT__output_mem__v95;
    IData/*31:0*/ __Vdlyvval__top_level__DOT__gen_clusters__BRA__0__KET____DOT__u_cluster__DOT__accum_bank__v4;
    IData/*31:0*/ __Vdlyvval__top_level__DOT__gen_clusters__BRA__0__KET____DOT__u_cluster__DOT__accum_bank__v5;
    IData/*31:0*/ __Vdlyvval__top_level__DOT__gen_clusters__BRA__0__KET____DOT__u_cluster__DOT__accum_bank__v6;
    IData/*31:0*/ __Vdlyvval__top_level__DOT__gen_clusters__BRA__0__KET____DOT__u_cluster__DOT__accum_bank__v7;
    IData/*31:0*/ __Vdlyvval__top_level__DOT__gen_clusters__BRA__1__KET____DOT__u_cluster__DOT__accum_bank__v4;
    IData/*31:0*/ __Vdlyvval__top_level__DOT__gen_clusters__BRA__1__KET____DOT__u_cluster__DOT__accum_bank__v5;
    IData/*31:0*/ __Vdlyvval__top_level__DOT__gen_clusters__BRA__1__KET____DOT__u_cluster__DOT__accum_bank__v6;
    IData/*31:0*/ __Vdlyvval__top_level__DOT__gen_clusters__BRA__1__KET____DOT__u_cluster__DOT__accum_bank__v7;
    IData/*31:0*/ __Vdlyvval__top_level__DOT__gen_clusters__BRA__2__KET____DOT__u_cluster__DOT__accum_bank__v4;
    IData/*31:0*/ __Vdlyvval__top_level__DOT__gen_clusters__BRA__2__KET____DOT__u_cluster__DOT__accum_bank__v5;
    IData/*31:0*/ __Vdlyvval__top_level__DOT__gen_clusters__BRA__2__KET____DOT__u_cluster__DOT__accum_bank__v6;
    IData/*31:0*/ __Vdlyvval__top_level__DOT__gen_clusters__BRA__2__KET____DOT__u_cluster__DOT__accum_bank__v7;
    IData/*31:0*/ __Vdlyvval__top_level__DOT__gen_clusters__BRA__3__KET____DOT__u_cluster__DOT__accum_bank__v4;
    IData/*31:0*/ __Vdlyvval__top_level__DOT__gen_clusters__BRA__3__KET____DOT__u_cluster__DOT__accum_bank__v5;
    IData/*31:0*/ __Vdlyvval__top_level__DOT__gen_clusters__BRA__3__KET____DOT__u_cluster__DOT__accum_bank__v6;
    IData/*31:0*/ __Vdlyvval__top_level__DOT__gen_clusters__BRA__3__KET____DOT__u_cluster__DOT__accum_bank__v7;
    IData/*31:0*/ __Vdlyvval__top_level__DOT__gen_clusters__BRA__4__KET____DOT__u_cluster__DOT__accum_bank__v4;
    IData/*31:0*/ __Vdlyvval__top_level__DOT__gen_clusters__BRA__4__KET____DOT__u_cluster__DOT__accum_bank__v5;
    IData/*31:0*/ __Vdlyvval__top_level__DOT__gen_clusters__BRA__4__KET____DOT__u_cluster__DOT__accum_bank__v6;
    IData/*31:0*/ __Vdlyvval__top_level__DOT__gen_clusters__BRA__4__KET____DOT__u_cluster__DOT__accum_bank__v7;
    IData/*31:0*/ __Vdlyvval__top_level__DOT__gen_clusters__BRA__5__KET____DOT__u_cluster__DOT__accum_bank__v4;
    IData/*31:0*/ __Vdlyvval__top_level__DOT__gen_clusters__BRA__5__KET____DOT__u_cluster__DOT__accum_bank__v5;
    IData/*31:0*/ __Vdlyvval__top_level__DOT__gen_clusters__BRA__5__KET____DOT__u_cluster__DOT__accum_bank__v6;
    IData/*31:0*/ __Vdlyvval__top_level__DOT__gen_clusters__BRA__5__KET____DOT__u_cluster__DOT__accum_bank__v7;
    IData/*31:0*/ __Vdlyvval__top_level__DOT__gen_clusters__BRA__6__KET____DOT__u_cluster__DOT__accum_bank__v4;
    IData/*31:0*/ __Vdlyvval__top_level__DOT__gen_clusters__BRA__6__KET____DOT__u_cluster__DOT__accum_bank__v5;
    IData/*31:0*/ __Vdlyvval__top_level__DOT__gen_clusters__BRA__6__KET____DOT__u_cluster__DOT__accum_bank__v6;
    IData/*31:0*/ __Vdlyvval__top_level__DOT__gen_clusters__BRA__6__KET____DOT__u_cluster__DOT__accum_bank__v7;
    IData/*31:0*/ __Vdlyvval__top_level__DOT__gen_clusters__BRA__7__KET____DOT__u_cluster__DOT__accum_bank__v4;
    IData/*31:0*/ __Vdlyvval__top_level__DOT__gen_clusters__BRA__7__KET____DOT__u_cluster__DOT__accum_bank__v5;
    IData/*31:0*/ __Vdlyvval__top_level__DOT__gen_clusters__BRA__7__KET____DOT__u_cluster__DOT__accum_bank__v6;
    IData/*31:0*/ __Vdlyvval__top_level__DOT__gen_clusters__BRA__7__KET____DOT__u_cluster__DOT__accum_bank__v7;
    WData/*127:0*/ __Vtemp1[4];
    IData/*31:0*/ __Vilp;
    // Body
    __Vdlyvset__top_level__DOT__gen_clusters__BRA__7__KET____DOT__u_cluster__DOT__accum_bank__v0 = 0U;
    __Vdlyvset__top_level__DOT__gen_clusters__BRA__7__KET____DOT__u_cluster__DOT__accum_bank__v4 = 0U;
    __Vdlyvset__top_level__DOT__gen_clusters__BRA__6__KET____DOT__u_cluster__DOT__accum_bank__v0 = 0U;
    __Vdlyvset__top_level__DOT__gen_clusters__BRA__6__KET____DOT__u_cluster__DOT__accum_bank__v4 = 0U;
    __Vdlyvset__top_level__DOT__gen_clusters__BRA__5__KET____DOT__u_cluster__DOT__accum_bank__v0 = 0U;
    __Vdlyvset__top_level__DOT__gen_clusters__BRA__5__KET____DOT__u_cluster__DOT__accum_bank__v4 = 0U;
    __Vdlyvset__top_level__DOT__gen_clusters__BRA__4__KET____DOT__u_cluster__DOT__accum_bank__v0 = 0U;
    __Vdlyvset__top_level__DOT__gen_clusters__BRA__4__KET____DOT__u_cluster__DOT__accum_bank__v4 = 0U;
    __Vdlyvset__top_level__DOT__gen_clusters__BRA__3__KET____DOT__u_cluster__DOT__accum_bank__v0 = 0U;
    __Vdlyvset__top_level__DOT__gen_clusters__BRA__3__KET____DOT__u_cluster__DOT__accum_bank__v4 = 0U;
    __Vdlyvset__top_level__DOT__gen_clusters__BRA__2__KET____DOT__u_cluster__DOT__accum_bank__v0 = 0U;
    __Vdlyvset__top_level__DOT__gen_clusters__BRA__2__KET____DOT__u_cluster__DOT__accum_bank__v4 = 0U;
    __Vdlyvset__top_level__DOT__gen_clusters__BRA__1__KET____DOT__u_cluster__DOT__accum_bank__v0 = 0U;
    __Vdlyvset__top_level__DOT__gen_clusters__BRA__1__KET____DOT__u_cluster__DOT__accum_bank__v4 = 0U;
    __Vdlyvset__top_level__DOT__gen_clusters__BRA__0__KET____DOT__u_cluster__DOT__accum_bank__v0 = 0U;
    __Vdlyvset__top_level__DOT__gen_clusters__BRA__0__KET____DOT__u_cluster__DOT__accum_bank__v4 = 0U;
    __Vdlyvset__top_level__DOT__output_mem__v0 = 0U;
    __Vdlyvset__top_level__DOT__output_mem__v64 = 0U;
    __Vdlyvset__top_level__DOT__output_mem__v65 = 0U;
    __Vdlyvset__top_level__DOT__output_mem__v66 = 0U;
    __Vdlyvset__top_level__DOT__output_mem__v67 = 0U;
    __Vdlyvset__top_level__DOT__output_mem__v68 = 0U;
    __Vdlyvset__top_level__DOT__output_mem__v69 = 0U;
    __Vdlyvset__top_level__DOT__output_mem__v70 = 0U;
    __Vdlyvset__top_level__DOT__output_mem__v71 = 0U;
    __Vdlyvset__top_level__DOT__output_mem__v72 = 0U;
    __Vdlyvset__top_level__DOT__output_mem__v73 = 0U;
    __Vdlyvset__top_level__DOT__output_mem__v74 = 0U;
    __Vdlyvset__top_level__DOT__output_mem__v75 = 0U;
    __Vdlyvset__top_level__DOT__output_mem__v76 = 0U;
    __Vdlyvset__top_level__DOT__output_mem__v77 = 0U;
    __Vdlyvset__top_level__DOT__output_mem__v78 = 0U;
    __Vdlyvset__top_level__DOT__output_mem__v79 = 0U;
    __Vdlyvset__top_level__DOT__output_mem__v80 = 0U;
    __Vdlyvset__top_level__DOT__output_mem__v81 = 0U;
    __Vdlyvset__top_level__DOT__output_mem__v82 = 0U;
    __Vdlyvset__top_level__DOT__output_mem__v83 = 0U;
    __Vdlyvset__top_level__DOT__output_mem__v84 = 0U;
    __Vdlyvset__top_level__DOT__output_mem__v85 = 0U;
    __Vdlyvset__top_level__DOT__output_mem__v86 = 0U;
    __Vdlyvset__top_level__DOT__output_mem__v87 = 0U;
    __Vdlyvset__top_level__DOT__output_mem__v88 = 0U;
    __Vdlyvset__top_level__DOT__output_mem__v89 = 0U;
    __Vdlyvset__top_level__DOT__output_mem__v90 = 0U;
    __Vdlyvset__top_level__DOT__output_mem__v91 = 0U;
    __Vdlyvset__top_level__DOT__output_mem__v92 = 0U;
    __Vdlyvset__top_level__DOT__output_mem__v93 = 0U;
    __Vdlyvset__top_level__DOT__output_mem__v94 = 0U;
    __Vdlyvset__top_level__DOT__output_mem__v95 = 0U;
    if (VL_UNLIKELY(((~ (IData)(vlTOPp->rst)) & (IData)(vlTOPp->done)))) {
        __Vtemp1[0U] = 0x2e6d656dU;
        __Vtemp1[1U] = 0x74707574U;
        __Vtemp1[2U] = 0x6d5f6f75U;
        __Vtemp1[3U] = 0x7369U;
        VL_WRITEMEM_N(true, 32, 64, 0, VL_CVT_PACK_STR_NW(4, __Vtemp1)
                      , vlTOPp->top_level__DOT__output_mem
                      , 0, ~0ULL);
    }
    if (vlTOPp->rst) {
        vlTOPp->top_level__DOT__cycle_count = 0U;
        vlTOPp->top_level__DOT__u_control__DOT__drain_iter_q = 0U;
    } else {
        vlTOPp->top_level__DOT__cycle_count = vlTOPp->top_level__DOT__u_control__DOT__cycle_count_d;
        vlTOPp->top_level__DOT__u_control__DOT__drain_iter_q 
            = vlTOPp->top_level__DOT__u_control__DOT__drain_iter_d;
    }
    if (((IData)(vlTOPp->rst) | (IData)(vlTOPp->top_level__DOT__clear_acc))) {
        __Vdlyvset__top_level__DOT__gen_clusters__BRA__7__KET____DOT__u_cluster__DOT__accum_bank__v0 = 1U;
    } else {
        __Vdlyvval__top_level__DOT__gen_clusters__BRA__7__KET____DOT__u_cluster__DOT__accum_bank__v4 
            = vlTOPp->top_level__DOT__gen_clusters__BRA__7__KET____DOT__u_cluster__DOT__accum_next
            [0U];
        __Vdlyvset__top_level__DOT__gen_clusters__BRA__7__KET____DOT__u_cluster__DOT__accum_bank__v4 = 1U;
        __Vdlyvval__top_level__DOT__gen_clusters__BRA__7__KET____DOT__u_cluster__DOT__accum_bank__v5 
            = vlTOPp->top_level__DOT__gen_clusters__BRA__7__KET____DOT__u_cluster__DOT__accum_next
            [1U];
        __Vdlyvval__top_level__DOT__gen_clusters__BRA__7__KET____DOT__u_cluster__DOT__accum_bank__v6 
            = vlTOPp->top_level__DOT__gen_clusters__BRA__7__KET____DOT__u_cluster__DOT__accum_next
            [2U];
        __Vdlyvval__top_level__DOT__gen_clusters__BRA__7__KET____DOT__u_cluster__DOT__accum_bank__v7 
            = vlTOPp->top_level__DOT__gen_clusters__BRA__7__KET____DOT__u_cluster__DOT__accum_next
            [3U];
    }
    if (((IData)(vlTOPp->rst) | (IData)(vlTOPp->top_level__DOT__clear_acc))) {
        __Vdlyvset__top_level__DOT__gen_clusters__BRA__6__KET____DOT__u_cluster__DOT__accum_bank__v0 = 1U;
    } else {
        __Vdlyvval__top_level__DOT__gen_clusters__BRA__6__KET____DOT__u_cluster__DOT__accum_bank__v4 
            = vlTOPp->top_level__DOT__gen_clusters__BRA__6__KET____DOT__u_cluster__DOT__accum_next
            [0U];
        __Vdlyvset__top_level__DOT__gen_clusters__BRA__6__KET____DOT__u_cluster__DOT__accum_bank__v4 = 1U;
        __Vdlyvval__top_level__DOT__gen_clusters__BRA__6__KET____DOT__u_cluster__DOT__accum_bank__v5 
            = vlTOPp->top_level__DOT__gen_clusters__BRA__6__KET____DOT__u_cluster__DOT__accum_next
            [1U];
        __Vdlyvval__top_level__DOT__gen_clusters__BRA__6__KET____DOT__u_cluster__DOT__accum_bank__v6 
            = vlTOPp->top_level__DOT__gen_clusters__BRA__6__KET____DOT__u_cluster__DOT__accum_next
            [2U];
        __Vdlyvval__top_level__DOT__gen_clusters__BRA__6__KET____DOT__u_cluster__DOT__accum_bank__v7 
            = vlTOPp->top_level__DOT__gen_clusters__BRA__6__KET____DOT__u_cluster__DOT__accum_next
            [3U];
    }
    if (((IData)(vlTOPp->rst) | (IData)(vlTOPp->top_level__DOT__clear_acc))) {
        __Vdlyvset__top_level__DOT__gen_clusters__BRA__5__KET____DOT__u_cluster__DOT__accum_bank__v0 = 1U;
    } else {
        __Vdlyvval__top_level__DOT__gen_clusters__BRA__5__KET____DOT__u_cluster__DOT__accum_bank__v4 
            = vlTOPp->top_level__DOT__gen_clusters__BRA__5__KET____DOT__u_cluster__DOT__accum_next
            [0U];
        __Vdlyvset__top_level__DOT__gen_clusters__BRA__5__KET____DOT__u_cluster__DOT__accum_bank__v4 = 1U;
        __Vdlyvval__top_level__DOT__gen_clusters__BRA__5__KET____DOT__u_cluster__DOT__accum_bank__v5 
            = vlTOPp->top_level__DOT__gen_clusters__BRA__5__KET____DOT__u_cluster__DOT__accum_next
            [1U];
        __Vdlyvval__top_level__DOT__gen_clusters__BRA__5__KET____DOT__u_cluster__DOT__accum_bank__v6 
            = vlTOPp->top_level__DOT__gen_clusters__BRA__5__KET____DOT__u_cluster__DOT__accum_next
            [2U];
        __Vdlyvval__top_level__DOT__gen_clusters__BRA__5__KET____DOT__u_cluster__DOT__accum_bank__v7 
            = vlTOPp->top_level__DOT__gen_clusters__BRA__5__KET____DOT__u_cluster__DOT__accum_next
            [3U];
    }
    if (((IData)(vlTOPp->rst) | (IData)(vlTOPp->top_level__DOT__clear_acc))) {
        __Vdlyvset__top_level__DOT__gen_clusters__BRA__4__KET____DOT__u_cluster__DOT__accum_bank__v0 = 1U;
    } else {
        __Vdlyvval__top_level__DOT__gen_clusters__BRA__4__KET____DOT__u_cluster__DOT__accum_bank__v4 
            = vlTOPp->top_level__DOT__gen_clusters__BRA__4__KET____DOT__u_cluster__DOT__accum_next
            [0U];
        __Vdlyvset__top_level__DOT__gen_clusters__BRA__4__KET____DOT__u_cluster__DOT__accum_bank__v4 = 1U;
        __Vdlyvval__top_level__DOT__gen_clusters__BRA__4__KET____DOT__u_cluster__DOT__accum_bank__v5 
            = vlTOPp->top_level__DOT__gen_clusters__BRA__4__KET____DOT__u_cluster__DOT__accum_next
            [1U];
        __Vdlyvval__top_level__DOT__gen_clusters__BRA__4__KET____DOT__u_cluster__DOT__accum_bank__v6 
            = vlTOPp->top_level__DOT__gen_clusters__BRA__4__KET____DOT__u_cluster__DOT__accum_next
            [2U];
        __Vdlyvval__top_level__DOT__gen_clusters__BRA__4__KET____DOT__u_cluster__DOT__accum_bank__v7 
            = vlTOPp->top_level__DOT__gen_clusters__BRA__4__KET____DOT__u_cluster__DOT__accum_next
            [3U];
    }
    if (((IData)(vlTOPp->rst) | (IData)(vlTOPp->top_level__DOT__clear_acc))) {
        __Vdlyvset__top_level__DOT__gen_clusters__BRA__3__KET____DOT__u_cluster__DOT__accum_bank__v0 = 1U;
    } else {
        __Vdlyvval__top_level__DOT__gen_clusters__BRA__3__KET____DOT__u_cluster__DOT__accum_bank__v4 
            = vlTOPp->top_level__DOT__gen_clusters__BRA__3__KET____DOT__u_cluster__DOT__accum_next
            [0U];
        __Vdlyvset__top_level__DOT__gen_clusters__BRA__3__KET____DOT__u_cluster__DOT__accum_bank__v4 = 1U;
        __Vdlyvval__top_level__DOT__gen_clusters__BRA__3__KET____DOT__u_cluster__DOT__accum_bank__v5 
            = vlTOPp->top_level__DOT__gen_clusters__BRA__3__KET____DOT__u_cluster__DOT__accum_next
            [1U];
        __Vdlyvval__top_level__DOT__gen_clusters__BRA__3__KET____DOT__u_cluster__DOT__accum_bank__v6 
            = vlTOPp->top_level__DOT__gen_clusters__BRA__3__KET____DOT__u_cluster__DOT__accum_next
            [2U];
        __Vdlyvval__top_level__DOT__gen_clusters__BRA__3__KET____DOT__u_cluster__DOT__accum_bank__v7 
            = vlTOPp->top_level__DOT__gen_clusters__BRA__3__KET____DOT__u_cluster__DOT__accum_next
            [3U];
    }
    if (((IData)(vlTOPp->rst) | (IData)(vlTOPp->top_level__DOT__clear_acc))) {
        __Vdlyvset__top_level__DOT__gen_clusters__BRA__2__KET____DOT__u_cluster__DOT__accum_bank__v0 = 1U;
    } else {
        __Vdlyvval__top_level__DOT__gen_clusters__BRA__2__KET____DOT__u_cluster__DOT__accum_bank__v4 
            = vlTOPp->top_level__DOT__gen_clusters__BRA__2__KET____DOT__u_cluster__DOT__accum_next
            [0U];
        __Vdlyvset__top_level__DOT__gen_clusters__BRA__2__KET____DOT__u_cluster__DOT__accum_bank__v4 = 1U;
        __Vdlyvval__top_level__DOT__gen_clusters__BRA__2__KET____DOT__u_cluster__DOT__accum_bank__v5 
            = vlTOPp->top_level__DOT__gen_clusters__BRA__2__KET____DOT__u_cluster__DOT__accum_next
            [1U];
        __Vdlyvval__top_level__DOT__gen_clusters__BRA__2__KET____DOT__u_cluster__DOT__accum_bank__v6 
            = vlTOPp->top_level__DOT__gen_clusters__BRA__2__KET____DOT__u_cluster__DOT__accum_next
            [2U];
        __Vdlyvval__top_level__DOT__gen_clusters__BRA__2__KET____DOT__u_cluster__DOT__accum_bank__v7 
            = vlTOPp->top_level__DOT__gen_clusters__BRA__2__KET____DOT__u_cluster__DOT__accum_next
            [3U];
    }
    if (((IData)(vlTOPp->rst) | (IData)(vlTOPp->top_level__DOT__clear_acc))) {
        __Vdlyvset__top_level__DOT__gen_clusters__BRA__1__KET____DOT__u_cluster__DOT__accum_bank__v0 = 1U;
    } else {
        __Vdlyvval__top_level__DOT__gen_clusters__BRA__1__KET____DOT__u_cluster__DOT__accum_bank__v4 
            = vlTOPp->top_level__DOT__gen_clusters__BRA__1__KET____DOT__u_cluster__DOT__accum_next
            [0U];
        __Vdlyvset__top_level__DOT__gen_clusters__BRA__1__KET____DOT__u_cluster__DOT__accum_bank__v4 = 1U;
        __Vdlyvval__top_level__DOT__gen_clusters__BRA__1__KET____DOT__u_cluster__DOT__accum_bank__v5 
            = vlTOPp->top_level__DOT__gen_clusters__BRA__1__KET____DOT__u_cluster__DOT__accum_next
            [1U];
        __Vdlyvval__top_level__DOT__gen_clusters__BRA__1__KET____DOT__u_cluster__DOT__accum_bank__v6 
            = vlTOPp->top_level__DOT__gen_clusters__BRA__1__KET____DOT__u_cluster__DOT__accum_next
            [2U];
        __Vdlyvval__top_level__DOT__gen_clusters__BRA__1__KET____DOT__u_cluster__DOT__accum_bank__v7 
            = vlTOPp->top_level__DOT__gen_clusters__BRA__1__KET____DOT__u_cluster__DOT__accum_next
            [3U];
    }
    if (((IData)(vlTOPp->rst) | (IData)(vlTOPp->top_level__DOT__clear_acc))) {
        __Vdlyvset__top_level__DOT__gen_clusters__BRA__0__KET____DOT__u_cluster__DOT__accum_bank__v0 = 1U;
    } else {
        __Vdlyvval__top_level__DOT__gen_clusters__BRA__0__KET____DOT__u_cluster__DOT__accum_bank__v4 
            = vlTOPp->top_level__DOT__gen_clusters__BRA__0__KET____DOT__u_cluster__DOT__accum_next
            [0U];
        __Vdlyvset__top_level__DOT__gen_clusters__BRA__0__KET____DOT__u_cluster__DOT__accum_bank__v4 = 1U;
        __Vdlyvval__top_level__DOT__gen_clusters__BRA__0__KET____DOT__u_cluster__DOT__accum_bank__v5 
            = vlTOPp->top_level__DOT__gen_clusters__BRA__0__KET____DOT__u_cluster__DOT__accum_next
            [1U];
        __Vdlyvval__top_level__DOT__gen_clusters__BRA__0__KET____DOT__u_cluster__DOT__accum_bank__v6 
            = vlTOPp->top_level__DOT__gen_clusters__BRA__0__KET____DOT__u_cluster__DOT__accum_next
            [2U];
        __Vdlyvval__top_level__DOT__gen_clusters__BRA__0__KET____DOT__u_cluster__DOT__accum_bank__v7 
            = vlTOPp->top_level__DOT__gen_clusters__BRA__0__KET____DOT__u_cluster__DOT__accum_next
            [3U];
    }
    if (vlTOPp->rst) {
        __Vdlyvset__top_level__DOT__output_mem__v0 = 1U;
    } else {
        if (vlTOPp->top_level__DOT__write_en) {
            __Vdlyvval__top_level__DOT__output_mem__v64 
                = vlTOPp->top_level__DOT__cluster_accum
                [0U][0U];
            __Vdlyvset__top_level__DOT__output_mem__v64 = 1U;
            __Vdlyvdim0__top_level__DOT__output_mem__v64 = 0U;
            __Vdlyvval__top_level__DOT__output_mem__v65 
                = vlTOPp->top_level__DOT__cluster_accum
                [0U][1U];
            __Vdlyvset__top_level__DOT__output_mem__v65 = 1U;
            __Vdlyvdim0__top_level__DOT__output_mem__v65 = 1U;
            __Vdlyvval__top_level__DOT__output_mem__v66 
                = vlTOPp->top_level__DOT__cluster_accum
                [0U][2U];
            __Vdlyvset__top_level__DOT__output_mem__v66 = 1U;
            __Vdlyvdim0__top_level__DOT__output_mem__v66 = 2U;
            __Vdlyvval__top_level__DOT__output_mem__v67 
                = vlTOPp->top_level__DOT__cluster_accum
                [0U][3U];
            __Vdlyvset__top_level__DOT__output_mem__v67 = 1U;
            __Vdlyvdim0__top_level__DOT__output_mem__v67 = 3U;
            __Vdlyvval__top_level__DOT__output_mem__v68 
                = vlTOPp->top_level__DOT__cluster_accum
                [1U][0U];
            __Vdlyvset__top_level__DOT__output_mem__v68 = 1U;
            __Vdlyvdim0__top_level__DOT__output_mem__v68 = 4U;
            __Vdlyvval__top_level__DOT__output_mem__v69 
                = vlTOPp->top_level__DOT__cluster_accum
                [1U][1U];
            __Vdlyvset__top_level__DOT__output_mem__v69 = 1U;
            __Vdlyvdim0__top_level__DOT__output_mem__v69 = 5U;
            __Vdlyvval__top_level__DOT__output_mem__v70 
                = vlTOPp->top_level__DOT__cluster_accum
                [1U][2U];
            __Vdlyvset__top_level__DOT__output_mem__v70 = 1U;
            __Vdlyvdim0__top_level__DOT__output_mem__v70 = 6U;
            __Vdlyvval__top_level__DOT__output_mem__v71 
                = vlTOPp->top_level__DOT__cluster_accum
                [1U][3U];
            __Vdlyvset__top_level__DOT__output_mem__v71 = 1U;
            __Vdlyvdim0__top_level__DOT__output_mem__v71 = 7U;
            __Vdlyvval__top_level__DOT__output_mem__v72 
                = vlTOPp->top_level__DOT__cluster_accum
                [2U][0U];
            __Vdlyvset__top_level__DOT__output_mem__v72 = 1U;
            __Vdlyvdim0__top_level__DOT__output_mem__v72 = 8U;
            __Vdlyvval__top_level__DOT__output_mem__v73 
                = vlTOPp->top_level__DOT__cluster_accum
                [2U][1U];
            __Vdlyvset__top_level__DOT__output_mem__v73 = 1U;
            __Vdlyvdim0__top_level__DOT__output_mem__v73 = 9U;
            __Vdlyvval__top_level__DOT__output_mem__v74 
                = vlTOPp->top_level__DOT__cluster_accum
                [2U][2U];
            __Vdlyvset__top_level__DOT__output_mem__v74 = 1U;
            __Vdlyvdim0__top_level__DOT__output_mem__v74 = 0xaU;
            __Vdlyvval__top_level__DOT__output_mem__v75 
                = vlTOPp->top_level__DOT__cluster_accum
                [2U][3U];
            __Vdlyvset__top_level__DOT__output_mem__v75 = 1U;
            __Vdlyvdim0__top_level__DOT__output_mem__v75 = 0xbU;
            __Vdlyvval__top_level__DOT__output_mem__v76 
                = vlTOPp->top_level__DOT__cluster_accum
                [3U][0U];
            __Vdlyvset__top_level__DOT__output_mem__v76 = 1U;
            __Vdlyvdim0__top_level__DOT__output_mem__v76 = 0xcU;
            __Vdlyvval__top_level__DOT__output_mem__v77 
                = vlTOPp->top_level__DOT__cluster_accum
                [3U][1U];
            __Vdlyvset__top_level__DOT__output_mem__v77 = 1U;
            __Vdlyvdim0__top_level__DOT__output_mem__v77 = 0xdU;
            __Vdlyvval__top_level__DOT__output_mem__v78 
                = vlTOPp->top_level__DOT__cluster_accum
                [3U][2U];
            __Vdlyvset__top_level__DOT__output_mem__v78 = 1U;
            __Vdlyvdim0__top_level__DOT__output_mem__v78 = 0xeU;
            __Vdlyvval__top_level__DOT__output_mem__v79 
                = vlTOPp->top_level__DOT__cluster_accum
                [3U][3U];
            __Vdlyvset__top_level__DOT__output_mem__v79 = 1U;
            __Vdlyvdim0__top_level__DOT__output_mem__v79 = 0xfU;
            __Vdlyvval__top_level__DOT__output_mem__v80 
                = vlTOPp->top_level__DOT__cluster_accum
                [4U][0U];
            __Vdlyvset__top_level__DOT__output_mem__v80 = 1U;
            __Vdlyvdim0__top_level__DOT__output_mem__v80 = 0x10U;
            __Vdlyvval__top_level__DOT__output_mem__v81 
                = vlTOPp->top_level__DOT__cluster_accum
                [4U][1U];
            __Vdlyvset__top_level__DOT__output_mem__v81 = 1U;
            __Vdlyvdim0__top_level__DOT__output_mem__v81 = 0x11U;
            __Vdlyvval__top_level__DOT__output_mem__v82 
                = vlTOPp->top_level__DOT__cluster_accum
                [4U][2U];
            __Vdlyvset__top_level__DOT__output_mem__v82 = 1U;
            __Vdlyvdim0__top_level__DOT__output_mem__v82 = 0x12U;
            __Vdlyvval__top_level__DOT__output_mem__v83 
                = vlTOPp->top_level__DOT__cluster_accum
                [4U][3U];
            __Vdlyvset__top_level__DOT__output_mem__v83 = 1U;
            __Vdlyvdim0__top_level__DOT__output_mem__v83 = 0x13U;
            __Vdlyvval__top_level__DOT__output_mem__v84 
                = vlTOPp->top_level__DOT__cluster_accum
                [5U][0U];
            __Vdlyvset__top_level__DOT__output_mem__v84 = 1U;
            __Vdlyvdim0__top_level__DOT__output_mem__v84 = 0x14U;
            __Vdlyvval__top_level__DOT__output_mem__v85 
                = vlTOPp->top_level__DOT__cluster_accum
                [5U][1U];
            __Vdlyvset__top_level__DOT__output_mem__v85 = 1U;
            __Vdlyvdim0__top_level__DOT__output_mem__v85 = 0x15U;
            __Vdlyvval__top_level__DOT__output_mem__v86 
                = vlTOPp->top_level__DOT__cluster_accum
                [5U][2U];
            __Vdlyvset__top_level__DOT__output_mem__v86 = 1U;
            __Vdlyvdim0__top_level__DOT__output_mem__v86 = 0x16U;
            __Vdlyvval__top_level__DOT__output_mem__v87 
                = vlTOPp->top_level__DOT__cluster_accum
                [5U][3U];
            __Vdlyvset__top_level__DOT__output_mem__v87 = 1U;
            __Vdlyvdim0__top_level__DOT__output_mem__v87 = 0x17U;
            __Vdlyvval__top_level__DOT__output_mem__v88 
                = vlTOPp->top_level__DOT__cluster_accum
                [6U][0U];
            __Vdlyvset__top_level__DOT__output_mem__v88 = 1U;
            __Vdlyvdim0__top_level__DOT__output_mem__v88 = 0x18U;
            __Vdlyvval__top_level__DOT__output_mem__v89 
                = vlTOPp->top_level__DOT__cluster_accum
                [6U][1U];
            __Vdlyvset__top_level__DOT__output_mem__v89 = 1U;
            __Vdlyvdim0__top_level__DOT__output_mem__v89 = 0x19U;
            __Vdlyvval__top_level__DOT__output_mem__v90 
                = vlTOPp->top_level__DOT__cluster_accum
                [6U][2U];
            __Vdlyvset__top_level__DOT__output_mem__v90 = 1U;
            __Vdlyvdim0__top_level__DOT__output_mem__v90 = 0x1aU;
            __Vdlyvval__top_level__DOT__output_mem__v91 
                = vlTOPp->top_level__DOT__cluster_accum
                [6U][3U];
            __Vdlyvset__top_level__DOT__output_mem__v91 = 1U;
            __Vdlyvdim0__top_level__DOT__output_mem__v91 = 0x1bU;
            __Vdlyvval__top_level__DOT__output_mem__v92 
                = vlTOPp->top_level__DOT__cluster_accum
                [7U][0U];
            __Vdlyvset__top_level__DOT__output_mem__v92 = 1U;
            __Vdlyvdim0__top_level__DOT__output_mem__v92 = 0x1cU;
            __Vdlyvval__top_level__DOT__output_mem__v93 
                = vlTOPp->top_level__DOT__cluster_accum
                [7U][1U];
            __Vdlyvset__top_level__DOT__output_mem__v93 = 1U;
            __Vdlyvdim0__top_level__DOT__output_mem__v93 = 0x1dU;
            __Vdlyvval__top_level__DOT__output_mem__v94 
                = vlTOPp->top_level__DOT__cluster_accum
                [7U][2U];
            __Vdlyvset__top_level__DOT__output_mem__v94 = 1U;
            __Vdlyvdim0__top_level__DOT__output_mem__v94 = 0x1eU;
            __Vdlyvval__top_level__DOT__output_mem__v95 
                = vlTOPp->top_level__DOT__cluster_accum
                [7U][3U];
            __Vdlyvset__top_level__DOT__output_mem__v95 = 1U;
            __Vdlyvdim0__top_level__DOT__output_mem__v95 = 0x1fU;
        }
    }
    if (vlTOPp->rst) {
        vlTOPp->top_level__DOT__u_control__DOT__compute_iter_q = 0U;
        vlTOPp->top_level__DOT__u_control__DOT__state_q = 0U;
    } else {
        vlTOPp->top_level__DOT__u_control__DOT__compute_iter_q 
            = vlTOPp->top_level__DOT__u_control__DOT__compute_iter_d;
        vlTOPp->top_level__DOT__u_control__DOT__state_q 
            = vlTOPp->top_level__DOT__u_control__DOT__state_d;
    }
    if (__Vdlyvset__top_level__DOT__gen_clusters__BRA__7__KET____DOT__u_cluster__DOT__accum_bank__v0) {
        vlTOPp->top_level__DOT__gen_clusters__BRA__7__KET____DOT__u_cluster__DOT__accum_bank[0U] = 0U;
        vlTOPp->top_level__DOT__gen_clusters__BRA__7__KET____DOT__u_cluster__DOT__accum_bank[1U] = 0U;
        vlTOPp->top_level__DOT__gen_clusters__BRA__7__KET____DOT__u_cluster__DOT__accum_bank[2U] = 0U;
        vlTOPp->top_level__DOT__gen_clusters__BRA__7__KET____DOT__u_cluster__DOT__accum_bank[3U] = 0U;
    }
    if (__Vdlyvset__top_level__DOT__gen_clusters__BRA__7__KET____DOT__u_cluster__DOT__accum_bank__v4) {
        vlTOPp->top_level__DOT__gen_clusters__BRA__7__KET____DOT__u_cluster__DOT__accum_bank[0U] 
            = __Vdlyvval__top_level__DOT__gen_clusters__BRA__7__KET____DOT__u_cluster__DOT__accum_bank__v4;
        vlTOPp->top_level__DOT__gen_clusters__BRA__7__KET____DOT__u_cluster__DOT__accum_bank[1U] 
            = __Vdlyvval__top_level__DOT__gen_clusters__BRA__7__KET____DOT__u_cluster__DOT__accum_bank__v5;
        vlTOPp->top_level__DOT__gen_clusters__BRA__7__KET____DOT__u_cluster__DOT__accum_bank[2U] 
            = __Vdlyvval__top_level__DOT__gen_clusters__BRA__7__KET____DOT__u_cluster__DOT__accum_bank__v6;
        vlTOPp->top_level__DOT__gen_clusters__BRA__7__KET____DOT__u_cluster__DOT__accum_bank[3U] 
            = __Vdlyvval__top_level__DOT__gen_clusters__BRA__7__KET____DOT__u_cluster__DOT__accum_bank__v7;
    }
    if (__Vdlyvset__top_level__DOT__gen_clusters__BRA__6__KET____DOT__u_cluster__DOT__accum_bank__v0) {
        vlTOPp->top_level__DOT__gen_clusters__BRA__6__KET____DOT__u_cluster__DOT__accum_bank[0U] = 0U;
        vlTOPp->top_level__DOT__gen_clusters__BRA__6__KET____DOT__u_cluster__DOT__accum_bank[1U] = 0U;
        vlTOPp->top_level__DOT__gen_clusters__BRA__6__KET____DOT__u_cluster__DOT__accum_bank[2U] = 0U;
        vlTOPp->top_level__DOT__gen_clusters__BRA__6__KET____DOT__u_cluster__DOT__accum_bank[3U] = 0U;
    }
    if (__Vdlyvset__top_level__DOT__gen_clusters__BRA__6__KET____DOT__u_cluster__DOT__accum_bank__v4) {
        vlTOPp->top_level__DOT__gen_clusters__BRA__6__KET____DOT__u_cluster__DOT__accum_bank[0U] 
            = __Vdlyvval__top_level__DOT__gen_clusters__BRA__6__KET____DOT__u_cluster__DOT__accum_bank__v4;
        vlTOPp->top_level__DOT__gen_clusters__BRA__6__KET____DOT__u_cluster__DOT__accum_bank[1U] 
            = __Vdlyvval__top_level__DOT__gen_clusters__BRA__6__KET____DOT__u_cluster__DOT__accum_bank__v5;
        vlTOPp->top_level__DOT__gen_clusters__BRA__6__KET____DOT__u_cluster__DOT__accum_bank[2U] 
            = __Vdlyvval__top_level__DOT__gen_clusters__BRA__6__KET____DOT__u_cluster__DOT__accum_bank__v6;
        vlTOPp->top_level__DOT__gen_clusters__BRA__6__KET____DOT__u_cluster__DOT__accum_bank[3U] 
            = __Vdlyvval__top_level__DOT__gen_clusters__BRA__6__KET____DOT__u_cluster__DOT__accum_bank__v7;
    }
    if (__Vdlyvset__top_level__DOT__gen_clusters__BRA__5__KET____DOT__u_cluster__DOT__accum_bank__v0) {
        vlTOPp->top_level__DOT__gen_clusters__BRA__5__KET____DOT__u_cluster__DOT__accum_bank[0U] = 0U;
        vlTOPp->top_level__DOT__gen_clusters__BRA__5__KET____DOT__u_cluster__DOT__accum_bank[1U] = 0U;
        vlTOPp->top_level__DOT__gen_clusters__BRA__5__KET____DOT__u_cluster__DOT__accum_bank[2U] = 0U;
        vlTOPp->top_level__DOT__gen_clusters__BRA__5__KET____DOT__u_cluster__DOT__accum_bank[3U] = 0U;
    }
    if (__Vdlyvset__top_level__DOT__gen_clusters__BRA__5__KET____DOT__u_cluster__DOT__accum_bank__v4) {
        vlTOPp->top_level__DOT__gen_clusters__BRA__5__KET____DOT__u_cluster__DOT__accum_bank[0U] 
            = __Vdlyvval__top_level__DOT__gen_clusters__BRA__5__KET____DOT__u_cluster__DOT__accum_bank__v4;
        vlTOPp->top_level__DOT__gen_clusters__BRA__5__KET____DOT__u_cluster__DOT__accum_bank[1U] 
            = __Vdlyvval__top_level__DOT__gen_clusters__BRA__5__KET____DOT__u_cluster__DOT__accum_bank__v5;
        vlTOPp->top_level__DOT__gen_clusters__BRA__5__KET____DOT__u_cluster__DOT__accum_bank[2U] 
            = __Vdlyvval__top_level__DOT__gen_clusters__BRA__5__KET____DOT__u_cluster__DOT__accum_bank__v6;
        vlTOPp->top_level__DOT__gen_clusters__BRA__5__KET____DOT__u_cluster__DOT__accum_bank[3U] 
            = __Vdlyvval__top_level__DOT__gen_clusters__BRA__5__KET____DOT__u_cluster__DOT__accum_bank__v7;
    }
    if (__Vdlyvset__top_level__DOT__gen_clusters__BRA__4__KET____DOT__u_cluster__DOT__accum_bank__v0) {
        vlTOPp->top_level__DOT__gen_clusters__BRA__4__KET____DOT__u_cluster__DOT__accum_bank[0U] = 0U;
        vlTOPp->top_level__DOT__gen_clusters__BRA__4__KET____DOT__u_cluster__DOT__accum_bank[1U] = 0U;
        vlTOPp->top_level__DOT__gen_clusters__BRA__4__KET____DOT__u_cluster__DOT__accum_bank[2U] = 0U;
        vlTOPp->top_level__DOT__gen_clusters__BRA__4__KET____DOT__u_cluster__DOT__accum_bank[3U] = 0U;
    }
    if (__Vdlyvset__top_level__DOT__gen_clusters__BRA__4__KET____DOT__u_cluster__DOT__accum_bank__v4) {
        vlTOPp->top_level__DOT__gen_clusters__BRA__4__KET____DOT__u_cluster__DOT__accum_bank[0U] 
            = __Vdlyvval__top_level__DOT__gen_clusters__BRA__4__KET____DOT__u_cluster__DOT__accum_bank__v4;
        vlTOPp->top_level__DOT__gen_clusters__BRA__4__KET____DOT__u_cluster__DOT__accum_bank[1U] 
            = __Vdlyvval__top_level__DOT__gen_clusters__BRA__4__KET____DOT__u_cluster__DOT__accum_bank__v5;
        vlTOPp->top_level__DOT__gen_clusters__BRA__4__KET____DOT__u_cluster__DOT__accum_bank[2U] 
            = __Vdlyvval__top_level__DOT__gen_clusters__BRA__4__KET____DOT__u_cluster__DOT__accum_bank__v6;
        vlTOPp->top_level__DOT__gen_clusters__BRA__4__KET____DOT__u_cluster__DOT__accum_bank[3U] 
            = __Vdlyvval__top_level__DOT__gen_clusters__BRA__4__KET____DOT__u_cluster__DOT__accum_bank__v7;
    }
    if (__Vdlyvset__top_level__DOT__gen_clusters__BRA__3__KET____DOT__u_cluster__DOT__accum_bank__v0) {
        vlTOPp->top_level__DOT__gen_clusters__BRA__3__KET____DOT__u_cluster__DOT__accum_bank[0U] = 0U;
        vlTOPp->top_level__DOT__gen_clusters__BRA__3__KET____DOT__u_cluster__DOT__accum_bank[1U] = 0U;
        vlTOPp->top_level__DOT__gen_clusters__BRA__3__KET____DOT__u_cluster__DOT__accum_bank[2U] = 0U;
        vlTOPp->top_level__DOT__gen_clusters__BRA__3__KET____DOT__u_cluster__DOT__accum_bank[3U] = 0U;
    }
    if (__Vdlyvset__top_level__DOT__gen_clusters__BRA__3__KET____DOT__u_cluster__DOT__accum_bank__v4) {
        vlTOPp->top_level__DOT__gen_clusters__BRA__3__KET____DOT__u_cluster__DOT__accum_bank[0U] 
            = __Vdlyvval__top_level__DOT__gen_clusters__BRA__3__KET____DOT__u_cluster__DOT__accum_bank__v4;
        vlTOPp->top_level__DOT__gen_clusters__BRA__3__KET____DOT__u_cluster__DOT__accum_bank[1U] 
            = __Vdlyvval__top_level__DOT__gen_clusters__BRA__3__KET____DOT__u_cluster__DOT__accum_bank__v5;
        vlTOPp->top_level__DOT__gen_clusters__BRA__3__KET____DOT__u_cluster__DOT__accum_bank[2U] 
            = __Vdlyvval__top_level__DOT__gen_clusters__BRA__3__KET____DOT__u_cluster__DOT__accum_bank__v6;
        vlTOPp->top_level__DOT__gen_clusters__BRA__3__KET____DOT__u_cluster__DOT__accum_bank[3U] 
            = __Vdlyvval__top_level__DOT__gen_clusters__BRA__3__KET____DOT__u_cluster__DOT__accum_bank__v7;
    }
    if (__Vdlyvset__top_level__DOT__gen_clusters__BRA__2__KET____DOT__u_cluster__DOT__accum_bank__v0) {
        vlTOPp->top_level__DOT__gen_clusters__BRA__2__KET____DOT__u_cluster__DOT__accum_bank[0U] = 0U;
        vlTOPp->top_level__DOT__gen_clusters__BRA__2__KET____DOT__u_cluster__DOT__accum_bank[1U] = 0U;
        vlTOPp->top_level__DOT__gen_clusters__BRA__2__KET____DOT__u_cluster__DOT__accum_bank[2U] = 0U;
        vlTOPp->top_level__DOT__gen_clusters__BRA__2__KET____DOT__u_cluster__DOT__accum_bank[3U] = 0U;
    }
    if (__Vdlyvset__top_level__DOT__gen_clusters__BRA__2__KET____DOT__u_cluster__DOT__accum_bank__v4) {
        vlTOPp->top_level__DOT__gen_clusters__BRA__2__KET____DOT__u_cluster__DOT__accum_bank[0U] 
            = __Vdlyvval__top_level__DOT__gen_clusters__BRA__2__KET____DOT__u_cluster__DOT__accum_bank__v4;
        vlTOPp->top_level__DOT__gen_clusters__BRA__2__KET____DOT__u_cluster__DOT__accum_bank[1U] 
            = __Vdlyvval__top_level__DOT__gen_clusters__BRA__2__KET____DOT__u_cluster__DOT__accum_bank__v5;
        vlTOPp->top_level__DOT__gen_clusters__BRA__2__KET____DOT__u_cluster__DOT__accum_bank[2U] 
            = __Vdlyvval__top_level__DOT__gen_clusters__BRA__2__KET____DOT__u_cluster__DOT__accum_bank__v6;
        vlTOPp->top_level__DOT__gen_clusters__BRA__2__KET____DOT__u_cluster__DOT__accum_bank[3U] 
            = __Vdlyvval__top_level__DOT__gen_clusters__BRA__2__KET____DOT__u_cluster__DOT__accum_bank__v7;
    }
    if (__Vdlyvset__top_level__DOT__gen_clusters__BRA__1__KET____DOT__u_cluster__DOT__accum_bank__v0) {
        vlTOPp->top_level__DOT__gen_clusters__BRA__1__KET____DOT__u_cluster__DOT__accum_bank[0U] = 0U;
        vlTOPp->top_level__DOT__gen_clusters__BRA__1__KET____DOT__u_cluster__DOT__accum_bank[1U] = 0U;
        vlTOPp->top_level__DOT__gen_clusters__BRA__1__KET____DOT__u_cluster__DOT__accum_bank[2U] = 0U;
        vlTOPp->top_level__DOT__gen_clusters__BRA__1__KET____DOT__u_cluster__DOT__accum_bank[3U] = 0U;
    }
    if (__Vdlyvset__top_level__DOT__gen_clusters__BRA__1__KET____DOT__u_cluster__DOT__accum_bank__v4) {
        vlTOPp->top_level__DOT__gen_clusters__BRA__1__KET____DOT__u_cluster__DOT__accum_bank[0U] 
            = __Vdlyvval__top_level__DOT__gen_clusters__BRA__1__KET____DOT__u_cluster__DOT__accum_bank__v4;
        vlTOPp->top_level__DOT__gen_clusters__BRA__1__KET____DOT__u_cluster__DOT__accum_bank[1U] 
            = __Vdlyvval__top_level__DOT__gen_clusters__BRA__1__KET____DOT__u_cluster__DOT__accum_bank__v5;
        vlTOPp->top_level__DOT__gen_clusters__BRA__1__KET____DOT__u_cluster__DOT__accum_bank[2U] 
            = __Vdlyvval__top_level__DOT__gen_clusters__BRA__1__KET____DOT__u_cluster__DOT__accum_bank__v6;
        vlTOPp->top_level__DOT__gen_clusters__BRA__1__KET____DOT__u_cluster__DOT__accum_bank[3U] 
            = __Vdlyvval__top_level__DOT__gen_clusters__BRA__1__KET____DOT__u_cluster__DOT__accum_bank__v7;
    }
    if (__Vdlyvset__top_level__DOT__gen_clusters__BRA__0__KET____DOT__u_cluster__DOT__accum_bank__v0) {
        vlTOPp->top_level__DOT__gen_clusters__BRA__0__KET____DOT__u_cluster__DOT__accum_bank[0U] = 0U;
        vlTOPp->top_level__DOT__gen_clusters__BRA__0__KET____DOT__u_cluster__DOT__accum_bank[1U] = 0U;
        vlTOPp->top_level__DOT__gen_clusters__BRA__0__KET____DOT__u_cluster__DOT__accum_bank[2U] = 0U;
        vlTOPp->top_level__DOT__gen_clusters__BRA__0__KET____DOT__u_cluster__DOT__accum_bank[3U] = 0U;
    }
    if (__Vdlyvset__top_level__DOT__gen_clusters__BRA__0__KET____DOT__u_cluster__DOT__accum_bank__v4) {
        vlTOPp->top_level__DOT__gen_clusters__BRA__0__KET____DOT__u_cluster__DOT__accum_bank[0U] 
            = __Vdlyvval__top_level__DOT__gen_clusters__BRA__0__KET____DOT__u_cluster__DOT__accum_bank__v4;
        vlTOPp->top_level__DOT__gen_clusters__BRA__0__KET____DOT__u_cluster__DOT__accum_bank[1U] 
            = __Vdlyvval__top_level__DOT__gen_clusters__BRA__0__KET____DOT__u_cluster__DOT__accum_bank__v5;
        vlTOPp->top_level__DOT__gen_clusters__BRA__0__KET____DOT__u_cluster__DOT__accum_bank[2U] 
            = __Vdlyvval__top_level__DOT__gen_clusters__BRA__0__KET____DOT__u_cluster__DOT__accum_bank__v6;
        vlTOPp->top_level__DOT__gen_clusters__BRA__0__KET____DOT__u_cluster__DOT__accum_bank[3U] 
            = __Vdlyvval__top_level__DOT__gen_clusters__BRA__0__KET____DOT__u_cluster__DOT__accum_bank__v7;
    }
    if (__Vdlyvset__top_level__DOT__output_mem__v0) {
        __Vilp = 0U;
        while ((__Vilp <= 0x3fU)) {
            vlTOPp->top_level__DOT__output_mem[__Vilp] = 0U;
            __Vilp = ((IData)(1U) + __Vilp);
        }
    }
    if (__Vdlyvset__top_level__DOT__output_mem__v64) {
        vlTOPp->top_level__DOT__output_mem[__Vdlyvdim0__top_level__DOT__output_mem__v64] 
            = __Vdlyvval__top_level__DOT__output_mem__v64;
    }
    if (__Vdlyvset__top_level__DOT__output_mem__v65) {
        vlTOPp->top_level__DOT__output_mem[__Vdlyvdim0__top_level__DOT__output_mem__v65] 
            = __Vdlyvval__top_level__DOT__output_mem__v65;
    }
    if (__Vdlyvset__top_level__DOT__output_mem__v66) {
        vlTOPp->top_level__DOT__output_mem[__Vdlyvdim0__top_level__DOT__output_mem__v66] 
            = __Vdlyvval__top_level__DOT__output_mem__v66;
    }
    if (__Vdlyvset__top_level__DOT__output_mem__v67) {
        vlTOPp->top_level__DOT__output_mem[__Vdlyvdim0__top_level__DOT__output_mem__v67] 
            = __Vdlyvval__top_level__DOT__output_mem__v67;
    }
    if (__Vdlyvset__top_level__DOT__output_mem__v68) {
        vlTOPp->top_level__DOT__output_mem[__Vdlyvdim0__top_level__DOT__output_mem__v68] 
            = __Vdlyvval__top_level__DOT__output_mem__v68;
    }
    if (__Vdlyvset__top_level__DOT__output_mem__v69) {
        vlTOPp->top_level__DOT__output_mem[__Vdlyvdim0__top_level__DOT__output_mem__v69] 
            = __Vdlyvval__top_level__DOT__output_mem__v69;
    }
    if (__Vdlyvset__top_level__DOT__output_mem__v70) {
        vlTOPp->top_level__DOT__output_mem[__Vdlyvdim0__top_level__DOT__output_mem__v70] 
            = __Vdlyvval__top_level__DOT__output_mem__v70;
    }
    if (__Vdlyvset__top_level__DOT__output_mem__v71) {
        vlTOPp->top_level__DOT__output_mem[__Vdlyvdim0__top_level__DOT__output_mem__v71] 
            = __Vdlyvval__top_level__DOT__output_mem__v71;
    }
    if (__Vdlyvset__top_level__DOT__output_mem__v72) {
        vlTOPp->top_level__DOT__output_mem[__Vdlyvdim0__top_level__DOT__output_mem__v72] 
            = __Vdlyvval__top_level__DOT__output_mem__v72;
    }
    if (__Vdlyvset__top_level__DOT__output_mem__v73) {
        vlTOPp->top_level__DOT__output_mem[__Vdlyvdim0__top_level__DOT__output_mem__v73] 
            = __Vdlyvval__top_level__DOT__output_mem__v73;
    }
    if (__Vdlyvset__top_level__DOT__output_mem__v74) {
        vlTOPp->top_level__DOT__output_mem[__Vdlyvdim0__top_level__DOT__output_mem__v74] 
            = __Vdlyvval__top_level__DOT__output_mem__v74;
    }
    if (__Vdlyvset__top_level__DOT__output_mem__v75) {
        vlTOPp->top_level__DOT__output_mem[__Vdlyvdim0__top_level__DOT__output_mem__v75] 
            = __Vdlyvval__top_level__DOT__output_mem__v75;
    }
    if (__Vdlyvset__top_level__DOT__output_mem__v76) {
        vlTOPp->top_level__DOT__output_mem[__Vdlyvdim0__top_level__DOT__output_mem__v76] 
            = __Vdlyvval__top_level__DOT__output_mem__v76;
    }
    if (__Vdlyvset__top_level__DOT__output_mem__v77) {
        vlTOPp->top_level__DOT__output_mem[__Vdlyvdim0__top_level__DOT__output_mem__v77] 
            = __Vdlyvval__top_level__DOT__output_mem__v77;
    }
    if (__Vdlyvset__top_level__DOT__output_mem__v78) {
        vlTOPp->top_level__DOT__output_mem[__Vdlyvdim0__top_level__DOT__output_mem__v78] 
            = __Vdlyvval__top_level__DOT__output_mem__v78;
    }
    if (__Vdlyvset__top_level__DOT__output_mem__v79) {
        vlTOPp->top_level__DOT__output_mem[__Vdlyvdim0__top_level__DOT__output_mem__v79] 
            = __Vdlyvval__top_level__DOT__output_mem__v79;
    }
    if (__Vdlyvset__top_level__DOT__output_mem__v80) {
        vlTOPp->top_level__DOT__output_mem[__Vdlyvdim0__top_level__DOT__output_mem__v80] 
            = __Vdlyvval__top_level__DOT__output_mem__v80;
    }
    if (__Vdlyvset__top_level__DOT__output_mem__v81) {
        vlTOPp->top_level__DOT__output_mem[__Vdlyvdim0__top_level__DOT__output_mem__v81] 
            = __Vdlyvval__top_level__DOT__output_mem__v81;
    }
    if (__Vdlyvset__top_level__DOT__output_mem__v82) {
        vlTOPp->top_level__DOT__output_mem[__Vdlyvdim0__top_level__DOT__output_mem__v82] 
            = __Vdlyvval__top_level__DOT__output_mem__v82;
    }
    if (__Vdlyvset__top_level__DOT__output_mem__v83) {
        vlTOPp->top_level__DOT__output_mem[__Vdlyvdim0__top_level__DOT__output_mem__v83] 
            = __Vdlyvval__top_level__DOT__output_mem__v83;
    }
    if (__Vdlyvset__top_level__DOT__output_mem__v84) {
        vlTOPp->top_level__DOT__output_mem[__Vdlyvdim0__top_level__DOT__output_mem__v84] 
            = __Vdlyvval__top_level__DOT__output_mem__v84;
    }
    if (__Vdlyvset__top_level__DOT__output_mem__v85) {
        vlTOPp->top_level__DOT__output_mem[__Vdlyvdim0__top_level__DOT__output_mem__v85] 
            = __Vdlyvval__top_level__DOT__output_mem__v85;
    }
    if (__Vdlyvset__top_level__DOT__output_mem__v86) {
        vlTOPp->top_level__DOT__output_mem[__Vdlyvdim0__top_level__DOT__output_mem__v86] 
            = __Vdlyvval__top_level__DOT__output_mem__v86;
    }
    if (__Vdlyvset__top_level__DOT__output_mem__v87) {
        vlTOPp->top_level__DOT__output_mem[__Vdlyvdim0__top_level__DOT__output_mem__v87] 
            = __Vdlyvval__top_level__DOT__output_mem__v87;
    }
    if (__Vdlyvset__top_level__DOT__output_mem__v88) {
        vlTOPp->top_level__DOT__output_mem[__Vdlyvdim0__top_level__DOT__output_mem__v88] 
            = __Vdlyvval__top_level__DOT__output_mem__v88;
    }
    if (__Vdlyvset__top_level__DOT__output_mem__v89) {
        vlTOPp->top_level__DOT__output_mem[__Vdlyvdim0__top_level__DOT__output_mem__v89] 
            = __Vdlyvval__top_level__DOT__output_mem__v89;
    }
    if (__Vdlyvset__top_level__DOT__output_mem__v90) {
        vlTOPp->top_level__DOT__output_mem[__Vdlyvdim0__top_level__DOT__output_mem__v90] 
            = __Vdlyvval__top_level__DOT__output_mem__v90;
    }
    if (__Vdlyvset__top_level__DOT__output_mem__v91) {
        vlTOPp->top_level__DOT__output_mem[__Vdlyvdim0__top_level__DOT__output_mem__v91] 
            = __Vdlyvval__top_level__DOT__output_mem__v91;
    }
    if (__Vdlyvset__top_level__DOT__output_mem__v92) {
        vlTOPp->top_level__DOT__output_mem[__Vdlyvdim0__top_level__DOT__output_mem__v92] 
            = __Vdlyvval__top_level__DOT__output_mem__v92;
    }
    if (__Vdlyvset__top_level__DOT__output_mem__v93) {
        vlTOPp->top_level__DOT__output_mem[__Vdlyvdim0__top_level__DOT__output_mem__v93] 
            = __Vdlyvval__top_level__DOT__output_mem__v93;
    }
    if (__Vdlyvset__top_level__DOT__output_mem__v94) {
        vlTOPp->top_level__DOT__output_mem[__Vdlyvdim0__top_level__DOT__output_mem__v94] 
            = __Vdlyvval__top_level__DOT__output_mem__v94;
    }
    if (__Vdlyvset__top_level__DOT__output_mem__v95) {
        vlTOPp->top_level__DOT__output_mem[__Vdlyvdim0__top_level__DOT__output_mem__v95] 
            = __Vdlyvval__top_level__DOT__output_mem__v95;
    }
    vlTOPp->debug_cycle_count = vlTOPp->top_level__DOT__cycle_count;
    vlTOPp->top_level__DOT____Vcellout__gen_clusters__BRA__7__KET____DOT__u_cluster__accum_out[0U] 
        = vlTOPp->top_level__DOT__gen_clusters__BRA__7__KET____DOT__u_cluster__DOT__accum_bank
        [0U];
    vlTOPp->top_level__DOT____Vcellout__gen_clusters__BRA__7__KET____DOT__u_cluster__accum_out[1U] 
        = vlTOPp->top_level__DOT__gen_clusters__BRA__7__KET____DOT__u_cluster__DOT__accum_bank
        [1U];
    vlTOPp->top_level__DOT____Vcellout__gen_clusters__BRA__7__KET____DOT__u_cluster__accum_out[2U] 
        = vlTOPp->top_level__DOT__gen_clusters__BRA__7__KET____DOT__u_cluster__DOT__accum_bank
        [2U];
    vlTOPp->top_level__DOT____Vcellout__gen_clusters__BRA__7__KET____DOT__u_cluster__accum_out[3U] 
        = vlTOPp->top_level__DOT__gen_clusters__BRA__7__KET____DOT__u_cluster__DOT__accum_bank
        [3U];
    vlTOPp->top_level__DOT____Vcellout__gen_clusters__BRA__6__KET____DOT__u_cluster__accum_out[0U] 
        = vlTOPp->top_level__DOT__gen_clusters__BRA__6__KET____DOT__u_cluster__DOT__accum_bank
        [0U];
    vlTOPp->top_level__DOT____Vcellout__gen_clusters__BRA__6__KET____DOT__u_cluster__accum_out[1U] 
        = vlTOPp->top_level__DOT__gen_clusters__BRA__6__KET____DOT__u_cluster__DOT__accum_bank
        [1U];
    vlTOPp->top_level__DOT____Vcellout__gen_clusters__BRA__6__KET____DOT__u_cluster__accum_out[2U] 
        = vlTOPp->top_level__DOT__gen_clusters__BRA__6__KET____DOT__u_cluster__DOT__accum_bank
        [2U];
    vlTOPp->top_level__DOT____Vcellout__gen_clusters__BRA__6__KET____DOT__u_cluster__accum_out[3U] 
        = vlTOPp->top_level__DOT__gen_clusters__BRA__6__KET____DOT__u_cluster__DOT__accum_bank
        [3U];
    vlTOPp->top_level__DOT____Vcellout__gen_clusters__BRA__5__KET____DOT__u_cluster__accum_out[0U] 
        = vlTOPp->top_level__DOT__gen_clusters__BRA__5__KET____DOT__u_cluster__DOT__accum_bank
        [0U];
    vlTOPp->top_level__DOT____Vcellout__gen_clusters__BRA__5__KET____DOT__u_cluster__accum_out[1U] 
        = vlTOPp->top_level__DOT__gen_clusters__BRA__5__KET____DOT__u_cluster__DOT__accum_bank
        [1U];
    vlTOPp->top_level__DOT____Vcellout__gen_clusters__BRA__5__KET____DOT__u_cluster__accum_out[2U] 
        = vlTOPp->top_level__DOT__gen_clusters__BRA__5__KET____DOT__u_cluster__DOT__accum_bank
        [2U];
    vlTOPp->top_level__DOT____Vcellout__gen_clusters__BRA__5__KET____DOT__u_cluster__accum_out[3U] 
        = vlTOPp->top_level__DOT__gen_clusters__BRA__5__KET____DOT__u_cluster__DOT__accum_bank
        [3U];
    vlTOPp->top_level__DOT____Vcellout__gen_clusters__BRA__4__KET____DOT__u_cluster__accum_out[0U] 
        = vlTOPp->top_level__DOT__gen_clusters__BRA__4__KET____DOT__u_cluster__DOT__accum_bank
        [0U];
    vlTOPp->top_level__DOT____Vcellout__gen_clusters__BRA__4__KET____DOT__u_cluster__accum_out[1U] 
        = vlTOPp->top_level__DOT__gen_clusters__BRA__4__KET____DOT__u_cluster__DOT__accum_bank
        [1U];
    vlTOPp->top_level__DOT____Vcellout__gen_clusters__BRA__4__KET____DOT__u_cluster__accum_out[2U] 
        = vlTOPp->top_level__DOT__gen_clusters__BRA__4__KET____DOT__u_cluster__DOT__accum_bank
        [2U];
    vlTOPp->top_level__DOT____Vcellout__gen_clusters__BRA__4__KET____DOT__u_cluster__accum_out[3U] 
        = vlTOPp->top_level__DOT__gen_clusters__BRA__4__KET____DOT__u_cluster__DOT__accum_bank
        [3U];
    vlTOPp->top_level__DOT____Vcellout__gen_clusters__BRA__3__KET____DOT__u_cluster__accum_out[0U] 
        = vlTOPp->top_level__DOT__gen_clusters__BRA__3__KET____DOT__u_cluster__DOT__accum_bank
        [0U];
    vlTOPp->top_level__DOT____Vcellout__gen_clusters__BRA__3__KET____DOT__u_cluster__accum_out[1U] 
        = vlTOPp->top_level__DOT__gen_clusters__BRA__3__KET____DOT__u_cluster__DOT__accum_bank
        [1U];
    vlTOPp->top_level__DOT____Vcellout__gen_clusters__BRA__3__KET____DOT__u_cluster__accum_out[2U] 
        = vlTOPp->top_level__DOT__gen_clusters__BRA__3__KET____DOT__u_cluster__DOT__accum_bank
        [2U];
    vlTOPp->top_level__DOT____Vcellout__gen_clusters__BRA__3__KET____DOT__u_cluster__accum_out[3U] 
        = vlTOPp->top_level__DOT__gen_clusters__BRA__3__KET____DOT__u_cluster__DOT__accum_bank
        [3U];
    vlTOPp->top_level__DOT____Vcellout__gen_clusters__BRA__2__KET____DOT__u_cluster__accum_out[0U] 
        = vlTOPp->top_level__DOT__gen_clusters__BRA__2__KET____DOT__u_cluster__DOT__accum_bank
        [0U];
    vlTOPp->top_level__DOT____Vcellout__gen_clusters__BRA__2__KET____DOT__u_cluster__accum_out[1U] 
        = vlTOPp->top_level__DOT__gen_clusters__BRA__2__KET____DOT__u_cluster__DOT__accum_bank
        [1U];
    vlTOPp->top_level__DOT____Vcellout__gen_clusters__BRA__2__KET____DOT__u_cluster__accum_out[2U] 
        = vlTOPp->top_level__DOT__gen_clusters__BRA__2__KET____DOT__u_cluster__DOT__accum_bank
        [2U];
    vlTOPp->top_level__DOT____Vcellout__gen_clusters__BRA__2__KET____DOT__u_cluster__accum_out[3U] 
        = vlTOPp->top_level__DOT__gen_clusters__BRA__2__KET____DOT__u_cluster__DOT__accum_bank
        [3U];
    vlTOPp->top_level__DOT____Vcellout__gen_clusters__BRA__1__KET____DOT__u_cluster__accum_out[0U] 
        = vlTOPp->top_level__DOT__gen_clusters__BRA__1__KET____DOT__u_cluster__DOT__accum_bank
        [0U];
    vlTOPp->top_level__DOT____Vcellout__gen_clusters__BRA__1__KET____DOT__u_cluster__accum_out[1U] 
        = vlTOPp->top_level__DOT__gen_clusters__BRA__1__KET____DOT__u_cluster__DOT__accum_bank
        [1U];
    vlTOPp->top_level__DOT____Vcellout__gen_clusters__BRA__1__KET____DOT__u_cluster__accum_out[2U] 
        = vlTOPp->top_level__DOT__gen_clusters__BRA__1__KET____DOT__u_cluster__DOT__accum_bank
        [2U];
    vlTOPp->top_level__DOT____Vcellout__gen_clusters__BRA__1__KET____DOT__u_cluster__accum_out[3U] 
        = vlTOPp->top_level__DOT__gen_clusters__BRA__1__KET____DOT__u_cluster__DOT__accum_bank
        [3U];
    vlTOPp->top_level__DOT____Vcellout__gen_clusters__BRA__0__KET____DOT__u_cluster__accum_out[0U] 
        = vlTOPp->top_level__DOT__gen_clusters__BRA__0__KET____DOT__u_cluster__DOT__accum_bank
        [0U];
    vlTOPp->top_level__DOT____Vcellout__gen_clusters__BRA__0__KET____DOT__u_cluster__accum_out[1U] 
        = vlTOPp->top_level__DOT__gen_clusters__BRA__0__KET____DOT__u_cluster__DOT__accum_bank
        [1U];
    vlTOPp->top_level__DOT____Vcellout__gen_clusters__BRA__0__KET____DOT__u_cluster__accum_out[2U] 
        = vlTOPp->top_level__DOT__gen_clusters__BRA__0__KET____DOT__u_cluster__DOT__accum_bank
        [2U];
    vlTOPp->top_level__DOT____Vcellout__gen_clusters__BRA__0__KET____DOT__u_cluster__accum_out[3U] 
        = vlTOPp->top_level__DOT__gen_clusters__BRA__0__KET____DOT__u_cluster__DOT__accum_bank
        [3U];
    vlTOPp->top_level__DOT__write_en = 0U;
    if ((4U & (IData)(vlTOPp->top_level__DOT__u_control__DOT__state_q))) {
        if ((1U & (~ ((IData)(vlTOPp->top_level__DOT__u_control__DOT__state_q) 
                      >> 1U)))) {
            if ((1U & (~ (IData)(vlTOPp->top_level__DOT__u_control__DOT__state_q)))) {
                vlTOPp->top_level__DOT__write_en = 1U;
            }
        }
    }
    vlTOPp->done = 0U;
    if ((4U & (IData)(vlTOPp->top_level__DOT__u_control__DOT__state_q))) {
        if ((1U & (~ ((IData)(vlTOPp->top_level__DOT__u_control__DOT__state_q) 
                      >> 1U)))) {
            if ((1U & (IData)(vlTOPp->top_level__DOT__u_control__DOT__state_q))) {
                vlTOPp->done = 1U;
            }
        }
    }
    vlTOPp->busy = 1U;
    if ((1U & (~ ((IData)(vlTOPp->top_level__DOT__u_control__DOT__state_q) 
                  >> 2U)))) {
        if ((1U & (~ ((IData)(vlTOPp->top_level__DOT__u_control__DOT__state_q) 
                      >> 1U)))) {
            if ((1U & (~ (IData)(vlTOPp->top_level__DOT__u_control__DOT__state_q)))) {
                vlTOPp->busy = 0U;
            }
        }
    }
    vlTOPp->top_level__DOT__clear_acc = 0U;
    if ((1U & (~ ((IData)(vlTOPp->top_level__DOT__u_control__DOT__state_q) 
                  >> 2U)))) {
        if ((1U & (~ ((IData)(vlTOPp->top_level__DOT__u_control__DOT__state_q) 
                      >> 1U)))) {
            if ((1U & (IData)(vlTOPp->top_level__DOT__u_control__DOT__state_q))) {
                vlTOPp->top_level__DOT__clear_acc = 1U;
            }
        }
    }
    vlTOPp->top_level__DOT__u_control__DOT__cycle_count_d 
        = vlTOPp->top_level__DOT__cycle_count;
    if ((4U & (IData)(vlTOPp->top_level__DOT__u_control__DOT__state_q))) {
        if ((1U & (~ ((IData)(vlTOPp->top_level__DOT__u_control__DOT__state_q) 
                      >> 1U)))) {
            vlTOPp->top_level__DOT__u_control__DOT__cycle_count_d 
                = ((1U & (IData)(vlTOPp->top_level__DOT__u_control__DOT__state_q))
                    ? vlTOPp->top_level__DOT__cycle_count
                    : ((IData)(1U) + vlTOPp->top_level__DOT__cycle_count));
        }
    } else {
        vlTOPp->top_level__DOT__u_control__DOT__cycle_count_d 
            = ((2U & (IData)(vlTOPp->top_level__DOT__u_control__DOT__state_q))
                ? ((1U & (IData)(vlTOPp->top_level__DOT__u_control__DOT__state_q))
                    ? ((IData)(1U) + vlTOPp->top_level__DOT__cycle_count)
                    : ((IData)(1U) + vlTOPp->top_level__DOT__cycle_count))
                : ((1U & (IData)(vlTOPp->top_level__DOT__u_control__DOT__state_q))
                    ? ((IData)(1U) + vlTOPp->top_level__DOT__cycle_count)
                    : 0U));
    }
    vlTOPp->top_level__DOT__u_control__DOT__drain_iter_d 
        = vlTOPp->top_level__DOT__u_control__DOT__drain_iter_q;
    if ((1U & (~ ((IData)(vlTOPp->top_level__DOT__u_control__DOT__state_q) 
                  >> 2U)))) {
        if ((2U & (IData)(vlTOPp->top_level__DOT__u_control__DOT__state_q))) {
            if ((1U & (IData)(vlTOPp->top_level__DOT__u_control__DOT__state_q))) {
                vlTOPp->top_level__DOT__u_control__DOT__drain_iter_d 
                    = ((1U <= ((IData)(1U) + vlTOPp->top_level__DOT__u_control__DOT__drain_iter_q))
                        ? 0U : ((IData)(1U) + vlTOPp->top_level__DOT__u_control__DOT__drain_iter_q));
            }
        } else {
            if ((1U & (IData)(vlTOPp->top_level__DOT__u_control__DOT__state_q))) {
                vlTOPp->top_level__DOT__u_control__DOT__drain_iter_d = 0U;
            }
        }
    }
    vlTOPp->top_level__DOT__u_control__DOT__compute_iter_d 
        = vlTOPp->top_level__DOT__u_control__DOT__compute_iter_q;
    if ((1U & (~ ((IData)(vlTOPp->top_level__DOT__u_control__DOT__state_q) 
                  >> 2U)))) {
        if ((2U & (IData)(vlTOPp->top_level__DOT__u_control__DOT__state_q))) {
            if ((1U & (~ (IData)(vlTOPp->top_level__DOT__u_control__DOT__state_q)))) {
                vlTOPp->top_level__DOT__u_control__DOT__compute_iter_d 
                    = ((8U <= ((IData)(1U) + vlTOPp->top_level__DOT__u_control__DOT__compute_iter_q))
                        ? 0U : ((IData)(1U) + vlTOPp->top_level__DOT__u_control__DOT__compute_iter_q));
            }
        } else {
            if ((1U & (IData)(vlTOPp->top_level__DOT__u_control__DOT__state_q))) {
                vlTOPp->top_level__DOT__u_control__DOT__compute_iter_d = 0U;
            }
        }
    }
    vlTOPp->top_level__DOT__compute_en = 0U;
    if ((1U & (~ ((IData)(vlTOPp->top_level__DOT__u_control__DOT__state_q) 
                  >> 2U)))) {
        if ((2U & (IData)(vlTOPp->top_level__DOT__u_control__DOT__state_q))) {
            if ((1U & (~ (IData)(vlTOPp->top_level__DOT__u_control__DOT__state_q)))) {
                vlTOPp->top_level__DOT__compute_en = 1U;
            }
        }
    }
    vlTOPp->top_level__DOT__shared_phase = 0U;
    if ((1U & (~ ((IData)(vlTOPp->top_level__DOT__u_control__DOT__state_q) 
                  >> 2U)))) {
        if ((2U & (IData)(vlTOPp->top_level__DOT__u_control__DOT__state_q))) {
            if ((1U & (~ (IData)(vlTOPp->top_level__DOT__u_control__DOT__state_q)))) {
                vlTOPp->top_level__DOT__shared_phase 
                    = (1U & vlTOPp->top_level__DOT__u_control__DOT__compute_iter_q);
            }
        }
    }
    vlTOPp->top_level__DOT__current_k = 0U;
    if ((1U & (~ ((IData)(vlTOPp->top_level__DOT__u_control__DOT__state_q) 
                  >> 2U)))) {
        if ((2U & (IData)(vlTOPp->top_level__DOT__u_control__DOT__state_q))) {
            if ((1U & (~ (IData)(vlTOPp->top_level__DOT__u_control__DOT__state_q)))) {
                vlTOPp->top_level__DOT__current_k = 
                    (3U & (vlTOPp->top_level__DOT__u_control__DOT__compute_iter_q 
                           >> 1U));
            }
        }
    }
    vlTOPp->top_level__DOT__cluster_accum[7U][0U] = 
        vlTOPp->top_level__DOT____Vcellout__gen_clusters__BRA__7__KET____DOT__u_cluster__accum_out
        [0U];
    vlTOPp->top_level__DOT__cluster_accum[7U][1U] = 
        vlTOPp->top_level__DOT____Vcellout__gen_clusters__BRA__7__KET____DOT__u_cluster__accum_out
        [1U];
    vlTOPp->top_level__DOT__cluster_accum[7U][2U] = 
        vlTOPp->top_level__DOT____Vcellout__gen_clusters__BRA__7__KET____DOT__u_cluster__accum_out
        [2U];
    vlTOPp->top_level__DOT__cluster_accum[7U][3U] = 
        vlTOPp->top_level__DOT____Vcellout__gen_clusters__BRA__7__KET____DOT__u_cluster__accum_out
        [3U];
    vlTOPp->top_level__DOT__cluster_accum[6U][0U] = 
        vlTOPp->top_level__DOT____Vcellout__gen_clusters__BRA__6__KET____DOT__u_cluster__accum_out
        [0U];
    vlTOPp->top_level__DOT__cluster_accum[6U][1U] = 
        vlTOPp->top_level__DOT____Vcellout__gen_clusters__BRA__6__KET____DOT__u_cluster__accum_out
        [1U];
    vlTOPp->top_level__DOT__cluster_accum[6U][2U] = 
        vlTOPp->top_level__DOT____Vcellout__gen_clusters__BRA__6__KET____DOT__u_cluster__accum_out
        [2U];
    vlTOPp->top_level__DOT__cluster_accum[6U][3U] = 
        vlTOPp->top_level__DOT____Vcellout__gen_clusters__BRA__6__KET____DOT__u_cluster__accum_out
        [3U];
    vlTOPp->top_level__DOT__cluster_accum[5U][0U] = 
        vlTOPp->top_level__DOT____Vcellout__gen_clusters__BRA__5__KET____DOT__u_cluster__accum_out
        [0U];
    vlTOPp->top_level__DOT__cluster_accum[5U][1U] = 
        vlTOPp->top_level__DOT____Vcellout__gen_clusters__BRA__5__KET____DOT__u_cluster__accum_out
        [1U];
    vlTOPp->top_level__DOT__cluster_accum[5U][2U] = 
        vlTOPp->top_level__DOT____Vcellout__gen_clusters__BRA__5__KET____DOT__u_cluster__accum_out
        [2U];
    vlTOPp->top_level__DOT__cluster_accum[5U][3U] = 
        vlTOPp->top_level__DOT____Vcellout__gen_clusters__BRA__5__KET____DOT__u_cluster__accum_out
        [3U];
    vlTOPp->top_level__DOT__cluster_accum[4U][0U] = 
        vlTOPp->top_level__DOT____Vcellout__gen_clusters__BRA__4__KET____DOT__u_cluster__accum_out
        [0U];
    vlTOPp->top_level__DOT__cluster_accum[4U][1U] = 
        vlTOPp->top_level__DOT____Vcellout__gen_clusters__BRA__4__KET____DOT__u_cluster__accum_out
        [1U];
    vlTOPp->top_level__DOT__cluster_accum[4U][2U] = 
        vlTOPp->top_level__DOT____Vcellout__gen_clusters__BRA__4__KET____DOT__u_cluster__accum_out
        [2U];
    vlTOPp->top_level__DOT__cluster_accum[4U][3U] = 
        vlTOPp->top_level__DOT____Vcellout__gen_clusters__BRA__4__KET____DOT__u_cluster__accum_out
        [3U];
    vlTOPp->top_level__DOT__cluster_accum[3U][0U] = 
        vlTOPp->top_level__DOT____Vcellout__gen_clusters__BRA__3__KET____DOT__u_cluster__accum_out
        [0U];
    vlTOPp->top_level__DOT__cluster_accum[3U][1U] = 
        vlTOPp->top_level__DOT____Vcellout__gen_clusters__BRA__3__KET____DOT__u_cluster__accum_out
        [1U];
    vlTOPp->top_level__DOT__cluster_accum[3U][2U] = 
        vlTOPp->top_level__DOT____Vcellout__gen_clusters__BRA__3__KET____DOT__u_cluster__accum_out
        [2U];
    vlTOPp->top_level__DOT__cluster_accum[3U][3U] = 
        vlTOPp->top_level__DOT____Vcellout__gen_clusters__BRA__3__KET____DOT__u_cluster__accum_out
        [3U];
    vlTOPp->top_level__DOT__cluster_accum[2U][0U] = 
        vlTOPp->top_level__DOT____Vcellout__gen_clusters__BRA__2__KET____DOT__u_cluster__accum_out
        [0U];
    vlTOPp->top_level__DOT__cluster_accum[2U][1U] = 
        vlTOPp->top_level__DOT____Vcellout__gen_clusters__BRA__2__KET____DOT__u_cluster__accum_out
        [1U];
    vlTOPp->top_level__DOT__cluster_accum[2U][2U] = 
        vlTOPp->top_level__DOT____Vcellout__gen_clusters__BRA__2__KET____DOT__u_cluster__accum_out
        [2U];
    vlTOPp->top_level__DOT__cluster_accum[2U][3U] = 
        vlTOPp->top_level__DOT____Vcellout__gen_clusters__BRA__2__KET____DOT__u_cluster__accum_out
        [3U];
    vlTOPp->top_level__DOT__cluster_accum[1U][0U] = 
        vlTOPp->top_level__DOT____Vcellout__gen_clusters__BRA__1__KET____DOT__u_cluster__accum_out
        [0U];
    vlTOPp->top_level__DOT__cluster_accum[1U][1U] = 
        vlTOPp->top_level__DOT____Vcellout__gen_clusters__BRA__1__KET____DOT__u_cluster__accum_out
        [1U];
    vlTOPp->top_level__DOT__cluster_accum[1U][2U] = 
        vlTOPp->top_level__DOT____Vcellout__gen_clusters__BRA__1__KET____DOT__u_cluster__accum_out
        [2U];
    vlTOPp->top_level__DOT__cluster_accum[1U][3U] = 
        vlTOPp->top_level__DOT____Vcellout__gen_clusters__BRA__1__KET____DOT__u_cluster__accum_out
        [3U];
    vlTOPp->top_level__DOT__cluster_accum[0U][0U] = 
        vlTOPp->top_level__DOT____Vcellout__gen_clusters__BRA__0__KET____DOT__u_cluster__accum_out
        [0U];
    vlTOPp->top_level__DOT__cluster_accum[0U][1U] = 
        vlTOPp->top_level__DOT____Vcellout__gen_clusters__BRA__0__KET____DOT__u_cluster__accum_out
        [1U];
    vlTOPp->top_level__DOT__cluster_accum[0U][2U] = 
        vlTOPp->top_level__DOT____Vcellout__gen_clusters__BRA__0__KET____DOT__u_cluster__accum_out
        [2U];
    vlTOPp->top_level__DOT__cluster_accum[0U][3U] = 
        vlTOPp->top_level__DOT____Vcellout__gen_clusters__BRA__0__KET____DOT__u_cluster__accum_out
        [3U];
    vlTOPp->top_level__DOT__u_interconnect__DOT__b_addr_calc 
        = VL_MULS_III(32,32,32, (IData)(4U), (IData)(vlTOPp->top_level__DOT__current_k));
    vlTOPp->top_level__DOT____Vcellout__u_interconnect__b_read_addr[0U] 
        = (0x3fU & vlTOPp->top_level__DOT__u_interconnect__DOT__b_addr_calc);
    vlTOPp->top_level__DOT__u_interconnect__DOT__b_addr_calc 
        = ((IData)(1U) + VL_MULS_III(32,32,32, (IData)(4U), (IData)(vlTOPp->top_level__DOT__current_k)));
    vlTOPp->top_level__DOT____Vcellout__u_interconnect__b_read_addr[1U] 
        = (0x3fU & vlTOPp->top_level__DOT__u_interconnect__DOT__b_addr_calc);
    vlTOPp->top_level__DOT__u_interconnect__DOT__b_addr_calc 
        = ((IData)(2U) + VL_MULS_III(32,32,32, (IData)(4U), (IData)(vlTOPp->top_level__DOT__current_k)));
    vlTOPp->top_level__DOT____Vcellout__u_interconnect__b_read_addr[2U] 
        = (0x3fU & vlTOPp->top_level__DOT__u_interconnect__DOT__b_addr_calc);
    vlTOPp->top_level__DOT__u_interconnect__DOT__b_addr_calc 
        = ((IData)(3U) + VL_MULS_III(32,32,32, (IData)(4U), (IData)(vlTOPp->top_level__DOT__current_k)));
    vlTOPp->top_level__DOT____Vcellout__u_interconnect__b_read_addr[3U] 
        = (0x3fU & vlTOPp->top_level__DOT__u_interconnect__DOT__b_addr_calc);
    vlTOPp->top_level__DOT__u_interconnect__DOT__a_addr_calc 
        = vlTOPp->top_level__DOT__current_k;
    vlTOPp->top_level__DOT____Vcellout__u_interconnect__a_read_addr[0U] 
        = (0x3fU & vlTOPp->top_level__DOT__u_interconnect__DOT__a_addr_calc);
    vlTOPp->top_level__DOT__u_interconnect__DOT__a_addr_calc 
        = ((IData)(4U) + (IData)(vlTOPp->top_level__DOT__current_k));
    vlTOPp->top_level__DOT____Vcellout__u_interconnect__a_read_addr[1U] 
        = (0x3fU & vlTOPp->top_level__DOT__u_interconnect__DOT__a_addr_calc);
    vlTOPp->top_level__DOT__u_interconnect__DOT__a_addr_calc 
        = ((IData)(8U) + (IData)(vlTOPp->top_level__DOT__current_k));
    vlTOPp->top_level__DOT____Vcellout__u_interconnect__a_read_addr[2U] 
        = (0x3fU & vlTOPp->top_level__DOT__u_interconnect__DOT__a_addr_calc);
    vlTOPp->top_level__DOT__u_interconnect__DOT__a_addr_calc 
        = ((IData)(0xcU) + (IData)(vlTOPp->top_level__DOT__current_k));
    vlTOPp->top_level__DOT____Vcellout__u_interconnect__a_read_addr[3U] 
        = (0x3fU & vlTOPp->top_level__DOT__u_interconnect__DOT__a_addr_calc);
    vlTOPp->top_level__DOT__u_interconnect__DOT__a_addr_calc 
        = ((IData)(0x10U) + (IData)(vlTOPp->top_level__DOT__current_k));
    vlTOPp->top_level__DOT____Vcellout__u_interconnect__a_read_addr[4U] 
        = (0x3fU & vlTOPp->top_level__DOT__u_interconnect__DOT__a_addr_calc);
    vlTOPp->top_level__DOT__u_interconnect__DOT__a_addr_calc 
        = ((IData)(0x14U) + (IData)(vlTOPp->top_level__DOT__current_k));
    vlTOPp->top_level__DOT____Vcellout__u_interconnect__a_read_addr[5U] 
        = (0x3fU & vlTOPp->top_level__DOT__u_interconnect__DOT__a_addr_calc);
    vlTOPp->top_level__DOT__u_interconnect__DOT__a_addr_calc 
        = ((IData)(0x18U) + (IData)(vlTOPp->top_level__DOT__current_k));
    vlTOPp->top_level__DOT____Vcellout__u_interconnect__a_read_addr[6U] 
        = (0x3fU & vlTOPp->top_level__DOT__u_interconnect__DOT__a_addr_calc);
    vlTOPp->top_level__DOT__u_interconnect__DOT__a_addr_calc 
        = ((IData)(0x1cU) + (IData)(vlTOPp->top_level__DOT__current_k));
    vlTOPp->top_level__DOT____Vcellout__u_interconnect__a_read_addr[7U] 
        = (0x3fU & vlTOPp->top_level__DOT__u_interconnect__DOT__a_addr_calc);
    vlTOPp->top_level__DOT__b_read_addr[0U] = vlTOPp->top_level__DOT____Vcellout__u_interconnect__b_read_addr
        [0U];
    vlTOPp->top_level__DOT__b_read_addr[1U] = vlTOPp->top_level__DOT____Vcellout__u_interconnect__b_read_addr
        [1U];
    vlTOPp->top_level__DOT__b_read_addr[2U] = vlTOPp->top_level__DOT____Vcellout__u_interconnect__b_read_addr
        [2U];
    vlTOPp->top_level__DOT__b_read_addr[3U] = vlTOPp->top_level__DOT____Vcellout__u_interconnect__b_read_addr
        [3U];
    vlTOPp->top_level__DOT__a_read_addr[0U] = vlTOPp->top_level__DOT____Vcellout__u_interconnect__a_read_addr
        [0U];
    vlTOPp->top_level__DOT__a_read_addr[1U] = vlTOPp->top_level__DOT____Vcellout__u_interconnect__a_read_addr
        [1U];
    vlTOPp->top_level__DOT__a_read_addr[2U] = vlTOPp->top_level__DOT____Vcellout__u_interconnect__a_read_addr
        [2U];
    vlTOPp->top_level__DOT__a_read_addr[3U] = vlTOPp->top_level__DOT____Vcellout__u_interconnect__a_read_addr
        [3U];
    vlTOPp->top_level__DOT__a_read_addr[4U] = vlTOPp->top_level__DOT____Vcellout__u_interconnect__a_read_addr
        [4U];
    vlTOPp->top_level__DOT__a_read_addr[5U] = vlTOPp->top_level__DOT____Vcellout__u_interconnect__a_read_addr
        [5U];
    vlTOPp->top_level__DOT__a_read_addr[6U] = vlTOPp->top_level__DOT____Vcellout__u_interconnect__a_read_addr
        [6U];
    vlTOPp->top_level__DOT__a_read_addr[7U] = vlTOPp->top_level__DOT____Vcellout__u_interconnect__a_read_addr
        [7U];
    vlTOPp->top_level__DOT____Vcellinp__u_b_buffer__read_addr[0U] 
        = vlTOPp->top_level__DOT__b_read_addr[0U];
    vlTOPp->top_level__DOT____Vcellinp__u_b_buffer__read_addr[1U] 
        = vlTOPp->top_level__DOT__b_read_addr[1U];
    vlTOPp->top_level__DOT____Vcellinp__u_b_buffer__read_addr[2U] 
        = vlTOPp->top_level__DOT__b_read_addr[2U];
    vlTOPp->top_level__DOT____Vcellinp__u_b_buffer__read_addr[3U] 
        = vlTOPp->top_level__DOT__b_read_addr[3U];
    vlTOPp->top_level__DOT____Vcellinp__u_a_buffer__read_addr[0U] 
        = vlTOPp->top_level__DOT__a_read_addr[0U];
    vlTOPp->top_level__DOT____Vcellinp__u_a_buffer__read_addr[1U] 
        = vlTOPp->top_level__DOT__a_read_addr[1U];
    vlTOPp->top_level__DOT____Vcellinp__u_a_buffer__read_addr[2U] 
        = vlTOPp->top_level__DOT__a_read_addr[2U];
    vlTOPp->top_level__DOT____Vcellinp__u_a_buffer__read_addr[3U] 
        = vlTOPp->top_level__DOT__a_read_addr[3U];
    vlTOPp->top_level__DOT____Vcellinp__u_a_buffer__read_addr[4U] 
        = vlTOPp->top_level__DOT__a_read_addr[4U];
    vlTOPp->top_level__DOT____Vcellinp__u_a_buffer__read_addr[5U] 
        = vlTOPp->top_level__DOT__a_read_addr[5U];
    vlTOPp->top_level__DOT____Vcellinp__u_a_buffer__read_addr[6U] 
        = vlTOPp->top_level__DOT__a_read_addr[6U];
    vlTOPp->top_level__DOT____Vcellinp__u_a_buffer__read_addr[7U] 
        = vlTOPp->top_level__DOT__a_read_addr[7U];
    vlTOPp->top_level__DOT____Vcellout__u_b_buffer__read_data[0U] 
        = vlTOPp->top_level__DOT__u_b_buffer__DOT__mem
        [vlTOPp->top_level__DOT____Vcellinp__u_b_buffer__read_addr
        [0U]];
    vlTOPp->top_level__DOT____Vcellout__u_b_buffer__read_data[1U] 
        = vlTOPp->top_level__DOT__u_b_buffer__DOT__mem
        [vlTOPp->top_level__DOT____Vcellinp__u_b_buffer__read_addr
        [1U]];
    vlTOPp->top_level__DOT____Vcellout__u_b_buffer__read_data[2U] 
        = vlTOPp->top_level__DOT__u_b_buffer__DOT__mem
        [vlTOPp->top_level__DOT____Vcellinp__u_b_buffer__read_addr
        [2U]];
    vlTOPp->top_level__DOT____Vcellout__u_b_buffer__read_data[3U] 
        = vlTOPp->top_level__DOT__u_b_buffer__DOT__mem
        [vlTOPp->top_level__DOT____Vcellinp__u_b_buffer__read_addr
        [3U]];
    vlTOPp->top_level__DOT____Vcellout__u_a_buffer__read_data[0U] 
        = vlTOPp->top_level__DOT__u_a_buffer__DOT__mem
        [vlTOPp->top_level__DOT____Vcellinp__u_a_buffer__read_addr
        [0U]];
    vlTOPp->top_level__DOT____Vcellout__u_a_buffer__read_data[1U] 
        = vlTOPp->top_level__DOT__u_a_buffer__DOT__mem
        [vlTOPp->top_level__DOT____Vcellinp__u_a_buffer__read_addr
        [1U]];
    vlTOPp->top_level__DOT____Vcellout__u_a_buffer__read_data[2U] 
        = vlTOPp->top_level__DOT__u_a_buffer__DOT__mem
        [vlTOPp->top_level__DOT____Vcellinp__u_a_buffer__read_addr
        [2U]];
    vlTOPp->top_level__DOT____Vcellout__u_a_buffer__read_data[3U] 
        = vlTOPp->top_level__DOT__u_a_buffer__DOT__mem
        [vlTOPp->top_level__DOT____Vcellinp__u_a_buffer__read_addr
        [3U]];
    vlTOPp->top_level__DOT____Vcellout__u_a_buffer__read_data[4U] 
        = vlTOPp->top_level__DOT__u_a_buffer__DOT__mem
        [vlTOPp->top_level__DOT____Vcellinp__u_a_buffer__read_addr
        [4U]];
    vlTOPp->top_level__DOT____Vcellout__u_a_buffer__read_data[5U] 
        = vlTOPp->top_level__DOT__u_a_buffer__DOT__mem
        [vlTOPp->top_level__DOT____Vcellinp__u_a_buffer__read_addr
        [5U]];
    vlTOPp->top_level__DOT____Vcellout__u_a_buffer__read_data[6U] 
        = vlTOPp->top_level__DOT__u_a_buffer__DOT__mem
        [vlTOPp->top_level__DOT____Vcellinp__u_a_buffer__read_addr
        [6U]];
    vlTOPp->top_level__DOT____Vcellout__u_a_buffer__read_data[7U] 
        = vlTOPp->top_level__DOT__u_a_buffer__DOT__mem
        [vlTOPp->top_level__DOT____Vcellinp__u_a_buffer__read_addr
        [7U]];
    vlTOPp->top_level__DOT__b_col_data[0U] = vlTOPp->top_level__DOT____Vcellout__u_b_buffer__read_data
        [0U];
    vlTOPp->top_level__DOT__b_col_data[1U] = vlTOPp->top_level__DOT____Vcellout__u_b_buffer__read_data
        [1U];
    vlTOPp->top_level__DOT__b_col_data[2U] = vlTOPp->top_level__DOT____Vcellout__u_b_buffer__read_data
        [2U];
    vlTOPp->top_level__DOT__b_col_data[3U] = vlTOPp->top_level__DOT____Vcellout__u_b_buffer__read_data
        [3U];
    vlTOPp->top_level__DOT__a_row_data[0U] = vlTOPp->top_level__DOT____Vcellout__u_a_buffer__read_data
        [0U];
    vlTOPp->top_level__DOT__a_row_data[1U] = vlTOPp->top_level__DOT____Vcellout__u_a_buffer__read_data
        [1U];
    vlTOPp->top_level__DOT__a_row_data[2U] = vlTOPp->top_level__DOT____Vcellout__u_a_buffer__read_data
        [2U];
    vlTOPp->top_level__DOT__a_row_data[3U] = vlTOPp->top_level__DOT____Vcellout__u_a_buffer__read_data
        [3U];
    vlTOPp->top_level__DOT__a_row_data[4U] = vlTOPp->top_level__DOT____Vcellout__u_a_buffer__read_data
        [4U];
    vlTOPp->top_level__DOT__a_row_data[5U] = vlTOPp->top_level__DOT____Vcellout__u_a_buffer__read_data
        [5U];
    vlTOPp->top_level__DOT__a_row_data[6U] = vlTOPp->top_level__DOT____Vcellout__u_a_buffer__read_data
        [6U];
    vlTOPp->top_level__DOT__a_row_data[7U] = vlTOPp->top_level__DOT____Vcellout__u_a_buffer__read_data
        [7U];
    vlTOPp->top_level__DOT____Vcellinp__u_interconnect__b_col_data[0U] 
        = vlTOPp->top_level__DOT__b_col_data[0U];
    vlTOPp->top_level__DOT____Vcellinp__u_interconnect__b_col_data[1U] 
        = vlTOPp->top_level__DOT__b_col_data[1U];
    vlTOPp->top_level__DOT____Vcellinp__u_interconnect__b_col_data[2U] 
        = vlTOPp->top_level__DOT__b_col_data[2U];
    vlTOPp->top_level__DOT____Vcellinp__u_interconnect__b_col_data[3U] 
        = vlTOPp->top_level__DOT__b_col_data[3U];
    vlTOPp->top_level__DOT____Vcellinp__u_interconnect__a_row_data[0U] 
        = vlTOPp->top_level__DOT__a_row_data[0U];
    vlTOPp->top_level__DOT____Vcellinp__u_interconnect__a_row_data[1U] 
        = vlTOPp->top_level__DOT__a_row_data[1U];
    vlTOPp->top_level__DOT____Vcellinp__u_interconnect__a_row_data[2U] 
        = vlTOPp->top_level__DOT__a_row_data[2U];
    vlTOPp->top_level__DOT____Vcellinp__u_interconnect__a_row_data[3U] 
        = vlTOPp->top_level__DOT__a_row_data[3U];
    vlTOPp->top_level__DOT____Vcellinp__u_interconnect__a_row_data[4U] 
        = vlTOPp->top_level__DOT__a_row_data[4U];
    vlTOPp->top_level__DOT____Vcellinp__u_interconnect__a_row_data[5U] 
        = vlTOPp->top_level__DOT__a_row_data[5U];
    vlTOPp->top_level__DOT____Vcellinp__u_interconnect__a_row_data[6U] 
        = vlTOPp->top_level__DOT__a_row_data[6U];
    vlTOPp->top_level__DOT____Vcellinp__u_interconnect__a_row_data[7U] 
        = vlTOPp->top_level__DOT__a_row_data[7U];
    vlTOPp->top_level__DOT____Vcellout__u_interconnect__lane_b[0U] 
        = vlTOPp->top_level__DOT____Vcellinp__u_interconnect__b_col_data
        [0U];
    vlTOPp->top_level__DOT____Vcellout__u_interconnect__lane_b[1U] 
        = vlTOPp->top_level__DOT____Vcellinp__u_interconnect__b_col_data
        [1U];
    vlTOPp->top_level__DOT____Vcellout__u_interconnect__lane_b[2U] 
        = vlTOPp->top_level__DOT____Vcellinp__u_interconnect__b_col_data
        [2U];
    vlTOPp->top_level__DOT____Vcellout__u_interconnect__lane_b[3U] 
        = vlTOPp->top_level__DOT____Vcellinp__u_interconnect__b_col_data
        [3U];
    vlTOPp->top_level__DOT____Vcellout__u_interconnect__lane_b[4U] 
        = vlTOPp->top_level__DOT____Vcellinp__u_interconnect__b_col_data
        [0U];
    vlTOPp->top_level__DOT____Vcellout__u_interconnect__lane_b[5U] 
        = vlTOPp->top_level__DOT____Vcellinp__u_interconnect__b_col_data
        [1U];
    vlTOPp->top_level__DOT____Vcellout__u_interconnect__lane_b[6U] 
        = vlTOPp->top_level__DOT____Vcellinp__u_interconnect__b_col_data
        [2U];
    vlTOPp->top_level__DOT____Vcellout__u_interconnect__lane_b[7U] 
        = vlTOPp->top_level__DOT____Vcellinp__u_interconnect__b_col_data
        [3U];
    vlTOPp->top_level__DOT____Vcellout__u_interconnect__lane_b[8U] 
        = vlTOPp->top_level__DOT____Vcellinp__u_interconnect__b_col_data
        [0U];
    vlTOPp->top_level__DOT____Vcellout__u_interconnect__lane_b[9U] 
        = vlTOPp->top_level__DOT____Vcellinp__u_interconnect__b_col_data
        [1U];
    vlTOPp->top_level__DOT____Vcellout__u_interconnect__lane_b[0xaU] 
        = vlTOPp->top_level__DOT____Vcellinp__u_interconnect__b_col_data
        [2U];
    vlTOPp->top_level__DOT____Vcellout__u_interconnect__lane_b[0xbU] 
        = vlTOPp->top_level__DOT____Vcellinp__u_interconnect__b_col_data
        [3U];
    vlTOPp->top_level__DOT____Vcellout__u_interconnect__lane_b[0xcU] 
        = vlTOPp->top_level__DOT____Vcellinp__u_interconnect__b_col_data
        [0U];
    vlTOPp->top_level__DOT____Vcellout__u_interconnect__lane_b[0xdU] 
        = vlTOPp->top_level__DOT____Vcellinp__u_interconnect__b_col_data
        [1U];
    vlTOPp->top_level__DOT____Vcellout__u_interconnect__lane_b[0xeU] 
        = vlTOPp->top_level__DOT____Vcellinp__u_interconnect__b_col_data
        [2U];
    vlTOPp->top_level__DOT____Vcellout__u_interconnect__lane_b[0xfU] 
        = vlTOPp->top_level__DOT____Vcellinp__u_interconnect__b_col_data
        [3U];
    vlTOPp->top_level__DOT____Vcellout__u_interconnect__lane_b[0x10U] 
        = vlTOPp->top_level__DOT____Vcellinp__u_interconnect__b_col_data
        [0U];
    vlTOPp->top_level__DOT____Vcellout__u_interconnect__lane_b[0x11U] 
        = vlTOPp->top_level__DOT____Vcellinp__u_interconnect__b_col_data
        [1U];
    vlTOPp->top_level__DOT____Vcellout__u_interconnect__lane_b[0x12U] 
        = vlTOPp->top_level__DOT____Vcellinp__u_interconnect__b_col_data
        [2U];
    vlTOPp->top_level__DOT____Vcellout__u_interconnect__lane_b[0x13U] 
        = vlTOPp->top_level__DOT____Vcellinp__u_interconnect__b_col_data
        [3U];
    vlTOPp->top_level__DOT____Vcellout__u_interconnect__lane_b[0x14U] 
        = vlTOPp->top_level__DOT____Vcellinp__u_interconnect__b_col_data
        [0U];
    vlTOPp->top_level__DOT____Vcellout__u_interconnect__lane_b[0x15U] 
        = vlTOPp->top_level__DOT____Vcellinp__u_interconnect__b_col_data
        [1U];
    vlTOPp->top_level__DOT____Vcellout__u_interconnect__lane_b[0x16U] 
        = vlTOPp->top_level__DOT____Vcellinp__u_interconnect__b_col_data
        [2U];
    vlTOPp->top_level__DOT____Vcellout__u_interconnect__lane_b[0x17U] 
        = vlTOPp->top_level__DOT____Vcellinp__u_interconnect__b_col_data
        [3U];
    vlTOPp->top_level__DOT____Vcellout__u_interconnect__lane_b[0x18U] 
        = vlTOPp->top_level__DOT____Vcellinp__u_interconnect__b_col_data
        [0U];
    vlTOPp->top_level__DOT____Vcellout__u_interconnect__lane_b[0x19U] 
        = vlTOPp->top_level__DOT____Vcellinp__u_interconnect__b_col_data
        [1U];
    vlTOPp->top_level__DOT____Vcellout__u_interconnect__lane_b[0x1aU] 
        = vlTOPp->top_level__DOT____Vcellinp__u_interconnect__b_col_data
        [2U];
    vlTOPp->top_level__DOT____Vcellout__u_interconnect__lane_b[0x1bU] 
        = vlTOPp->top_level__DOT____Vcellinp__u_interconnect__b_col_data
        [3U];
    vlTOPp->top_level__DOT____Vcellout__u_interconnect__lane_b[0x1cU] 
        = vlTOPp->top_level__DOT____Vcellinp__u_interconnect__b_col_data
        [0U];
    vlTOPp->top_level__DOT____Vcellout__u_interconnect__lane_b[0x1dU] 
        = vlTOPp->top_level__DOT____Vcellinp__u_interconnect__b_col_data
        [1U];
    vlTOPp->top_level__DOT____Vcellout__u_interconnect__lane_b[0x1eU] 
        = vlTOPp->top_level__DOT____Vcellinp__u_interconnect__b_col_data
        [2U];
    vlTOPp->top_level__DOT____Vcellout__u_interconnect__lane_b[0x1fU] 
        = vlTOPp->top_level__DOT____Vcellinp__u_interconnect__b_col_data
        [3U];
    vlTOPp->top_level__DOT____Vcellout__u_interconnect__lane_a[0U] 
        = vlTOPp->top_level__DOT____Vcellinp__u_interconnect__a_row_data
        [0U];
    vlTOPp->top_level__DOT____Vcellout__u_interconnect__lane_a[1U] 
        = vlTOPp->top_level__DOT____Vcellinp__u_interconnect__a_row_data
        [0U];
    vlTOPp->top_level__DOT____Vcellout__u_interconnect__lane_a[2U] 
        = vlTOPp->top_level__DOT____Vcellinp__u_interconnect__a_row_data
        [0U];
    vlTOPp->top_level__DOT____Vcellout__u_interconnect__lane_a[3U] 
        = vlTOPp->top_level__DOT____Vcellinp__u_interconnect__a_row_data
        [0U];
    vlTOPp->top_level__DOT____Vcellout__u_interconnect__lane_a[4U] 
        = vlTOPp->top_level__DOT____Vcellinp__u_interconnect__a_row_data
        [1U];
    vlTOPp->top_level__DOT____Vcellout__u_interconnect__lane_a[5U] 
        = vlTOPp->top_level__DOT____Vcellinp__u_interconnect__a_row_data
        [1U];
    vlTOPp->top_level__DOT____Vcellout__u_interconnect__lane_a[6U] 
        = vlTOPp->top_level__DOT____Vcellinp__u_interconnect__a_row_data
        [1U];
    vlTOPp->top_level__DOT____Vcellout__u_interconnect__lane_a[7U] 
        = vlTOPp->top_level__DOT____Vcellinp__u_interconnect__a_row_data
        [1U];
    vlTOPp->top_level__DOT____Vcellout__u_interconnect__lane_a[8U] 
        = vlTOPp->top_level__DOT____Vcellinp__u_interconnect__a_row_data
        [2U];
    vlTOPp->top_level__DOT____Vcellout__u_interconnect__lane_a[9U] 
        = vlTOPp->top_level__DOT____Vcellinp__u_interconnect__a_row_data
        [2U];
    vlTOPp->top_level__DOT____Vcellout__u_interconnect__lane_a[0xaU] 
        = vlTOPp->top_level__DOT____Vcellinp__u_interconnect__a_row_data
        [2U];
    vlTOPp->top_level__DOT____Vcellout__u_interconnect__lane_a[0xbU] 
        = vlTOPp->top_level__DOT____Vcellinp__u_interconnect__a_row_data
        [2U];
    vlTOPp->top_level__DOT____Vcellout__u_interconnect__lane_a[0xcU] 
        = vlTOPp->top_level__DOT____Vcellinp__u_interconnect__a_row_data
        [3U];
    vlTOPp->top_level__DOT____Vcellout__u_interconnect__lane_a[0xdU] 
        = vlTOPp->top_level__DOT____Vcellinp__u_interconnect__a_row_data
        [3U];
    vlTOPp->top_level__DOT____Vcellout__u_interconnect__lane_a[0xeU] 
        = vlTOPp->top_level__DOT____Vcellinp__u_interconnect__a_row_data
        [3U];
    vlTOPp->top_level__DOT____Vcellout__u_interconnect__lane_a[0xfU] 
        = vlTOPp->top_level__DOT____Vcellinp__u_interconnect__a_row_data
        [3U];
    vlTOPp->top_level__DOT____Vcellout__u_interconnect__lane_a[0x10U] 
        = vlTOPp->top_level__DOT____Vcellinp__u_interconnect__a_row_data
        [4U];
    vlTOPp->top_level__DOT____Vcellout__u_interconnect__lane_a[0x11U] 
        = vlTOPp->top_level__DOT____Vcellinp__u_interconnect__a_row_data
        [4U];
    vlTOPp->top_level__DOT____Vcellout__u_interconnect__lane_a[0x12U] 
        = vlTOPp->top_level__DOT____Vcellinp__u_interconnect__a_row_data
        [4U];
    vlTOPp->top_level__DOT____Vcellout__u_interconnect__lane_a[0x13U] 
        = vlTOPp->top_level__DOT____Vcellinp__u_interconnect__a_row_data
        [4U];
    vlTOPp->top_level__DOT____Vcellout__u_interconnect__lane_a[0x14U] 
        = vlTOPp->top_level__DOT____Vcellinp__u_interconnect__a_row_data
        [5U];
    vlTOPp->top_level__DOT____Vcellout__u_interconnect__lane_a[0x15U] 
        = vlTOPp->top_level__DOT____Vcellinp__u_interconnect__a_row_data
        [5U];
    vlTOPp->top_level__DOT____Vcellout__u_interconnect__lane_a[0x16U] 
        = vlTOPp->top_level__DOT____Vcellinp__u_interconnect__a_row_data
        [5U];
    vlTOPp->top_level__DOT____Vcellout__u_interconnect__lane_a[0x17U] 
        = vlTOPp->top_level__DOT____Vcellinp__u_interconnect__a_row_data
        [5U];
    vlTOPp->top_level__DOT____Vcellout__u_interconnect__lane_a[0x18U] 
        = vlTOPp->top_level__DOT____Vcellinp__u_interconnect__a_row_data
        [6U];
    vlTOPp->top_level__DOT____Vcellout__u_interconnect__lane_a[0x19U] 
        = vlTOPp->top_level__DOT____Vcellinp__u_interconnect__a_row_data
        [6U];
    vlTOPp->top_level__DOT____Vcellout__u_interconnect__lane_a[0x1aU] 
        = vlTOPp->top_level__DOT____Vcellinp__u_interconnect__a_row_data
        [6U];
    vlTOPp->top_level__DOT____Vcellout__u_interconnect__lane_a[0x1bU] 
        = vlTOPp->top_level__DOT____Vcellinp__u_interconnect__a_row_data
        [6U];
    vlTOPp->top_level__DOT____Vcellout__u_interconnect__lane_a[0x1cU] 
        = vlTOPp->top_level__DOT____Vcellinp__u_interconnect__a_row_data
        [7U];
    vlTOPp->top_level__DOT____Vcellout__u_interconnect__lane_a[0x1dU] 
        = vlTOPp->top_level__DOT____Vcellinp__u_interconnect__a_row_data
        [7U];
    vlTOPp->top_level__DOT____Vcellout__u_interconnect__lane_a[0x1eU] 
        = vlTOPp->top_level__DOT____Vcellinp__u_interconnect__a_row_data
        [7U];
    vlTOPp->top_level__DOT____Vcellout__u_interconnect__lane_a[0x1fU] 
        = vlTOPp->top_level__DOT____Vcellinp__u_interconnect__a_row_data
        [7U];
    vlTOPp->top_level__DOT__lane_b[0U] = vlTOPp->top_level__DOT____Vcellout__u_interconnect__lane_b
        [0U];
    vlTOPp->top_level__DOT__lane_b[1U] = vlTOPp->top_level__DOT____Vcellout__u_interconnect__lane_b
        [1U];
    vlTOPp->top_level__DOT__lane_b[2U] = vlTOPp->top_level__DOT____Vcellout__u_interconnect__lane_b
        [2U];
    vlTOPp->top_level__DOT__lane_b[3U] = vlTOPp->top_level__DOT____Vcellout__u_interconnect__lane_b
        [3U];
    vlTOPp->top_level__DOT__lane_b[4U] = vlTOPp->top_level__DOT____Vcellout__u_interconnect__lane_b
        [4U];
    vlTOPp->top_level__DOT__lane_b[5U] = vlTOPp->top_level__DOT____Vcellout__u_interconnect__lane_b
        [5U];
    vlTOPp->top_level__DOT__lane_b[6U] = vlTOPp->top_level__DOT____Vcellout__u_interconnect__lane_b
        [6U];
    vlTOPp->top_level__DOT__lane_b[7U] = vlTOPp->top_level__DOT____Vcellout__u_interconnect__lane_b
        [7U];
    vlTOPp->top_level__DOT__lane_b[8U] = vlTOPp->top_level__DOT____Vcellout__u_interconnect__lane_b
        [8U];
    vlTOPp->top_level__DOT__lane_b[9U] = vlTOPp->top_level__DOT____Vcellout__u_interconnect__lane_b
        [9U];
    vlTOPp->top_level__DOT__lane_b[0xaU] = vlTOPp->top_level__DOT____Vcellout__u_interconnect__lane_b
        [0xaU];
    vlTOPp->top_level__DOT__lane_b[0xbU] = vlTOPp->top_level__DOT____Vcellout__u_interconnect__lane_b
        [0xbU];
    vlTOPp->top_level__DOT__lane_b[0xcU] = vlTOPp->top_level__DOT____Vcellout__u_interconnect__lane_b
        [0xcU];
    vlTOPp->top_level__DOT__lane_b[0xdU] = vlTOPp->top_level__DOT____Vcellout__u_interconnect__lane_b
        [0xdU];
    vlTOPp->top_level__DOT__lane_b[0xeU] = vlTOPp->top_level__DOT____Vcellout__u_interconnect__lane_b
        [0xeU];
    vlTOPp->top_level__DOT__lane_b[0xfU] = vlTOPp->top_level__DOT____Vcellout__u_interconnect__lane_b
        [0xfU];
    vlTOPp->top_level__DOT__lane_b[0x10U] = vlTOPp->top_level__DOT____Vcellout__u_interconnect__lane_b
        [0x10U];
    vlTOPp->top_level__DOT__lane_b[0x11U] = vlTOPp->top_level__DOT____Vcellout__u_interconnect__lane_b
        [0x11U];
    vlTOPp->top_level__DOT__lane_b[0x12U] = vlTOPp->top_level__DOT____Vcellout__u_interconnect__lane_b
        [0x12U];
    vlTOPp->top_level__DOT__lane_b[0x13U] = vlTOPp->top_level__DOT____Vcellout__u_interconnect__lane_b
        [0x13U];
    vlTOPp->top_level__DOT__lane_b[0x14U] = vlTOPp->top_level__DOT____Vcellout__u_interconnect__lane_b
        [0x14U];
    vlTOPp->top_level__DOT__lane_b[0x15U] = vlTOPp->top_level__DOT____Vcellout__u_interconnect__lane_b
        [0x15U];
    vlTOPp->top_level__DOT__lane_b[0x16U] = vlTOPp->top_level__DOT____Vcellout__u_interconnect__lane_b
        [0x16U];
    vlTOPp->top_level__DOT__lane_b[0x17U] = vlTOPp->top_level__DOT____Vcellout__u_interconnect__lane_b
        [0x17U];
    vlTOPp->top_level__DOT__lane_b[0x18U] = vlTOPp->top_level__DOT____Vcellout__u_interconnect__lane_b
        [0x18U];
    vlTOPp->top_level__DOT__lane_b[0x19U] = vlTOPp->top_level__DOT____Vcellout__u_interconnect__lane_b
        [0x19U];
    vlTOPp->top_level__DOT__lane_b[0x1aU] = vlTOPp->top_level__DOT____Vcellout__u_interconnect__lane_b
        [0x1aU];
    vlTOPp->top_level__DOT__lane_b[0x1bU] = vlTOPp->top_level__DOT____Vcellout__u_interconnect__lane_b
        [0x1bU];
    vlTOPp->top_level__DOT__lane_b[0x1cU] = vlTOPp->top_level__DOT____Vcellout__u_interconnect__lane_b
        [0x1cU];
    vlTOPp->top_level__DOT__lane_b[0x1dU] = vlTOPp->top_level__DOT____Vcellout__u_interconnect__lane_b
        [0x1dU];
    vlTOPp->top_level__DOT__lane_b[0x1eU] = vlTOPp->top_level__DOT____Vcellout__u_interconnect__lane_b
        [0x1eU];
    vlTOPp->top_level__DOT__lane_b[0x1fU] = vlTOPp->top_level__DOT____Vcellout__u_interconnect__lane_b
        [0x1fU];
    vlTOPp->top_level__DOT__lane_a[0U] = vlTOPp->top_level__DOT____Vcellout__u_interconnect__lane_a
        [0U];
    vlTOPp->top_level__DOT__lane_a[1U] = vlTOPp->top_level__DOT____Vcellout__u_interconnect__lane_a
        [1U];
    vlTOPp->top_level__DOT__lane_a[2U] = vlTOPp->top_level__DOT____Vcellout__u_interconnect__lane_a
        [2U];
    vlTOPp->top_level__DOT__lane_a[3U] = vlTOPp->top_level__DOT____Vcellout__u_interconnect__lane_a
        [3U];
    vlTOPp->top_level__DOT__lane_a[4U] = vlTOPp->top_level__DOT____Vcellout__u_interconnect__lane_a
        [4U];
    vlTOPp->top_level__DOT__lane_a[5U] = vlTOPp->top_level__DOT____Vcellout__u_interconnect__lane_a
        [5U];
    vlTOPp->top_level__DOT__lane_a[6U] = vlTOPp->top_level__DOT____Vcellout__u_interconnect__lane_a
        [6U];
    vlTOPp->top_level__DOT__lane_a[7U] = vlTOPp->top_level__DOT____Vcellout__u_interconnect__lane_a
        [7U];
    vlTOPp->top_level__DOT__lane_a[8U] = vlTOPp->top_level__DOT____Vcellout__u_interconnect__lane_a
        [8U];
    vlTOPp->top_level__DOT__lane_a[9U] = vlTOPp->top_level__DOT____Vcellout__u_interconnect__lane_a
        [9U];
    vlTOPp->top_level__DOT__lane_a[0xaU] = vlTOPp->top_level__DOT____Vcellout__u_interconnect__lane_a
        [0xaU];
    vlTOPp->top_level__DOT__lane_a[0xbU] = vlTOPp->top_level__DOT____Vcellout__u_interconnect__lane_a
        [0xbU];
    vlTOPp->top_level__DOT__lane_a[0xcU] = vlTOPp->top_level__DOT____Vcellout__u_interconnect__lane_a
        [0xcU];
    vlTOPp->top_level__DOT__lane_a[0xdU] = vlTOPp->top_level__DOT____Vcellout__u_interconnect__lane_a
        [0xdU];
    vlTOPp->top_level__DOT__lane_a[0xeU] = vlTOPp->top_level__DOT____Vcellout__u_interconnect__lane_a
        [0xeU];
    vlTOPp->top_level__DOT__lane_a[0xfU] = vlTOPp->top_level__DOT____Vcellout__u_interconnect__lane_a
        [0xfU];
    vlTOPp->top_level__DOT__lane_a[0x10U] = vlTOPp->top_level__DOT____Vcellout__u_interconnect__lane_a
        [0x10U];
    vlTOPp->top_level__DOT__lane_a[0x11U] = vlTOPp->top_level__DOT____Vcellout__u_interconnect__lane_a
        [0x11U];
    vlTOPp->top_level__DOT__lane_a[0x12U] = vlTOPp->top_level__DOT____Vcellout__u_interconnect__lane_a
        [0x12U];
    vlTOPp->top_level__DOT__lane_a[0x13U] = vlTOPp->top_level__DOT____Vcellout__u_interconnect__lane_a
        [0x13U];
    vlTOPp->top_level__DOT__lane_a[0x14U] = vlTOPp->top_level__DOT____Vcellout__u_interconnect__lane_a
        [0x14U];
    vlTOPp->top_level__DOT__lane_a[0x15U] = vlTOPp->top_level__DOT____Vcellout__u_interconnect__lane_a
        [0x15U];
    vlTOPp->top_level__DOT__lane_a[0x16U] = vlTOPp->top_level__DOT____Vcellout__u_interconnect__lane_a
        [0x16U];
    vlTOPp->top_level__DOT__lane_a[0x17U] = vlTOPp->top_level__DOT____Vcellout__u_interconnect__lane_a
        [0x17U];
    vlTOPp->top_level__DOT__lane_a[0x18U] = vlTOPp->top_level__DOT____Vcellout__u_interconnect__lane_a
        [0x18U];
    vlTOPp->top_level__DOT__lane_a[0x19U] = vlTOPp->top_level__DOT____Vcellout__u_interconnect__lane_a
        [0x19U];
    vlTOPp->top_level__DOT__lane_a[0x1aU] = vlTOPp->top_level__DOT____Vcellout__u_interconnect__lane_a
        [0x1aU];
    vlTOPp->top_level__DOT__lane_a[0x1bU] = vlTOPp->top_level__DOT____Vcellout__u_interconnect__lane_a
        [0x1bU];
    vlTOPp->top_level__DOT__lane_a[0x1cU] = vlTOPp->top_level__DOT____Vcellout__u_interconnect__lane_a
        [0x1cU];
    vlTOPp->top_level__DOT__lane_a[0x1dU] = vlTOPp->top_level__DOT____Vcellout__u_interconnect__lane_a
        [0x1dU];
    vlTOPp->top_level__DOT__lane_a[0x1eU] = vlTOPp->top_level__DOT____Vcellout__u_interconnect__lane_a
        [0x1eU];
    vlTOPp->top_level__DOT__lane_a[0x1fU] = vlTOPp->top_level__DOT____Vcellout__u_interconnect__lane_a
        [0x1fU];
    vlTOPp->top_level__DOT__gen_clusters__BRA__0__KET____DOT__cluster_lane_b[0U] 
        = vlTOPp->top_level__DOT__lane_b[0U];
    vlTOPp->top_level__DOT__gen_clusters__BRA__0__KET____DOT__cluster_lane_b[1U] 
        = vlTOPp->top_level__DOT__lane_b[1U];
    vlTOPp->top_level__DOT__gen_clusters__BRA__0__KET____DOT__cluster_lane_b[2U] 
        = vlTOPp->top_level__DOT__lane_b[2U];
    vlTOPp->top_level__DOT__gen_clusters__BRA__0__KET____DOT__cluster_lane_b[3U] 
        = vlTOPp->top_level__DOT__lane_b[3U];
    vlTOPp->top_level__DOT__gen_clusters__BRA__1__KET____DOT__cluster_lane_b[0U] 
        = vlTOPp->top_level__DOT__lane_b[4U];
    vlTOPp->top_level__DOT__gen_clusters__BRA__1__KET____DOT__cluster_lane_b[1U] 
        = vlTOPp->top_level__DOT__lane_b[5U];
    vlTOPp->top_level__DOT__gen_clusters__BRA__1__KET____DOT__cluster_lane_b[2U] 
        = vlTOPp->top_level__DOT__lane_b[6U];
    vlTOPp->top_level__DOT__gen_clusters__BRA__1__KET____DOT__cluster_lane_b[3U] 
        = vlTOPp->top_level__DOT__lane_b[7U];
    vlTOPp->top_level__DOT__gen_clusters__BRA__2__KET____DOT__cluster_lane_b[0U] 
        = vlTOPp->top_level__DOT__lane_b[8U];
    vlTOPp->top_level__DOT__gen_clusters__BRA__2__KET____DOT__cluster_lane_b[1U] 
        = vlTOPp->top_level__DOT__lane_b[9U];
    vlTOPp->top_level__DOT__gen_clusters__BRA__2__KET____DOT__cluster_lane_b[2U] 
        = vlTOPp->top_level__DOT__lane_b[0xaU];
    vlTOPp->top_level__DOT__gen_clusters__BRA__2__KET____DOT__cluster_lane_b[3U] 
        = vlTOPp->top_level__DOT__lane_b[0xbU];
    vlTOPp->top_level__DOT__gen_clusters__BRA__3__KET____DOT__cluster_lane_b[0U] 
        = vlTOPp->top_level__DOT__lane_b[0xcU];
    vlTOPp->top_level__DOT__gen_clusters__BRA__3__KET____DOT__cluster_lane_b[1U] 
        = vlTOPp->top_level__DOT__lane_b[0xdU];
    vlTOPp->top_level__DOT__gen_clusters__BRA__3__KET____DOT__cluster_lane_b[2U] 
        = vlTOPp->top_level__DOT__lane_b[0xeU];
    vlTOPp->top_level__DOT__gen_clusters__BRA__3__KET____DOT__cluster_lane_b[3U] 
        = vlTOPp->top_level__DOT__lane_b[0xfU];
    vlTOPp->top_level__DOT__gen_clusters__BRA__4__KET____DOT__cluster_lane_b[0U] 
        = vlTOPp->top_level__DOT__lane_b[0x10U];
    vlTOPp->top_level__DOT__gen_clusters__BRA__4__KET____DOT__cluster_lane_b[1U] 
        = vlTOPp->top_level__DOT__lane_b[0x11U];
    vlTOPp->top_level__DOT__gen_clusters__BRA__4__KET____DOT__cluster_lane_b[2U] 
        = vlTOPp->top_level__DOT__lane_b[0x12U];
    vlTOPp->top_level__DOT__gen_clusters__BRA__4__KET____DOT__cluster_lane_b[3U] 
        = vlTOPp->top_level__DOT__lane_b[0x13U];
    vlTOPp->top_level__DOT__gen_clusters__BRA__5__KET____DOT__cluster_lane_b[0U] 
        = vlTOPp->top_level__DOT__lane_b[0x14U];
    vlTOPp->top_level__DOT__gen_clusters__BRA__5__KET____DOT__cluster_lane_b[1U] 
        = vlTOPp->top_level__DOT__lane_b[0x15U];
    vlTOPp->top_level__DOT__gen_clusters__BRA__5__KET____DOT__cluster_lane_b[2U] 
        = vlTOPp->top_level__DOT__lane_b[0x16U];
    vlTOPp->top_level__DOT__gen_clusters__BRA__5__KET____DOT__cluster_lane_b[3U] 
        = vlTOPp->top_level__DOT__lane_b[0x17U];
    vlTOPp->top_level__DOT__gen_clusters__BRA__6__KET____DOT__cluster_lane_b[0U] 
        = vlTOPp->top_level__DOT__lane_b[0x18U];
    vlTOPp->top_level__DOT__gen_clusters__BRA__6__KET____DOT__cluster_lane_b[1U] 
        = vlTOPp->top_level__DOT__lane_b[0x19U];
    vlTOPp->top_level__DOT__gen_clusters__BRA__6__KET____DOT__cluster_lane_b[2U] 
        = vlTOPp->top_level__DOT__lane_b[0x1aU];
    vlTOPp->top_level__DOT__gen_clusters__BRA__6__KET____DOT__cluster_lane_b[3U] 
        = vlTOPp->top_level__DOT__lane_b[0x1bU];
    vlTOPp->top_level__DOT__gen_clusters__BRA__7__KET____DOT__cluster_lane_b[0U] 
        = vlTOPp->top_level__DOT__lane_b[0x1cU];
    vlTOPp->top_level__DOT__gen_clusters__BRA__7__KET____DOT__cluster_lane_b[1U] 
        = vlTOPp->top_level__DOT__lane_b[0x1dU];
    vlTOPp->top_level__DOT__gen_clusters__BRA__7__KET____DOT__cluster_lane_b[2U] 
        = vlTOPp->top_level__DOT__lane_b[0x1eU];
    vlTOPp->top_level__DOT__gen_clusters__BRA__7__KET____DOT__cluster_lane_b[3U] 
        = vlTOPp->top_level__DOT__lane_b[0x1fU];
    vlTOPp->top_level__DOT__gen_clusters__BRA__0__KET____DOT__cluster_lane_a[0U] 
        = vlTOPp->top_level__DOT__lane_a[0U];
    vlTOPp->top_level__DOT__gen_clusters__BRA__0__KET____DOT__cluster_lane_a[1U] 
        = vlTOPp->top_level__DOT__lane_a[1U];
    vlTOPp->top_level__DOT__gen_clusters__BRA__0__KET____DOT__cluster_lane_a[2U] 
        = vlTOPp->top_level__DOT__lane_a[2U];
    vlTOPp->top_level__DOT__gen_clusters__BRA__0__KET____DOT__cluster_lane_a[3U] 
        = vlTOPp->top_level__DOT__lane_a[3U];
    vlTOPp->top_level__DOT__gen_clusters__BRA__1__KET____DOT__cluster_lane_a[0U] 
        = vlTOPp->top_level__DOT__lane_a[4U];
    vlTOPp->top_level__DOT__gen_clusters__BRA__1__KET____DOT__cluster_lane_a[1U] 
        = vlTOPp->top_level__DOT__lane_a[5U];
    vlTOPp->top_level__DOT__gen_clusters__BRA__1__KET____DOT__cluster_lane_a[2U] 
        = vlTOPp->top_level__DOT__lane_a[6U];
    vlTOPp->top_level__DOT__gen_clusters__BRA__1__KET____DOT__cluster_lane_a[3U] 
        = vlTOPp->top_level__DOT__lane_a[7U];
    vlTOPp->top_level__DOT__gen_clusters__BRA__2__KET____DOT__cluster_lane_a[0U] 
        = vlTOPp->top_level__DOT__lane_a[8U];
    vlTOPp->top_level__DOT__gen_clusters__BRA__2__KET____DOT__cluster_lane_a[1U] 
        = vlTOPp->top_level__DOT__lane_a[9U];
    vlTOPp->top_level__DOT__gen_clusters__BRA__2__KET____DOT__cluster_lane_a[2U] 
        = vlTOPp->top_level__DOT__lane_a[0xaU];
    vlTOPp->top_level__DOT__gen_clusters__BRA__2__KET____DOT__cluster_lane_a[3U] 
        = vlTOPp->top_level__DOT__lane_a[0xbU];
    vlTOPp->top_level__DOT__gen_clusters__BRA__3__KET____DOT__cluster_lane_a[0U] 
        = vlTOPp->top_level__DOT__lane_a[0xcU];
    vlTOPp->top_level__DOT__gen_clusters__BRA__3__KET____DOT__cluster_lane_a[1U] 
        = vlTOPp->top_level__DOT__lane_a[0xdU];
    vlTOPp->top_level__DOT__gen_clusters__BRA__3__KET____DOT__cluster_lane_a[2U] 
        = vlTOPp->top_level__DOT__lane_a[0xeU];
    vlTOPp->top_level__DOT__gen_clusters__BRA__3__KET____DOT__cluster_lane_a[3U] 
        = vlTOPp->top_level__DOT__lane_a[0xfU];
    vlTOPp->top_level__DOT__gen_clusters__BRA__4__KET____DOT__cluster_lane_a[0U] 
        = vlTOPp->top_level__DOT__lane_a[0x10U];
    vlTOPp->top_level__DOT__gen_clusters__BRA__4__KET____DOT__cluster_lane_a[1U] 
        = vlTOPp->top_level__DOT__lane_a[0x11U];
    vlTOPp->top_level__DOT__gen_clusters__BRA__4__KET____DOT__cluster_lane_a[2U] 
        = vlTOPp->top_level__DOT__lane_a[0x12U];
    vlTOPp->top_level__DOT__gen_clusters__BRA__4__KET____DOT__cluster_lane_a[3U] 
        = vlTOPp->top_level__DOT__lane_a[0x13U];
    vlTOPp->top_level__DOT__gen_clusters__BRA__5__KET____DOT__cluster_lane_a[0U] 
        = vlTOPp->top_level__DOT__lane_a[0x14U];
    vlTOPp->top_level__DOT__gen_clusters__BRA__5__KET____DOT__cluster_lane_a[1U] 
        = vlTOPp->top_level__DOT__lane_a[0x15U];
    vlTOPp->top_level__DOT__gen_clusters__BRA__5__KET____DOT__cluster_lane_a[2U] 
        = vlTOPp->top_level__DOT__lane_a[0x16U];
    vlTOPp->top_level__DOT__gen_clusters__BRA__5__KET____DOT__cluster_lane_a[3U] 
        = vlTOPp->top_level__DOT__lane_a[0x17U];
    vlTOPp->top_level__DOT__gen_clusters__BRA__6__KET____DOT__cluster_lane_a[0U] 
        = vlTOPp->top_level__DOT__lane_a[0x18U];
    vlTOPp->top_level__DOT__gen_clusters__BRA__6__KET____DOT__cluster_lane_a[1U] 
        = vlTOPp->top_level__DOT__lane_a[0x19U];
    vlTOPp->top_level__DOT__gen_clusters__BRA__6__KET____DOT__cluster_lane_a[2U] 
        = vlTOPp->top_level__DOT__lane_a[0x1aU];
    vlTOPp->top_level__DOT__gen_clusters__BRA__6__KET____DOT__cluster_lane_a[3U] 
        = vlTOPp->top_level__DOT__lane_a[0x1bU];
    vlTOPp->top_level__DOT__gen_clusters__BRA__7__KET____DOT__cluster_lane_a[0U] 
        = vlTOPp->top_level__DOT__lane_a[0x1cU];
    vlTOPp->top_level__DOT__gen_clusters__BRA__7__KET____DOT__cluster_lane_a[1U] 
        = vlTOPp->top_level__DOT__lane_a[0x1dU];
    vlTOPp->top_level__DOT__gen_clusters__BRA__7__KET____DOT__cluster_lane_a[2U] 
        = vlTOPp->top_level__DOT__lane_a[0x1eU];
    vlTOPp->top_level__DOT__gen_clusters__BRA__7__KET____DOT__cluster_lane_a[3U] 
        = vlTOPp->top_level__DOT__lane_a[0x1fU];
    vlTOPp->top_level__DOT____Vcellinp__gen_clusters__BRA__0__KET____DOT__u_cluster__lane_b[0U] 
        = vlTOPp->top_level__DOT__gen_clusters__BRA__0__KET____DOT__cluster_lane_b
        [0U];
    vlTOPp->top_level__DOT____Vcellinp__gen_clusters__BRA__0__KET____DOT__u_cluster__lane_b[1U] 
        = vlTOPp->top_level__DOT__gen_clusters__BRA__0__KET____DOT__cluster_lane_b
        [1U];
    vlTOPp->top_level__DOT____Vcellinp__gen_clusters__BRA__0__KET____DOT__u_cluster__lane_b[2U] 
        = vlTOPp->top_level__DOT__gen_clusters__BRA__0__KET____DOT__cluster_lane_b
        [2U];
    vlTOPp->top_level__DOT____Vcellinp__gen_clusters__BRA__0__KET____DOT__u_cluster__lane_b[3U] 
        = vlTOPp->top_level__DOT__gen_clusters__BRA__0__KET____DOT__cluster_lane_b
        [3U];
    vlTOPp->top_level__DOT____Vcellinp__gen_clusters__BRA__1__KET____DOT__u_cluster__lane_b[0U] 
        = vlTOPp->top_level__DOT__gen_clusters__BRA__1__KET____DOT__cluster_lane_b
        [0U];
    vlTOPp->top_level__DOT____Vcellinp__gen_clusters__BRA__1__KET____DOT__u_cluster__lane_b[1U] 
        = vlTOPp->top_level__DOT__gen_clusters__BRA__1__KET____DOT__cluster_lane_b
        [1U];
    vlTOPp->top_level__DOT____Vcellinp__gen_clusters__BRA__1__KET____DOT__u_cluster__lane_b[2U] 
        = vlTOPp->top_level__DOT__gen_clusters__BRA__1__KET____DOT__cluster_lane_b
        [2U];
    vlTOPp->top_level__DOT____Vcellinp__gen_clusters__BRA__1__KET____DOT__u_cluster__lane_b[3U] 
        = vlTOPp->top_level__DOT__gen_clusters__BRA__1__KET____DOT__cluster_lane_b
        [3U];
    vlTOPp->top_level__DOT____Vcellinp__gen_clusters__BRA__2__KET____DOT__u_cluster__lane_b[0U] 
        = vlTOPp->top_level__DOT__gen_clusters__BRA__2__KET____DOT__cluster_lane_b
        [0U];
    vlTOPp->top_level__DOT____Vcellinp__gen_clusters__BRA__2__KET____DOT__u_cluster__lane_b[1U] 
        = vlTOPp->top_level__DOT__gen_clusters__BRA__2__KET____DOT__cluster_lane_b
        [1U];
    vlTOPp->top_level__DOT____Vcellinp__gen_clusters__BRA__2__KET____DOT__u_cluster__lane_b[2U] 
        = vlTOPp->top_level__DOT__gen_clusters__BRA__2__KET____DOT__cluster_lane_b
        [2U];
    vlTOPp->top_level__DOT____Vcellinp__gen_clusters__BRA__2__KET____DOT__u_cluster__lane_b[3U] 
        = vlTOPp->top_level__DOT__gen_clusters__BRA__2__KET____DOT__cluster_lane_b
        [3U];
    vlTOPp->top_level__DOT____Vcellinp__gen_clusters__BRA__3__KET____DOT__u_cluster__lane_b[0U] 
        = vlTOPp->top_level__DOT__gen_clusters__BRA__3__KET____DOT__cluster_lane_b
        [0U];
    vlTOPp->top_level__DOT____Vcellinp__gen_clusters__BRA__3__KET____DOT__u_cluster__lane_b[1U] 
        = vlTOPp->top_level__DOT__gen_clusters__BRA__3__KET____DOT__cluster_lane_b
        [1U];
    vlTOPp->top_level__DOT____Vcellinp__gen_clusters__BRA__3__KET____DOT__u_cluster__lane_b[2U] 
        = vlTOPp->top_level__DOT__gen_clusters__BRA__3__KET____DOT__cluster_lane_b
        [2U];
    vlTOPp->top_level__DOT____Vcellinp__gen_clusters__BRA__3__KET____DOT__u_cluster__lane_b[3U] 
        = vlTOPp->top_level__DOT__gen_clusters__BRA__3__KET____DOT__cluster_lane_b
        [3U];
    vlTOPp->top_level__DOT____Vcellinp__gen_clusters__BRA__4__KET____DOT__u_cluster__lane_b[0U] 
        = vlTOPp->top_level__DOT__gen_clusters__BRA__4__KET____DOT__cluster_lane_b
        [0U];
    vlTOPp->top_level__DOT____Vcellinp__gen_clusters__BRA__4__KET____DOT__u_cluster__lane_b[1U] 
        = vlTOPp->top_level__DOT__gen_clusters__BRA__4__KET____DOT__cluster_lane_b
        [1U];
    vlTOPp->top_level__DOT____Vcellinp__gen_clusters__BRA__4__KET____DOT__u_cluster__lane_b[2U] 
        = vlTOPp->top_level__DOT__gen_clusters__BRA__4__KET____DOT__cluster_lane_b
        [2U];
    vlTOPp->top_level__DOT____Vcellinp__gen_clusters__BRA__4__KET____DOT__u_cluster__lane_b[3U] 
        = vlTOPp->top_level__DOT__gen_clusters__BRA__4__KET____DOT__cluster_lane_b
        [3U];
    vlTOPp->top_level__DOT____Vcellinp__gen_clusters__BRA__5__KET____DOT__u_cluster__lane_b[0U] 
        = vlTOPp->top_level__DOT__gen_clusters__BRA__5__KET____DOT__cluster_lane_b
        [0U];
    vlTOPp->top_level__DOT____Vcellinp__gen_clusters__BRA__5__KET____DOT__u_cluster__lane_b[1U] 
        = vlTOPp->top_level__DOT__gen_clusters__BRA__5__KET____DOT__cluster_lane_b
        [1U];
    vlTOPp->top_level__DOT____Vcellinp__gen_clusters__BRA__5__KET____DOT__u_cluster__lane_b[2U] 
        = vlTOPp->top_level__DOT__gen_clusters__BRA__5__KET____DOT__cluster_lane_b
        [2U];
    vlTOPp->top_level__DOT____Vcellinp__gen_clusters__BRA__5__KET____DOT__u_cluster__lane_b[3U] 
        = vlTOPp->top_level__DOT__gen_clusters__BRA__5__KET____DOT__cluster_lane_b
        [3U];
    vlTOPp->top_level__DOT____Vcellinp__gen_clusters__BRA__6__KET____DOT__u_cluster__lane_b[0U] 
        = vlTOPp->top_level__DOT__gen_clusters__BRA__6__KET____DOT__cluster_lane_b
        [0U];
    vlTOPp->top_level__DOT____Vcellinp__gen_clusters__BRA__6__KET____DOT__u_cluster__lane_b[1U] 
        = vlTOPp->top_level__DOT__gen_clusters__BRA__6__KET____DOT__cluster_lane_b
        [1U];
    vlTOPp->top_level__DOT____Vcellinp__gen_clusters__BRA__6__KET____DOT__u_cluster__lane_b[2U] 
        = vlTOPp->top_level__DOT__gen_clusters__BRA__6__KET____DOT__cluster_lane_b
        [2U];
    vlTOPp->top_level__DOT____Vcellinp__gen_clusters__BRA__6__KET____DOT__u_cluster__lane_b[3U] 
        = vlTOPp->top_level__DOT__gen_clusters__BRA__6__KET____DOT__cluster_lane_b
        [3U];
    vlTOPp->top_level__DOT____Vcellinp__gen_clusters__BRA__7__KET____DOT__u_cluster__lane_b[0U] 
        = vlTOPp->top_level__DOT__gen_clusters__BRA__7__KET____DOT__cluster_lane_b
        [0U];
    vlTOPp->top_level__DOT____Vcellinp__gen_clusters__BRA__7__KET____DOT__u_cluster__lane_b[1U] 
        = vlTOPp->top_level__DOT__gen_clusters__BRA__7__KET____DOT__cluster_lane_b
        [1U];
    vlTOPp->top_level__DOT____Vcellinp__gen_clusters__BRA__7__KET____DOT__u_cluster__lane_b[2U] 
        = vlTOPp->top_level__DOT__gen_clusters__BRA__7__KET____DOT__cluster_lane_b
        [2U];
    vlTOPp->top_level__DOT____Vcellinp__gen_clusters__BRA__7__KET____DOT__u_cluster__lane_b[3U] 
        = vlTOPp->top_level__DOT__gen_clusters__BRA__7__KET____DOT__cluster_lane_b
        [3U];
    vlTOPp->top_level__DOT____Vcellinp__gen_clusters__BRA__0__KET____DOT__u_cluster__lane_a[0U] 
        = vlTOPp->top_level__DOT__gen_clusters__BRA__0__KET____DOT__cluster_lane_a
        [0U];
    vlTOPp->top_level__DOT____Vcellinp__gen_clusters__BRA__0__KET____DOT__u_cluster__lane_a[1U] 
        = vlTOPp->top_level__DOT__gen_clusters__BRA__0__KET____DOT__cluster_lane_a
        [1U];
    vlTOPp->top_level__DOT____Vcellinp__gen_clusters__BRA__0__KET____DOT__u_cluster__lane_a[2U] 
        = vlTOPp->top_level__DOT__gen_clusters__BRA__0__KET____DOT__cluster_lane_a
        [2U];
    vlTOPp->top_level__DOT____Vcellinp__gen_clusters__BRA__0__KET____DOT__u_cluster__lane_a[3U] 
        = vlTOPp->top_level__DOT__gen_clusters__BRA__0__KET____DOT__cluster_lane_a
        [3U];
    vlTOPp->top_level__DOT____Vcellinp__gen_clusters__BRA__1__KET____DOT__u_cluster__lane_a[0U] 
        = vlTOPp->top_level__DOT__gen_clusters__BRA__1__KET____DOT__cluster_lane_a
        [0U];
    vlTOPp->top_level__DOT____Vcellinp__gen_clusters__BRA__1__KET____DOT__u_cluster__lane_a[1U] 
        = vlTOPp->top_level__DOT__gen_clusters__BRA__1__KET____DOT__cluster_lane_a
        [1U];
    vlTOPp->top_level__DOT____Vcellinp__gen_clusters__BRA__1__KET____DOT__u_cluster__lane_a[2U] 
        = vlTOPp->top_level__DOT__gen_clusters__BRA__1__KET____DOT__cluster_lane_a
        [2U];
    vlTOPp->top_level__DOT____Vcellinp__gen_clusters__BRA__1__KET____DOT__u_cluster__lane_a[3U] 
        = vlTOPp->top_level__DOT__gen_clusters__BRA__1__KET____DOT__cluster_lane_a
        [3U];
    vlTOPp->top_level__DOT____Vcellinp__gen_clusters__BRA__2__KET____DOT__u_cluster__lane_a[0U] 
        = vlTOPp->top_level__DOT__gen_clusters__BRA__2__KET____DOT__cluster_lane_a
        [0U];
    vlTOPp->top_level__DOT____Vcellinp__gen_clusters__BRA__2__KET____DOT__u_cluster__lane_a[1U] 
        = vlTOPp->top_level__DOT__gen_clusters__BRA__2__KET____DOT__cluster_lane_a
        [1U];
    vlTOPp->top_level__DOT____Vcellinp__gen_clusters__BRA__2__KET____DOT__u_cluster__lane_a[2U] 
        = vlTOPp->top_level__DOT__gen_clusters__BRA__2__KET____DOT__cluster_lane_a
        [2U];
    vlTOPp->top_level__DOT____Vcellinp__gen_clusters__BRA__2__KET____DOT__u_cluster__lane_a[3U] 
        = vlTOPp->top_level__DOT__gen_clusters__BRA__2__KET____DOT__cluster_lane_a
        [3U];
    vlTOPp->top_level__DOT____Vcellinp__gen_clusters__BRA__3__KET____DOT__u_cluster__lane_a[0U] 
        = vlTOPp->top_level__DOT__gen_clusters__BRA__3__KET____DOT__cluster_lane_a
        [0U];
    vlTOPp->top_level__DOT____Vcellinp__gen_clusters__BRA__3__KET____DOT__u_cluster__lane_a[1U] 
        = vlTOPp->top_level__DOT__gen_clusters__BRA__3__KET____DOT__cluster_lane_a
        [1U];
    vlTOPp->top_level__DOT____Vcellinp__gen_clusters__BRA__3__KET____DOT__u_cluster__lane_a[2U] 
        = vlTOPp->top_level__DOT__gen_clusters__BRA__3__KET____DOT__cluster_lane_a
        [2U];
    vlTOPp->top_level__DOT____Vcellinp__gen_clusters__BRA__3__KET____DOT__u_cluster__lane_a[3U] 
        = vlTOPp->top_level__DOT__gen_clusters__BRA__3__KET____DOT__cluster_lane_a
        [3U];
    vlTOPp->top_level__DOT____Vcellinp__gen_clusters__BRA__4__KET____DOT__u_cluster__lane_a[0U] 
        = vlTOPp->top_level__DOT__gen_clusters__BRA__4__KET____DOT__cluster_lane_a
        [0U];
    vlTOPp->top_level__DOT____Vcellinp__gen_clusters__BRA__4__KET____DOT__u_cluster__lane_a[1U] 
        = vlTOPp->top_level__DOT__gen_clusters__BRA__4__KET____DOT__cluster_lane_a
        [1U];
    vlTOPp->top_level__DOT____Vcellinp__gen_clusters__BRA__4__KET____DOT__u_cluster__lane_a[2U] 
        = vlTOPp->top_level__DOT__gen_clusters__BRA__4__KET____DOT__cluster_lane_a
        [2U];
    vlTOPp->top_level__DOT____Vcellinp__gen_clusters__BRA__4__KET____DOT__u_cluster__lane_a[3U] 
        = vlTOPp->top_level__DOT__gen_clusters__BRA__4__KET____DOT__cluster_lane_a
        [3U];
    vlTOPp->top_level__DOT____Vcellinp__gen_clusters__BRA__5__KET____DOT__u_cluster__lane_a[0U] 
        = vlTOPp->top_level__DOT__gen_clusters__BRA__5__KET____DOT__cluster_lane_a
        [0U];
    vlTOPp->top_level__DOT____Vcellinp__gen_clusters__BRA__5__KET____DOT__u_cluster__lane_a[1U] 
        = vlTOPp->top_level__DOT__gen_clusters__BRA__5__KET____DOT__cluster_lane_a
        [1U];
    vlTOPp->top_level__DOT____Vcellinp__gen_clusters__BRA__5__KET____DOT__u_cluster__lane_a[2U] 
        = vlTOPp->top_level__DOT__gen_clusters__BRA__5__KET____DOT__cluster_lane_a
        [2U];
    vlTOPp->top_level__DOT____Vcellinp__gen_clusters__BRA__5__KET____DOT__u_cluster__lane_a[3U] 
        = vlTOPp->top_level__DOT__gen_clusters__BRA__5__KET____DOT__cluster_lane_a
        [3U];
    vlTOPp->top_level__DOT____Vcellinp__gen_clusters__BRA__6__KET____DOT__u_cluster__lane_a[0U] 
        = vlTOPp->top_level__DOT__gen_clusters__BRA__6__KET____DOT__cluster_lane_a
        [0U];
    vlTOPp->top_level__DOT____Vcellinp__gen_clusters__BRA__6__KET____DOT__u_cluster__lane_a[1U] 
        = vlTOPp->top_level__DOT__gen_clusters__BRA__6__KET____DOT__cluster_lane_a
        [1U];
    vlTOPp->top_level__DOT____Vcellinp__gen_clusters__BRA__6__KET____DOT__u_cluster__lane_a[2U] 
        = vlTOPp->top_level__DOT__gen_clusters__BRA__6__KET____DOT__cluster_lane_a
        [2U];
    vlTOPp->top_level__DOT____Vcellinp__gen_clusters__BRA__6__KET____DOT__u_cluster__lane_a[3U] 
        = vlTOPp->top_level__DOT__gen_clusters__BRA__6__KET____DOT__cluster_lane_a
        [3U];
    vlTOPp->top_level__DOT____Vcellinp__gen_clusters__BRA__7__KET____DOT__u_cluster__lane_a[0U] 
        = vlTOPp->top_level__DOT__gen_clusters__BRA__7__KET____DOT__cluster_lane_a
        [0U];
    vlTOPp->top_level__DOT____Vcellinp__gen_clusters__BRA__7__KET____DOT__u_cluster__lane_a[1U] 
        = vlTOPp->top_level__DOT__gen_clusters__BRA__7__KET____DOT__cluster_lane_a
        [1U];
    vlTOPp->top_level__DOT____Vcellinp__gen_clusters__BRA__7__KET____DOT__u_cluster__lane_a[2U] 
        = vlTOPp->top_level__DOT__gen_clusters__BRA__7__KET____DOT__cluster_lane_a
        [2U];
    vlTOPp->top_level__DOT____Vcellinp__gen_clusters__BRA__7__KET____DOT__u_cluster__lane_a[3U] 
        = vlTOPp->top_level__DOT__gen_clusters__BRA__7__KET____DOT__cluster_lane_a
        [3U];
    vlTOPp->top_level__DOT__gen_clusters__BRA__0__KET____DOT__u_cluster__DOT__logical_lane 
        = ((IData)(vlTOPp->top_level__DOT__shared_phase) 
           << 1U);
    if (VL_GTS_III(1,32,32, 4U, vlTOPp->top_level__DOT__gen_clusters__BRA__0__KET____DOT__u_cluster__DOT__logical_lane)) {
        vlTOPp->top_level__DOT__gen_clusters__BRA__0__KET____DOT__u_cluster__DOT__pe_valid[0U] = 1U;
        vlTOPp->top_level__DOT__gen_clusters__BRA__0__KET____DOT__u_cluster__DOT__pe_a[0U] 
            = vlTOPp->top_level__DOT____Vcellinp__gen_clusters__BRA__0__KET____DOT__u_cluster__lane_a
            [(3U & vlTOPp->top_level__DOT__gen_clusters__BRA__0__KET____DOT__u_cluster__DOT__logical_lane)];
        vlTOPp->top_level__DOT__gen_clusters__BRA__0__KET____DOT__u_cluster__DOT__pe_b[0U] 
            = vlTOPp->top_level__DOT____Vcellinp__gen_clusters__BRA__0__KET____DOT__u_cluster__lane_b
            [(3U & vlTOPp->top_level__DOT__gen_clusters__BRA__0__KET____DOT__u_cluster__DOT__logical_lane)];
        vlTOPp->top_level__DOT__gen_clusters__BRA__0__KET____DOT__u_cluster__DOT__pe_seed[0U] 
            = vlTOPp->top_level__DOT__gen_clusters__BRA__0__KET____DOT__u_cluster__DOT__accum_bank
            [(3U & vlTOPp->top_level__DOT__gen_clusters__BRA__0__KET____DOT__u_cluster__DOT__logical_lane)];
    } else {
        vlTOPp->top_level__DOT__gen_clusters__BRA__0__KET____DOT__u_cluster__DOT__pe_valid[0U] = 0U;
        vlTOPp->top_level__DOT__gen_clusters__BRA__0__KET____DOT__u_cluster__DOT__pe_a[0U] = 0U;
        vlTOPp->top_level__DOT__gen_clusters__BRA__0__KET____DOT__u_cluster__DOT__pe_b[0U] = 0U;
        vlTOPp->top_level__DOT__gen_clusters__BRA__0__KET____DOT__u_cluster__DOT__pe_seed[0U] = 0U;
    }
    vlTOPp->top_level__DOT__gen_clusters__BRA__0__KET____DOT__u_cluster__DOT__logical_lane 
        = ((IData)(1U) + ((IData)(vlTOPp->top_level__DOT__shared_phase) 
                          << 1U));
    if (VL_GTS_III(1,32,32, 4U, vlTOPp->top_level__DOT__gen_clusters__BRA__0__KET____DOT__u_cluster__DOT__logical_lane)) {
        vlTOPp->top_level__DOT__gen_clusters__BRA__0__KET____DOT__u_cluster__DOT__pe_valid[1U] = 1U;
        vlTOPp->top_level__DOT__gen_clusters__BRA__0__KET____DOT__u_cluster__DOT__pe_a[1U] 
            = vlTOPp->top_level__DOT____Vcellinp__gen_clusters__BRA__0__KET____DOT__u_cluster__lane_a
            [(3U & vlTOPp->top_level__DOT__gen_clusters__BRA__0__KET____DOT__u_cluster__DOT__logical_lane)];
        vlTOPp->top_level__DOT__gen_clusters__BRA__0__KET____DOT__u_cluster__DOT__pe_b[1U] 
            = vlTOPp->top_level__DOT____Vcellinp__gen_clusters__BRA__0__KET____DOT__u_cluster__lane_b
            [(3U & vlTOPp->top_level__DOT__gen_clusters__BRA__0__KET____DOT__u_cluster__DOT__logical_lane)];
        vlTOPp->top_level__DOT__gen_clusters__BRA__0__KET____DOT__u_cluster__DOT__pe_seed[1U] 
            = vlTOPp->top_level__DOT__gen_clusters__BRA__0__KET____DOT__u_cluster__DOT__accum_bank
            [(3U & vlTOPp->top_level__DOT__gen_clusters__BRA__0__KET____DOT__u_cluster__DOT__logical_lane)];
    } else {
        vlTOPp->top_level__DOT__gen_clusters__BRA__0__KET____DOT__u_cluster__DOT__pe_valid[1U] = 0U;
        vlTOPp->top_level__DOT__gen_clusters__BRA__0__KET____DOT__u_cluster__DOT__pe_a[1U] = 0U;
        vlTOPp->top_level__DOT__gen_clusters__BRA__0__KET____DOT__u_cluster__DOT__pe_b[1U] = 0U;
        vlTOPp->top_level__DOT__gen_clusters__BRA__0__KET____DOT__u_cluster__DOT__pe_seed[1U] = 0U;
    }
    vlTOPp->top_level__DOT__gen_clusters__BRA__1__KET____DOT__u_cluster__DOT__logical_lane 
        = ((IData)(vlTOPp->top_level__DOT__shared_phase) 
           << 1U);
    if (VL_GTS_III(1,32,32, 4U, vlTOPp->top_level__DOT__gen_clusters__BRA__1__KET____DOT__u_cluster__DOT__logical_lane)) {
        vlTOPp->top_level__DOT__gen_clusters__BRA__1__KET____DOT__u_cluster__DOT__pe_valid[0U] = 1U;
        vlTOPp->top_level__DOT__gen_clusters__BRA__1__KET____DOT__u_cluster__DOT__pe_a[0U] 
            = vlTOPp->top_level__DOT____Vcellinp__gen_clusters__BRA__1__KET____DOT__u_cluster__lane_a
            [(3U & vlTOPp->top_level__DOT__gen_clusters__BRA__1__KET____DOT__u_cluster__DOT__logical_lane)];
        vlTOPp->top_level__DOT__gen_clusters__BRA__1__KET____DOT__u_cluster__DOT__pe_b[0U] 
            = vlTOPp->top_level__DOT____Vcellinp__gen_clusters__BRA__1__KET____DOT__u_cluster__lane_b
            [(3U & vlTOPp->top_level__DOT__gen_clusters__BRA__1__KET____DOT__u_cluster__DOT__logical_lane)];
        vlTOPp->top_level__DOT__gen_clusters__BRA__1__KET____DOT__u_cluster__DOT__pe_seed[0U] 
            = vlTOPp->top_level__DOT__gen_clusters__BRA__1__KET____DOT__u_cluster__DOT__accum_bank
            [(3U & vlTOPp->top_level__DOT__gen_clusters__BRA__1__KET____DOT__u_cluster__DOT__logical_lane)];
    } else {
        vlTOPp->top_level__DOT__gen_clusters__BRA__1__KET____DOT__u_cluster__DOT__pe_valid[0U] = 0U;
        vlTOPp->top_level__DOT__gen_clusters__BRA__1__KET____DOT__u_cluster__DOT__pe_a[0U] = 0U;
        vlTOPp->top_level__DOT__gen_clusters__BRA__1__KET____DOT__u_cluster__DOT__pe_b[0U] = 0U;
        vlTOPp->top_level__DOT__gen_clusters__BRA__1__KET____DOT__u_cluster__DOT__pe_seed[0U] = 0U;
    }
    vlTOPp->top_level__DOT__gen_clusters__BRA__1__KET____DOT__u_cluster__DOT__logical_lane 
        = ((IData)(1U) + ((IData)(vlTOPp->top_level__DOT__shared_phase) 
                          << 1U));
    if (VL_GTS_III(1,32,32, 4U, vlTOPp->top_level__DOT__gen_clusters__BRA__1__KET____DOT__u_cluster__DOT__logical_lane)) {
        vlTOPp->top_level__DOT__gen_clusters__BRA__1__KET____DOT__u_cluster__DOT__pe_valid[1U] = 1U;
        vlTOPp->top_level__DOT__gen_clusters__BRA__1__KET____DOT__u_cluster__DOT__pe_a[1U] 
            = vlTOPp->top_level__DOT____Vcellinp__gen_clusters__BRA__1__KET____DOT__u_cluster__lane_a
            [(3U & vlTOPp->top_level__DOT__gen_clusters__BRA__1__KET____DOT__u_cluster__DOT__logical_lane)];
        vlTOPp->top_level__DOT__gen_clusters__BRA__1__KET____DOT__u_cluster__DOT__pe_b[1U] 
            = vlTOPp->top_level__DOT____Vcellinp__gen_clusters__BRA__1__KET____DOT__u_cluster__lane_b
            [(3U & vlTOPp->top_level__DOT__gen_clusters__BRA__1__KET____DOT__u_cluster__DOT__logical_lane)];
        vlTOPp->top_level__DOT__gen_clusters__BRA__1__KET____DOT__u_cluster__DOT__pe_seed[1U] 
            = vlTOPp->top_level__DOT__gen_clusters__BRA__1__KET____DOT__u_cluster__DOT__accum_bank
            [(3U & vlTOPp->top_level__DOT__gen_clusters__BRA__1__KET____DOT__u_cluster__DOT__logical_lane)];
    } else {
        vlTOPp->top_level__DOT__gen_clusters__BRA__1__KET____DOT__u_cluster__DOT__pe_valid[1U] = 0U;
        vlTOPp->top_level__DOT__gen_clusters__BRA__1__KET____DOT__u_cluster__DOT__pe_a[1U] = 0U;
        vlTOPp->top_level__DOT__gen_clusters__BRA__1__KET____DOT__u_cluster__DOT__pe_b[1U] = 0U;
        vlTOPp->top_level__DOT__gen_clusters__BRA__1__KET____DOT__u_cluster__DOT__pe_seed[1U] = 0U;
    }
    vlTOPp->top_level__DOT__gen_clusters__BRA__2__KET____DOT__u_cluster__DOT__logical_lane 
        = ((IData)(vlTOPp->top_level__DOT__shared_phase) 
           << 1U);
    if (VL_GTS_III(1,32,32, 4U, vlTOPp->top_level__DOT__gen_clusters__BRA__2__KET____DOT__u_cluster__DOT__logical_lane)) {
        vlTOPp->top_level__DOT__gen_clusters__BRA__2__KET____DOT__u_cluster__DOT__pe_valid[0U] = 1U;
        vlTOPp->top_level__DOT__gen_clusters__BRA__2__KET____DOT__u_cluster__DOT__pe_a[0U] 
            = vlTOPp->top_level__DOT____Vcellinp__gen_clusters__BRA__2__KET____DOT__u_cluster__lane_a
            [(3U & vlTOPp->top_level__DOT__gen_clusters__BRA__2__KET____DOT__u_cluster__DOT__logical_lane)];
        vlTOPp->top_level__DOT__gen_clusters__BRA__2__KET____DOT__u_cluster__DOT__pe_b[0U] 
            = vlTOPp->top_level__DOT____Vcellinp__gen_clusters__BRA__2__KET____DOT__u_cluster__lane_b
            [(3U & vlTOPp->top_level__DOT__gen_clusters__BRA__2__KET____DOT__u_cluster__DOT__logical_lane)];
        vlTOPp->top_level__DOT__gen_clusters__BRA__2__KET____DOT__u_cluster__DOT__pe_seed[0U] 
            = vlTOPp->top_level__DOT__gen_clusters__BRA__2__KET____DOT__u_cluster__DOT__accum_bank
            [(3U & vlTOPp->top_level__DOT__gen_clusters__BRA__2__KET____DOT__u_cluster__DOT__logical_lane)];
    } else {
        vlTOPp->top_level__DOT__gen_clusters__BRA__2__KET____DOT__u_cluster__DOT__pe_valid[0U] = 0U;
        vlTOPp->top_level__DOT__gen_clusters__BRA__2__KET____DOT__u_cluster__DOT__pe_a[0U] = 0U;
        vlTOPp->top_level__DOT__gen_clusters__BRA__2__KET____DOT__u_cluster__DOT__pe_b[0U] = 0U;
        vlTOPp->top_level__DOT__gen_clusters__BRA__2__KET____DOT__u_cluster__DOT__pe_seed[0U] = 0U;
    }
    vlTOPp->top_level__DOT__gen_clusters__BRA__2__KET____DOT__u_cluster__DOT__logical_lane 
        = ((IData)(1U) + ((IData)(vlTOPp->top_level__DOT__shared_phase) 
                          << 1U));
    if (VL_GTS_III(1,32,32, 4U, vlTOPp->top_level__DOT__gen_clusters__BRA__2__KET____DOT__u_cluster__DOT__logical_lane)) {
        vlTOPp->top_level__DOT__gen_clusters__BRA__2__KET____DOT__u_cluster__DOT__pe_valid[1U] = 1U;
        vlTOPp->top_level__DOT__gen_clusters__BRA__2__KET____DOT__u_cluster__DOT__pe_a[1U] 
            = vlTOPp->top_level__DOT____Vcellinp__gen_clusters__BRA__2__KET____DOT__u_cluster__lane_a
            [(3U & vlTOPp->top_level__DOT__gen_clusters__BRA__2__KET____DOT__u_cluster__DOT__logical_lane)];
        vlTOPp->top_level__DOT__gen_clusters__BRA__2__KET____DOT__u_cluster__DOT__pe_b[1U] 
            = vlTOPp->top_level__DOT____Vcellinp__gen_clusters__BRA__2__KET____DOT__u_cluster__lane_b
            [(3U & vlTOPp->top_level__DOT__gen_clusters__BRA__2__KET____DOT__u_cluster__DOT__logical_lane)];
        vlTOPp->top_level__DOT__gen_clusters__BRA__2__KET____DOT__u_cluster__DOT__pe_seed[1U] 
            = vlTOPp->top_level__DOT__gen_clusters__BRA__2__KET____DOT__u_cluster__DOT__accum_bank
            [(3U & vlTOPp->top_level__DOT__gen_clusters__BRA__2__KET____DOT__u_cluster__DOT__logical_lane)];
    } else {
        vlTOPp->top_level__DOT__gen_clusters__BRA__2__KET____DOT__u_cluster__DOT__pe_valid[1U] = 0U;
        vlTOPp->top_level__DOT__gen_clusters__BRA__2__KET____DOT__u_cluster__DOT__pe_a[1U] = 0U;
        vlTOPp->top_level__DOT__gen_clusters__BRA__2__KET____DOT__u_cluster__DOT__pe_b[1U] = 0U;
        vlTOPp->top_level__DOT__gen_clusters__BRA__2__KET____DOT__u_cluster__DOT__pe_seed[1U] = 0U;
    }
    vlTOPp->top_level__DOT__gen_clusters__BRA__3__KET____DOT__u_cluster__DOT__logical_lane 
        = ((IData)(vlTOPp->top_level__DOT__shared_phase) 
           << 1U);
    if (VL_GTS_III(1,32,32, 4U, vlTOPp->top_level__DOT__gen_clusters__BRA__3__KET____DOT__u_cluster__DOT__logical_lane)) {
        vlTOPp->top_level__DOT__gen_clusters__BRA__3__KET____DOT__u_cluster__DOT__pe_valid[0U] = 1U;
        vlTOPp->top_level__DOT__gen_clusters__BRA__3__KET____DOT__u_cluster__DOT__pe_a[0U] 
            = vlTOPp->top_level__DOT____Vcellinp__gen_clusters__BRA__3__KET____DOT__u_cluster__lane_a
            [(3U & vlTOPp->top_level__DOT__gen_clusters__BRA__3__KET____DOT__u_cluster__DOT__logical_lane)];
        vlTOPp->top_level__DOT__gen_clusters__BRA__3__KET____DOT__u_cluster__DOT__pe_b[0U] 
            = vlTOPp->top_level__DOT____Vcellinp__gen_clusters__BRA__3__KET____DOT__u_cluster__lane_b
            [(3U & vlTOPp->top_level__DOT__gen_clusters__BRA__3__KET____DOT__u_cluster__DOT__logical_lane)];
        vlTOPp->top_level__DOT__gen_clusters__BRA__3__KET____DOT__u_cluster__DOT__pe_seed[0U] 
            = vlTOPp->top_level__DOT__gen_clusters__BRA__3__KET____DOT__u_cluster__DOT__accum_bank
            [(3U & vlTOPp->top_level__DOT__gen_clusters__BRA__3__KET____DOT__u_cluster__DOT__logical_lane)];
    } else {
        vlTOPp->top_level__DOT__gen_clusters__BRA__3__KET____DOT__u_cluster__DOT__pe_valid[0U] = 0U;
        vlTOPp->top_level__DOT__gen_clusters__BRA__3__KET____DOT__u_cluster__DOT__pe_a[0U] = 0U;
        vlTOPp->top_level__DOT__gen_clusters__BRA__3__KET____DOT__u_cluster__DOT__pe_b[0U] = 0U;
        vlTOPp->top_level__DOT__gen_clusters__BRA__3__KET____DOT__u_cluster__DOT__pe_seed[0U] = 0U;
    }
    vlTOPp->top_level__DOT__gen_clusters__BRA__3__KET____DOT__u_cluster__DOT__logical_lane 
        = ((IData)(1U) + ((IData)(vlTOPp->top_level__DOT__shared_phase) 
                          << 1U));
    if (VL_GTS_III(1,32,32, 4U, vlTOPp->top_level__DOT__gen_clusters__BRA__3__KET____DOT__u_cluster__DOT__logical_lane)) {
        vlTOPp->top_level__DOT__gen_clusters__BRA__3__KET____DOT__u_cluster__DOT__pe_valid[1U] = 1U;
        vlTOPp->top_level__DOT__gen_clusters__BRA__3__KET____DOT__u_cluster__DOT__pe_a[1U] 
            = vlTOPp->top_level__DOT____Vcellinp__gen_clusters__BRA__3__KET____DOT__u_cluster__lane_a
            [(3U & vlTOPp->top_level__DOT__gen_clusters__BRA__3__KET____DOT__u_cluster__DOT__logical_lane)];
        vlTOPp->top_level__DOT__gen_clusters__BRA__3__KET____DOT__u_cluster__DOT__pe_b[1U] 
            = vlTOPp->top_level__DOT____Vcellinp__gen_clusters__BRA__3__KET____DOT__u_cluster__lane_b
            [(3U & vlTOPp->top_level__DOT__gen_clusters__BRA__3__KET____DOT__u_cluster__DOT__logical_lane)];
        vlTOPp->top_level__DOT__gen_clusters__BRA__3__KET____DOT__u_cluster__DOT__pe_seed[1U] 
            = vlTOPp->top_level__DOT__gen_clusters__BRA__3__KET____DOT__u_cluster__DOT__accum_bank
            [(3U & vlTOPp->top_level__DOT__gen_clusters__BRA__3__KET____DOT__u_cluster__DOT__logical_lane)];
    } else {
        vlTOPp->top_level__DOT__gen_clusters__BRA__3__KET____DOT__u_cluster__DOT__pe_valid[1U] = 0U;
        vlTOPp->top_level__DOT__gen_clusters__BRA__3__KET____DOT__u_cluster__DOT__pe_a[1U] = 0U;
        vlTOPp->top_level__DOT__gen_clusters__BRA__3__KET____DOT__u_cluster__DOT__pe_b[1U] = 0U;
        vlTOPp->top_level__DOT__gen_clusters__BRA__3__KET____DOT__u_cluster__DOT__pe_seed[1U] = 0U;
    }
    vlTOPp->top_level__DOT__gen_clusters__BRA__4__KET____DOT__u_cluster__DOT__logical_lane 
        = ((IData)(vlTOPp->top_level__DOT__shared_phase) 
           << 1U);
    if (VL_GTS_III(1,32,32, 4U, vlTOPp->top_level__DOT__gen_clusters__BRA__4__KET____DOT__u_cluster__DOT__logical_lane)) {
        vlTOPp->top_level__DOT__gen_clusters__BRA__4__KET____DOT__u_cluster__DOT__pe_valid[0U] = 1U;
        vlTOPp->top_level__DOT__gen_clusters__BRA__4__KET____DOT__u_cluster__DOT__pe_a[0U] 
            = vlTOPp->top_level__DOT____Vcellinp__gen_clusters__BRA__4__KET____DOT__u_cluster__lane_a
            [(3U & vlTOPp->top_level__DOT__gen_clusters__BRA__4__KET____DOT__u_cluster__DOT__logical_lane)];
        vlTOPp->top_level__DOT__gen_clusters__BRA__4__KET____DOT__u_cluster__DOT__pe_b[0U] 
            = vlTOPp->top_level__DOT____Vcellinp__gen_clusters__BRA__4__KET____DOT__u_cluster__lane_b
            [(3U & vlTOPp->top_level__DOT__gen_clusters__BRA__4__KET____DOT__u_cluster__DOT__logical_lane)];
        vlTOPp->top_level__DOT__gen_clusters__BRA__4__KET____DOT__u_cluster__DOT__pe_seed[0U] 
            = vlTOPp->top_level__DOT__gen_clusters__BRA__4__KET____DOT__u_cluster__DOT__accum_bank
            [(3U & vlTOPp->top_level__DOT__gen_clusters__BRA__4__KET____DOT__u_cluster__DOT__logical_lane)];
    } else {
        vlTOPp->top_level__DOT__gen_clusters__BRA__4__KET____DOT__u_cluster__DOT__pe_valid[0U] = 0U;
        vlTOPp->top_level__DOT__gen_clusters__BRA__4__KET____DOT__u_cluster__DOT__pe_a[0U] = 0U;
        vlTOPp->top_level__DOT__gen_clusters__BRA__4__KET____DOT__u_cluster__DOT__pe_b[0U] = 0U;
        vlTOPp->top_level__DOT__gen_clusters__BRA__4__KET____DOT__u_cluster__DOT__pe_seed[0U] = 0U;
    }
    vlTOPp->top_level__DOT__gen_clusters__BRA__4__KET____DOT__u_cluster__DOT__logical_lane 
        = ((IData)(1U) + ((IData)(vlTOPp->top_level__DOT__shared_phase) 
                          << 1U));
    if (VL_GTS_III(1,32,32, 4U, vlTOPp->top_level__DOT__gen_clusters__BRA__4__KET____DOT__u_cluster__DOT__logical_lane)) {
        vlTOPp->top_level__DOT__gen_clusters__BRA__4__KET____DOT__u_cluster__DOT__pe_valid[1U] = 1U;
        vlTOPp->top_level__DOT__gen_clusters__BRA__4__KET____DOT__u_cluster__DOT__pe_a[1U] 
            = vlTOPp->top_level__DOT____Vcellinp__gen_clusters__BRA__4__KET____DOT__u_cluster__lane_a
            [(3U & vlTOPp->top_level__DOT__gen_clusters__BRA__4__KET____DOT__u_cluster__DOT__logical_lane)];
        vlTOPp->top_level__DOT__gen_clusters__BRA__4__KET____DOT__u_cluster__DOT__pe_b[1U] 
            = vlTOPp->top_level__DOT____Vcellinp__gen_clusters__BRA__4__KET____DOT__u_cluster__lane_b
            [(3U & vlTOPp->top_level__DOT__gen_clusters__BRA__4__KET____DOT__u_cluster__DOT__logical_lane)];
        vlTOPp->top_level__DOT__gen_clusters__BRA__4__KET____DOT__u_cluster__DOT__pe_seed[1U] 
            = vlTOPp->top_level__DOT__gen_clusters__BRA__4__KET____DOT__u_cluster__DOT__accum_bank
            [(3U & vlTOPp->top_level__DOT__gen_clusters__BRA__4__KET____DOT__u_cluster__DOT__logical_lane)];
    } else {
        vlTOPp->top_level__DOT__gen_clusters__BRA__4__KET____DOT__u_cluster__DOT__pe_valid[1U] = 0U;
        vlTOPp->top_level__DOT__gen_clusters__BRA__4__KET____DOT__u_cluster__DOT__pe_a[1U] = 0U;
        vlTOPp->top_level__DOT__gen_clusters__BRA__4__KET____DOT__u_cluster__DOT__pe_b[1U] = 0U;
        vlTOPp->top_level__DOT__gen_clusters__BRA__4__KET____DOT__u_cluster__DOT__pe_seed[1U] = 0U;
    }
    vlTOPp->top_level__DOT__gen_clusters__BRA__5__KET____DOT__u_cluster__DOT__logical_lane 
        = ((IData)(vlTOPp->top_level__DOT__shared_phase) 
           << 1U);
    if (VL_GTS_III(1,32,32, 4U, vlTOPp->top_level__DOT__gen_clusters__BRA__5__KET____DOT__u_cluster__DOT__logical_lane)) {
        vlTOPp->top_level__DOT__gen_clusters__BRA__5__KET____DOT__u_cluster__DOT__pe_valid[0U] = 1U;
        vlTOPp->top_level__DOT__gen_clusters__BRA__5__KET____DOT__u_cluster__DOT__pe_a[0U] 
            = vlTOPp->top_level__DOT____Vcellinp__gen_clusters__BRA__5__KET____DOT__u_cluster__lane_a
            [(3U & vlTOPp->top_level__DOT__gen_clusters__BRA__5__KET____DOT__u_cluster__DOT__logical_lane)];
        vlTOPp->top_level__DOT__gen_clusters__BRA__5__KET____DOT__u_cluster__DOT__pe_b[0U] 
            = vlTOPp->top_level__DOT____Vcellinp__gen_clusters__BRA__5__KET____DOT__u_cluster__lane_b
            [(3U & vlTOPp->top_level__DOT__gen_clusters__BRA__5__KET____DOT__u_cluster__DOT__logical_lane)];
        vlTOPp->top_level__DOT__gen_clusters__BRA__5__KET____DOT__u_cluster__DOT__pe_seed[0U] 
            = vlTOPp->top_level__DOT__gen_clusters__BRA__5__KET____DOT__u_cluster__DOT__accum_bank
            [(3U & vlTOPp->top_level__DOT__gen_clusters__BRA__5__KET____DOT__u_cluster__DOT__logical_lane)];
    } else {
        vlTOPp->top_level__DOT__gen_clusters__BRA__5__KET____DOT__u_cluster__DOT__pe_valid[0U] = 0U;
        vlTOPp->top_level__DOT__gen_clusters__BRA__5__KET____DOT__u_cluster__DOT__pe_a[0U] = 0U;
        vlTOPp->top_level__DOT__gen_clusters__BRA__5__KET____DOT__u_cluster__DOT__pe_b[0U] = 0U;
        vlTOPp->top_level__DOT__gen_clusters__BRA__5__KET____DOT__u_cluster__DOT__pe_seed[0U] = 0U;
    }
    vlTOPp->top_level__DOT__gen_clusters__BRA__5__KET____DOT__u_cluster__DOT__logical_lane 
        = ((IData)(1U) + ((IData)(vlTOPp->top_level__DOT__shared_phase) 
                          << 1U));
    if (VL_GTS_III(1,32,32, 4U, vlTOPp->top_level__DOT__gen_clusters__BRA__5__KET____DOT__u_cluster__DOT__logical_lane)) {
        vlTOPp->top_level__DOT__gen_clusters__BRA__5__KET____DOT__u_cluster__DOT__pe_valid[1U] = 1U;
        vlTOPp->top_level__DOT__gen_clusters__BRA__5__KET____DOT__u_cluster__DOT__pe_a[1U] 
            = vlTOPp->top_level__DOT____Vcellinp__gen_clusters__BRA__5__KET____DOT__u_cluster__lane_a
            [(3U & vlTOPp->top_level__DOT__gen_clusters__BRA__5__KET____DOT__u_cluster__DOT__logical_lane)];
        vlTOPp->top_level__DOT__gen_clusters__BRA__5__KET____DOT__u_cluster__DOT__pe_b[1U] 
            = vlTOPp->top_level__DOT____Vcellinp__gen_clusters__BRA__5__KET____DOT__u_cluster__lane_b
            [(3U & vlTOPp->top_level__DOT__gen_clusters__BRA__5__KET____DOT__u_cluster__DOT__logical_lane)];
        vlTOPp->top_level__DOT__gen_clusters__BRA__5__KET____DOT__u_cluster__DOT__pe_seed[1U] 
            = vlTOPp->top_level__DOT__gen_clusters__BRA__5__KET____DOT__u_cluster__DOT__accum_bank
            [(3U & vlTOPp->top_level__DOT__gen_clusters__BRA__5__KET____DOT__u_cluster__DOT__logical_lane)];
    } else {
        vlTOPp->top_level__DOT__gen_clusters__BRA__5__KET____DOT__u_cluster__DOT__pe_valid[1U] = 0U;
        vlTOPp->top_level__DOT__gen_clusters__BRA__5__KET____DOT__u_cluster__DOT__pe_a[1U] = 0U;
        vlTOPp->top_level__DOT__gen_clusters__BRA__5__KET____DOT__u_cluster__DOT__pe_b[1U] = 0U;
        vlTOPp->top_level__DOT__gen_clusters__BRA__5__KET____DOT__u_cluster__DOT__pe_seed[1U] = 0U;
    }
    vlTOPp->top_level__DOT__gen_clusters__BRA__6__KET____DOT__u_cluster__DOT__logical_lane 
        = ((IData)(vlTOPp->top_level__DOT__shared_phase) 
           << 1U);
    if (VL_GTS_III(1,32,32, 4U, vlTOPp->top_level__DOT__gen_clusters__BRA__6__KET____DOT__u_cluster__DOT__logical_lane)) {
        vlTOPp->top_level__DOT__gen_clusters__BRA__6__KET____DOT__u_cluster__DOT__pe_valid[0U] = 1U;
        vlTOPp->top_level__DOT__gen_clusters__BRA__6__KET____DOT__u_cluster__DOT__pe_a[0U] 
            = vlTOPp->top_level__DOT____Vcellinp__gen_clusters__BRA__6__KET____DOT__u_cluster__lane_a
            [(3U & vlTOPp->top_level__DOT__gen_clusters__BRA__6__KET____DOT__u_cluster__DOT__logical_lane)];
        vlTOPp->top_level__DOT__gen_clusters__BRA__6__KET____DOT__u_cluster__DOT__pe_b[0U] 
            = vlTOPp->top_level__DOT____Vcellinp__gen_clusters__BRA__6__KET____DOT__u_cluster__lane_b
            [(3U & vlTOPp->top_level__DOT__gen_clusters__BRA__6__KET____DOT__u_cluster__DOT__logical_lane)];
        vlTOPp->top_level__DOT__gen_clusters__BRA__6__KET____DOT__u_cluster__DOT__pe_seed[0U] 
            = vlTOPp->top_level__DOT__gen_clusters__BRA__6__KET____DOT__u_cluster__DOT__accum_bank
            [(3U & vlTOPp->top_level__DOT__gen_clusters__BRA__6__KET____DOT__u_cluster__DOT__logical_lane)];
    } else {
        vlTOPp->top_level__DOT__gen_clusters__BRA__6__KET____DOT__u_cluster__DOT__pe_valid[0U] = 0U;
        vlTOPp->top_level__DOT__gen_clusters__BRA__6__KET____DOT__u_cluster__DOT__pe_a[0U] = 0U;
        vlTOPp->top_level__DOT__gen_clusters__BRA__6__KET____DOT__u_cluster__DOT__pe_b[0U] = 0U;
        vlTOPp->top_level__DOT__gen_clusters__BRA__6__KET____DOT__u_cluster__DOT__pe_seed[0U] = 0U;
    }
    vlTOPp->top_level__DOT__gen_clusters__BRA__6__KET____DOT__u_cluster__DOT__logical_lane 
        = ((IData)(1U) + ((IData)(vlTOPp->top_level__DOT__shared_phase) 
                          << 1U));
    if (VL_GTS_III(1,32,32, 4U, vlTOPp->top_level__DOT__gen_clusters__BRA__6__KET____DOT__u_cluster__DOT__logical_lane)) {
        vlTOPp->top_level__DOT__gen_clusters__BRA__6__KET____DOT__u_cluster__DOT__pe_valid[1U] = 1U;
        vlTOPp->top_level__DOT__gen_clusters__BRA__6__KET____DOT__u_cluster__DOT__pe_a[1U] 
            = vlTOPp->top_level__DOT____Vcellinp__gen_clusters__BRA__6__KET____DOT__u_cluster__lane_a
            [(3U & vlTOPp->top_level__DOT__gen_clusters__BRA__6__KET____DOT__u_cluster__DOT__logical_lane)];
        vlTOPp->top_level__DOT__gen_clusters__BRA__6__KET____DOT__u_cluster__DOT__pe_b[1U] 
            = vlTOPp->top_level__DOT____Vcellinp__gen_clusters__BRA__6__KET____DOT__u_cluster__lane_b
            [(3U & vlTOPp->top_level__DOT__gen_clusters__BRA__6__KET____DOT__u_cluster__DOT__logical_lane)];
        vlTOPp->top_level__DOT__gen_clusters__BRA__6__KET____DOT__u_cluster__DOT__pe_seed[1U] 
            = vlTOPp->top_level__DOT__gen_clusters__BRA__6__KET____DOT__u_cluster__DOT__accum_bank
            [(3U & vlTOPp->top_level__DOT__gen_clusters__BRA__6__KET____DOT__u_cluster__DOT__logical_lane)];
    } else {
        vlTOPp->top_level__DOT__gen_clusters__BRA__6__KET____DOT__u_cluster__DOT__pe_valid[1U] = 0U;
        vlTOPp->top_level__DOT__gen_clusters__BRA__6__KET____DOT__u_cluster__DOT__pe_a[1U] = 0U;
        vlTOPp->top_level__DOT__gen_clusters__BRA__6__KET____DOT__u_cluster__DOT__pe_b[1U] = 0U;
        vlTOPp->top_level__DOT__gen_clusters__BRA__6__KET____DOT__u_cluster__DOT__pe_seed[1U] = 0U;
    }
    vlTOPp->top_level__DOT__gen_clusters__BRA__7__KET____DOT__u_cluster__DOT__logical_lane 
        = ((IData)(vlTOPp->top_level__DOT__shared_phase) 
           << 1U);
    if (VL_GTS_III(1,32,32, 4U, vlTOPp->top_level__DOT__gen_clusters__BRA__7__KET____DOT__u_cluster__DOT__logical_lane)) {
        vlTOPp->top_level__DOT__gen_clusters__BRA__7__KET____DOT__u_cluster__DOT__pe_valid[0U] = 1U;
        vlTOPp->top_level__DOT__gen_clusters__BRA__7__KET____DOT__u_cluster__DOT__pe_a[0U] 
            = vlTOPp->top_level__DOT____Vcellinp__gen_clusters__BRA__7__KET____DOT__u_cluster__lane_a
            [(3U & vlTOPp->top_level__DOT__gen_clusters__BRA__7__KET____DOT__u_cluster__DOT__logical_lane)];
        vlTOPp->top_level__DOT__gen_clusters__BRA__7__KET____DOT__u_cluster__DOT__pe_b[0U] 
            = vlTOPp->top_level__DOT____Vcellinp__gen_clusters__BRA__7__KET____DOT__u_cluster__lane_b
            [(3U & vlTOPp->top_level__DOT__gen_clusters__BRA__7__KET____DOT__u_cluster__DOT__logical_lane)];
        vlTOPp->top_level__DOT__gen_clusters__BRA__7__KET____DOT__u_cluster__DOT__pe_seed[0U] 
            = vlTOPp->top_level__DOT__gen_clusters__BRA__7__KET____DOT__u_cluster__DOT__accum_bank
            [(3U & vlTOPp->top_level__DOT__gen_clusters__BRA__7__KET____DOT__u_cluster__DOT__logical_lane)];
    } else {
        vlTOPp->top_level__DOT__gen_clusters__BRA__7__KET____DOT__u_cluster__DOT__pe_valid[0U] = 0U;
        vlTOPp->top_level__DOT__gen_clusters__BRA__7__KET____DOT__u_cluster__DOT__pe_a[0U] = 0U;
        vlTOPp->top_level__DOT__gen_clusters__BRA__7__KET____DOT__u_cluster__DOT__pe_b[0U] = 0U;
        vlTOPp->top_level__DOT__gen_clusters__BRA__7__KET____DOT__u_cluster__DOT__pe_seed[0U] = 0U;
    }
    vlTOPp->top_level__DOT__gen_clusters__BRA__7__KET____DOT__u_cluster__DOT__logical_lane 
        = ((IData)(1U) + ((IData)(vlTOPp->top_level__DOT__shared_phase) 
                          << 1U));
    if (VL_GTS_III(1,32,32, 4U, vlTOPp->top_level__DOT__gen_clusters__BRA__7__KET____DOT__u_cluster__DOT__logical_lane)) {
        vlTOPp->top_level__DOT__gen_clusters__BRA__7__KET____DOT__u_cluster__DOT__pe_valid[1U] = 1U;
        vlTOPp->top_level__DOT__gen_clusters__BRA__7__KET____DOT__u_cluster__DOT__pe_a[1U] 
            = vlTOPp->top_level__DOT____Vcellinp__gen_clusters__BRA__7__KET____DOT__u_cluster__lane_a
            [(3U & vlTOPp->top_level__DOT__gen_clusters__BRA__7__KET____DOT__u_cluster__DOT__logical_lane)];
        vlTOPp->top_level__DOT__gen_clusters__BRA__7__KET____DOT__u_cluster__DOT__pe_b[1U] 
            = vlTOPp->top_level__DOT____Vcellinp__gen_clusters__BRA__7__KET____DOT__u_cluster__lane_b
            [(3U & vlTOPp->top_level__DOT__gen_clusters__BRA__7__KET____DOT__u_cluster__DOT__logical_lane)];
        vlTOPp->top_level__DOT__gen_clusters__BRA__7__KET____DOT__u_cluster__DOT__pe_seed[1U] 
            = vlTOPp->top_level__DOT__gen_clusters__BRA__7__KET____DOT__u_cluster__DOT__accum_bank
            [(3U & vlTOPp->top_level__DOT__gen_clusters__BRA__7__KET____DOT__u_cluster__DOT__logical_lane)];
    } else {
        vlTOPp->top_level__DOT__gen_clusters__BRA__7__KET____DOT__u_cluster__DOT__pe_valid[1U] = 0U;
        vlTOPp->top_level__DOT__gen_clusters__BRA__7__KET____DOT__u_cluster__DOT__pe_a[1U] = 0U;
        vlTOPp->top_level__DOT__gen_clusters__BRA__7__KET____DOT__u_cluster__DOT__pe_b[1U] = 0U;
        vlTOPp->top_level__DOT__gen_clusters__BRA__7__KET____DOT__u_cluster__DOT__pe_seed[1U] = 0U;
    }
    vlTOPp->top_level__DOT__gen_clusters__BRA__0__KET____DOT__u_cluster__DOT__pe_done[0U] 
        = ((IData)(vlTOPp->top_level__DOT__compute_en) 
           & vlTOPp->top_level__DOT__gen_clusters__BRA__0__KET____DOT__u_cluster__DOT__pe_valid
           [0U]);
    vlTOPp->top_level__DOT__gen_clusters__BRA__0__KET____DOT__u_cluster__DOT__pe_done[1U] 
        = ((IData)(vlTOPp->top_level__DOT__compute_en) 
           & vlTOPp->top_level__DOT__gen_clusters__BRA__0__KET____DOT__u_cluster__DOT__pe_valid
           [1U]);
    vlTOPp->top_level__DOT__gen_clusters__BRA__0__KET____DOT__u_cluster__DOT__gen_main_pes__BRA__0__KET____DOT__u_pe__DOT__product_full 
        = VL_MULS_III(32,32,32, VL_EXTENDS_II(32,16, 
                                              vlTOPp->top_level__DOT__gen_clusters__BRA__0__KET____DOT__u_cluster__DOT__pe_a
                                              [0U]), 
                      VL_EXTENDS_II(32,16, vlTOPp->top_level__DOT__gen_clusters__BRA__0__KET____DOT__u_cluster__DOT__pe_b
                                    [0U]));
    vlTOPp->top_level__DOT__gen_clusters__BRA__0__KET____DOT__u_cluster__DOT__gen_main_pes__BRA__0__KET____DOT__u_pe__DOT__product_scaled 
        = VL_SHIFTRS_III(32,32,32, vlTOPp->top_level__DOT__gen_clusters__BRA__0__KET____DOT__u_cluster__DOT__gen_main_pes__BRA__0__KET____DOT__u_pe__DOT__product_full, 8U);
    vlTOPp->top_level__DOT__gen_clusters__BRA__0__KET____DOT__u_cluster__DOT____Vcellout__gen_main_pes__BRA__0__KET____DOT__u_pe__acc_result 
        = (vlTOPp->top_level__DOT__gen_clusters__BRA__0__KET____DOT__u_cluster__DOT__pe_seed
           [0U] + vlTOPp->top_level__DOT__gen_clusters__BRA__0__KET____DOT__u_cluster__DOT__gen_main_pes__BRA__0__KET____DOT__u_pe__DOT__product_scaled);
    vlTOPp->top_level__DOT__gen_clusters__BRA__0__KET____DOT__u_cluster__DOT__gen_main_pes__BRA__1__KET____DOT__u_pe__DOT__product_full 
        = VL_MULS_III(32,32,32, VL_EXTENDS_II(32,16, 
                                              vlTOPp->top_level__DOT__gen_clusters__BRA__0__KET____DOT__u_cluster__DOT__pe_a
                                              [1U]), 
                      VL_EXTENDS_II(32,16, vlTOPp->top_level__DOT__gen_clusters__BRA__0__KET____DOT__u_cluster__DOT__pe_b
                                    [1U]));
    vlTOPp->top_level__DOT__gen_clusters__BRA__0__KET____DOT__u_cluster__DOT__gen_main_pes__BRA__1__KET____DOT__u_pe__DOT__product_scaled 
        = VL_SHIFTRS_III(32,32,32, vlTOPp->top_level__DOT__gen_clusters__BRA__0__KET____DOT__u_cluster__DOT__gen_main_pes__BRA__1__KET____DOT__u_pe__DOT__product_full, 8U);
    vlTOPp->top_level__DOT__gen_clusters__BRA__0__KET____DOT__u_cluster__DOT____Vcellout__gen_main_pes__BRA__1__KET____DOT__u_pe__acc_result 
        = (vlTOPp->top_level__DOT__gen_clusters__BRA__0__KET____DOT__u_cluster__DOT__pe_seed
           [1U] + vlTOPp->top_level__DOT__gen_clusters__BRA__0__KET____DOT__u_cluster__DOT__gen_main_pes__BRA__1__KET____DOT__u_pe__DOT__product_scaled);
    vlTOPp->top_level__DOT__gen_clusters__BRA__1__KET____DOT__u_cluster__DOT__pe_done[0U] 
        = ((IData)(vlTOPp->top_level__DOT__compute_en) 
           & vlTOPp->top_level__DOT__gen_clusters__BRA__1__KET____DOT__u_cluster__DOT__pe_valid
           [0U]);
    vlTOPp->top_level__DOT__gen_clusters__BRA__1__KET____DOT__u_cluster__DOT__pe_done[1U] 
        = ((IData)(vlTOPp->top_level__DOT__compute_en) 
           & vlTOPp->top_level__DOT__gen_clusters__BRA__1__KET____DOT__u_cluster__DOT__pe_valid
           [1U]);
    vlTOPp->top_level__DOT__gen_clusters__BRA__1__KET____DOT__u_cluster__DOT__gen_main_pes__BRA__0__KET____DOT__u_pe__DOT__product_full 
        = VL_MULS_III(32,32,32, VL_EXTENDS_II(32,16, 
                                              vlTOPp->top_level__DOT__gen_clusters__BRA__1__KET____DOT__u_cluster__DOT__pe_a
                                              [0U]), 
                      VL_EXTENDS_II(32,16, vlTOPp->top_level__DOT__gen_clusters__BRA__1__KET____DOT__u_cluster__DOT__pe_b
                                    [0U]));
    vlTOPp->top_level__DOT__gen_clusters__BRA__1__KET____DOT__u_cluster__DOT__gen_main_pes__BRA__0__KET____DOT__u_pe__DOT__product_scaled 
        = VL_SHIFTRS_III(32,32,32, vlTOPp->top_level__DOT__gen_clusters__BRA__1__KET____DOT__u_cluster__DOT__gen_main_pes__BRA__0__KET____DOT__u_pe__DOT__product_full, 8U);
    vlTOPp->top_level__DOT__gen_clusters__BRA__1__KET____DOT__u_cluster__DOT____Vcellout__gen_main_pes__BRA__0__KET____DOT__u_pe__acc_result 
        = (vlTOPp->top_level__DOT__gen_clusters__BRA__1__KET____DOT__u_cluster__DOT__pe_seed
           [0U] + vlTOPp->top_level__DOT__gen_clusters__BRA__1__KET____DOT__u_cluster__DOT__gen_main_pes__BRA__0__KET____DOT__u_pe__DOT__product_scaled);
    vlTOPp->top_level__DOT__gen_clusters__BRA__1__KET____DOT__u_cluster__DOT__gen_main_pes__BRA__1__KET____DOT__u_pe__DOT__product_full 
        = VL_MULS_III(32,32,32, VL_EXTENDS_II(32,16, 
                                              vlTOPp->top_level__DOT__gen_clusters__BRA__1__KET____DOT__u_cluster__DOT__pe_a
                                              [1U]), 
                      VL_EXTENDS_II(32,16, vlTOPp->top_level__DOT__gen_clusters__BRA__1__KET____DOT__u_cluster__DOT__pe_b
                                    [1U]));
    vlTOPp->top_level__DOT__gen_clusters__BRA__1__KET____DOT__u_cluster__DOT__gen_main_pes__BRA__1__KET____DOT__u_pe__DOT__product_scaled 
        = VL_SHIFTRS_III(32,32,32, vlTOPp->top_level__DOT__gen_clusters__BRA__1__KET____DOT__u_cluster__DOT__gen_main_pes__BRA__1__KET____DOT__u_pe__DOT__product_full, 8U);
    vlTOPp->top_level__DOT__gen_clusters__BRA__1__KET____DOT__u_cluster__DOT____Vcellout__gen_main_pes__BRA__1__KET____DOT__u_pe__acc_result 
        = (vlTOPp->top_level__DOT__gen_clusters__BRA__1__KET____DOT__u_cluster__DOT__pe_seed
           [1U] + vlTOPp->top_level__DOT__gen_clusters__BRA__1__KET____DOT__u_cluster__DOT__gen_main_pes__BRA__1__KET____DOT__u_pe__DOT__product_scaled);
    vlTOPp->top_level__DOT__gen_clusters__BRA__2__KET____DOT__u_cluster__DOT__pe_done[0U] 
        = ((IData)(vlTOPp->top_level__DOT__compute_en) 
           & vlTOPp->top_level__DOT__gen_clusters__BRA__2__KET____DOT__u_cluster__DOT__pe_valid
           [0U]);
    vlTOPp->top_level__DOT__gen_clusters__BRA__2__KET____DOT__u_cluster__DOT__pe_done[1U] 
        = ((IData)(vlTOPp->top_level__DOT__compute_en) 
           & vlTOPp->top_level__DOT__gen_clusters__BRA__2__KET____DOT__u_cluster__DOT__pe_valid
           [1U]);
    vlTOPp->top_level__DOT__gen_clusters__BRA__2__KET____DOT__u_cluster__DOT__gen_main_pes__BRA__0__KET____DOT__u_pe__DOT__product_full 
        = VL_MULS_III(32,32,32, VL_EXTENDS_II(32,16, 
                                              vlTOPp->top_level__DOT__gen_clusters__BRA__2__KET____DOT__u_cluster__DOT__pe_a
                                              [0U]), 
                      VL_EXTENDS_II(32,16, vlTOPp->top_level__DOT__gen_clusters__BRA__2__KET____DOT__u_cluster__DOT__pe_b
                                    [0U]));
    vlTOPp->top_level__DOT__gen_clusters__BRA__2__KET____DOT__u_cluster__DOT__gen_main_pes__BRA__0__KET____DOT__u_pe__DOT__product_scaled 
        = VL_SHIFTRS_III(32,32,32, vlTOPp->top_level__DOT__gen_clusters__BRA__2__KET____DOT__u_cluster__DOT__gen_main_pes__BRA__0__KET____DOT__u_pe__DOT__product_full, 8U);
    vlTOPp->top_level__DOT__gen_clusters__BRA__2__KET____DOT__u_cluster__DOT____Vcellout__gen_main_pes__BRA__0__KET____DOT__u_pe__acc_result 
        = (vlTOPp->top_level__DOT__gen_clusters__BRA__2__KET____DOT__u_cluster__DOT__pe_seed
           [0U] + vlTOPp->top_level__DOT__gen_clusters__BRA__2__KET____DOT__u_cluster__DOT__gen_main_pes__BRA__0__KET____DOT__u_pe__DOT__product_scaled);
    vlTOPp->top_level__DOT__gen_clusters__BRA__2__KET____DOT__u_cluster__DOT__gen_main_pes__BRA__1__KET____DOT__u_pe__DOT__product_full 
        = VL_MULS_III(32,32,32, VL_EXTENDS_II(32,16, 
                                              vlTOPp->top_level__DOT__gen_clusters__BRA__2__KET____DOT__u_cluster__DOT__pe_a
                                              [1U]), 
                      VL_EXTENDS_II(32,16, vlTOPp->top_level__DOT__gen_clusters__BRA__2__KET____DOT__u_cluster__DOT__pe_b
                                    [1U]));
    vlTOPp->top_level__DOT__gen_clusters__BRA__2__KET____DOT__u_cluster__DOT__gen_main_pes__BRA__1__KET____DOT__u_pe__DOT__product_scaled 
        = VL_SHIFTRS_III(32,32,32, vlTOPp->top_level__DOT__gen_clusters__BRA__2__KET____DOT__u_cluster__DOT__gen_main_pes__BRA__1__KET____DOT__u_pe__DOT__product_full, 8U);
    vlTOPp->top_level__DOT__gen_clusters__BRA__2__KET____DOT__u_cluster__DOT____Vcellout__gen_main_pes__BRA__1__KET____DOT__u_pe__acc_result 
        = (vlTOPp->top_level__DOT__gen_clusters__BRA__2__KET____DOT__u_cluster__DOT__pe_seed
           [1U] + vlTOPp->top_level__DOT__gen_clusters__BRA__2__KET____DOT__u_cluster__DOT__gen_main_pes__BRA__1__KET____DOT__u_pe__DOT__product_scaled);
    vlTOPp->top_level__DOT__gen_clusters__BRA__3__KET____DOT__u_cluster__DOT__pe_done[0U] 
        = ((IData)(vlTOPp->top_level__DOT__compute_en) 
           & vlTOPp->top_level__DOT__gen_clusters__BRA__3__KET____DOT__u_cluster__DOT__pe_valid
           [0U]);
    vlTOPp->top_level__DOT__gen_clusters__BRA__3__KET____DOT__u_cluster__DOT__pe_done[1U] 
        = ((IData)(vlTOPp->top_level__DOT__compute_en) 
           & vlTOPp->top_level__DOT__gen_clusters__BRA__3__KET____DOT__u_cluster__DOT__pe_valid
           [1U]);
    vlTOPp->top_level__DOT__gen_clusters__BRA__3__KET____DOT__u_cluster__DOT__gen_main_pes__BRA__0__KET____DOT__u_pe__DOT__product_full 
        = VL_MULS_III(32,32,32, VL_EXTENDS_II(32,16, 
                                              vlTOPp->top_level__DOT__gen_clusters__BRA__3__KET____DOT__u_cluster__DOT__pe_a
                                              [0U]), 
                      VL_EXTENDS_II(32,16, vlTOPp->top_level__DOT__gen_clusters__BRA__3__KET____DOT__u_cluster__DOT__pe_b
                                    [0U]));
    vlTOPp->top_level__DOT__gen_clusters__BRA__3__KET____DOT__u_cluster__DOT__gen_main_pes__BRA__0__KET____DOT__u_pe__DOT__product_scaled 
        = VL_SHIFTRS_III(32,32,32, vlTOPp->top_level__DOT__gen_clusters__BRA__3__KET____DOT__u_cluster__DOT__gen_main_pes__BRA__0__KET____DOT__u_pe__DOT__product_full, 8U);
    vlTOPp->top_level__DOT__gen_clusters__BRA__3__KET____DOT__u_cluster__DOT____Vcellout__gen_main_pes__BRA__0__KET____DOT__u_pe__acc_result 
        = (vlTOPp->top_level__DOT__gen_clusters__BRA__3__KET____DOT__u_cluster__DOT__pe_seed
           [0U] + vlTOPp->top_level__DOT__gen_clusters__BRA__3__KET____DOT__u_cluster__DOT__gen_main_pes__BRA__0__KET____DOT__u_pe__DOT__product_scaled);
    vlTOPp->top_level__DOT__gen_clusters__BRA__3__KET____DOT__u_cluster__DOT__gen_main_pes__BRA__1__KET____DOT__u_pe__DOT__product_full 
        = VL_MULS_III(32,32,32, VL_EXTENDS_II(32,16, 
                                              vlTOPp->top_level__DOT__gen_clusters__BRA__3__KET____DOT__u_cluster__DOT__pe_a
                                              [1U]), 
                      VL_EXTENDS_II(32,16, vlTOPp->top_level__DOT__gen_clusters__BRA__3__KET____DOT__u_cluster__DOT__pe_b
                                    [1U]));
    vlTOPp->top_level__DOT__gen_clusters__BRA__3__KET____DOT__u_cluster__DOT__gen_main_pes__BRA__1__KET____DOT__u_pe__DOT__product_scaled 
        = VL_SHIFTRS_III(32,32,32, vlTOPp->top_level__DOT__gen_clusters__BRA__3__KET____DOT__u_cluster__DOT__gen_main_pes__BRA__1__KET____DOT__u_pe__DOT__product_full, 8U);
    vlTOPp->top_level__DOT__gen_clusters__BRA__3__KET____DOT__u_cluster__DOT____Vcellout__gen_main_pes__BRA__1__KET____DOT__u_pe__acc_result 
        = (vlTOPp->top_level__DOT__gen_clusters__BRA__3__KET____DOT__u_cluster__DOT__pe_seed
           [1U] + vlTOPp->top_level__DOT__gen_clusters__BRA__3__KET____DOT__u_cluster__DOT__gen_main_pes__BRA__1__KET____DOT__u_pe__DOT__product_scaled);
    vlTOPp->top_level__DOT__gen_clusters__BRA__4__KET____DOT__u_cluster__DOT__pe_done[0U] 
        = ((IData)(vlTOPp->top_level__DOT__compute_en) 
           & vlTOPp->top_level__DOT__gen_clusters__BRA__4__KET____DOT__u_cluster__DOT__pe_valid
           [0U]);
    vlTOPp->top_level__DOT__gen_clusters__BRA__4__KET____DOT__u_cluster__DOT__pe_done[1U] 
        = ((IData)(vlTOPp->top_level__DOT__compute_en) 
           & vlTOPp->top_level__DOT__gen_clusters__BRA__4__KET____DOT__u_cluster__DOT__pe_valid
           [1U]);
    vlTOPp->top_level__DOT__gen_clusters__BRA__4__KET____DOT__u_cluster__DOT__gen_main_pes__BRA__0__KET____DOT__u_pe__DOT__product_full 
        = VL_MULS_III(32,32,32, VL_EXTENDS_II(32,16, 
                                              vlTOPp->top_level__DOT__gen_clusters__BRA__4__KET____DOT__u_cluster__DOT__pe_a
                                              [0U]), 
                      VL_EXTENDS_II(32,16, vlTOPp->top_level__DOT__gen_clusters__BRA__4__KET____DOT__u_cluster__DOT__pe_b
                                    [0U]));
    vlTOPp->top_level__DOT__gen_clusters__BRA__4__KET____DOT__u_cluster__DOT__gen_main_pes__BRA__0__KET____DOT__u_pe__DOT__product_scaled 
        = VL_SHIFTRS_III(32,32,32, vlTOPp->top_level__DOT__gen_clusters__BRA__4__KET____DOT__u_cluster__DOT__gen_main_pes__BRA__0__KET____DOT__u_pe__DOT__product_full, 8U);
    vlTOPp->top_level__DOT__gen_clusters__BRA__4__KET____DOT__u_cluster__DOT____Vcellout__gen_main_pes__BRA__0__KET____DOT__u_pe__acc_result 
        = (vlTOPp->top_level__DOT__gen_clusters__BRA__4__KET____DOT__u_cluster__DOT__pe_seed
           [0U] + vlTOPp->top_level__DOT__gen_clusters__BRA__4__KET____DOT__u_cluster__DOT__gen_main_pes__BRA__0__KET____DOT__u_pe__DOT__product_scaled);
    vlTOPp->top_level__DOT__gen_clusters__BRA__4__KET____DOT__u_cluster__DOT__gen_main_pes__BRA__1__KET____DOT__u_pe__DOT__product_full 
        = VL_MULS_III(32,32,32, VL_EXTENDS_II(32,16, 
                                              vlTOPp->top_level__DOT__gen_clusters__BRA__4__KET____DOT__u_cluster__DOT__pe_a
                                              [1U]), 
                      VL_EXTENDS_II(32,16, vlTOPp->top_level__DOT__gen_clusters__BRA__4__KET____DOT__u_cluster__DOT__pe_b
                                    [1U]));
    vlTOPp->top_level__DOT__gen_clusters__BRA__4__KET____DOT__u_cluster__DOT__gen_main_pes__BRA__1__KET____DOT__u_pe__DOT__product_scaled 
        = VL_SHIFTRS_III(32,32,32, vlTOPp->top_level__DOT__gen_clusters__BRA__4__KET____DOT__u_cluster__DOT__gen_main_pes__BRA__1__KET____DOT__u_pe__DOT__product_full, 8U);
    vlTOPp->top_level__DOT__gen_clusters__BRA__4__KET____DOT__u_cluster__DOT____Vcellout__gen_main_pes__BRA__1__KET____DOT__u_pe__acc_result 
        = (vlTOPp->top_level__DOT__gen_clusters__BRA__4__KET____DOT__u_cluster__DOT__pe_seed
           [1U] + vlTOPp->top_level__DOT__gen_clusters__BRA__4__KET____DOT__u_cluster__DOT__gen_main_pes__BRA__1__KET____DOT__u_pe__DOT__product_scaled);
    vlTOPp->top_level__DOT__gen_clusters__BRA__5__KET____DOT__u_cluster__DOT__pe_done[0U] 
        = ((IData)(vlTOPp->top_level__DOT__compute_en) 
           & vlTOPp->top_level__DOT__gen_clusters__BRA__5__KET____DOT__u_cluster__DOT__pe_valid
           [0U]);
    vlTOPp->top_level__DOT__gen_clusters__BRA__5__KET____DOT__u_cluster__DOT__pe_done[1U] 
        = ((IData)(vlTOPp->top_level__DOT__compute_en) 
           & vlTOPp->top_level__DOT__gen_clusters__BRA__5__KET____DOT__u_cluster__DOT__pe_valid
           [1U]);
    vlTOPp->top_level__DOT__gen_clusters__BRA__5__KET____DOT__u_cluster__DOT__gen_main_pes__BRA__0__KET____DOT__u_pe__DOT__product_full 
        = VL_MULS_III(32,32,32, VL_EXTENDS_II(32,16, 
                                              vlTOPp->top_level__DOT__gen_clusters__BRA__5__KET____DOT__u_cluster__DOT__pe_a
                                              [0U]), 
                      VL_EXTENDS_II(32,16, vlTOPp->top_level__DOT__gen_clusters__BRA__5__KET____DOT__u_cluster__DOT__pe_b
                                    [0U]));
    vlTOPp->top_level__DOT__gen_clusters__BRA__5__KET____DOT__u_cluster__DOT__gen_main_pes__BRA__0__KET____DOT__u_pe__DOT__product_scaled 
        = VL_SHIFTRS_III(32,32,32, vlTOPp->top_level__DOT__gen_clusters__BRA__5__KET____DOT__u_cluster__DOT__gen_main_pes__BRA__0__KET____DOT__u_pe__DOT__product_full, 8U);
    vlTOPp->top_level__DOT__gen_clusters__BRA__5__KET____DOT__u_cluster__DOT____Vcellout__gen_main_pes__BRA__0__KET____DOT__u_pe__acc_result 
        = (vlTOPp->top_level__DOT__gen_clusters__BRA__5__KET____DOT__u_cluster__DOT__pe_seed
           [0U] + vlTOPp->top_level__DOT__gen_clusters__BRA__5__KET____DOT__u_cluster__DOT__gen_main_pes__BRA__0__KET____DOT__u_pe__DOT__product_scaled);
    vlTOPp->top_level__DOT__gen_clusters__BRA__5__KET____DOT__u_cluster__DOT__gen_main_pes__BRA__1__KET____DOT__u_pe__DOT__product_full 
        = VL_MULS_III(32,32,32, VL_EXTENDS_II(32,16, 
                                              vlTOPp->top_level__DOT__gen_clusters__BRA__5__KET____DOT__u_cluster__DOT__pe_a
                                              [1U]), 
                      VL_EXTENDS_II(32,16, vlTOPp->top_level__DOT__gen_clusters__BRA__5__KET____DOT__u_cluster__DOT__pe_b
                                    [1U]));
    vlTOPp->top_level__DOT__gen_clusters__BRA__5__KET____DOT__u_cluster__DOT__gen_main_pes__BRA__1__KET____DOT__u_pe__DOT__product_scaled 
        = VL_SHIFTRS_III(32,32,32, vlTOPp->top_level__DOT__gen_clusters__BRA__5__KET____DOT__u_cluster__DOT__gen_main_pes__BRA__1__KET____DOT__u_pe__DOT__product_full, 8U);
    vlTOPp->top_level__DOT__gen_clusters__BRA__5__KET____DOT__u_cluster__DOT____Vcellout__gen_main_pes__BRA__1__KET____DOT__u_pe__acc_result 
        = (vlTOPp->top_level__DOT__gen_clusters__BRA__5__KET____DOT__u_cluster__DOT__pe_seed
           [1U] + vlTOPp->top_level__DOT__gen_clusters__BRA__5__KET____DOT__u_cluster__DOT__gen_main_pes__BRA__1__KET____DOT__u_pe__DOT__product_scaled);
    vlTOPp->top_level__DOT__gen_clusters__BRA__6__KET____DOT__u_cluster__DOT__pe_done[0U] 
        = ((IData)(vlTOPp->top_level__DOT__compute_en) 
           & vlTOPp->top_level__DOT__gen_clusters__BRA__6__KET____DOT__u_cluster__DOT__pe_valid
           [0U]);
    vlTOPp->top_level__DOT__gen_clusters__BRA__6__KET____DOT__u_cluster__DOT__pe_done[1U] 
        = ((IData)(vlTOPp->top_level__DOT__compute_en) 
           & vlTOPp->top_level__DOT__gen_clusters__BRA__6__KET____DOT__u_cluster__DOT__pe_valid
           [1U]);
    vlTOPp->top_level__DOT__gen_clusters__BRA__6__KET____DOT__u_cluster__DOT__gen_main_pes__BRA__0__KET____DOT__u_pe__DOT__product_full 
        = VL_MULS_III(32,32,32, VL_EXTENDS_II(32,16, 
                                              vlTOPp->top_level__DOT__gen_clusters__BRA__6__KET____DOT__u_cluster__DOT__pe_a
                                              [0U]), 
                      VL_EXTENDS_II(32,16, vlTOPp->top_level__DOT__gen_clusters__BRA__6__KET____DOT__u_cluster__DOT__pe_b
                                    [0U]));
    vlTOPp->top_level__DOT__gen_clusters__BRA__6__KET____DOT__u_cluster__DOT__gen_main_pes__BRA__0__KET____DOT__u_pe__DOT__product_scaled 
        = VL_SHIFTRS_III(32,32,32, vlTOPp->top_level__DOT__gen_clusters__BRA__6__KET____DOT__u_cluster__DOT__gen_main_pes__BRA__0__KET____DOT__u_pe__DOT__product_full, 8U);
    vlTOPp->top_level__DOT__gen_clusters__BRA__6__KET____DOT__u_cluster__DOT____Vcellout__gen_main_pes__BRA__0__KET____DOT__u_pe__acc_result 
        = (vlTOPp->top_level__DOT__gen_clusters__BRA__6__KET____DOT__u_cluster__DOT__pe_seed
           [0U] + vlTOPp->top_level__DOT__gen_clusters__BRA__6__KET____DOT__u_cluster__DOT__gen_main_pes__BRA__0__KET____DOT__u_pe__DOT__product_scaled);
    vlTOPp->top_level__DOT__gen_clusters__BRA__6__KET____DOT__u_cluster__DOT__gen_main_pes__BRA__1__KET____DOT__u_pe__DOT__product_full 
        = VL_MULS_III(32,32,32, VL_EXTENDS_II(32,16, 
                                              vlTOPp->top_level__DOT__gen_clusters__BRA__6__KET____DOT__u_cluster__DOT__pe_a
                                              [1U]), 
                      VL_EXTENDS_II(32,16, vlTOPp->top_level__DOT__gen_clusters__BRA__6__KET____DOT__u_cluster__DOT__pe_b
                                    [1U]));
    vlTOPp->top_level__DOT__gen_clusters__BRA__6__KET____DOT__u_cluster__DOT__gen_main_pes__BRA__1__KET____DOT__u_pe__DOT__product_scaled 
        = VL_SHIFTRS_III(32,32,32, vlTOPp->top_level__DOT__gen_clusters__BRA__6__KET____DOT__u_cluster__DOT__gen_main_pes__BRA__1__KET____DOT__u_pe__DOT__product_full, 8U);
    vlTOPp->top_level__DOT__gen_clusters__BRA__6__KET____DOT__u_cluster__DOT____Vcellout__gen_main_pes__BRA__1__KET____DOT__u_pe__acc_result 
        = (vlTOPp->top_level__DOT__gen_clusters__BRA__6__KET____DOT__u_cluster__DOT__pe_seed
           [1U] + vlTOPp->top_level__DOT__gen_clusters__BRA__6__KET____DOT__u_cluster__DOT__gen_main_pes__BRA__1__KET____DOT__u_pe__DOT__product_scaled);
    vlTOPp->top_level__DOT__gen_clusters__BRA__7__KET____DOT__u_cluster__DOT__pe_done[0U] 
        = ((IData)(vlTOPp->top_level__DOT__compute_en) 
           & vlTOPp->top_level__DOT__gen_clusters__BRA__7__KET____DOT__u_cluster__DOT__pe_valid
           [0U]);
    vlTOPp->top_level__DOT__gen_clusters__BRA__7__KET____DOT__u_cluster__DOT__pe_done[1U] 
        = ((IData)(vlTOPp->top_level__DOT__compute_en) 
           & vlTOPp->top_level__DOT__gen_clusters__BRA__7__KET____DOT__u_cluster__DOT__pe_valid
           [1U]);
    vlTOPp->top_level__DOT__gen_clusters__BRA__7__KET____DOT__u_cluster__DOT__gen_main_pes__BRA__0__KET____DOT__u_pe__DOT__product_full 
        = VL_MULS_III(32,32,32, VL_EXTENDS_II(32,16, 
                                              vlTOPp->top_level__DOT__gen_clusters__BRA__7__KET____DOT__u_cluster__DOT__pe_a
                                              [0U]), 
                      VL_EXTENDS_II(32,16, vlTOPp->top_level__DOT__gen_clusters__BRA__7__KET____DOT__u_cluster__DOT__pe_b
                                    [0U]));
    vlTOPp->top_level__DOT__gen_clusters__BRA__7__KET____DOT__u_cluster__DOT__gen_main_pes__BRA__0__KET____DOT__u_pe__DOT__product_scaled 
        = VL_SHIFTRS_III(32,32,32, vlTOPp->top_level__DOT__gen_clusters__BRA__7__KET____DOT__u_cluster__DOT__gen_main_pes__BRA__0__KET____DOT__u_pe__DOT__product_full, 8U);
    vlTOPp->top_level__DOT__gen_clusters__BRA__7__KET____DOT__u_cluster__DOT____Vcellout__gen_main_pes__BRA__0__KET____DOT__u_pe__acc_result 
        = (vlTOPp->top_level__DOT__gen_clusters__BRA__7__KET____DOT__u_cluster__DOT__pe_seed
           [0U] + vlTOPp->top_level__DOT__gen_clusters__BRA__7__KET____DOT__u_cluster__DOT__gen_main_pes__BRA__0__KET____DOT__u_pe__DOT__product_scaled);
    vlTOPp->top_level__DOT__gen_clusters__BRA__7__KET____DOT__u_cluster__DOT__gen_main_pes__BRA__1__KET____DOT__u_pe__DOT__product_full 
        = VL_MULS_III(32,32,32, VL_EXTENDS_II(32,16, 
                                              vlTOPp->top_level__DOT__gen_clusters__BRA__7__KET____DOT__u_cluster__DOT__pe_a
                                              [1U]), 
                      VL_EXTENDS_II(32,16, vlTOPp->top_level__DOT__gen_clusters__BRA__7__KET____DOT__u_cluster__DOT__pe_b
                                    [1U]));
    vlTOPp->top_level__DOT__gen_clusters__BRA__7__KET____DOT__u_cluster__DOT__gen_main_pes__BRA__1__KET____DOT__u_pe__DOT__product_scaled 
        = VL_SHIFTRS_III(32,32,32, vlTOPp->top_level__DOT__gen_clusters__BRA__7__KET____DOT__u_cluster__DOT__gen_main_pes__BRA__1__KET____DOT__u_pe__DOT__product_full, 8U);
    vlTOPp->top_level__DOT__gen_clusters__BRA__7__KET____DOT__u_cluster__DOT____Vcellout__gen_main_pes__BRA__1__KET____DOT__u_pe__acc_result 
        = (vlTOPp->top_level__DOT__gen_clusters__BRA__7__KET____DOT__u_cluster__DOT__pe_seed
           [1U] + vlTOPp->top_level__DOT__gen_clusters__BRA__7__KET____DOT__u_cluster__DOT__gen_main_pes__BRA__1__KET____DOT__u_pe__DOT__product_scaled);
    vlTOPp->top_level__DOT__gen_clusters__BRA__0__KET____DOT__u_cluster__DOT__pe_result[0U] 
        = vlTOPp->top_level__DOT__gen_clusters__BRA__0__KET____DOT__u_cluster__DOT____Vcellout__gen_main_pes__BRA__0__KET____DOT__u_pe__acc_result;
    vlTOPp->top_level__DOT__gen_clusters__BRA__0__KET____DOT__u_cluster__DOT__pe_result[1U] 
        = vlTOPp->top_level__DOT__gen_clusters__BRA__0__KET____DOT__u_cluster__DOT____Vcellout__gen_main_pes__BRA__1__KET____DOT__u_pe__acc_result;
    vlTOPp->top_level__DOT__gen_clusters__BRA__1__KET____DOT__u_cluster__DOT__pe_result[0U] 
        = vlTOPp->top_level__DOT__gen_clusters__BRA__1__KET____DOT__u_cluster__DOT____Vcellout__gen_main_pes__BRA__0__KET____DOT__u_pe__acc_result;
    vlTOPp->top_level__DOT__gen_clusters__BRA__1__KET____DOT__u_cluster__DOT__pe_result[1U] 
        = vlTOPp->top_level__DOT__gen_clusters__BRA__1__KET____DOT__u_cluster__DOT____Vcellout__gen_main_pes__BRA__1__KET____DOT__u_pe__acc_result;
    vlTOPp->top_level__DOT__gen_clusters__BRA__2__KET____DOT__u_cluster__DOT__pe_result[0U] 
        = vlTOPp->top_level__DOT__gen_clusters__BRA__2__KET____DOT__u_cluster__DOT____Vcellout__gen_main_pes__BRA__0__KET____DOT__u_pe__acc_result;
    vlTOPp->top_level__DOT__gen_clusters__BRA__2__KET____DOT__u_cluster__DOT__pe_result[1U] 
        = vlTOPp->top_level__DOT__gen_clusters__BRA__2__KET____DOT__u_cluster__DOT____Vcellout__gen_main_pes__BRA__1__KET____DOT__u_pe__acc_result;
    vlTOPp->top_level__DOT__gen_clusters__BRA__3__KET____DOT__u_cluster__DOT__pe_result[0U] 
        = vlTOPp->top_level__DOT__gen_clusters__BRA__3__KET____DOT__u_cluster__DOT____Vcellout__gen_main_pes__BRA__0__KET____DOT__u_pe__acc_result;
    vlTOPp->top_level__DOT__gen_clusters__BRA__3__KET____DOT__u_cluster__DOT__pe_result[1U] 
        = vlTOPp->top_level__DOT__gen_clusters__BRA__3__KET____DOT__u_cluster__DOT____Vcellout__gen_main_pes__BRA__1__KET____DOT__u_pe__acc_result;
    vlTOPp->top_level__DOT__gen_clusters__BRA__4__KET____DOT__u_cluster__DOT__pe_result[0U] 
        = vlTOPp->top_level__DOT__gen_clusters__BRA__4__KET____DOT__u_cluster__DOT____Vcellout__gen_main_pes__BRA__0__KET____DOT__u_pe__acc_result;
    vlTOPp->top_level__DOT__gen_clusters__BRA__4__KET____DOT__u_cluster__DOT__pe_result[1U] 
        = vlTOPp->top_level__DOT__gen_clusters__BRA__4__KET____DOT__u_cluster__DOT____Vcellout__gen_main_pes__BRA__1__KET____DOT__u_pe__acc_result;
    vlTOPp->top_level__DOT__gen_clusters__BRA__5__KET____DOT__u_cluster__DOT__pe_result[0U] 
        = vlTOPp->top_level__DOT__gen_clusters__BRA__5__KET____DOT__u_cluster__DOT____Vcellout__gen_main_pes__BRA__0__KET____DOT__u_pe__acc_result;
    vlTOPp->top_level__DOT__gen_clusters__BRA__5__KET____DOT__u_cluster__DOT__pe_result[1U] 
        = vlTOPp->top_level__DOT__gen_clusters__BRA__5__KET____DOT__u_cluster__DOT____Vcellout__gen_main_pes__BRA__1__KET____DOT__u_pe__acc_result;
    vlTOPp->top_level__DOT__gen_clusters__BRA__6__KET____DOT__u_cluster__DOT__pe_result[0U] 
        = vlTOPp->top_level__DOT__gen_clusters__BRA__6__KET____DOT__u_cluster__DOT____Vcellout__gen_main_pes__BRA__0__KET____DOT__u_pe__acc_result;
    vlTOPp->top_level__DOT__gen_clusters__BRA__6__KET____DOT__u_cluster__DOT__pe_result[1U] 
        = vlTOPp->top_level__DOT__gen_clusters__BRA__6__KET____DOT__u_cluster__DOT____Vcellout__gen_main_pes__BRA__1__KET____DOT__u_pe__acc_result;
    vlTOPp->top_level__DOT__gen_clusters__BRA__7__KET____DOT__u_cluster__DOT__pe_result[0U] 
        = vlTOPp->top_level__DOT__gen_clusters__BRA__7__KET____DOT__u_cluster__DOT____Vcellout__gen_main_pes__BRA__0__KET____DOT__u_pe__acc_result;
    vlTOPp->top_level__DOT__gen_clusters__BRA__7__KET____DOT__u_cluster__DOT__pe_result[1U] 
        = vlTOPp->top_level__DOT__gen_clusters__BRA__7__KET____DOT__u_cluster__DOT____Vcellout__gen_main_pes__BRA__1__KET____DOT__u_pe__acc_result;
    vlTOPp->top_level__DOT__gen_clusters__BRA__0__KET____DOT__u_cluster__DOT__accum_next[0U] 
        = vlTOPp->top_level__DOT__gen_clusters__BRA__0__KET____DOT__u_cluster__DOT__accum_bank
        [0U];
    vlTOPp->top_level__DOT__gen_clusters__BRA__0__KET____DOT__u_cluster__DOT__accum_next[1U] 
        = vlTOPp->top_level__DOT__gen_clusters__BRA__0__KET____DOT__u_cluster__DOT__accum_bank
        [1U];
    vlTOPp->top_level__DOT__gen_clusters__BRA__0__KET____DOT__u_cluster__DOT__accum_next[2U] 
        = vlTOPp->top_level__DOT__gen_clusters__BRA__0__KET____DOT__u_cluster__DOT__accum_bank
        [2U];
    vlTOPp->top_level__DOT__gen_clusters__BRA__0__KET____DOT__u_cluster__DOT__accum_next[3U] 
        = vlTOPp->top_level__DOT__gen_clusters__BRA__0__KET____DOT__u_cluster__DOT__accum_bank
        [3U];
    vlTOPp->top_level__DOT__gen_clusters__BRA__0__KET____DOT__u_cluster__DOT__logical_lane 
        = ((IData)(vlTOPp->top_level__DOT__shared_phase) 
           << 1U);
    if ((vlTOPp->top_level__DOT__gen_clusters__BRA__0__KET____DOT__u_cluster__DOT__pe_done
         [0U] & VL_GTS_III(1,32,32, 4U, vlTOPp->top_level__DOT__gen_clusters__BRA__0__KET____DOT__u_cluster__DOT__logical_lane))) {
        vlTOPp->top_level__DOT__gen_clusters__BRA__0__KET____DOT__u_cluster__DOT__accum_next[(3U 
                                                                                & vlTOPp->top_level__DOT__gen_clusters__BRA__0__KET____DOT__u_cluster__DOT__logical_lane)] 
            = vlTOPp->top_level__DOT__gen_clusters__BRA__0__KET____DOT__u_cluster__DOT__pe_result
            [0U];
    }
    vlTOPp->top_level__DOT__gen_clusters__BRA__0__KET____DOT__u_cluster__DOT__logical_lane 
        = ((IData)(1U) + ((IData)(vlTOPp->top_level__DOT__shared_phase) 
                          << 1U));
    if ((vlTOPp->top_level__DOT__gen_clusters__BRA__0__KET____DOT__u_cluster__DOT__pe_done
         [1U] & VL_GTS_III(1,32,32, 4U, vlTOPp->top_level__DOT__gen_clusters__BRA__0__KET____DOT__u_cluster__DOT__logical_lane))) {
        vlTOPp->top_level__DOT__gen_clusters__BRA__0__KET____DOT__u_cluster__DOT__accum_next[(3U 
                                                                                & vlTOPp->top_level__DOT__gen_clusters__BRA__0__KET____DOT__u_cluster__DOT__logical_lane)] 
            = vlTOPp->top_level__DOT__gen_clusters__BRA__0__KET____DOT__u_cluster__DOT__pe_result
            [1U];
    }
    vlTOPp->top_level__DOT__gen_clusters__BRA__1__KET____DOT__u_cluster__DOT__accum_next[0U] 
        = vlTOPp->top_level__DOT__gen_clusters__BRA__1__KET____DOT__u_cluster__DOT__accum_bank
        [0U];
    vlTOPp->top_level__DOT__gen_clusters__BRA__1__KET____DOT__u_cluster__DOT__accum_next[1U] 
        = vlTOPp->top_level__DOT__gen_clusters__BRA__1__KET____DOT__u_cluster__DOT__accum_bank
        [1U];
    vlTOPp->top_level__DOT__gen_clusters__BRA__1__KET____DOT__u_cluster__DOT__accum_next[2U] 
        = vlTOPp->top_level__DOT__gen_clusters__BRA__1__KET____DOT__u_cluster__DOT__accum_bank
        [2U];
    vlTOPp->top_level__DOT__gen_clusters__BRA__1__KET____DOT__u_cluster__DOT__accum_next[3U] 
        = vlTOPp->top_level__DOT__gen_clusters__BRA__1__KET____DOT__u_cluster__DOT__accum_bank
        [3U];
    vlTOPp->top_level__DOT__gen_clusters__BRA__1__KET____DOT__u_cluster__DOT__logical_lane 
        = ((IData)(vlTOPp->top_level__DOT__shared_phase) 
           << 1U);
    if ((vlTOPp->top_level__DOT__gen_clusters__BRA__1__KET____DOT__u_cluster__DOT__pe_done
         [0U] & VL_GTS_III(1,32,32, 4U, vlTOPp->top_level__DOT__gen_clusters__BRA__1__KET____DOT__u_cluster__DOT__logical_lane))) {
        vlTOPp->top_level__DOT__gen_clusters__BRA__1__KET____DOT__u_cluster__DOT__accum_next[(3U 
                                                                                & vlTOPp->top_level__DOT__gen_clusters__BRA__1__KET____DOT__u_cluster__DOT__logical_lane)] 
            = vlTOPp->top_level__DOT__gen_clusters__BRA__1__KET____DOT__u_cluster__DOT__pe_result
            [0U];
    }
    vlTOPp->top_level__DOT__gen_clusters__BRA__1__KET____DOT__u_cluster__DOT__logical_lane 
        = ((IData)(1U) + ((IData)(vlTOPp->top_level__DOT__shared_phase) 
                          << 1U));
    if ((vlTOPp->top_level__DOT__gen_clusters__BRA__1__KET____DOT__u_cluster__DOT__pe_done
         [1U] & VL_GTS_III(1,32,32, 4U, vlTOPp->top_level__DOT__gen_clusters__BRA__1__KET____DOT__u_cluster__DOT__logical_lane))) {
        vlTOPp->top_level__DOT__gen_clusters__BRA__1__KET____DOT__u_cluster__DOT__accum_next[(3U 
                                                                                & vlTOPp->top_level__DOT__gen_clusters__BRA__1__KET____DOT__u_cluster__DOT__logical_lane)] 
            = vlTOPp->top_level__DOT__gen_clusters__BRA__1__KET____DOT__u_cluster__DOT__pe_result
            [1U];
    }
    vlTOPp->top_level__DOT__gen_clusters__BRA__2__KET____DOT__u_cluster__DOT__accum_next[0U] 
        = vlTOPp->top_level__DOT__gen_clusters__BRA__2__KET____DOT__u_cluster__DOT__accum_bank
        [0U];
    vlTOPp->top_level__DOT__gen_clusters__BRA__2__KET____DOT__u_cluster__DOT__accum_next[1U] 
        = vlTOPp->top_level__DOT__gen_clusters__BRA__2__KET____DOT__u_cluster__DOT__accum_bank
        [1U];
    vlTOPp->top_level__DOT__gen_clusters__BRA__2__KET____DOT__u_cluster__DOT__accum_next[2U] 
        = vlTOPp->top_level__DOT__gen_clusters__BRA__2__KET____DOT__u_cluster__DOT__accum_bank
        [2U];
    vlTOPp->top_level__DOT__gen_clusters__BRA__2__KET____DOT__u_cluster__DOT__accum_next[3U] 
        = vlTOPp->top_level__DOT__gen_clusters__BRA__2__KET____DOT__u_cluster__DOT__accum_bank
        [3U];
    vlTOPp->top_level__DOT__gen_clusters__BRA__2__KET____DOT__u_cluster__DOT__logical_lane 
        = ((IData)(vlTOPp->top_level__DOT__shared_phase) 
           << 1U);
    if ((vlTOPp->top_level__DOT__gen_clusters__BRA__2__KET____DOT__u_cluster__DOT__pe_done
         [0U] & VL_GTS_III(1,32,32, 4U, vlTOPp->top_level__DOT__gen_clusters__BRA__2__KET____DOT__u_cluster__DOT__logical_lane))) {
        vlTOPp->top_level__DOT__gen_clusters__BRA__2__KET____DOT__u_cluster__DOT__accum_next[(3U 
                                                                                & vlTOPp->top_level__DOT__gen_clusters__BRA__2__KET____DOT__u_cluster__DOT__logical_lane)] 
            = vlTOPp->top_level__DOT__gen_clusters__BRA__2__KET____DOT__u_cluster__DOT__pe_result
            [0U];
    }
    vlTOPp->top_level__DOT__gen_clusters__BRA__2__KET____DOT__u_cluster__DOT__logical_lane 
        = ((IData)(1U) + ((IData)(vlTOPp->top_level__DOT__shared_phase) 
                          << 1U));
    if ((vlTOPp->top_level__DOT__gen_clusters__BRA__2__KET____DOT__u_cluster__DOT__pe_done
         [1U] & VL_GTS_III(1,32,32, 4U, vlTOPp->top_level__DOT__gen_clusters__BRA__2__KET____DOT__u_cluster__DOT__logical_lane))) {
        vlTOPp->top_level__DOT__gen_clusters__BRA__2__KET____DOT__u_cluster__DOT__accum_next[(3U 
                                                                                & vlTOPp->top_level__DOT__gen_clusters__BRA__2__KET____DOT__u_cluster__DOT__logical_lane)] 
            = vlTOPp->top_level__DOT__gen_clusters__BRA__2__KET____DOT__u_cluster__DOT__pe_result
            [1U];
    }
    vlTOPp->top_level__DOT__gen_clusters__BRA__3__KET____DOT__u_cluster__DOT__accum_next[0U] 
        = vlTOPp->top_level__DOT__gen_clusters__BRA__3__KET____DOT__u_cluster__DOT__accum_bank
        [0U];
    vlTOPp->top_level__DOT__gen_clusters__BRA__3__KET____DOT__u_cluster__DOT__accum_next[1U] 
        = vlTOPp->top_level__DOT__gen_clusters__BRA__3__KET____DOT__u_cluster__DOT__accum_bank
        [1U];
    vlTOPp->top_level__DOT__gen_clusters__BRA__3__KET____DOT__u_cluster__DOT__accum_next[2U] 
        = vlTOPp->top_level__DOT__gen_clusters__BRA__3__KET____DOT__u_cluster__DOT__accum_bank
        [2U];
    vlTOPp->top_level__DOT__gen_clusters__BRA__3__KET____DOT__u_cluster__DOT__accum_next[3U] 
        = vlTOPp->top_level__DOT__gen_clusters__BRA__3__KET____DOT__u_cluster__DOT__accum_bank
        [3U];
    vlTOPp->top_level__DOT__gen_clusters__BRA__3__KET____DOT__u_cluster__DOT__logical_lane 
        = ((IData)(vlTOPp->top_level__DOT__shared_phase) 
           << 1U);
    if ((vlTOPp->top_level__DOT__gen_clusters__BRA__3__KET____DOT__u_cluster__DOT__pe_done
         [0U] & VL_GTS_III(1,32,32, 4U, vlTOPp->top_level__DOT__gen_clusters__BRA__3__KET____DOT__u_cluster__DOT__logical_lane))) {
        vlTOPp->top_level__DOT__gen_clusters__BRA__3__KET____DOT__u_cluster__DOT__accum_next[(3U 
                                                                                & vlTOPp->top_level__DOT__gen_clusters__BRA__3__KET____DOT__u_cluster__DOT__logical_lane)] 
            = vlTOPp->top_level__DOT__gen_clusters__BRA__3__KET____DOT__u_cluster__DOT__pe_result
            [0U];
    }
    vlTOPp->top_level__DOT__gen_clusters__BRA__3__KET____DOT__u_cluster__DOT__logical_lane 
        = ((IData)(1U) + ((IData)(vlTOPp->top_level__DOT__shared_phase) 
                          << 1U));
    if ((vlTOPp->top_level__DOT__gen_clusters__BRA__3__KET____DOT__u_cluster__DOT__pe_done
         [1U] & VL_GTS_III(1,32,32, 4U, vlTOPp->top_level__DOT__gen_clusters__BRA__3__KET____DOT__u_cluster__DOT__logical_lane))) {
        vlTOPp->top_level__DOT__gen_clusters__BRA__3__KET____DOT__u_cluster__DOT__accum_next[(3U 
                                                                                & vlTOPp->top_level__DOT__gen_clusters__BRA__3__KET____DOT__u_cluster__DOT__logical_lane)] 
            = vlTOPp->top_level__DOT__gen_clusters__BRA__3__KET____DOT__u_cluster__DOT__pe_result
            [1U];
    }
    vlTOPp->top_level__DOT__gen_clusters__BRA__4__KET____DOT__u_cluster__DOT__accum_next[0U] 
        = vlTOPp->top_level__DOT__gen_clusters__BRA__4__KET____DOT__u_cluster__DOT__accum_bank
        [0U];
    vlTOPp->top_level__DOT__gen_clusters__BRA__4__KET____DOT__u_cluster__DOT__accum_next[1U] 
        = vlTOPp->top_level__DOT__gen_clusters__BRA__4__KET____DOT__u_cluster__DOT__accum_bank
        [1U];
    vlTOPp->top_level__DOT__gen_clusters__BRA__4__KET____DOT__u_cluster__DOT__accum_next[2U] 
        = vlTOPp->top_level__DOT__gen_clusters__BRA__4__KET____DOT__u_cluster__DOT__accum_bank
        [2U];
    vlTOPp->top_level__DOT__gen_clusters__BRA__4__KET____DOT__u_cluster__DOT__accum_next[3U] 
        = vlTOPp->top_level__DOT__gen_clusters__BRA__4__KET____DOT__u_cluster__DOT__accum_bank
        [3U];
    vlTOPp->top_level__DOT__gen_clusters__BRA__4__KET____DOT__u_cluster__DOT__logical_lane 
        = ((IData)(vlTOPp->top_level__DOT__shared_phase) 
           << 1U);
    if ((vlTOPp->top_level__DOT__gen_clusters__BRA__4__KET____DOT__u_cluster__DOT__pe_done
         [0U] & VL_GTS_III(1,32,32, 4U, vlTOPp->top_level__DOT__gen_clusters__BRA__4__KET____DOT__u_cluster__DOT__logical_lane))) {
        vlTOPp->top_level__DOT__gen_clusters__BRA__4__KET____DOT__u_cluster__DOT__accum_next[(3U 
                                                                                & vlTOPp->top_level__DOT__gen_clusters__BRA__4__KET____DOT__u_cluster__DOT__logical_lane)] 
            = vlTOPp->top_level__DOT__gen_clusters__BRA__4__KET____DOT__u_cluster__DOT__pe_result
            [0U];
    }
    vlTOPp->top_level__DOT__gen_clusters__BRA__4__KET____DOT__u_cluster__DOT__logical_lane 
        = ((IData)(1U) + ((IData)(vlTOPp->top_level__DOT__shared_phase) 
                          << 1U));
    if ((vlTOPp->top_level__DOT__gen_clusters__BRA__4__KET____DOT__u_cluster__DOT__pe_done
         [1U] & VL_GTS_III(1,32,32, 4U, vlTOPp->top_level__DOT__gen_clusters__BRA__4__KET____DOT__u_cluster__DOT__logical_lane))) {
        vlTOPp->top_level__DOT__gen_clusters__BRA__4__KET____DOT__u_cluster__DOT__accum_next[(3U 
                                                                                & vlTOPp->top_level__DOT__gen_clusters__BRA__4__KET____DOT__u_cluster__DOT__logical_lane)] 
            = vlTOPp->top_level__DOT__gen_clusters__BRA__4__KET____DOT__u_cluster__DOT__pe_result
            [1U];
    }
    vlTOPp->top_level__DOT__gen_clusters__BRA__5__KET____DOT__u_cluster__DOT__accum_next[0U] 
        = vlTOPp->top_level__DOT__gen_clusters__BRA__5__KET____DOT__u_cluster__DOT__accum_bank
        [0U];
    vlTOPp->top_level__DOT__gen_clusters__BRA__5__KET____DOT__u_cluster__DOT__accum_next[1U] 
        = vlTOPp->top_level__DOT__gen_clusters__BRA__5__KET____DOT__u_cluster__DOT__accum_bank
        [1U];
    vlTOPp->top_level__DOT__gen_clusters__BRA__5__KET____DOT__u_cluster__DOT__accum_next[2U] 
        = vlTOPp->top_level__DOT__gen_clusters__BRA__5__KET____DOT__u_cluster__DOT__accum_bank
        [2U];
    vlTOPp->top_level__DOT__gen_clusters__BRA__5__KET____DOT__u_cluster__DOT__accum_next[3U] 
        = vlTOPp->top_level__DOT__gen_clusters__BRA__5__KET____DOT__u_cluster__DOT__accum_bank
        [3U];
    vlTOPp->top_level__DOT__gen_clusters__BRA__5__KET____DOT__u_cluster__DOT__logical_lane 
        = ((IData)(vlTOPp->top_level__DOT__shared_phase) 
           << 1U);
    if ((vlTOPp->top_level__DOT__gen_clusters__BRA__5__KET____DOT__u_cluster__DOT__pe_done
         [0U] & VL_GTS_III(1,32,32, 4U, vlTOPp->top_level__DOT__gen_clusters__BRA__5__KET____DOT__u_cluster__DOT__logical_lane))) {
        vlTOPp->top_level__DOT__gen_clusters__BRA__5__KET____DOT__u_cluster__DOT__accum_next[(3U 
                                                                                & vlTOPp->top_level__DOT__gen_clusters__BRA__5__KET____DOT__u_cluster__DOT__logical_lane)] 
            = vlTOPp->top_level__DOT__gen_clusters__BRA__5__KET____DOT__u_cluster__DOT__pe_result
            [0U];
    }
    vlTOPp->top_level__DOT__gen_clusters__BRA__5__KET____DOT__u_cluster__DOT__logical_lane 
        = ((IData)(1U) + ((IData)(vlTOPp->top_level__DOT__shared_phase) 
                          << 1U));
    if ((vlTOPp->top_level__DOT__gen_clusters__BRA__5__KET____DOT__u_cluster__DOT__pe_done
         [1U] & VL_GTS_III(1,32,32, 4U, vlTOPp->top_level__DOT__gen_clusters__BRA__5__KET____DOT__u_cluster__DOT__logical_lane))) {
        vlTOPp->top_level__DOT__gen_clusters__BRA__5__KET____DOT__u_cluster__DOT__accum_next[(3U 
                                                                                & vlTOPp->top_level__DOT__gen_clusters__BRA__5__KET____DOT__u_cluster__DOT__logical_lane)] 
            = vlTOPp->top_level__DOT__gen_clusters__BRA__5__KET____DOT__u_cluster__DOT__pe_result
            [1U];
    }
    vlTOPp->top_level__DOT__gen_clusters__BRA__6__KET____DOT__u_cluster__DOT__accum_next[0U] 
        = vlTOPp->top_level__DOT__gen_clusters__BRA__6__KET____DOT__u_cluster__DOT__accum_bank
        [0U];
    vlTOPp->top_level__DOT__gen_clusters__BRA__6__KET____DOT__u_cluster__DOT__accum_next[1U] 
        = vlTOPp->top_level__DOT__gen_clusters__BRA__6__KET____DOT__u_cluster__DOT__accum_bank
        [1U];
    vlTOPp->top_level__DOT__gen_clusters__BRA__6__KET____DOT__u_cluster__DOT__accum_next[2U] 
        = vlTOPp->top_level__DOT__gen_clusters__BRA__6__KET____DOT__u_cluster__DOT__accum_bank
        [2U];
    vlTOPp->top_level__DOT__gen_clusters__BRA__6__KET____DOT__u_cluster__DOT__accum_next[3U] 
        = vlTOPp->top_level__DOT__gen_clusters__BRA__6__KET____DOT__u_cluster__DOT__accum_bank
        [3U];
    vlTOPp->top_level__DOT__gen_clusters__BRA__6__KET____DOT__u_cluster__DOT__logical_lane 
        = ((IData)(vlTOPp->top_level__DOT__shared_phase) 
           << 1U);
    if ((vlTOPp->top_level__DOT__gen_clusters__BRA__6__KET____DOT__u_cluster__DOT__pe_done
         [0U] & VL_GTS_III(1,32,32, 4U, vlTOPp->top_level__DOT__gen_clusters__BRA__6__KET____DOT__u_cluster__DOT__logical_lane))) {
        vlTOPp->top_level__DOT__gen_clusters__BRA__6__KET____DOT__u_cluster__DOT__accum_next[(3U 
                                                                                & vlTOPp->top_level__DOT__gen_clusters__BRA__6__KET____DOT__u_cluster__DOT__logical_lane)] 
            = vlTOPp->top_level__DOT__gen_clusters__BRA__6__KET____DOT__u_cluster__DOT__pe_result
            [0U];
    }
    vlTOPp->top_level__DOT__gen_clusters__BRA__6__KET____DOT__u_cluster__DOT__logical_lane 
        = ((IData)(1U) + ((IData)(vlTOPp->top_level__DOT__shared_phase) 
                          << 1U));
    if ((vlTOPp->top_level__DOT__gen_clusters__BRA__6__KET____DOT__u_cluster__DOT__pe_done
         [1U] & VL_GTS_III(1,32,32, 4U, vlTOPp->top_level__DOT__gen_clusters__BRA__6__KET____DOT__u_cluster__DOT__logical_lane))) {
        vlTOPp->top_level__DOT__gen_clusters__BRA__6__KET____DOT__u_cluster__DOT__accum_next[(3U 
                                                                                & vlTOPp->top_level__DOT__gen_clusters__BRA__6__KET____DOT__u_cluster__DOT__logical_lane)] 
            = vlTOPp->top_level__DOT__gen_clusters__BRA__6__KET____DOT__u_cluster__DOT__pe_result
            [1U];
    }
    vlTOPp->top_level__DOT__gen_clusters__BRA__7__KET____DOT__u_cluster__DOT__accum_next[0U] 
        = vlTOPp->top_level__DOT__gen_clusters__BRA__7__KET____DOT__u_cluster__DOT__accum_bank
        [0U];
    vlTOPp->top_level__DOT__gen_clusters__BRA__7__KET____DOT__u_cluster__DOT__accum_next[1U] 
        = vlTOPp->top_level__DOT__gen_clusters__BRA__7__KET____DOT__u_cluster__DOT__accum_bank
        [1U];
    vlTOPp->top_level__DOT__gen_clusters__BRA__7__KET____DOT__u_cluster__DOT__accum_next[2U] 
        = vlTOPp->top_level__DOT__gen_clusters__BRA__7__KET____DOT__u_cluster__DOT__accum_bank
        [2U];
    vlTOPp->top_level__DOT__gen_clusters__BRA__7__KET____DOT__u_cluster__DOT__accum_next[3U] 
        = vlTOPp->top_level__DOT__gen_clusters__BRA__7__KET____DOT__u_cluster__DOT__accum_bank
        [3U];
    vlTOPp->top_level__DOT__gen_clusters__BRA__7__KET____DOT__u_cluster__DOT__logical_lane 
        = ((IData)(vlTOPp->top_level__DOT__shared_phase) 
           << 1U);
    if ((vlTOPp->top_level__DOT__gen_clusters__BRA__7__KET____DOT__u_cluster__DOT__pe_done
         [0U] & VL_GTS_III(1,32,32, 4U, vlTOPp->top_level__DOT__gen_clusters__BRA__7__KET____DOT__u_cluster__DOT__logical_lane))) {
        vlTOPp->top_level__DOT__gen_clusters__BRA__7__KET____DOT__u_cluster__DOT__accum_next[(3U 
                                                                                & vlTOPp->top_level__DOT__gen_clusters__BRA__7__KET____DOT__u_cluster__DOT__logical_lane)] 
            = vlTOPp->top_level__DOT__gen_clusters__BRA__7__KET____DOT__u_cluster__DOT__pe_result
            [0U];
    }
    vlTOPp->top_level__DOT__gen_clusters__BRA__7__KET____DOT__u_cluster__DOT__logical_lane 
        = ((IData)(1U) + ((IData)(vlTOPp->top_level__DOT__shared_phase) 
                          << 1U));
    if ((vlTOPp->top_level__DOT__gen_clusters__BRA__7__KET____DOT__u_cluster__DOT__pe_done
         [1U] & VL_GTS_III(1,32,32, 4U, vlTOPp->top_level__DOT__gen_clusters__BRA__7__KET____DOT__u_cluster__DOT__logical_lane))) {
        vlTOPp->top_level__DOT__gen_clusters__BRA__7__KET____DOT__u_cluster__DOT__accum_next[(3U 
                                                                                & vlTOPp->top_level__DOT__gen_clusters__BRA__7__KET____DOT__u_cluster__DOT__logical_lane)] 
            = vlTOPp->top_level__DOT__gen_clusters__BRA__7__KET____DOT__u_cluster__DOT__pe_result
            [1U];
    }
}

VL_INLINE_OPT void Vtop_level::_combo__TOP__5(Vtop_level__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop_level::_combo__TOP__5\n"); );
    Vtop_level* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->top_level__DOT__u_control__DOT__state_d 
        = vlTOPp->top_level__DOT__u_control__DOT__state_q;
    if ((4U & (IData)(vlTOPp->top_level__DOT__u_control__DOT__state_q))) {
        if ((2U & (IData)(vlTOPp->top_level__DOT__u_control__DOT__state_q))) {
            vlTOPp->top_level__DOT__u_control__DOT__state_d = 0U;
        } else {
            if ((1U & (IData)(vlTOPp->top_level__DOT__u_control__DOT__state_q))) {
                if ((1U & (~ (IData)(vlTOPp->start)))) {
                    vlTOPp->top_level__DOT__u_control__DOT__state_d = 0U;
                }
            } else {
                vlTOPp->top_level__DOT__u_control__DOT__state_d = 5U;
            }
        }
    } else {
        if ((2U & (IData)(vlTOPp->top_level__DOT__u_control__DOT__state_q))) {
            if ((1U & (IData)(vlTOPp->top_level__DOT__u_control__DOT__state_q))) {
                if ((1U <= ((IData)(1U) + vlTOPp->top_level__DOT__u_control__DOT__drain_iter_q))) {
                    vlTOPp->top_level__DOT__u_control__DOT__state_d = 4U;
                }
            } else {
                if ((8U <= ((IData)(1U) + vlTOPp->top_level__DOT__u_control__DOT__compute_iter_q))) {
                    vlTOPp->top_level__DOT__u_control__DOT__state_d = 3U;
                }
            }
        } else {
            if ((1U & (IData)(vlTOPp->top_level__DOT__u_control__DOT__state_q))) {
                vlTOPp->top_level__DOT__u_control__DOT__state_d = 2U;
            } else {
                if (vlTOPp->start) {
                    vlTOPp->top_level__DOT__u_control__DOT__state_d = 1U;
                }
            }
        }
    }
}

void Vtop_level::_eval(Vtop_level__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop_level::_eval\n"); );
    Vtop_level* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    if (((IData)(vlTOPp->clk) & (~ (IData)(vlTOPp->__Vclklast__TOP__clk)))) {
        vlTOPp->_sequent__TOP__3(vlSymsp);
    }
    vlTOPp->_combo__TOP__5(vlSymsp);
    // Final
    vlTOPp->__Vclklast__TOP__clk = vlTOPp->clk;
}

VL_INLINE_OPT QData Vtop_level::_change_request(Vtop_level__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop_level::_change_request\n"); );
    Vtop_level* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    return (vlTOPp->_change_request_1(vlSymsp));
}

VL_INLINE_OPT QData Vtop_level::_change_request_1(Vtop_level__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop_level::_change_request_1\n"); );
    Vtop_level* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    // Change detection
    QData __req = false;  // Logically a bool
    return __req;
}

#ifdef VL_DEBUG
void Vtop_level::_eval_debug_assertions() {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop_level::_eval_debug_assertions\n"); );
    // Body
    if (VL_UNLIKELY((clk & 0xfeU))) {
        Verilated::overWidthError("clk");}
    if (VL_UNLIKELY((rst & 0xfeU))) {
        Verilated::overWidthError("rst");}
    if (VL_UNLIKELY((start & 0xfeU))) {
        Verilated::overWidthError("start");}
}
#endif  // VL_DEBUG
