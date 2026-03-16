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

VL_INLINE_OPT void Vtop_level::_sequent__TOP__4(Vtop_level__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop_level::_sequent__TOP__4\n"); );
    Vtop_level* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Variables
    CData/*0:0*/ __Vdlyvset__top_level__DOT__output_mem__v0;
    CData/*5:0*/ __Vdlyvdim0__top_level__DOT__output_mem__v64;
    CData/*0:0*/ __Vdlyvset__top_level__DOT__output_mem__v64;
    IData/*31:0*/ __Vdlyvval__top_level__DOT__output_mem__v64;
    IData/*31:0*/ __Vdly__debug_primary_checksum;
    IData/*31:0*/ __Vdly__top_level__DOT__shadow_checksum_q;
    WData/*127:0*/ __Vtemp1[4];
    IData/*31:0*/ __Vilp;
    // Body
    __Vdly__debug_primary_checksum = vlTOPp->debug_primary_checksum;
    __Vdly__top_level__DOT__shadow_checksum_q = vlTOPp->top_level__DOT__shadow_checksum_q;
    __Vdlyvset__top_level__DOT__output_mem__v0 = 0U;
    __Vdlyvset__top_level__DOT__output_mem__v64 = 0U;
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
    if (vlTOPp->rst) {
        __Vdly__debug_primary_checksum = 0U;
    } else {
        if (vlTOPp->top_level__DOT__write_en) {
            if ((0x20U > vlTOPp->top_level__DOT__u_control__DOT__write_iter_q)) {
                __Vdly__debug_primary_checksum = ((vlTOPp->debug_primary_checksum 
                                                   ^ 
                                                   vlTOPp->top_level__DOT__logical_accum
                                                   [
                                                   (0x1fU 
                                                    & vlTOPp->top_level__DOT__u_control__DOT__write_iter_q)]) 
                                                  ^ vlTOPp->top_level__DOT__u_control__DOT__write_iter_q);
            }
        }
    }
    if (vlTOPp->rst) {
        __Vdly__top_level__DOT__shadow_checksum_q = 0U;
    } else {
        if (vlTOPp->top_level__DOT__write_en) {
            if ((0x20U > vlTOPp->top_level__DOT__u_control__DOT__write_iter_q)) {
                __Vdly__top_level__DOT__shadow_checksum_q 
                    = ((vlTOPp->top_level__DOT__shadow_checksum_q 
                        ^ vlTOPp->top_level__DOT__logical_shadow_accum
                        [(0x1fU & vlTOPp->top_level__DOT__u_control__DOT__write_iter_q)]) 
                       ^ (vlTOPp->top_level__DOT__u_control__DOT__write_iter_q 
                          << 1U));
            }
        }
    }
    if (vlTOPp->rst) {
        __Vdlyvset__top_level__DOT__output_mem__v0 = 1U;
    } else {
        if (vlTOPp->top_level__DOT__write_en) {
            if (((0x40U > vlTOPp->top_level__DOT__u_control__DOT__write_iter_q) 
                 & (0x20U > vlTOPp->top_level__DOT__u_control__DOT__write_iter_q))) {
                __Vdlyvval__top_level__DOT__output_mem__v64 
                    = vlTOPp->top_level__DOT__logical_accum
                    [(0x1fU & vlTOPp->top_level__DOT__u_control__DOT__write_iter_q)];
                __Vdlyvset__top_level__DOT__output_mem__v64 = 1U;
                __Vdlyvdim0__top_level__DOT__output_mem__v64 
                    = (0x3fU & vlTOPp->top_level__DOT__u_control__DOT__write_iter_q);
            }
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
    vlTOPp->debug_primary_checksum = __Vdly__debug_primary_checksum;
    vlTOPp->top_level__DOT__shadow_checksum_q = __Vdly__top_level__DOT__shadow_checksum_q;
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
    vlTOPp->debug_cycle_count = vlTOPp->top_level__DOT__cycle_count;
    vlTOPp->debug_shadow_checksum = vlTOPp->top_level__DOT__shadow_checksum_q;
    vlTOPp->top_level__DOT__u_control__DOT__write_iter_q 
        = ((IData)(vlTOPp->rst) ? 0U : vlTOPp->top_level__DOT__u_control__DOT__write_iter_d);
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
                    = ((4U <= ((IData)(1U) + vlTOPp->top_level__DOT__u_control__DOT__compute_iter_q))
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
    vlTOPp->top_level__DOT__current_k = 0U;
    if ((1U & (~ ((IData)(vlTOPp->top_level__DOT__u_control__DOT__state_q) 
                  >> 2U)))) {
        if ((2U & (IData)(vlTOPp->top_level__DOT__u_control__DOT__state_q))) {
            if ((1U & (~ (IData)(vlTOPp->top_level__DOT__u_control__DOT__state_q)))) {
                vlTOPp->top_level__DOT__current_k = 
                    (3U & vlTOPp->top_level__DOT__u_control__DOT__compute_iter_q);
            }
        }
    }
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
    vlTOPp->top_level__DOT__u_control__DOT__write_iter_d 
        = vlTOPp->top_level__DOT__u_control__DOT__write_iter_q;
    if ((4U & (IData)(vlTOPp->top_level__DOT__u_control__DOT__state_q))) {
        if ((1U & (~ ((IData)(vlTOPp->top_level__DOT__u_control__DOT__state_q) 
                      >> 1U)))) {
            if ((1U & (~ (IData)(vlTOPp->top_level__DOT__u_control__DOT__state_q)))) {
                vlTOPp->top_level__DOT__u_control__DOT__write_iter_d 
                    = ((0x20U <= ((IData)(1U) + vlTOPp->top_level__DOT__u_control__DOT__write_iter_q))
                        ? 0U : ((IData)(1U) + vlTOPp->top_level__DOT__u_control__DOT__write_iter_q));
            }
        }
    } else {
        if ((1U & (~ ((IData)(vlTOPp->top_level__DOT__u_control__DOT__state_q) 
                      >> 1U)))) {
            if ((1U & (IData)(vlTOPp->top_level__DOT__u_control__DOT__state_q))) {
                vlTOPp->top_level__DOT__u_control__DOT__write_iter_d = 0U;
            }
        }
    }
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
    vlSymsp->TOP__top_level__DOT__gen_clusters__BRA__0__KET____DOT__u_cluster.lane_b[0U] 
        = vlTOPp->top_level__DOT____Vcellinp__gen_clusters__BRA__0__KET____DOT__u_cluster__lane_b
        [0U];
    vlSymsp->TOP__top_level__DOT__gen_clusters__BRA__0__KET____DOT__u_cluster.lane_b[1U] 
        = vlTOPp->top_level__DOT____Vcellinp__gen_clusters__BRA__0__KET____DOT__u_cluster__lane_b
        [1U];
    vlSymsp->TOP__top_level__DOT__gen_clusters__BRA__0__KET____DOT__u_cluster.lane_b[2U] 
        = vlTOPp->top_level__DOT____Vcellinp__gen_clusters__BRA__0__KET____DOT__u_cluster__lane_b
        [2U];
    vlSymsp->TOP__top_level__DOT__gen_clusters__BRA__0__KET____DOT__u_cluster.lane_b[3U] 
        = vlTOPp->top_level__DOT____Vcellinp__gen_clusters__BRA__0__KET____DOT__u_cluster__lane_b
        [3U];
    vlSymsp->TOP__top_level__DOT__gen_clusters__BRA__1__KET____DOT__u_cluster.lane_b[0U] 
        = vlTOPp->top_level__DOT____Vcellinp__gen_clusters__BRA__1__KET____DOT__u_cluster__lane_b
        [0U];
    vlSymsp->TOP__top_level__DOT__gen_clusters__BRA__1__KET____DOT__u_cluster.lane_b[1U] 
        = vlTOPp->top_level__DOT____Vcellinp__gen_clusters__BRA__1__KET____DOT__u_cluster__lane_b
        [1U];
    vlSymsp->TOP__top_level__DOT__gen_clusters__BRA__1__KET____DOT__u_cluster.lane_b[2U] 
        = vlTOPp->top_level__DOT____Vcellinp__gen_clusters__BRA__1__KET____DOT__u_cluster__lane_b
        [2U];
    vlSymsp->TOP__top_level__DOT__gen_clusters__BRA__1__KET____DOT__u_cluster.lane_b[3U] 
        = vlTOPp->top_level__DOT____Vcellinp__gen_clusters__BRA__1__KET____DOT__u_cluster__lane_b
        [3U];
    vlSymsp->TOP__top_level__DOT__gen_clusters__BRA__2__KET____DOT__u_cluster.lane_b[0U] 
        = vlTOPp->top_level__DOT____Vcellinp__gen_clusters__BRA__2__KET____DOT__u_cluster__lane_b
        [0U];
    vlSymsp->TOP__top_level__DOT__gen_clusters__BRA__2__KET____DOT__u_cluster.lane_b[1U] 
        = vlTOPp->top_level__DOT____Vcellinp__gen_clusters__BRA__2__KET____DOT__u_cluster__lane_b
        [1U];
    vlSymsp->TOP__top_level__DOT__gen_clusters__BRA__2__KET____DOT__u_cluster.lane_b[2U] 
        = vlTOPp->top_level__DOT____Vcellinp__gen_clusters__BRA__2__KET____DOT__u_cluster__lane_b
        [2U];
    vlSymsp->TOP__top_level__DOT__gen_clusters__BRA__2__KET____DOT__u_cluster.lane_b[3U] 
        = vlTOPp->top_level__DOT____Vcellinp__gen_clusters__BRA__2__KET____DOT__u_cluster__lane_b
        [3U];
    vlSymsp->TOP__top_level__DOT__gen_clusters__BRA__3__KET____DOT__u_cluster.lane_b[0U] 
        = vlTOPp->top_level__DOT____Vcellinp__gen_clusters__BRA__3__KET____DOT__u_cluster__lane_b
        [0U];
    vlSymsp->TOP__top_level__DOT__gen_clusters__BRA__3__KET____DOT__u_cluster.lane_b[1U] 
        = vlTOPp->top_level__DOT____Vcellinp__gen_clusters__BRA__3__KET____DOT__u_cluster__lane_b
        [1U];
    vlSymsp->TOP__top_level__DOT__gen_clusters__BRA__3__KET____DOT__u_cluster.lane_b[2U] 
        = vlTOPp->top_level__DOT____Vcellinp__gen_clusters__BRA__3__KET____DOT__u_cluster__lane_b
        [2U];
    vlSymsp->TOP__top_level__DOT__gen_clusters__BRA__3__KET____DOT__u_cluster.lane_b[3U] 
        = vlTOPp->top_level__DOT____Vcellinp__gen_clusters__BRA__3__KET____DOT__u_cluster__lane_b
        [3U];
    vlSymsp->TOP__top_level__DOT__gen_clusters__BRA__4__KET____DOT__u_cluster.lane_b[0U] 
        = vlTOPp->top_level__DOT____Vcellinp__gen_clusters__BRA__4__KET____DOT__u_cluster__lane_b
        [0U];
    vlSymsp->TOP__top_level__DOT__gen_clusters__BRA__4__KET____DOT__u_cluster.lane_b[1U] 
        = vlTOPp->top_level__DOT____Vcellinp__gen_clusters__BRA__4__KET____DOT__u_cluster__lane_b
        [1U];
    vlSymsp->TOP__top_level__DOT__gen_clusters__BRA__4__KET____DOT__u_cluster.lane_b[2U] 
        = vlTOPp->top_level__DOT____Vcellinp__gen_clusters__BRA__4__KET____DOT__u_cluster__lane_b
        [2U];
    vlSymsp->TOP__top_level__DOT__gen_clusters__BRA__4__KET____DOT__u_cluster.lane_b[3U] 
        = vlTOPp->top_level__DOT____Vcellinp__gen_clusters__BRA__4__KET____DOT__u_cluster__lane_b
        [3U];
    vlSymsp->TOP__top_level__DOT__gen_clusters__BRA__5__KET____DOT__u_cluster.lane_b[0U] 
        = vlTOPp->top_level__DOT____Vcellinp__gen_clusters__BRA__5__KET____DOT__u_cluster__lane_b
        [0U];
    vlSymsp->TOP__top_level__DOT__gen_clusters__BRA__5__KET____DOT__u_cluster.lane_b[1U] 
        = vlTOPp->top_level__DOT____Vcellinp__gen_clusters__BRA__5__KET____DOT__u_cluster__lane_b
        [1U];
    vlSymsp->TOP__top_level__DOT__gen_clusters__BRA__5__KET____DOT__u_cluster.lane_b[2U] 
        = vlTOPp->top_level__DOT____Vcellinp__gen_clusters__BRA__5__KET____DOT__u_cluster__lane_b
        [2U];
    vlSymsp->TOP__top_level__DOT__gen_clusters__BRA__5__KET____DOT__u_cluster.lane_b[3U] 
        = vlTOPp->top_level__DOT____Vcellinp__gen_clusters__BRA__5__KET____DOT__u_cluster__lane_b
        [3U];
    vlSymsp->TOP__top_level__DOT__gen_clusters__BRA__6__KET____DOT__u_cluster.lane_b[0U] 
        = vlTOPp->top_level__DOT____Vcellinp__gen_clusters__BRA__6__KET____DOT__u_cluster__lane_b
        [0U];
    vlSymsp->TOP__top_level__DOT__gen_clusters__BRA__6__KET____DOT__u_cluster.lane_b[1U] 
        = vlTOPp->top_level__DOT____Vcellinp__gen_clusters__BRA__6__KET____DOT__u_cluster__lane_b
        [1U];
    vlSymsp->TOP__top_level__DOT__gen_clusters__BRA__6__KET____DOT__u_cluster.lane_b[2U] 
        = vlTOPp->top_level__DOT____Vcellinp__gen_clusters__BRA__6__KET____DOT__u_cluster__lane_b
        [2U];
    vlSymsp->TOP__top_level__DOT__gen_clusters__BRA__6__KET____DOT__u_cluster.lane_b[3U] 
        = vlTOPp->top_level__DOT____Vcellinp__gen_clusters__BRA__6__KET____DOT__u_cluster__lane_b
        [3U];
    vlSymsp->TOP__top_level__DOT__gen_clusters__BRA__7__KET____DOT__u_cluster.lane_b[0U] 
        = vlTOPp->top_level__DOT____Vcellinp__gen_clusters__BRA__7__KET____DOT__u_cluster__lane_b
        [0U];
    vlSymsp->TOP__top_level__DOT__gen_clusters__BRA__7__KET____DOT__u_cluster.lane_b[1U] 
        = vlTOPp->top_level__DOT____Vcellinp__gen_clusters__BRA__7__KET____DOT__u_cluster__lane_b
        [1U];
    vlSymsp->TOP__top_level__DOT__gen_clusters__BRA__7__KET____DOT__u_cluster.lane_b[2U] 
        = vlTOPp->top_level__DOT____Vcellinp__gen_clusters__BRA__7__KET____DOT__u_cluster__lane_b
        [2U];
    vlSymsp->TOP__top_level__DOT__gen_clusters__BRA__7__KET____DOT__u_cluster.lane_b[3U] 
        = vlTOPp->top_level__DOT____Vcellinp__gen_clusters__BRA__7__KET____DOT__u_cluster__lane_b
        [3U];
    vlSymsp->TOP__top_level__DOT__gen_clusters__BRA__0__KET____DOT__u_cluster.lane_a[0U] 
        = vlTOPp->top_level__DOT____Vcellinp__gen_clusters__BRA__0__KET____DOT__u_cluster__lane_a
        [0U];
    vlSymsp->TOP__top_level__DOT__gen_clusters__BRA__0__KET____DOT__u_cluster.lane_a[1U] 
        = vlTOPp->top_level__DOT____Vcellinp__gen_clusters__BRA__0__KET____DOT__u_cluster__lane_a
        [1U];
    vlSymsp->TOP__top_level__DOT__gen_clusters__BRA__0__KET____DOT__u_cluster.lane_a[2U] 
        = vlTOPp->top_level__DOT____Vcellinp__gen_clusters__BRA__0__KET____DOT__u_cluster__lane_a
        [2U];
    vlSymsp->TOP__top_level__DOT__gen_clusters__BRA__0__KET____DOT__u_cluster.lane_a[3U] 
        = vlTOPp->top_level__DOT____Vcellinp__gen_clusters__BRA__0__KET____DOT__u_cluster__lane_a
        [3U];
    vlSymsp->TOP__top_level__DOT__gen_clusters__BRA__1__KET____DOT__u_cluster.lane_a[0U] 
        = vlTOPp->top_level__DOT____Vcellinp__gen_clusters__BRA__1__KET____DOT__u_cluster__lane_a
        [0U];
    vlSymsp->TOP__top_level__DOT__gen_clusters__BRA__1__KET____DOT__u_cluster.lane_a[1U] 
        = vlTOPp->top_level__DOT____Vcellinp__gen_clusters__BRA__1__KET____DOT__u_cluster__lane_a
        [1U];
    vlSymsp->TOP__top_level__DOT__gen_clusters__BRA__1__KET____DOT__u_cluster.lane_a[2U] 
        = vlTOPp->top_level__DOT____Vcellinp__gen_clusters__BRA__1__KET____DOT__u_cluster__lane_a
        [2U];
    vlSymsp->TOP__top_level__DOT__gen_clusters__BRA__1__KET____DOT__u_cluster.lane_a[3U] 
        = vlTOPp->top_level__DOT____Vcellinp__gen_clusters__BRA__1__KET____DOT__u_cluster__lane_a
        [3U];
    vlSymsp->TOP__top_level__DOT__gen_clusters__BRA__2__KET____DOT__u_cluster.lane_a[0U] 
        = vlTOPp->top_level__DOT____Vcellinp__gen_clusters__BRA__2__KET____DOT__u_cluster__lane_a
        [0U];
    vlSymsp->TOP__top_level__DOT__gen_clusters__BRA__2__KET____DOT__u_cluster.lane_a[1U] 
        = vlTOPp->top_level__DOT____Vcellinp__gen_clusters__BRA__2__KET____DOT__u_cluster__lane_a
        [1U];
    vlSymsp->TOP__top_level__DOT__gen_clusters__BRA__2__KET____DOT__u_cluster.lane_a[2U] 
        = vlTOPp->top_level__DOT____Vcellinp__gen_clusters__BRA__2__KET____DOT__u_cluster__lane_a
        [2U];
    vlSymsp->TOP__top_level__DOT__gen_clusters__BRA__2__KET____DOT__u_cluster.lane_a[3U] 
        = vlTOPp->top_level__DOT____Vcellinp__gen_clusters__BRA__2__KET____DOT__u_cluster__lane_a
        [3U];
    vlSymsp->TOP__top_level__DOT__gen_clusters__BRA__3__KET____DOT__u_cluster.lane_a[0U] 
        = vlTOPp->top_level__DOT____Vcellinp__gen_clusters__BRA__3__KET____DOT__u_cluster__lane_a
        [0U];
    vlSymsp->TOP__top_level__DOT__gen_clusters__BRA__3__KET____DOT__u_cluster.lane_a[1U] 
        = vlTOPp->top_level__DOT____Vcellinp__gen_clusters__BRA__3__KET____DOT__u_cluster__lane_a
        [1U];
    vlSymsp->TOP__top_level__DOT__gen_clusters__BRA__3__KET____DOT__u_cluster.lane_a[2U] 
        = vlTOPp->top_level__DOT____Vcellinp__gen_clusters__BRA__3__KET____DOT__u_cluster__lane_a
        [2U];
    vlSymsp->TOP__top_level__DOT__gen_clusters__BRA__3__KET____DOT__u_cluster.lane_a[3U] 
        = vlTOPp->top_level__DOT____Vcellinp__gen_clusters__BRA__3__KET____DOT__u_cluster__lane_a
        [3U];
    vlSymsp->TOP__top_level__DOT__gen_clusters__BRA__4__KET____DOT__u_cluster.lane_a[0U] 
        = vlTOPp->top_level__DOT____Vcellinp__gen_clusters__BRA__4__KET____DOT__u_cluster__lane_a
        [0U];
    vlSymsp->TOP__top_level__DOT__gen_clusters__BRA__4__KET____DOT__u_cluster.lane_a[1U] 
        = vlTOPp->top_level__DOT____Vcellinp__gen_clusters__BRA__4__KET____DOT__u_cluster__lane_a
        [1U];
    vlSymsp->TOP__top_level__DOT__gen_clusters__BRA__4__KET____DOT__u_cluster.lane_a[2U] 
        = vlTOPp->top_level__DOT____Vcellinp__gen_clusters__BRA__4__KET____DOT__u_cluster__lane_a
        [2U];
    vlSymsp->TOP__top_level__DOT__gen_clusters__BRA__4__KET____DOT__u_cluster.lane_a[3U] 
        = vlTOPp->top_level__DOT____Vcellinp__gen_clusters__BRA__4__KET____DOT__u_cluster__lane_a
        [3U];
    vlSymsp->TOP__top_level__DOT__gen_clusters__BRA__5__KET____DOT__u_cluster.lane_a[0U] 
        = vlTOPp->top_level__DOT____Vcellinp__gen_clusters__BRA__5__KET____DOT__u_cluster__lane_a
        [0U];
    vlSymsp->TOP__top_level__DOT__gen_clusters__BRA__5__KET____DOT__u_cluster.lane_a[1U] 
        = vlTOPp->top_level__DOT____Vcellinp__gen_clusters__BRA__5__KET____DOT__u_cluster__lane_a
        [1U];
    vlSymsp->TOP__top_level__DOT__gen_clusters__BRA__5__KET____DOT__u_cluster.lane_a[2U] 
        = vlTOPp->top_level__DOT____Vcellinp__gen_clusters__BRA__5__KET____DOT__u_cluster__lane_a
        [2U];
    vlSymsp->TOP__top_level__DOT__gen_clusters__BRA__5__KET____DOT__u_cluster.lane_a[3U] 
        = vlTOPp->top_level__DOT____Vcellinp__gen_clusters__BRA__5__KET____DOT__u_cluster__lane_a
        [3U];
    vlSymsp->TOP__top_level__DOT__gen_clusters__BRA__6__KET____DOT__u_cluster.lane_a[0U] 
        = vlTOPp->top_level__DOT____Vcellinp__gen_clusters__BRA__6__KET____DOT__u_cluster__lane_a
        [0U];
    vlSymsp->TOP__top_level__DOT__gen_clusters__BRA__6__KET____DOT__u_cluster.lane_a[1U] 
        = vlTOPp->top_level__DOT____Vcellinp__gen_clusters__BRA__6__KET____DOT__u_cluster__lane_a
        [1U];
    vlSymsp->TOP__top_level__DOT__gen_clusters__BRA__6__KET____DOT__u_cluster.lane_a[2U] 
        = vlTOPp->top_level__DOT____Vcellinp__gen_clusters__BRA__6__KET____DOT__u_cluster__lane_a
        [2U];
    vlSymsp->TOP__top_level__DOT__gen_clusters__BRA__6__KET____DOT__u_cluster.lane_a[3U] 
        = vlTOPp->top_level__DOT____Vcellinp__gen_clusters__BRA__6__KET____DOT__u_cluster__lane_a
        [3U];
    vlSymsp->TOP__top_level__DOT__gen_clusters__BRA__7__KET____DOT__u_cluster.lane_a[0U] 
        = vlTOPp->top_level__DOT____Vcellinp__gen_clusters__BRA__7__KET____DOT__u_cluster__lane_a
        [0U];
    vlSymsp->TOP__top_level__DOT__gen_clusters__BRA__7__KET____DOT__u_cluster.lane_a[1U] 
        = vlTOPp->top_level__DOT____Vcellinp__gen_clusters__BRA__7__KET____DOT__u_cluster__lane_a
        [1U];
    vlSymsp->TOP__top_level__DOT__gen_clusters__BRA__7__KET____DOT__u_cluster.lane_a[2U] 
        = vlTOPp->top_level__DOT____Vcellinp__gen_clusters__BRA__7__KET____DOT__u_cluster__lane_a
        [2U];
    vlSymsp->TOP__top_level__DOT__gen_clusters__BRA__7__KET____DOT__u_cluster.lane_a[3U] 
        = vlTOPp->top_level__DOT____Vcellinp__gen_clusters__BRA__7__KET____DOT__u_cluster__lane_a
        [3U];
}

VL_INLINE_OPT void Vtop_level::_sequent__TOP__5(Vtop_level__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop_level::_sequent__TOP__5\n"); );
    Vtop_level* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->top_level__DOT____Vcellout__gen_clusters__BRA__0__KET____DOT__u_cluster__shadow_accum_out[0U] 
        = vlSymsp->TOP__top_level__DOT__gen_clusters__BRA__0__KET____DOT__u_cluster.shadow_accum_out
        [0U];
    vlTOPp->top_level__DOT____Vcellout__gen_clusters__BRA__0__KET____DOT__u_cluster__shadow_accum_out[1U] 
        = vlSymsp->TOP__top_level__DOT__gen_clusters__BRA__0__KET____DOT__u_cluster.shadow_accum_out
        [1U];
    vlTOPp->top_level__DOT____Vcellout__gen_clusters__BRA__0__KET____DOT__u_cluster__shadow_accum_out[2U] 
        = vlSymsp->TOP__top_level__DOT__gen_clusters__BRA__0__KET____DOT__u_cluster.shadow_accum_out
        [2U];
    vlTOPp->top_level__DOT____Vcellout__gen_clusters__BRA__0__KET____DOT__u_cluster__shadow_accum_out[3U] 
        = vlSymsp->TOP__top_level__DOT__gen_clusters__BRA__0__KET____DOT__u_cluster.shadow_accum_out
        [3U];
    vlTOPp->top_level__DOT____Vcellout__gen_clusters__BRA__0__KET____DOT__u_cluster__accum_out[0U] 
        = vlSymsp->TOP__top_level__DOT__gen_clusters__BRA__0__KET____DOT__u_cluster.accum_out
        [0U];
    vlTOPp->top_level__DOT____Vcellout__gen_clusters__BRA__0__KET____DOT__u_cluster__accum_out[1U] 
        = vlSymsp->TOP__top_level__DOT__gen_clusters__BRA__0__KET____DOT__u_cluster.accum_out
        [1U];
    vlTOPp->top_level__DOT____Vcellout__gen_clusters__BRA__0__KET____DOT__u_cluster__accum_out[2U] 
        = vlSymsp->TOP__top_level__DOT__gen_clusters__BRA__0__KET____DOT__u_cluster.accum_out
        [2U];
    vlTOPp->top_level__DOT____Vcellout__gen_clusters__BRA__0__KET____DOT__u_cluster__accum_out[3U] 
        = vlSymsp->TOP__top_level__DOT__gen_clusters__BRA__0__KET____DOT__u_cluster.accum_out
        [3U];
    vlTOPp->top_level__DOT____Vcellout__gen_clusters__BRA__1__KET____DOT__u_cluster__shadow_accum_out[0U] 
        = vlSymsp->TOP__top_level__DOT__gen_clusters__BRA__1__KET____DOT__u_cluster.shadow_accum_out
        [0U];
    vlTOPp->top_level__DOT____Vcellout__gen_clusters__BRA__1__KET____DOT__u_cluster__shadow_accum_out[1U] 
        = vlSymsp->TOP__top_level__DOT__gen_clusters__BRA__1__KET____DOT__u_cluster.shadow_accum_out
        [1U];
    vlTOPp->top_level__DOT____Vcellout__gen_clusters__BRA__1__KET____DOT__u_cluster__shadow_accum_out[2U] 
        = vlSymsp->TOP__top_level__DOT__gen_clusters__BRA__1__KET____DOT__u_cluster.shadow_accum_out
        [2U];
    vlTOPp->top_level__DOT____Vcellout__gen_clusters__BRA__1__KET____DOT__u_cluster__shadow_accum_out[3U] 
        = vlSymsp->TOP__top_level__DOT__gen_clusters__BRA__1__KET____DOT__u_cluster.shadow_accum_out
        [3U];
    vlTOPp->top_level__DOT____Vcellout__gen_clusters__BRA__1__KET____DOT__u_cluster__accum_out[0U] 
        = vlSymsp->TOP__top_level__DOT__gen_clusters__BRA__1__KET____DOT__u_cluster.accum_out
        [0U];
    vlTOPp->top_level__DOT____Vcellout__gen_clusters__BRA__1__KET____DOT__u_cluster__accum_out[1U] 
        = vlSymsp->TOP__top_level__DOT__gen_clusters__BRA__1__KET____DOT__u_cluster.accum_out
        [1U];
    vlTOPp->top_level__DOT____Vcellout__gen_clusters__BRA__1__KET____DOT__u_cluster__accum_out[2U] 
        = vlSymsp->TOP__top_level__DOT__gen_clusters__BRA__1__KET____DOT__u_cluster.accum_out
        [2U];
    vlTOPp->top_level__DOT____Vcellout__gen_clusters__BRA__1__KET____DOT__u_cluster__accum_out[3U] 
        = vlSymsp->TOP__top_level__DOT__gen_clusters__BRA__1__KET____DOT__u_cluster.accum_out
        [3U];
    vlTOPp->top_level__DOT____Vcellout__gen_clusters__BRA__2__KET____DOT__u_cluster__shadow_accum_out[0U] 
        = vlSymsp->TOP__top_level__DOT__gen_clusters__BRA__2__KET____DOT__u_cluster.shadow_accum_out
        [0U];
    vlTOPp->top_level__DOT____Vcellout__gen_clusters__BRA__2__KET____DOT__u_cluster__shadow_accum_out[1U] 
        = vlSymsp->TOP__top_level__DOT__gen_clusters__BRA__2__KET____DOT__u_cluster.shadow_accum_out
        [1U];
    vlTOPp->top_level__DOT____Vcellout__gen_clusters__BRA__2__KET____DOT__u_cluster__shadow_accum_out[2U] 
        = vlSymsp->TOP__top_level__DOT__gen_clusters__BRA__2__KET____DOT__u_cluster.shadow_accum_out
        [2U];
    vlTOPp->top_level__DOT____Vcellout__gen_clusters__BRA__2__KET____DOT__u_cluster__shadow_accum_out[3U] 
        = vlSymsp->TOP__top_level__DOT__gen_clusters__BRA__2__KET____DOT__u_cluster.shadow_accum_out
        [3U];
    vlTOPp->top_level__DOT____Vcellout__gen_clusters__BRA__2__KET____DOT__u_cluster__accum_out[0U] 
        = vlSymsp->TOP__top_level__DOT__gen_clusters__BRA__2__KET____DOT__u_cluster.accum_out
        [0U];
    vlTOPp->top_level__DOT____Vcellout__gen_clusters__BRA__2__KET____DOT__u_cluster__accum_out[1U] 
        = vlSymsp->TOP__top_level__DOT__gen_clusters__BRA__2__KET____DOT__u_cluster.accum_out
        [1U];
    vlTOPp->top_level__DOT____Vcellout__gen_clusters__BRA__2__KET____DOT__u_cluster__accum_out[2U] 
        = vlSymsp->TOP__top_level__DOT__gen_clusters__BRA__2__KET____DOT__u_cluster.accum_out
        [2U];
    vlTOPp->top_level__DOT____Vcellout__gen_clusters__BRA__2__KET____DOT__u_cluster__accum_out[3U] 
        = vlSymsp->TOP__top_level__DOT__gen_clusters__BRA__2__KET____DOT__u_cluster.accum_out
        [3U];
    vlTOPp->top_level__DOT____Vcellout__gen_clusters__BRA__3__KET____DOT__u_cluster__shadow_accum_out[0U] 
        = vlSymsp->TOP__top_level__DOT__gen_clusters__BRA__3__KET____DOT__u_cluster.shadow_accum_out
        [0U];
    vlTOPp->top_level__DOT____Vcellout__gen_clusters__BRA__3__KET____DOT__u_cluster__shadow_accum_out[1U] 
        = vlSymsp->TOP__top_level__DOT__gen_clusters__BRA__3__KET____DOT__u_cluster.shadow_accum_out
        [1U];
    vlTOPp->top_level__DOT____Vcellout__gen_clusters__BRA__3__KET____DOT__u_cluster__shadow_accum_out[2U] 
        = vlSymsp->TOP__top_level__DOT__gen_clusters__BRA__3__KET____DOT__u_cluster.shadow_accum_out
        [2U];
    vlTOPp->top_level__DOT____Vcellout__gen_clusters__BRA__3__KET____DOT__u_cluster__shadow_accum_out[3U] 
        = vlSymsp->TOP__top_level__DOT__gen_clusters__BRA__3__KET____DOT__u_cluster.shadow_accum_out
        [3U];
    vlTOPp->top_level__DOT____Vcellout__gen_clusters__BRA__3__KET____DOT__u_cluster__accum_out[0U] 
        = vlSymsp->TOP__top_level__DOT__gen_clusters__BRA__3__KET____DOT__u_cluster.accum_out
        [0U];
    vlTOPp->top_level__DOT____Vcellout__gen_clusters__BRA__3__KET____DOT__u_cluster__accum_out[1U] 
        = vlSymsp->TOP__top_level__DOT__gen_clusters__BRA__3__KET____DOT__u_cluster.accum_out
        [1U];
    vlTOPp->top_level__DOT____Vcellout__gen_clusters__BRA__3__KET____DOT__u_cluster__accum_out[2U] 
        = vlSymsp->TOP__top_level__DOT__gen_clusters__BRA__3__KET____DOT__u_cluster.accum_out
        [2U];
    vlTOPp->top_level__DOT____Vcellout__gen_clusters__BRA__3__KET____DOT__u_cluster__accum_out[3U] 
        = vlSymsp->TOP__top_level__DOT__gen_clusters__BRA__3__KET____DOT__u_cluster.accum_out
        [3U];
    vlTOPp->top_level__DOT____Vcellout__gen_clusters__BRA__4__KET____DOT__u_cluster__shadow_accum_out[0U] 
        = vlSymsp->TOP__top_level__DOT__gen_clusters__BRA__4__KET____DOT__u_cluster.shadow_accum_out
        [0U];
    vlTOPp->top_level__DOT____Vcellout__gen_clusters__BRA__4__KET____DOT__u_cluster__shadow_accum_out[1U] 
        = vlSymsp->TOP__top_level__DOT__gen_clusters__BRA__4__KET____DOT__u_cluster.shadow_accum_out
        [1U];
    vlTOPp->top_level__DOT____Vcellout__gen_clusters__BRA__4__KET____DOT__u_cluster__shadow_accum_out[2U] 
        = vlSymsp->TOP__top_level__DOT__gen_clusters__BRA__4__KET____DOT__u_cluster.shadow_accum_out
        [2U];
    vlTOPp->top_level__DOT____Vcellout__gen_clusters__BRA__4__KET____DOT__u_cluster__shadow_accum_out[3U] 
        = vlSymsp->TOP__top_level__DOT__gen_clusters__BRA__4__KET____DOT__u_cluster.shadow_accum_out
        [3U];
    vlTOPp->top_level__DOT____Vcellout__gen_clusters__BRA__4__KET____DOT__u_cluster__accum_out[0U] 
        = vlSymsp->TOP__top_level__DOT__gen_clusters__BRA__4__KET____DOT__u_cluster.accum_out
        [0U];
    vlTOPp->top_level__DOT____Vcellout__gen_clusters__BRA__4__KET____DOT__u_cluster__accum_out[1U] 
        = vlSymsp->TOP__top_level__DOT__gen_clusters__BRA__4__KET____DOT__u_cluster.accum_out
        [1U];
    vlTOPp->top_level__DOT____Vcellout__gen_clusters__BRA__4__KET____DOT__u_cluster__accum_out[2U] 
        = vlSymsp->TOP__top_level__DOT__gen_clusters__BRA__4__KET____DOT__u_cluster.accum_out
        [2U];
    vlTOPp->top_level__DOT____Vcellout__gen_clusters__BRA__4__KET____DOT__u_cluster__accum_out[3U] 
        = vlSymsp->TOP__top_level__DOT__gen_clusters__BRA__4__KET____DOT__u_cluster.accum_out
        [3U];
    vlTOPp->top_level__DOT____Vcellout__gen_clusters__BRA__5__KET____DOT__u_cluster__shadow_accum_out[0U] 
        = vlSymsp->TOP__top_level__DOT__gen_clusters__BRA__5__KET____DOT__u_cluster.shadow_accum_out
        [0U];
    vlTOPp->top_level__DOT____Vcellout__gen_clusters__BRA__5__KET____DOT__u_cluster__shadow_accum_out[1U] 
        = vlSymsp->TOP__top_level__DOT__gen_clusters__BRA__5__KET____DOT__u_cluster.shadow_accum_out
        [1U];
    vlTOPp->top_level__DOT____Vcellout__gen_clusters__BRA__5__KET____DOT__u_cluster__shadow_accum_out[2U] 
        = vlSymsp->TOP__top_level__DOT__gen_clusters__BRA__5__KET____DOT__u_cluster.shadow_accum_out
        [2U];
    vlTOPp->top_level__DOT____Vcellout__gen_clusters__BRA__5__KET____DOT__u_cluster__shadow_accum_out[3U] 
        = vlSymsp->TOP__top_level__DOT__gen_clusters__BRA__5__KET____DOT__u_cluster.shadow_accum_out
        [3U];
    vlTOPp->top_level__DOT____Vcellout__gen_clusters__BRA__5__KET____DOT__u_cluster__accum_out[0U] 
        = vlSymsp->TOP__top_level__DOT__gen_clusters__BRA__5__KET____DOT__u_cluster.accum_out
        [0U];
    vlTOPp->top_level__DOT____Vcellout__gen_clusters__BRA__5__KET____DOT__u_cluster__accum_out[1U] 
        = vlSymsp->TOP__top_level__DOT__gen_clusters__BRA__5__KET____DOT__u_cluster.accum_out
        [1U];
    vlTOPp->top_level__DOT____Vcellout__gen_clusters__BRA__5__KET____DOT__u_cluster__accum_out[2U] 
        = vlSymsp->TOP__top_level__DOT__gen_clusters__BRA__5__KET____DOT__u_cluster.accum_out
        [2U];
    vlTOPp->top_level__DOT____Vcellout__gen_clusters__BRA__5__KET____DOT__u_cluster__accum_out[3U] 
        = vlSymsp->TOP__top_level__DOT__gen_clusters__BRA__5__KET____DOT__u_cluster.accum_out
        [3U];
    vlTOPp->top_level__DOT____Vcellout__gen_clusters__BRA__6__KET____DOT__u_cluster__shadow_accum_out[0U] 
        = vlSymsp->TOP__top_level__DOT__gen_clusters__BRA__6__KET____DOT__u_cluster.shadow_accum_out
        [0U];
    vlTOPp->top_level__DOT____Vcellout__gen_clusters__BRA__6__KET____DOT__u_cluster__shadow_accum_out[1U] 
        = vlSymsp->TOP__top_level__DOT__gen_clusters__BRA__6__KET____DOT__u_cluster.shadow_accum_out
        [1U];
    vlTOPp->top_level__DOT____Vcellout__gen_clusters__BRA__6__KET____DOT__u_cluster__shadow_accum_out[2U] 
        = vlSymsp->TOP__top_level__DOT__gen_clusters__BRA__6__KET____DOT__u_cluster.shadow_accum_out
        [2U];
    vlTOPp->top_level__DOT____Vcellout__gen_clusters__BRA__6__KET____DOT__u_cluster__shadow_accum_out[3U] 
        = vlSymsp->TOP__top_level__DOT__gen_clusters__BRA__6__KET____DOT__u_cluster.shadow_accum_out
        [3U];
    vlTOPp->top_level__DOT____Vcellout__gen_clusters__BRA__6__KET____DOT__u_cluster__accum_out[0U] 
        = vlSymsp->TOP__top_level__DOT__gen_clusters__BRA__6__KET____DOT__u_cluster.accum_out
        [0U];
    vlTOPp->top_level__DOT____Vcellout__gen_clusters__BRA__6__KET____DOT__u_cluster__accum_out[1U] 
        = vlSymsp->TOP__top_level__DOT__gen_clusters__BRA__6__KET____DOT__u_cluster.accum_out
        [1U];
    vlTOPp->top_level__DOT____Vcellout__gen_clusters__BRA__6__KET____DOT__u_cluster__accum_out[2U] 
        = vlSymsp->TOP__top_level__DOT__gen_clusters__BRA__6__KET____DOT__u_cluster.accum_out
        [2U];
    vlTOPp->top_level__DOT____Vcellout__gen_clusters__BRA__6__KET____DOT__u_cluster__accum_out[3U] 
        = vlSymsp->TOP__top_level__DOT__gen_clusters__BRA__6__KET____DOT__u_cluster.accum_out
        [3U];
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
    vlTOPp->top_level__DOT____Vcellout__gen_clusters__BRA__7__KET____DOT__u_cluster__shadow_accum_out[0U] 
        = vlSymsp->TOP__top_level__DOT__gen_clusters__BRA__7__KET____DOT__u_cluster.shadow_accum_out
        [0U];
    vlTOPp->top_level__DOT____Vcellout__gen_clusters__BRA__7__KET____DOT__u_cluster__shadow_accum_out[1U] 
        = vlSymsp->TOP__top_level__DOT__gen_clusters__BRA__7__KET____DOT__u_cluster.shadow_accum_out
        [1U];
    vlTOPp->top_level__DOT____Vcellout__gen_clusters__BRA__7__KET____DOT__u_cluster__shadow_accum_out[2U] 
        = vlSymsp->TOP__top_level__DOT__gen_clusters__BRA__7__KET____DOT__u_cluster.shadow_accum_out
        [2U];
    vlTOPp->top_level__DOT____Vcellout__gen_clusters__BRA__7__KET____DOT__u_cluster__shadow_accum_out[3U] 
        = vlSymsp->TOP__top_level__DOT__gen_clusters__BRA__7__KET____DOT__u_cluster.shadow_accum_out
        [3U];
    vlTOPp->top_level__DOT____Vcellout__gen_clusters__BRA__7__KET____DOT__u_cluster__accum_out[0U] 
        = vlSymsp->TOP__top_level__DOT__gen_clusters__BRA__7__KET____DOT__u_cluster.accum_out
        [0U];
    vlTOPp->top_level__DOT____Vcellout__gen_clusters__BRA__7__KET____DOT__u_cluster__accum_out[1U] 
        = vlSymsp->TOP__top_level__DOT__gen_clusters__BRA__7__KET____DOT__u_cluster.accum_out
        [1U];
    vlTOPp->top_level__DOT____Vcellout__gen_clusters__BRA__7__KET____DOT__u_cluster__accum_out[2U] 
        = vlSymsp->TOP__top_level__DOT__gen_clusters__BRA__7__KET____DOT__u_cluster.accum_out
        [2U];
    vlTOPp->top_level__DOT____Vcellout__gen_clusters__BRA__7__KET____DOT__u_cluster__accum_out[3U] 
        = vlSymsp->TOP__top_level__DOT__gen_clusters__BRA__7__KET____DOT__u_cluster.accum_out
        [3U];
    vlTOPp->top_level__DOT__cluster_shadow_accum[0U][0U] 
        = vlTOPp->top_level__DOT____Vcellout__gen_clusters__BRA__0__KET____DOT__u_cluster__shadow_accum_out
        [0U];
    vlTOPp->top_level__DOT__cluster_shadow_accum[0U][1U] 
        = vlTOPp->top_level__DOT____Vcellout__gen_clusters__BRA__0__KET____DOT__u_cluster__shadow_accum_out
        [1U];
    vlTOPp->top_level__DOT__cluster_shadow_accum[0U][2U] 
        = vlTOPp->top_level__DOT____Vcellout__gen_clusters__BRA__0__KET____DOT__u_cluster__shadow_accum_out
        [2U];
    vlTOPp->top_level__DOT__cluster_shadow_accum[0U][3U] 
        = vlTOPp->top_level__DOT____Vcellout__gen_clusters__BRA__0__KET____DOT__u_cluster__shadow_accum_out
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
    vlTOPp->top_level__DOT__cluster_shadow_accum[1U][0U] 
        = vlTOPp->top_level__DOT____Vcellout__gen_clusters__BRA__1__KET____DOT__u_cluster__shadow_accum_out
        [0U];
    vlTOPp->top_level__DOT__cluster_shadow_accum[1U][1U] 
        = vlTOPp->top_level__DOT____Vcellout__gen_clusters__BRA__1__KET____DOT__u_cluster__shadow_accum_out
        [1U];
    vlTOPp->top_level__DOT__cluster_shadow_accum[1U][2U] 
        = vlTOPp->top_level__DOT____Vcellout__gen_clusters__BRA__1__KET____DOT__u_cluster__shadow_accum_out
        [2U];
    vlTOPp->top_level__DOT__cluster_shadow_accum[1U][3U] 
        = vlTOPp->top_level__DOT____Vcellout__gen_clusters__BRA__1__KET____DOT__u_cluster__shadow_accum_out
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
    vlTOPp->top_level__DOT__cluster_shadow_accum[2U][0U] 
        = vlTOPp->top_level__DOT____Vcellout__gen_clusters__BRA__2__KET____DOT__u_cluster__shadow_accum_out
        [0U];
    vlTOPp->top_level__DOT__cluster_shadow_accum[2U][1U] 
        = vlTOPp->top_level__DOT____Vcellout__gen_clusters__BRA__2__KET____DOT__u_cluster__shadow_accum_out
        [1U];
    vlTOPp->top_level__DOT__cluster_shadow_accum[2U][2U] 
        = vlTOPp->top_level__DOT____Vcellout__gen_clusters__BRA__2__KET____DOT__u_cluster__shadow_accum_out
        [2U];
    vlTOPp->top_level__DOT__cluster_shadow_accum[2U][3U] 
        = vlTOPp->top_level__DOT____Vcellout__gen_clusters__BRA__2__KET____DOT__u_cluster__shadow_accum_out
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
    vlTOPp->top_level__DOT__cluster_shadow_accum[3U][0U] 
        = vlTOPp->top_level__DOT____Vcellout__gen_clusters__BRA__3__KET____DOT__u_cluster__shadow_accum_out
        [0U];
    vlTOPp->top_level__DOT__cluster_shadow_accum[3U][1U] 
        = vlTOPp->top_level__DOT____Vcellout__gen_clusters__BRA__3__KET____DOT__u_cluster__shadow_accum_out
        [1U];
    vlTOPp->top_level__DOT__cluster_shadow_accum[3U][2U] 
        = vlTOPp->top_level__DOT____Vcellout__gen_clusters__BRA__3__KET____DOT__u_cluster__shadow_accum_out
        [2U];
    vlTOPp->top_level__DOT__cluster_shadow_accum[3U][3U] 
        = vlTOPp->top_level__DOT____Vcellout__gen_clusters__BRA__3__KET____DOT__u_cluster__shadow_accum_out
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
    vlTOPp->top_level__DOT__cluster_shadow_accum[4U][0U] 
        = vlTOPp->top_level__DOT____Vcellout__gen_clusters__BRA__4__KET____DOT__u_cluster__shadow_accum_out
        [0U];
    vlTOPp->top_level__DOT__cluster_shadow_accum[4U][1U] 
        = vlTOPp->top_level__DOT____Vcellout__gen_clusters__BRA__4__KET____DOT__u_cluster__shadow_accum_out
        [1U];
    vlTOPp->top_level__DOT__cluster_shadow_accum[4U][2U] 
        = vlTOPp->top_level__DOT____Vcellout__gen_clusters__BRA__4__KET____DOT__u_cluster__shadow_accum_out
        [2U];
    vlTOPp->top_level__DOT__cluster_shadow_accum[4U][3U] 
        = vlTOPp->top_level__DOT____Vcellout__gen_clusters__BRA__4__KET____DOT__u_cluster__shadow_accum_out
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
    vlTOPp->top_level__DOT__cluster_shadow_accum[5U][0U] 
        = vlTOPp->top_level__DOT____Vcellout__gen_clusters__BRA__5__KET____DOT__u_cluster__shadow_accum_out
        [0U];
    vlTOPp->top_level__DOT__cluster_shadow_accum[5U][1U] 
        = vlTOPp->top_level__DOT____Vcellout__gen_clusters__BRA__5__KET____DOT__u_cluster__shadow_accum_out
        [1U];
    vlTOPp->top_level__DOT__cluster_shadow_accum[5U][2U] 
        = vlTOPp->top_level__DOT____Vcellout__gen_clusters__BRA__5__KET____DOT__u_cluster__shadow_accum_out
        [2U];
    vlTOPp->top_level__DOT__cluster_shadow_accum[5U][3U] 
        = vlTOPp->top_level__DOT____Vcellout__gen_clusters__BRA__5__KET____DOT__u_cluster__shadow_accum_out
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
    vlTOPp->top_level__DOT__cluster_shadow_accum[6U][0U] 
        = vlTOPp->top_level__DOT____Vcellout__gen_clusters__BRA__6__KET____DOT__u_cluster__shadow_accum_out
        [0U];
    vlTOPp->top_level__DOT__cluster_shadow_accum[6U][1U] 
        = vlTOPp->top_level__DOT____Vcellout__gen_clusters__BRA__6__KET____DOT__u_cluster__shadow_accum_out
        [1U];
    vlTOPp->top_level__DOT__cluster_shadow_accum[6U][2U] 
        = vlTOPp->top_level__DOT____Vcellout__gen_clusters__BRA__6__KET____DOT__u_cluster__shadow_accum_out
        [2U];
    vlTOPp->top_level__DOT__cluster_shadow_accum[6U][3U] 
        = vlTOPp->top_level__DOT____Vcellout__gen_clusters__BRA__6__KET____DOT__u_cluster__shadow_accum_out
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
    vlTOPp->top_level__DOT__cluster_shadow_accum[7U][0U] 
        = vlTOPp->top_level__DOT____Vcellout__gen_clusters__BRA__7__KET____DOT__u_cluster__shadow_accum_out
        [0U];
    vlTOPp->top_level__DOT__cluster_shadow_accum[7U][1U] 
        = vlTOPp->top_level__DOT____Vcellout__gen_clusters__BRA__7__KET____DOT__u_cluster__shadow_accum_out
        [1U];
    vlTOPp->top_level__DOT__cluster_shadow_accum[7U][2U] 
        = vlTOPp->top_level__DOT____Vcellout__gen_clusters__BRA__7__KET____DOT__u_cluster__shadow_accum_out
        [2U];
    vlTOPp->top_level__DOT__cluster_shadow_accum[7U][3U] 
        = vlTOPp->top_level__DOT____Vcellout__gen_clusters__BRA__7__KET____DOT__u_cluster__shadow_accum_out
        [3U];
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
    vlTOPp->top_level__DOT__logical_accum[0U] = 0U;
    vlTOPp->top_level__DOT__logical_shadow_accum[0U] = 0U;
    vlTOPp->top_level__DOT__logical_accum[1U] = 0U;
    vlTOPp->top_level__DOT__logical_shadow_accum[1U] = 0U;
    vlTOPp->top_level__DOT__logical_accum[2U] = 0U;
    vlTOPp->top_level__DOT__logical_shadow_accum[2U] = 0U;
    vlTOPp->top_level__DOT__logical_accum[3U] = 0U;
    vlTOPp->top_level__DOT__logical_shadow_accum[3U] = 0U;
    vlTOPp->top_level__DOT__logical_accum[4U] = 0U;
    vlTOPp->top_level__DOT__logical_shadow_accum[4U] = 0U;
    vlTOPp->top_level__DOT__logical_accum[5U] = 0U;
    vlTOPp->top_level__DOT__logical_shadow_accum[5U] = 0U;
    vlTOPp->top_level__DOT__logical_accum[6U] = 0U;
    vlTOPp->top_level__DOT__logical_shadow_accum[6U] = 0U;
    vlTOPp->top_level__DOT__logical_accum[7U] = 0U;
    vlTOPp->top_level__DOT__logical_shadow_accum[7U] = 0U;
    vlTOPp->top_level__DOT__logical_accum[8U] = 0U;
    vlTOPp->top_level__DOT__logical_shadow_accum[8U] = 0U;
    vlTOPp->top_level__DOT__logical_accum[9U] = 0U;
    vlTOPp->top_level__DOT__logical_shadow_accum[9U] = 0U;
    vlTOPp->top_level__DOT__logical_accum[0xaU] = 0U;
    vlTOPp->top_level__DOT__logical_shadow_accum[0xaU] = 0U;
    vlTOPp->top_level__DOT__logical_accum[0xbU] = 0U;
    vlTOPp->top_level__DOT__logical_shadow_accum[0xbU] = 0U;
    vlTOPp->top_level__DOT__logical_accum[0xcU] = 0U;
    vlTOPp->top_level__DOT__logical_shadow_accum[0xcU] = 0U;
    vlTOPp->top_level__DOT__logical_accum[0xdU] = 0U;
    vlTOPp->top_level__DOT__logical_shadow_accum[0xdU] = 0U;
    vlTOPp->top_level__DOT__logical_accum[0xeU] = 0U;
    vlTOPp->top_level__DOT__logical_shadow_accum[0xeU] = 0U;
    vlTOPp->top_level__DOT__logical_accum[0xfU] = 0U;
    vlTOPp->top_level__DOT__logical_shadow_accum[0xfU] = 0U;
    vlTOPp->top_level__DOT__logical_accum[0x10U] = 0U;
    vlTOPp->top_level__DOT__logical_shadow_accum[0x10U] = 0U;
    vlTOPp->top_level__DOT__logical_accum[0x11U] = 0U;
    vlTOPp->top_level__DOT__logical_shadow_accum[0x11U] = 0U;
    vlTOPp->top_level__DOT__logical_accum[0x12U] = 0U;
    vlTOPp->top_level__DOT__logical_shadow_accum[0x12U] = 0U;
    vlTOPp->top_level__DOT__logical_accum[0x13U] = 0U;
    vlTOPp->top_level__DOT__logical_shadow_accum[0x13U] = 0U;
    vlTOPp->top_level__DOT__logical_accum[0x14U] = 0U;
    vlTOPp->top_level__DOT__logical_shadow_accum[0x14U] = 0U;
    vlTOPp->top_level__DOT__logical_accum[0x15U] = 0U;
    vlTOPp->top_level__DOT__logical_shadow_accum[0x15U] = 0U;
    vlTOPp->top_level__DOT__logical_accum[0x16U] = 0U;
    vlTOPp->top_level__DOT__logical_shadow_accum[0x16U] = 0U;
    vlTOPp->top_level__DOT__logical_accum[0x17U] = 0U;
    vlTOPp->top_level__DOT__logical_shadow_accum[0x17U] = 0U;
    vlTOPp->top_level__DOT__logical_accum[0x18U] = 0U;
    vlTOPp->top_level__DOT__logical_shadow_accum[0x18U] = 0U;
    vlTOPp->top_level__DOT__logical_accum[0x19U] = 0U;
    vlTOPp->top_level__DOT__logical_shadow_accum[0x19U] = 0U;
    vlTOPp->top_level__DOT__logical_accum[0x1aU] = 0U;
    vlTOPp->top_level__DOT__logical_shadow_accum[0x1aU] = 0U;
    vlTOPp->top_level__DOT__logical_accum[0x1bU] = 0U;
    vlTOPp->top_level__DOT__logical_shadow_accum[0x1bU] = 0U;
    vlTOPp->top_level__DOT__logical_accum[0x1cU] = 0U;
    vlTOPp->top_level__DOT__logical_shadow_accum[0x1cU] = 0U;
    vlTOPp->top_level__DOT__logical_accum[0x1dU] = 0U;
    vlTOPp->top_level__DOT__logical_shadow_accum[0x1dU] = 0U;
    vlTOPp->top_level__DOT__logical_accum[0x1eU] = 0U;
    vlTOPp->top_level__DOT__logical_shadow_accum[0x1eU] = 0U;
    vlTOPp->top_level__DOT__logical_accum[0x1fU] = 0U;
    vlTOPp->top_level__DOT__logical_shadow_accum[0x1fU] = 0U;
    vlTOPp->top_level__DOT__logical_accum[0U] = vlTOPp->top_level__DOT__cluster_accum
        [0U][0U];
    vlTOPp->top_level__DOT__logical_shadow_accum[0U] 
        = vlTOPp->top_level__DOT__cluster_shadow_accum
        [0U][0U];
    vlTOPp->top_level__DOT__logical_accum[1U] = vlTOPp->top_level__DOT__cluster_accum
        [0U][1U];
    vlTOPp->top_level__DOT__logical_shadow_accum[1U] 
        = vlTOPp->top_level__DOT__cluster_shadow_accum
        [0U][1U];
    vlTOPp->top_level__DOT__logical_accum[2U] = vlTOPp->top_level__DOT__cluster_accum
        [0U][2U];
    vlTOPp->top_level__DOT__logical_shadow_accum[2U] 
        = vlTOPp->top_level__DOT__cluster_shadow_accum
        [0U][2U];
    vlTOPp->top_level__DOT__logical_accum[3U] = vlTOPp->top_level__DOT__cluster_accum
        [0U][3U];
    vlTOPp->top_level__DOT__logical_shadow_accum[3U] 
        = vlTOPp->top_level__DOT__cluster_shadow_accum
        [0U][3U];
    vlTOPp->top_level__DOT__logical_accum[4U] = vlTOPp->top_level__DOT__cluster_accum
        [1U][0U];
    vlTOPp->top_level__DOT__logical_shadow_accum[4U] 
        = vlTOPp->top_level__DOT__cluster_shadow_accum
        [1U][0U];
    vlTOPp->top_level__DOT__logical_accum[5U] = vlTOPp->top_level__DOT__cluster_accum
        [1U][1U];
    vlTOPp->top_level__DOT__logical_shadow_accum[5U] 
        = vlTOPp->top_level__DOT__cluster_shadow_accum
        [1U][1U];
    vlTOPp->top_level__DOT__logical_accum[6U] = vlTOPp->top_level__DOT__cluster_accum
        [1U][2U];
    vlTOPp->top_level__DOT__logical_shadow_accum[6U] 
        = vlTOPp->top_level__DOT__cluster_shadow_accum
        [1U][2U];
    vlTOPp->top_level__DOT__logical_accum[7U] = vlTOPp->top_level__DOT__cluster_accum
        [1U][3U];
    vlTOPp->top_level__DOT__logical_shadow_accum[7U] 
        = vlTOPp->top_level__DOT__cluster_shadow_accum
        [1U][3U];
    vlTOPp->top_level__DOT__logical_accum[8U] = vlTOPp->top_level__DOT__cluster_accum
        [2U][0U];
    vlTOPp->top_level__DOT__logical_shadow_accum[8U] 
        = vlTOPp->top_level__DOT__cluster_shadow_accum
        [2U][0U];
    vlTOPp->top_level__DOT__logical_accum[9U] = vlTOPp->top_level__DOT__cluster_accum
        [2U][1U];
    vlTOPp->top_level__DOT__logical_shadow_accum[9U] 
        = vlTOPp->top_level__DOT__cluster_shadow_accum
        [2U][1U];
    vlTOPp->top_level__DOT__logical_accum[0xaU] = vlTOPp->top_level__DOT__cluster_accum
        [2U][2U];
    vlTOPp->top_level__DOT__logical_shadow_accum[0xaU] 
        = vlTOPp->top_level__DOT__cluster_shadow_accum
        [2U][2U];
    vlTOPp->top_level__DOT__logical_accum[0xbU] = vlTOPp->top_level__DOT__cluster_accum
        [2U][3U];
    vlTOPp->top_level__DOT__logical_shadow_accum[0xbU] 
        = vlTOPp->top_level__DOT__cluster_shadow_accum
        [2U][3U];
    vlTOPp->top_level__DOT__logical_accum[0xcU] = vlTOPp->top_level__DOT__cluster_accum
        [3U][0U];
    vlTOPp->top_level__DOT__logical_shadow_accum[0xcU] 
        = vlTOPp->top_level__DOT__cluster_shadow_accum
        [3U][0U];
    vlTOPp->top_level__DOT__logical_accum[0xdU] = vlTOPp->top_level__DOT__cluster_accum
        [3U][1U];
    vlTOPp->top_level__DOT__logical_shadow_accum[0xdU] 
        = vlTOPp->top_level__DOT__cluster_shadow_accum
        [3U][1U];
    vlTOPp->top_level__DOT__logical_accum[0xeU] = vlTOPp->top_level__DOT__cluster_accum
        [3U][2U];
    vlTOPp->top_level__DOT__logical_shadow_accum[0xeU] 
        = vlTOPp->top_level__DOT__cluster_shadow_accum
        [3U][2U];
    vlTOPp->top_level__DOT__logical_accum[0xfU] = vlTOPp->top_level__DOT__cluster_accum
        [3U][3U];
    vlTOPp->top_level__DOT__logical_shadow_accum[0xfU] 
        = vlTOPp->top_level__DOT__cluster_shadow_accum
        [3U][3U];
    vlTOPp->top_level__DOT__logical_accum[0x10U] = 
        vlTOPp->top_level__DOT__cluster_accum[4U][0U];
    vlTOPp->top_level__DOT__logical_shadow_accum[0x10U] 
        = vlTOPp->top_level__DOT__cluster_shadow_accum
        [4U][0U];
    vlTOPp->top_level__DOT__logical_accum[0x11U] = 
        vlTOPp->top_level__DOT__cluster_accum[4U][1U];
    vlTOPp->top_level__DOT__logical_shadow_accum[0x11U] 
        = vlTOPp->top_level__DOT__cluster_shadow_accum
        [4U][1U];
    vlTOPp->top_level__DOT__logical_accum[0x12U] = 
        vlTOPp->top_level__DOT__cluster_accum[4U][2U];
    vlTOPp->top_level__DOT__logical_shadow_accum[0x12U] 
        = vlTOPp->top_level__DOT__cluster_shadow_accum
        [4U][2U];
    vlTOPp->top_level__DOT__logical_accum[0x13U] = 
        vlTOPp->top_level__DOT__cluster_accum[4U][3U];
    vlTOPp->top_level__DOT__logical_shadow_accum[0x13U] 
        = vlTOPp->top_level__DOT__cluster_shadow_accum
        [4U][3U];
    vlTOPp->top_level__DOT__logical_accum[0x14U] = 
        vlTOPp->top_level__DOT__cluster_accum[5U][0U];
    vlTOPp->top_level__DOT__logical_shadow_accum[0x14U] 
        = vlTOPp->top_level__DOT__cluster_shadow_accum
        [5U][0U];
    vlTOPp->top_level__DOT__logical_accum[0x15U] = 
        vlTOPp->top_level__DOT__cluster_accum[5U][1U];
    vlTOPp->top_level__DOT__logical_shadow_accum[0x15U] 
        = vlTOPp->top_level__DOT__cluster_shadow_accum
        [5U][1U];
    vlTOPp->top_level__DOT__logical_accum[0x16U] = 
        vlTOPp->top_level__DOT__cluster_accum[5U][2U];
    vlTOPp->top_level__DOT__logical_shadow_accum[0x16U] 
        = vlTOPp->top_level__DOT__cluster_shadow_accum
        [5U][2U];
    vlTOPp->top_level__DOT__logical_accum[0x17U] = 
        vlTOPp->top_level__DOT__cluster_accum[5U][3U];
    vlTOPp->top_level__DOT__logical_shadow_accum[0x17U] 
        = vlTOPp->top_level__DOT__cluster_shadow_accum
        [5U][3U];
    vlTOPp->top_level__DOT__logical_accum[0x18U] = 
        vlTOPp->top_level__DOT__cluster_accum[6U][0U];
    vlTOPp->top_level__DOT__logical_shadow_accum[0x18U] 
        = vlTOPp->top_level__DOT__cluster_shadow_accum
        [6U][0U];
    vlTOPp->top_level__DOT__logical_accum[0x19U] = 
        vlTOPp->top_level__DOT__cluster_accum[6U][1U];
    vlTOPp->top_level__DOT__logical_shadow_accum[0x19U] 
        = vlTOPp->top_level__DOT__cluster_shadow_accum
        [6U][1U];
    vlTOPp->top_level__DOT__logical_accum[0x1aU] = 
        vlTOPp->top_level__DOT__cluster_accum[6U][2U];
    vlTOPp->top_level__DOT__logical_shadow_accum[0x1aU] 
        = vlTOPp->top_level__DOT__cluster_shadow_accum
        [6U][2U];
    vlTOPp->top_level__DOT__logical_accum[0x1bU] = 
        vlTOPp->top_level__DOT__cluster_accum[6U][3U];
    vlTOPp->top_level__DOT__logical_shadow_accum[0x1bU] 
        = vlTOPp->top_level__DOT__cluster_shadow_accum
        [6U][3U];
    vlTOPp->top_level__DOT__logical_accum[0x1cU] = 
        vlTOPp->top_level__DOT__cluster_accum[7U][0U];
    vlTOPp->top_level__DOT__logical_shadow_accum[0x1cU] 
        = vlTOPp->top_level__DOT__cluster_shadow_accum
        [7U][0U];
    vlTOPp->top_level__DOT__logical_accum[0x1dU] = 
        vlTOPp->top_level__DOT__cluster_accum[7U][1U];
    vlTOPp->top_level__DOT__logical_shadow_accum[0x1dU] 
        = vlTOPp->top_level__DOT__cluster_shadow_accum
        [7U][1U];
    vlTOPp->top_level__DOT__logical_accum[0x1eU] = 
        vlTOPp->top_level__DOT__cluster_accum[7U][2U];
    vlTOPp->top_level__DOT__logical_shadow_accum[0x1eU] 
        = vlTOPp->top_level__DOT__cluster_shadow_accum
        [7U][2U];
    vlTOPp->top_level__DOT__logical_accum[0x1fU] = 
        vlTOPp->top_level__DOT__cluster_accum[7U][3U];
    vlTOPp->top_level__DOT__logical_shadow_accum[0x1fU] 
        = vlTOPp->top_level__DOT__cluster_shadow_accum
        [7U][3U];
}

VL_INLINE_OPT void Vtop_level::_combo__TOP__6(Vtop_level__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop_level::_combo__TOP__6\n"); );
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
                if ((0x20U <= ((IData)(1U) + vlTOPp->top_level__DOT__u_control__DOT__write_iter_q))) {
                    vlTOPp->top_level__DOT__u_control__DOT__state_d = 5U;
                }
            }
        }
    } else {
        if ((2U & (IData)(vlTOPp->top_level__DOT__u_control__DOT__state_q))) {
            if ((1U & (IData)(vlTOPp->top_level__DOT__u_control__DOT__state_q))) {
                if ((1U <= ((IData)(1U) + vlTOPp->top_level__DOT__u_control__DOT__drain_iter_q))) {
                    vlTOPp->top_level__DOT__u_control__DOT__state_d = 4U;
                }
            } else {
                if ((4U <= ((IData)(1U) + vlTOPp->top_level__DOT__u_control__DOT__compute_iter_q))) {
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
        vlTOPp->_sequent__TOP__4(vlSymsp);
        vlSymsp->TOP__top_level__DOT__gen_clusters__BRA__0__KET____DOT__u_cluster._sequent__TOP__top_level__DOT__gen_clusters__BRA__0__KET____DOT__u_cluster__9(vlSymsp);
        vlSymsp->TOP__top_level__DOT__gen_clusters__BRA__1__KET____DOT__u_cluster._sequent__TOP__top_level__DOT__gen_clusters__BRA__0__KET____DOT__u_cluster__9(vlSymsp);
        vlSymsp->TOP__top_level__DOT__gen_clusters__BRA__2__KET____DOT__u_cluster._sequent__TOP__top_level__DOT__gen_clusters__BRA__0__KET____DOT__u_cluster__9(vlSymsp);
        vlSymsp->TOP__top_level__DOT__gen_clusters__BRA__3__KET____DOT__u_cluster._sequent__TOP__top_level__DOT__gen_clusters__BRA__0__KET____DOT__u_cluster__9(vlSymsp);
        vlSymsp->TOP__top_level__DOT__gen_clusters__BRA__4__KET____DOT__u_cluster._sequent__TOP__top_level__DOT__gen_clusters__BRA__0__KET____DOT__u_cluster__9(vlSymsp);
        vlSymsp->TOP__top_level__DOT__gen_clusters__BRA__5__KET____DOT__u_cluster._sequent__TOP__top_level__DOT__gen_clusters__BRA__0__KET____DOT__u_cluster__9(vlSymsp);
        vlSymsp->TOP__top_level__DOT__gen_clusters__BRA__6__KET____DOT__u_cluster._sequent__TOP__top_level__DOT__gen_clusters__BRA__0__KET____DOT__u_cluster__9(vlSymsp);
        vlSymsp->TOP__top_level__DOT__gen_clusters__BRA__7__KET____DOT__u_cluster._sequent__TOP__top_level__DOT__gen_clusters__BRA__0__KET____DOT__u_cluster__9(vlSymsp);
        vlTOPp->_sequent__TOP__5(vlSymsp);
    }
    vlTOPp->_combo__TOP__6(vlSymsp);
    vlSymsp->TOP__top_level__DOT__gen_clusters__BRA__0__KET____DOT__u_cluster._combo__TOP__top_level__DOT__gen_clusters__BRA__0__KET____DOT__u_cluster__17(vlSymsp);
    vlSymsp->TOP__top_level__DOT__gen_clusters__BRA__1__KET____DOT__u_cluster._combo__TOP__top_level__DOT__gen_clusters__BRA__0__KET____DOT__u_cluster__17(vlSymsp);
    vlSymsp->TOP__top_level__DOT__gen_clusters__BRA__2__KET____DOT__u_cluster._combo__TOP__top_level__DOT__gen_clusters__BRA__0__KET____DOT__u_cluster__17(vlSymsp);
    vlSymsp->TOP__top_level__DOT__gen_clusters__BRA__3__KET____DOT__u_cluster._combo__TOP__top_level__DOT__gen_clusters__BRA__0__KET____DOT__u_cluster__17(vlSymsp);
    vlSymsp->TOP__top_level__DOT__gen_clusters__BRA__4__KET____DOT__u_cluster._combo__TOP__top_level__DOT__gen_clusters__BRA__0__KET____DOT__u_cluster__17(vlSymsp);
    vlSymsp->TOP__top_level__DOT__gen_clusters__BRA__5__KET____DOT__u_cluster._combo__TOP__top_level__DOT__gen_clusters__BRA__0__KET____DOT__u_cluster__17(vlSymsp);
    vlSymsp->TOP__top_level__DOT__gen_clusters__BRA__6__KET____DOT__u_cluster._combo__TOP__top_level__DOT__gen_clusters__BRA__0__KET____DOT__u_cluster__17(vlSymsp);
    vlSymsp->TOP__top_level__DOT__gen_clusters__BRA__7__KET____DOT__u_cluster._combo__TOP__top_level__DOT__gen_clusters__BRA__0__KET____DOT__u_cluster__17(vlSymsp);
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
