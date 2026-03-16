// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vtop_level.h for the primary calling header

#include "Vtop_level.h"
#include "Vtop_level__Syms.h"

//==========

VL_CTOR_IMP(Vtop_level) {
    Vtop_level__Syms* __restrict vlSymsp = __VlSymsp = new Vtop_level__Syms(this, name());
    Vtop_level* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Reset internal values
    
    // Reset structure values
    _ctor_var_reset();
}

void Vtop_level::__Vconfigure(Vtop_level__Syms* vlSymsp, bool first) {
    if (false && first) {}  // Prevent unused
    this->__VlSymsp = vlSymsp;
    if (false && this->__VlSymsp) {}  // Prevent unused
    Verilated::timeunit(-12);
    Verilated::timeprecision(-12);
}

Vtop_level::~Vtop_level() {
    VL_DO_CLEAR(delete __VlSymsp, __VlSymsp = NULL);
}

void Vtop_level::_settle__TOP__1(Vtop_level__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop_level::_settle__TOP__1\n"); );
    Vtop_level* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->top_level__DOT__gen_clusters__BRA__0__KET____DOT__u_cluster__DOT__pe_valid[0U] = 1U;
    vlTOPp->top_level__DOT__gen_clusters__BRA__0__KET____DOT__u_cluster__DOT__pe_valid[1U] = 1U;
    vlTOPp->top_level__DOT__gen_clusters__BRA__0__KET____DOT__u_cluster__DOT__pe_valid[2U] = 1U;
    vlTOPp->top_level__DOT__gen_clusters__BRA__0__KET____DOT__u_cluster__DOT__pe_valid[3U] = 1U;
    vlTOPp->top_level__DOT__gen_clusters__BRA__1__KET____DOT__u_cluster__DOT__pe_valid[0U] = 1U;
    vlTOPp->top_level__DOT__gen_clusters__BRA__1__KET____DOT__u_cluster__DOT__pe_valid[1U] = 1U;
    vlTOPp->top_level__DOT__gen_clusters__BRA__1__KET____DOT__u_cluster__DOT__pe_valid[2U] = 1U;
    vlTOPp->top_level__DOT__gen_clusters__BRA__1__KET____DOT__u_cluster__DOT__pe_valid[3U] = 1U;
    vlTOPp->top_level__DOT__gen_clusters__BRA__2__KET____DOT__u_cluster__DOT__pe_valid[0U] = 1U;
    vlTOPp->top_level__DOT__gen_clusters__BRA__2__KET____DOT__u_cluster__DOT__pe_valid[1U] = 1U;
    vlTOPp->top_level__DOT__gen_clusters__BRA__2__KET____DOT__u_cluster__DOT__pe_valid[2U] = 1U;
    vlTOPp->top_level__DOT__gen_clusters__BRA__2__KET____DOT__u_cluster__DOT__pe_valid[3U] = 1U;
    vlTOPp->top_level__DOT__gen_clusters__BRA__3__KET____DOT__u_cluster__DOT__pe_valid[0U] = 1U;
    vlTOPp->top_level__DOT__gen_clusters__BRA__3__KET____DOT__u_cluster__DOT__pe_valid[1U] = 1U;
    vlTOPp->top_level__DOT__gen_clusters__BRA__3__KET____DOT__u_cluster__DOT__pe_valid[2U] = 1U;
    vlTOPp->top_level__DOT__gen_clusters__BRA__3__KET____DOT__u_cluster__DOT__pe_valid[3U] = 1U;
    vlTOPp->debug_cycle_count = vlTOPp->top_level__DOT__cycle_count;
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
                    = ((4U <= ((IData)(1U) + vlTOPp->top_level__DOT__u_control__DOT__compute_iter_q))
                        ? 0U : ((IData)(1U) + vlTOPp->top_level__DOT__u_control__DOT__compute_iter_q));
            }
        } else {
            if ((1U & (IData)(vlTOPp->top_level__DOT__u_control__DOT__state_q))) {
                vlTOPp->top_level__DOT__u_control__DOT__compute_iter_d = 0U;
            }
        }
    }
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
    vlTOPp->top_level__DOT__gen_clusters__BRA__0__KET____DOT__u_cluster__DOT__pe_done[0U] 
        = ((IData)(vlTOPp->top_level__DOT__compute_en) 
           & vlTOPp->top_level__DOT__gen_clusters__BRA__0__KET____DOT__u_cluster__DOT__pe_valid
           [0U]);
    vlTOPp->top_level__DOT__gen_clusters__BRA__0__KET____DOT__u_cluster__DOT__pe_done[1U] 
        = ((IData)(vlTOPp->top_level__DOT__compute_en) 
           & vlTOPp->top_level__DOT__gen_clusters__BRA__0__KET____DOT__u_cluster__DOT__pe_valid
           [1U]);
    vlTOPp->top_level__DOT__gen_clusters__BRA__0__KET____DOT__u_cluster__DOT__pe_done[2U] 
        = ((IData)(vlTOPp->top_level__DOT__compute_en) 
           & vlTOPp->top_level__DOT__gen_clusters__BRA__0__KET____DOT__u_cluster__DOT__pe_valid
           [2U]);
    vlTOPp->top_level__DOT__gen_clusters__BRA__0__KET____DOT__u_cluster__DOT__pe_done[3U] 
        = ((IData)(vlTOPp->top_level__DOT__compute_en) 
           & vlTOPp->top_level__DOT__gen_clusters__BRA__0__KET____DOT__u_cluster__DOT__pe_valid
           [3U]);
    vlTOPp->top_level__DOT__gen_clusters__BRA__1__KET____DOT__u_cluster__DOT__pe_done[0U] 
        = ((IData)(vlTOPp->top_level__DOT__compute_en) 
           & vlTOPp->top_level__DOT__gen_clusters__BRA__1__KET____DOT__u_cluster__DOT__pe_valid
           [0U]);
    vlTOPp->top_level__DOT__gen_clusters__BRA__1__KET____DOT__u_cluster__DOT__pe_done[1U] 
        = ((IData)(vlTOPp->top_level__DOT__compute_en) 
           & vlTOPp->top_level__DOT__gen_clusters__BRA__1__KET____DOT__u_cluster__DOT__pe_valid
           [1U]);
    vlTOPp->top_level__DOT__gen_clusters__BRA__1__KET____DOT__u_cluster__DOT__pe_done[2U] 
        = ((IData)(vlTOPp->top_level__DOT__compute_en) 
           & vlTOPp->top_level__DOT__gen_clusters__BRA__1__KET____DOT__u_cluster__DOT__pe_valid
           [2U]);
    vlTOPp->top_level__DOT__gen_clusters__BRA__1__KET____DOT__u_cluster__DOT__pe_done[3U] 
        = ((IData)(vlTOPp->top_level__DOT__compute_en) 
           & vlTOPp->top_level__DOT__gen_clusters__BRA__1__KET____DOT__u_cluster__DOT__pe_valid
           [3U]);
    vlTOPp->top_level__DOT__gen_clusters__BRA__2__KET____DOT__u_cluster__DOT__pe_done[0U] 
        = ((IData)(vlTOPp->top_level__DOT__compute_en) 
           & vlTOPp->top_level__DOT__gen_clusters__BRA__2__KET____DOT__u_cluster__DOT__pe_valid
           [0U]);
    vlTOPp->top_level__DOT__gen_clusters__BRA__2__KET____DOT__u_cluster__DOT__pe_done[1U] 
        = ((IData)(vlTOPp->top_level__DOT__compute_en) 
           & vlTOPp->top_level__DOT__gen_clusters__BRA__2__KET____DOT__u_cluster__DOT__pe_valid
           [1U]);
    vlTOPp->top_level__DOT__gen_clusters__BRA__2__KET____DOT__u_cluster__DOT__pe_done[2U] 
        = ((IData)(vlTOPp->top_level__DOT__compute_en) 
           & vlTOPp->top_level__DOT__gen_clusters__BRA__2__KET____DOT__u_cluster__DOT__pe_valid
           [2U]);
    vlTOPp->top_level__DOT__gen_clusters__BRA__2__KET____DOT__u_cluster__DOT__pe_done[3U] 
        = ((IData)(vlTOPp->top_level__DOT__compute_en) 
           & vlTOPp->top_level__DOT__gen_clusters__BRA__2__KET____DOT__u_cluster__DOT__pe_valid
           [3U]);
    vlTOPp->top_level__DOT__gen_clusters__BRA__3__KET____DOT__u_cluster__DOT__pe_done[0U] 
        = ((IData)(vlTOPp->top_level__DOT__compute_en) 
           & vlTOPp->top_level__DOT__gen_clusters__BRA__3__KET____DOT__u_cluster__DOT__pe_valid
           [0U]);
    vlTOPp->top_level__DOT__gen_clusters__BRA__3__KET____DOT__u_cluster__DOT__pe_done[1U] 
        = ((IData)(vlTOPp->top_level__DOT__compute_en) 
           & vlTOPp->top_level__DOT__gen_clusters__BRA__3__KET____DOT__u_cluster__DOT__pe_valid
           [1U]);
    vlTOPp->top_level__DOT__gen_clusters__BRA__3__KET____DOT__u_cluster__DOT__pe_done[2U] 
        = ((IData)(vlTOPp->top_level__DOT__compute_en) 
           & vlTOPp->top_level__DOT__gen_clusters__BRA__3__KET____DOT__u_cluster__DOT__pe_valid
           [2U]);
    vlTOPp->top_level__DOT__gen_clusters__BRA__3__KET____DOT__u_cluster__DOT__pe_done[3U] 
        = ((IData)(vlTOPp->top_level__DOT__compute_en) 
           & vlTOPp->top_level__DOT__gen_clusters__BRA__3__KET____DOT__u_cluster__DOT__pe_valid
           [3U]);
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
    vlTOPp->top_level__DOT__a_read_addr[0U] = vlTOPp->top_level__DOT____Vcellout__u_interconnect__a_read_addr
        [0U];
    vlTOPp->top_level__DOT__a_read_addr[1U] = vlTOPp->top_level__DOT____Vcellout__u_interconnect__a_read_addr
        [1U];
    vlTOPp->top_level__DOT__a_read_addr[2U] = vlTOPp->top_level__DOT____Vcellout__u_interconnect__a_read_addr
        [2U];
    vlTOPp->top_level__DOT__a_read_addr[3U] = vlTOPp->top_level__DOT____Vcellout__u_interconnect__a_read_addr
        [3U];
    vlTOPp->top_level__DOT__b_read_addr[0U] = vlTOPp->top_level__DOT____Vcellout__u_interconnect__b_read_addr
        [0U];
    vlTOPp->top_level__DOT__b_read_addr[1U] = vlTOPp->top_level__DOT____Vcellout__u_interconnect__b_read_addr
        [1U];
    vlTOPp->top_level__DOT__b_read_addr[2U] = vlTOPp->top_level__DOT____Vcellout__u_interconnect__b_read_addr
        [2U];
    vlTOPp->top_level__DOT__b_read_addr[3U] = vlTOPp->top_level__DOT____Vcellout__u_interconnect__b_read_addr
        [3U];
    vlTOPp->top_level__DOT____Vcellinp__u_a_buffer__read_addr[0U] 
        = vlTOPp->top_level__DOT__a_read_addr[0U];
    vlTOPp->top_level__DOT____Vcellinp__u_a_buffer__read_addr[1U] 
        = vlTOPp->top_level__DOT__a_read_addr[1U];
    vlTOPp->top_level__DOT____Vcellinp__u_a_buffer__read_addr[2U] 
        = vlTOPp->top_level__DOT__a_read_addr[2U];
    vlTOPp->top_level__DOT____Vcellinp__u_a_buffer__read_addr[3U] 
        = vlTOPp->top_level__DOT__a_read_addr[3U];
    vlTOPp->top_level__DOT____Vcellinp__u_b_buffer__read_addr[0U] 
        = vlTOPp->top_level__DOT__b_read_addr[0U];
    vlTOPp->top_level__DOT____Vcellinp__u_b_buffer__read_addr[1U] 
        = vlTOPp->top_level__DOT__b_read_addr[1U];
    vlTOPp->top_level__DOT____Vcellinp__u_b_buffer__read_addr[2U] 
        = vlTOPp->top_level__DOT__b_read_addr[2U];
    vlTOPp->top_level__DOT____Vcellinp__u_b_buffer__read_addr[3U] 
        = vlTOPp->top_level__DOT__b_read_addr[3U];
}

void Vtop_level::_initial__TOP__2(Vtop_level__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop_level::_initial__TOP__2\n"); );
    Vtop_level* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Variables
    IData/*31:0*/ __Vilp;
    // Body
    __Vilp = 0U;
    while ((__Vilp <= 0x3fU)) {
        vlTOPp->top_level__DOT__u_a_buffer__DOT__mem[__Vilp] = 0U;
        __Vilp = ((IData)(1U) + __Vilp);
    }
    VL_READMEM_N(true, 16, 64, 0, std::string("data/input_a.mem")
                 , vlTOPp->top_level__DOT__u_a_buffer__DOT__mem
                 , 0, ~0ULL);
    __Vilp = 0U;
    while ((__Vilp <= 0x3fU)) {
        vlTOPp->top_level__DOT__u_b_buffer__DOT__mem[__Vilp] = 0U;
        __Vilp = ((IData)(1U) + __Vilp);
    }
    VL_READMEM_N(true, 16, 64, 0, std::string("data/input_b.mem")
                 , vlTOPp->top_level__DOT__u_b_buffer__DOT__mem
                 , 0, ~0ULL);
}

void Vtop_level::_settle__TOP__4(Vtop_level__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop_level::_settle__TOP__4\n"); );
    Vtop_level* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
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
    vlTOPp->top_level__DOT__a_row_data[0U] = vlTOPp->top_level__DOT____Vcellout__u_a_buffer__read_data
        [0U];
    vlTOPp->top_level__DOT__a_row_data[1U] = vlTOPp->top_level__DOT____Vcellout__u_a_buffer__read_data
        [1U];
    vlTOPp->top_level__DOT__a_row_data[2U] = vlTOPp->top_level__DOT____Vcellout__u_a_buffer__read_data
        [2U];
    vlTOPp->top_level__DOT__a_row_data[3U] = vlTOPp->top_level__DOT____Vcellout__u_a_buffer__read_data
        [3U];
    vlTOPp->top_level__DOT__b_col_data[0U] = vlTOPp->top_level__DOT____Vcellout__u_b_buffer__read_data
        [0U];
    vlTOPp->top_level__DOT__b_col_data[1U] = vlTOPp->top_level__DOT____Vcellout__u_b_buffer__read_data
        [1U];
    vlTOPp->top_level__DOT__b_col_data[2U] = vlTOPp->top_level__DOT____Vcellout__u_b_buffer__read_data
        [2U];
    vlTOPp->top_level__DOT__b_col_data[3U] = vlTOPp->top_level__DOT____Vcellout__u_b_buffer__read_data
        [3U];
    vlTOPp->top_level__DOT____Vcellinp__u_interconnect__a_row_data[0U] 
        = vlTOPp->top_level__DOT__a_row_data[0U];
    vlTOPp->top_level__DOT____Vcellinp__u_interconnect__a_row_data[1U] 
        = vlTOPp->top_level__DOT__a_row_data[1U];
    vlTOPp->top_level__DOT____Vcellinp__u_interconnect__a_row_data[2U] 
        = vlTOPp->top_level__DOT__a_row_data[2U];
    vlTOPp->top_level__DOT____Vcellinp__u_interconnect__a_row_data[3U] 
        = vlTOPp->top_level__DOT__a_row_data[3U];
    vlTOPp->top_level__DOT____Vcellinp__u_interconnect__b_col_data[0U] 
        = vlTOPp->top_level__DOT__b_col_data[0U];
    vlTOPp->top_level__DOT____Vcellinp__u_interconnect__b_col_data[1U] 
        = vlTOPp->top_level__DOT__b_col_data[1U];
    vlTOPp->top_level__DOT____Vcellinp__u_interconnect__b_col_data[2U] 
        = vlTOPp->top_level__DOT__b_col_data[2U];
    vlTOPp->top_level__DOT____Vcellinp__u_interconnect__b_col_data[3U] 
        = vlTOPp->top_level__DOT__b_col_data[3U];
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
    vlTOPp->top_level__DOT__gen_clusters__BRA__0__KET____DOT__u_cluster__DOT__pe_a[0U] 
        = vlTOPp->top_level__DOT____Vcellinp__gen_clusters__BRA__0__KET____DOT__u_cluster__lane_a
        [0U];
    vlTOPp->top_level__DOT__gen_clusters__BRA__0__KET____DOT__u_cluster__DOT__pe_b[0U] 
        = vlTOPp->top_level__DOT____Vcellinp__gen_clusters__BRA__0__KET____DOT__u_cluster__lane_b
        [0U];
    vlTOPp->top_level__DOT__gen_clusters__BRA__0__KET____DOT__u_cluster__DOT__pe_seed[0U] 
        = vlTOPp->top_level__DOT__gen_clusters__BRA__0__KET____DOT__u_cluster__DOT__accum_bank
        [0U];
    vlTOPp->top_level__DOT__gen_clusters__BRA__0__KET____DOT__u_cluster__DOT__pe_a[1U] 
        = vlTOPp->top_level__DOT____Vcellinp__gen_clusters__BRA__0__KET____DOT__u_cluster__lane_a
        [1U];
    vlTOPp->top_level__DOT__gen_clusters__BRA__0__KET____DOT__u_cluster__DOT__pe_b[1U] 
        = vlTOPp->top_level__DOT____Vcellinp__gen_clusters__BRA__0__KET____DOT__u_cluster__lane_b
        [1U];
    vlTOPp->top_level__DOT__gen_clusters__BRA__0__KET____DOT__u_cluster__DOT__pe_seed[1U] 
        = vlTOPp->top_level__DOT__gen_clusters__BRA__0__KET____DOT__u_cluster__DOT__accum_bank
        [1U];
    vlTOPp->top_level__DOT__gen_clusters__BRA__0__KET____DOT__u_cluster__DOT__pe_a[2U] 
        = vlTOPp->top_level__DOT____Vcellinp__gen_clusters__BRA__0__KET____DOT__u_cluster__lane_a
        [2U];
    vlTOPp->top_level__DOT__gen_clusters__BRA__0__KET____DOT__u_cluster__DOT__pe_b[2U] 
        = vlTOPp->top_level__DOT____Vcellinp__gen_clusters__BRA__0__KET____DOT__u_cluster__lane_b
        [2U];
    vlTOPp->top_level__DOT__gen_clusters__BRA__0__KET____DOT__u_cluster__DOT__pe_seed[2U] 
        = vlTOPp->top_level__DOT__gen_clusters__BRA__0__KET____DOT__u_cluster__DOT__accum_bank
        [2U];
    vlTOPp->top_level__DOT__gen_clusters__BRA__0__KET____DOT__u_cluster__DOT__pe_a[3U] 
        = vlTOPp->top_level__DOT____Vcellinp__gen_clusters__BRA__0__KET____DOT__u_cluster__lane_a
        [3U];
    vlTOPp->top_level__DOT__gen_clusters__BRA__0__KET____DOT__u_cluster__DOT__pe_b[3U] 
        = vlTOPp->top_level__DOT____Vcellinp__gen_clusters__BRA__0__KET____DOT__u_cluster__lane_b
        [3U];
    vlTOPp->top_level__DOT__gen_clusters__BRA__0__KET____DOT__u_cluster__DOT__pe_seed[3U] 
        = vlTOPp->top_level__DOT__gen_clusters__BRA__0__KET____DOT__u_cluster__DOT__accum_bank
        [3U];
    vlTOPp->top_level__DOT__gen_clusters__BRA__1__KET____DOT__u_cluster__DOT__pe_a[0U] 
        = vlTOPp->top_level__DOT____Vcellinp__gen_clusters__BRA__1__KET____DOT__u_cluster__lane_a
        [0U];
    vlTOPp->top_level__DOT__gen_clusters__BRA__1__KET____DOT__u_cluster__DOT__pe_b[0U] 
        = vlTOPp->top_level__DOT____Vcellinp__gen_clusters__BRA__1__KET____DOT__u_cluster__lane_b
        [0U];
    vlTOPp->top_level__DOT__gen_clusters__BRA__1__KET____DOT__u_cluster__DOT__pe_seed[0U] 
        = vlTOPp->top_level__DOT__gen_clusters__BRA__1__KET____DOT__u_cluster__DOT__accum_bank
        [0U];
    vlTOPp->top_level__DOT__gen_clusters__BRA__1__KET____DOT__u_cluster__DOT__pe_a[1U] 
        = vlTOPp->top_level__DOT____Vcellinp__gen_clusters__BRA__1__KET____DOT__u_cluster__lane_a
        [1U];
    vlTOPp->top_level__DOT__gen_clusters__BRA__1__KET____DOT__u_cluster__DOT__pe_b[1U] 
        = vlTOPp->top_level__DOT____Vcellinp__gen_clusters__BRA__1__KET____DOT__u_cluster__lane_b
        [1U];
    vlTOPp->top_level__DOT__gen_clusters__BRA__1__KET____DOT__u_cluster__DOT__pe_seed[1U] 
        = vlTOPp->top_level__DOT__gen_clusters__BRA__1__KET____DOT__u_cluster__DOT__accum_bank
        [1U];
    vlTOPp->top_level__DOT__gen_clusters__BRA__1__KET____DOT__u_cluster__DOT__pe_a[2U] 
        = vlTOPp->top_level__DOT____Vcellinp__gen_clusters__BRA__1__KET____DOT__u_cluster__lane_a
        [2U];
    vlTOPp->top_level__DOT__gen_clusters__BRA__1__KET____DOT__u_cluster__DOT__pe_b[2U] 
        = vlTOPp->top_level__DOT____Vcellinp__gen_clusters__BRA__1__KET____DOT__u_cluster__lane_b
        [2U];
    vlTOPp->top_level__DOT__gen_clusters__BRA__1__KET____DOT__u_cluster__DOT__pe_seed[2U] 
        = vlTOPp->top_level__DOT__gen_clusters__BRA__1__KET____DOT__u_cluster__DOT__accum_bank
        [2U];
    vlTOPp->top_level__DOT__gen_clusters__BRA__1__KET____DOT__u_cluster__DOT__pe_a[3U] 
        = vlTOPp->top_level__DOT____Vcellinp__gen_clusters__BRA__1__KET____DOT__u_cluster__lane_a
        [3U];
    vlTOPp->top_level__DOT__gen_clusters__BRA__1__KET____DOT__u_cluster__DOT__pe_b[3U] 
        = vlTOPp->top_level__DOT____Vcellinp__gen_clusters__BRA__1__KET____DOT__u_cluster__lane_b
        [3U];
    vlTOPp->top_level__DOT__gen_clusters__BRA__1__KET____DOT__u_cluster__DOT__pe_seed[3U] 
        = vlTOPp->top_level__DOT__gen_clusters__BRA__1__KET____DOT__u_cluster__DOT__accum_bank
        [3U];
    vlTOPp->top_level__DOT__gen_clusters__BRA__2__KET____DOT__u_cluster__DOT__pe_a[0U] 
        = vlTOPp->top_level__DOT____Vcellinp__gen_clusters__BRA__2__KET____DOT__u_cluster__lane_a
        [0U];
    vlTOPp->top_level__DOT__gen_clusters__BRA__2__KET____DOT__u_cluster__DOT__pe_b[0U] 
        = vlTOPp->top_level__DOT____Vcellinp__gen_clusters__BRA__2__KET____DOT__u_cluster__lane_b
        [0U];
    vlTOPp->top_level__DOT__gen_clusters__BRA__2__KET____DOT__u_cluster__DOT__pe_seed[0U] 
        = vlTOPp->top_level__DOT__gen_clusters__BRA__2__KET____DOT__u_cluster__DOT__accum_bank
        [0U];
    vlTOPp->top_level__DOT__gen_clusters__BRA__2__KET____DOT__u_cluster__DOT__pe_a[1U] 
        = vlTOPp->top_level__DOT____Vcellinp__gen_clusters__BRA__2__KET____DOT__u_cluster__lane_a
        [1U];
    vlTOPp->top_level__DOT__gen_clusters__BRA__2__KET____DOT__u_cluster__DOT__pe_b[1U] 
        = vlTOPp->top_level__DOT____Vcellinp__gen_clusters__BRA__2__KET____DOT__u_cluster__lane_b
        [1U];
    vlTOPp->top_level__DOT__gen_clusters__BRA__2__KET____DOT__u_cluster__DOT__pe_seed[1U] 
        = vlTOPp->top_level__DOT__gen_clusters__BRA__2__KET____DOT__u_cluster__DOT__accum_bank
        [1U];
    vlTOPp->top_level__DOT__gen_clusters__BRA__2__KET____DOT__u_cluster__DOT__pe_a[2U] 
        = vlTOPp->top_level__DOT____Vcellinp__gen_clusters__BRA__2__KET____DOT__u_cluster__lane_a
        [2U];
    vlTOPp->top_level__DOT__gen_clusters__BRA__2__KET____DOT__u_cluster__DOT__pe_b[2U] 
        = vlTOPp->top_level__DOT____Vcellinp__gen_clusters__BRA__2__KET____DOT__u_cluster__lane_b
        [2U];
    vlTOPp->top_level__DOT__gen_clusters__BRA__2__KET____DOT__u_cluster__DOT__pe_seed[2U] 
        = vlTOPp->top_level__DOT__gen_clusters__BRA__2__KET____DOT__u_cluster__DOT__accum_bank
        [2U];
    vlTOPp->top_level__DOT__gen_clusters__BRA__2__KET____DOT__u_cluster__DOT__pe_a[3U] 
        = vlTOPp->top_level__DOT____Vcellinp__gen_clusters__BRA__2__KET____DOT__u_cluster__lane_a
        [3U];
    vlTOPp->top_level__DOT__gen_clusters__BRA__2__KET____DOT__u_cluster__DOT__pe_b[3U] 
        = vlTOPp->top_level__DOT____Vcellinp__gen_clusters__BRA__2__KET____DOT__u_cluster__lane_b
        [3U];
    vlTOPp->top_level__DOT__gen_clusters__BRA__2__KET____DOT__u_cluster__DOT__pe_seed[3U] 
        = vlTOPp->top_level__DOT__gen_clusters__BRA__2__KET____DOT__u_cluster__DOT__accum_bank
        [3U];
    vlTOPp->top_level__DOT__gen_clusters__BRA__3__KET____DOT__u_cluster__DOT__pe_a[0U] 
        = vlTOPp->top_level__DOT____Vcellinp__gen_clusters__BRA__3__KET____DOT__u_cluster__lane_a
        [0U];
    vlTOPp->top_level__DOT__gen_clusters__BRA__3__KET____DOT__u_cluster__DOT__pe_b[0U] 
        = vlTOPp->top_level__DOT____Vcellinp__gen_clusters__BRA__3__KET____DOT__u_cluster__lane_b
        [0U];
    vlTOPp->top_level__DOT__gen_clusters__BRA__3__KET____DOT__u_cluster__DOT__pe_seed[0U] 
        = vlTOPp->top_level__DOT__gen_clusters__BRA__3__KET____DOT__u_cluster__DOT__accum_bank
        [0U];
    vlTOPp->top_level__DOT__gen_clusters__BRA__3__KET____DOT__u_cluster__DOT__pe_a[1U] 
        = vlTOPp->top_level__DOT____Vcellinp__gen_clusters__BRA__3__KET____DOT__u_cluster__lane_a
        [1U];
    vlTOPp->top_level__DOT__gen_clusters__BRA__3__KET____DOT__u_cluster__DOT__pe_b[1U] 
        = vlTOPp->top_level__DOT____Vcellinp__gen_clusters__BRA__3__KET____DOT__u_cluster__lane_b
        [1U];
    vlTOPp->top_level__DOT__gen_clusters__BRA__3__KET____DOT__u_cluster__DOT__pe_seed[1U] 
        = vlTOPp->top_level__DOT__gen_clusters__BRA__3__KET____DOT__u_cluster__DOT__accum_bank
        [1U];
    vlTOPp->top_level__DOT__gen_clusters__BRA__3__KET____DOT__u_cluster__DOT__pe_a[2U] 
        = vlTOPp->top_level__DOT____Vcellinp__gen_clusters__BRA__3__KET____DOT__u_cluster__lane_a
        [2U];
    vlTOPp->top_level__DOT__gen_clusters__BRA__3__KET____DOT__u_cluster__DOT__pe_b[2U] 
        = vlTOPp->top_level__DOT____Vcellinp__gen_clusters__BRA__3__KET____DOT__u_cluster__lane_b
        [2U];
    vlTOPp->top_level__DOT__gen_clusters__BRA__3__KET____DOT__u_cluster__DOT__pe_seed[2U] 
        = vlTOPp->top_level__DOT__gen_clusters__BRA__3__KET____DOT__u_cluster__DOT__accum_bank
        [2U];
    vlTOPp->top_level__DOT__gen_clusters__BRA__3__KET____DOT__u_cluster__DOT__pe_a[3U] 
        = vlTOPp->top_level__DOT____Vcellinp__gen_clusters__BRA__3__KET____DOT__u_cluster__lane_a
        [3U];
    vlTOPp->top_level__DOT__gen_clusters__BRA__3__KET____DOT__u_cluster__DOT__pe_b[3U] 
        = vlTOPp->top_level__DOT____Vcellinp__gen_clusters__BRA__3__KET____DOT__u_cluster__lane_b
        [3U];
    vlTOPp->top_level__DOT__gen_clusters__BRA__3__KET____DOT__u_cluster__DOT__pe_seed[3U] 
        = vlTOPp->top_level__DOT__gen_clusters__BRA__3__KET____DOT__u_cluster__DOT__accum_bank
        [3U];
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
    vlTOPp->top_level__DOT__gen_clusters__BRA__0__KET____DOT__u_cluster__DOT__gen_main_pes__BRA__2__KET____DOT__u_pe__DOT__product_full 
        = VL_MULS_III(32,32,32, VL_EXTENDS_II(32,16, 
                                              vlTOPp->top_level__DOT__gen_clusters__BRA__0__KET____DOT__u_cluster__DOT__pe_a
                                              [2U]), 
                      VL_EXTENDS_II(32,16, vlTOPp->top_level__DOT__gen_clusters__BRA__0__KET____DOT__u_cluster__DOT__pe_b
                                    [2U]));
    vlTOPp->top_level__DOT__gen_clusters__BRA__0__KET____DOT__u_cluster__DOT__gen_main_pes__BRA__2__KET____DOT__u_pe__DOT__product_scaled 
        = VL_SHIFTRS_III(32,32,32, vlTOPp->top_level__DOT__gen_clusters__BRA__0__KET____DOT__u_cluster__DOT__gen_main_pes__BRA__2__KET____DOT__u_pe__DOT__product_full, 8U);
    vlTOPp->top_level__DOT__gen_clusters__BRA__0__KET____DOT__u_cluster__DOT____Vcellout__gen_main_pes__BRA__2__KET____DOT__u_pe__acc_result 
        = (vlTOPp->top_level__DOT__gen_clusters__BRA__0__KET____DOT__u_cluster__DOT__pe_seed
           [2U] + vlTOPp->top_level__DOT__gen_clusters__BRA__0__KET____DOT__u_cluster__DOT__gen_main_pes__BRA__2__KET____DOT__u_pe__DOT__product_scaled);
    vlTOPp->top_level__DOT__gen_clusters__BRA__0__KET____DOT__u_cluster__DOT__gen_main_pes__BRA__3__KET____DOT__u_pe__DOT__product_full 
        = VL_MULS_III(32,32,32, VL_EXTENDS_II(32,16, 
                                              vlTOPp->top_level__DOT__gen_clusters__BRA__0__KET____DOT__u_cluster__DOT__pe_a
                                              [3U]), 
                      VL_EXTENDS_II(32,16, vlTOPp->top_level__DOT__gen_clusters__BRA__0__KET____DOT__u_cluster__DOT__pe_b
                                    [3U]));
    vlTOPp->top_level__DOT__gen_clusters__BRA__0__KET____DOT__u_cluster__DOT__gen_main_pes__BRA__3__KET____DOT__u_pe__DOT__product_scaled 
        = VL_SHIFTRS_III(32,32,32, vlTOPp->top_level__DOT__gen_clusters__BRA__0__KET____DOT__u_cluster__DOT__gen_main_pes__BRA__3__KET____DOT__u_pe__DOT__product_full, 8U);
    vlTOPp->top_level__DOT__gen_clusters__BRA__0__KET____DOT__u_cluster__DOT____Vcellout__gen_main_pes__BRA__3__KET____DOT__u_pe__acc_result 
        = (vlTOPp->top_level__DOT__gen_clusters__BRA__0__KET____DOT__u_cluster__DOT__pe_seed
           [3U] + vlTOPp->top_level__DOT__gen_clusters__BRA__0__KET____DOT__u_cluster__DOT__gen_main_pes__BRA__3__KET____DOT__u_pe__DOT__product_scaled);
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
    vlTOPp->top_level__DOT__gen_clusters__BRA__1__KET____DOT__u_cluster__DOT__gen_main_pes__BRA__2__KET____DOT__u_pe__DOT__product_full 
        = VL_MULS_III(32,32,32, VL_EXTENDS_II(32,16, 
                                              vlTOPp->top_level__DOT__gen_clusters__BRA__1__KET____DOT__u_cluster__DOT__pe_a
                                              [2U]), 
                      VL_EXTENDS_II(32,16, vlTOPp->top_level__DOT__gen_clusters__BRA__1__KET____DOT__u_cluster__DOT__pe_b
                                    [2U]));
    vlTOPp->top_level__DOT__gen_clusters__BRA__1__KET____DOT__u_cluster__DOT__gen_main_pes__BRA__2__KET____DOT__u_pe__DOT__product_scaled 
        = VL_SHIFTRS_III(32,32,32, vlTOPp->top_level__DOT__gen_clusters__BRA__1__KET____DOT__u_cluster__DOT__gen_main_pes__BRA__2__KET____DOT__u_pe__DOT__product_full, 8U);
    vlTOPp->top_level__DOT__gen_clusters__BRA__1__KET____DOT__u_cluster__DOT____Vcellout__gen_main_pes__BRA__2__KET____DOT__u_pe__acc_result 
        = (vlTOPp->top_level__DOT__gen_clusters__BRA__1__KET____DOT__u_cluster__DOT__pe_seed
           [2U] + vlTOPp->top_level__DOT__gen_clusters__BRA__1__KET____DOT__u_cluster__DOT__gen_main_pes__BRA__2__KET____DOT__u_pe__DOT__product_scaled);
    vlTOPp->top_level__DOT__gen_clusters__BRA__1__KET____DOT__u_cluster__DOT__gen_main_pes__BRA__3__KET____DOT__u_pe__DOT__product_full 
        = VL_MULS_III(32,32,32, VL_EXTENDS_II(32,16, 
                                              vlTOPp->top_level__DOT__gen_clusters__BRA__1__KET____DOT__u_cluster__DOT__pe_a
                                              [3U]), 
                      VL_EXTENDS_II(32,16, vlTOPp->top_level__DOT__gen_clusters__BRA__1__KET____DOT__u_cluster__DOT__pe_b
                                    [3U]));
    vlTOPp->top_level__DOT__gen_clusters__BRA__1__KET____DOT__u_cluster__DOT__gen_main_pes__BRA__3__KET____DOT__u_pe__DOT__product_scaled 
        = VL_SHIFTRS_III(32,32,32, vlTOPp->top_level__DOT__gen_clusters__BRA__1__KET____DOT__u_cluster__DOT__gen_main_pes__BRA__3__KET____DOT__u_pe__DOT__product_full, 8U);
    vlTOPp->top_level__DOT__gen_clusters__BRA__1__KET____DOT__u_cluster__DOT____Vcellout__gen_main_pes__BRA__3__KET____DOT__u_pe__acc_result 
        = (vlTOPp->top_level__DOT__gen_clusters__BRA__1__KET____DOT__u_cluster__DOT__pe_seed
           [3U] + vlTOPp->top_level__DOT__gen_clusters__BRA__1__KET____DOT__u_cluster__DOT__gen_main_pes__BRA__3__KET____DOT__u_pe__DOT__product_scaled);
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
    vlTOPp->top_level__DOT__gen_clusters__BRA__2__KET____DOT__u_cluster__DOT__gen_main_pes__BRA__2__KET____DOT__u_pe__DOT__product_full 
        = VL_MULS_III(32,32,32, VL_EXTENDS_II(32,16, 
                                              vlTOPp->top_level__DOT__gen_clusters__BRA__2__KET____DOT__u_cluster__DOT__pe_a
                                              [2U]), 
                      VL_EXTENDS_II(32,16, vlTOPp->top_level__DOT__gen_clusters__BRA__2__KET____DOT__u_cluster__DOT__pe_b
                                    [2U]));
    vlTOPp->top_level__DOT__gen_clusters__BRA__2__KET____DOT__u_cluster__DOT__gen_main_pes__BRA__2__KET____DOT__u_pe__DOT__product_scaled 
        = VL_SHIFTRS_III(32,32,32, vlTOPp->top_level__DOT__gen_clusters__BRA__2__KET____DOT__u_cluster__DOT__gen_main_pes__BRA__2__KET____DOT__u_pe__DOT__product_full, 8U);
    vlTOPp->top_level__DOT__gen_clusters__BRA__2__KET____DOT__u_cluster__DOT____Vcellout__gen_main_pes__BRA__2__KET____DOT__u_pe__acc_result 
        = (vlTOPp->top_level__DOT__gen_clusters__BRA__2__KET____DOT__u_cluster__DOT__pe_seed
           [2U] + vlTOPp->top_level__DOT__gen_clusters__BRA__2__KET____DOT__u_cluster__DOT__gen_main_pes__BRA__2__KET____DOT__u_pe__DOT__product_scaled);
    vlTOPp->top_level__DOT__gen_clusters__BRA__2__KET____DOT__u_cluster__DOT__gen_main_pes__BRA__3__KET____DOT__u_pe__DOT__product_full 
        = VL_MULS_III(32,32,32, VL_EXTENDS_II(32,16, 
                                              vlTOPp->top_level__DOT__gen_clusters__BRA__2__KET____DOT__u_cluster__DOT__pe_a
                                              [3U]), 
                      VL_EXTENDS_II(32,16, vlTOPp->top_level__DOT__gen_clusters__BRA__2__KET____DOT__u_cluster__DOT__pe_b
                                    [3U]));
    vlTOPp->top_level__DOT__gen_clusters__BRA__2__KET____DOT__u_cluster__DOT__gen_main_pes__BRA__3__KET____DOT__u_pe__DOT__product_scaled 
        = VL_SHIFTRS_III(32,32,32, vlTOPp->top_level__DOT__gen_clusters__BRA__2__KET____DOT__u_cluster__DOT__gen_main_pes__BRA__3__KET____DOT__u_pe__DOT__product_full, 8U);
    vlTOPp->top_level__DOT__gen_clusters__BRA__2__KET____DOT__u_cluster__DOT____Vcellout__gen_main_pes__BRA__3__KET____DOT__u_pe__acc_result 
        = (vlTOPp->top_level__DOT__gen_clusters__BRA__2__KET____DOT__u_cluster__DOT__pe_seed
           [3U] + vlTOPp->top_level__DOT__gen_clusters__BRA__2__KET____DOT__u_cluster__DOT__gen_main_pes__BRA__3__KET____DOT__u_pe__DOT__product_scaled);
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
    vlTOPp->top_level__DOT__gen_clusters__BRA__3__KET____DOT__u_cluster__DOT__gen_main_pes__BRA__2__KET____DOT__u_pe__DOT__product_full 
        = VL_MULS_III(32,32,32, VL_EXTENDS_II(32,16, 
                                              vlTOPp->top_level__DOT__gen_clusters__BRA__3__KET____DOT__u_cluster__DOT__pe_a
                                              [2U]), 
                      VL_EXTENDS_II(32,16, vlTOPp->top_level__DOT__gen_clusters__BRA__3__KET____DOT__u_cluster__DOT__pe_b
                                    [2U]));
    vlTOPp->top_level__DOT__gen_clusters__BRA__3__KET____DOT__u_cluster__DOT__gen_main_pes__BRA__2__KET____DOT__u_pe__DOT__product_scaled 
        = VL_SHIFTRS_III(32,32,32, vlTOPp->top_level__DOT__gen_clusters__BRA__3__KET____DOT__u_cluster__DOT__gen_main_pes__BRA__2__KET____DOT__u_pe__DOT__product_full, 8U);
    vlTOPp->top_level__DOT__gen_clusters__BRA__3__KET____DOT__u_cluster__DOT____Vcellout__gen_main_pes__BRA__2__KET____DOT__u_pe__acc_result 
        = (vlTOPp->top_level__DOT__gen_clusters__BRA__3__KET____DOT__u_cluster__DOT__pe_seed
           [2U] + vlTOPp->top_level__DOT__gen_clusters__BRA__3__KET____DOT__u_cluster__DOT__gen_main_pes__BRA__2__KET____DOT__u_pe__DOT__product_scaled);
    vlTOPp->top_level__DOT__gen_clusters__BRA__3__KET____DOT__u_cluster__DOT__gen_main_pes__BRA__3__KET____DOT__u_pe__DOT__product_full 
        = VL_MULS_III(32,32,32, VL_EXTENDS_II(32,16, 
                                              vlTOPp->top_level__DOT__gen_clusters__BRA__3__KET____DOT__u_cluster__DOT__pe_a
                                              [3U]), 
                      VL_EXTENDS_II(32,16, vlTOPp->top_level__DOT__gen_clusters__BRA__3__KET____DOT__u_cluster__DOT__pe_b
                                    [3U]));
    vlTOPp->top_level__DOT__gen_clusters__BRA__3__KET____DOT__u_cluster__DOT__gen_main_pes__BRA__3__KET____DOT__u_pe__DOT__product_scaled 
        = VL_SHIFTRS_III(32,32,32, vlTOPp->top_level__DOT__gen_clusters__BRA__3__KET____DOT__u_cluster__DOT__gen_main_pes__BRA__3__KET____DOT__u_pe__DOT__product_full, 8U);
    vlTOPp->top_level__DOT__gen_clusters__BRA__3__KET____DOT__u_cluster__DOT____Vcellout__gen_main_pes__BRA__3__KET____DOT__u_pe__acc_result 
        = (vlTOPp->top_level__DOT__gen_clusters__BRA__3__KET____DOT__u_cluster__DOT__pe_seed
           [3U] + vlTOPp->top_level__DOT__gen_clusters__BRA__3__KET____DOT__u_cluster__DOT__gen_main_pes__BRA__3__KET____DOT__u_pe__DOT__product_scaled);
    vlTOPp->top_level__DOT__gen_clusters__BRA__0__KET____DOT__u_cluster__DOT__pe_result[0U] 
        = vlTOPp->top_level__DOT__gen_clusters__BRA__0__KET____DOT__u_cluster__DOT____Vcellout__gen_main_pes__BRA__0__KET____DOT__u_pe__acc_result;
    vlTOPp->top_level__DOT__gen_clusters__BRA__0__KET____DOT__u_cluster__DOT__pe_result[1U] 
        = vlTOPp->top_level__DOT__gen_clusters__BRA__0__KET____DOT__u_cluster__DOT____Vcellout__gen_main_pes__BRA__1__KET____DOT__u_pe__acc_result;
    vlTOPp->top_level__DOT__gen_clusters__BRA__0__KET____DOT__u_cluster__DOT__pe_result[2U] 
        = vlTOPp->top_level__DOT__gen_clusters__BRA__0__KET____DOT__u_cluster__DOT____Vcellout__gen_main_pes__BRA__2__KET____DOT__u_pe__acc_result;
    vlTOPp->top_level__DOT__gen_clusters__BRA__0__KET____DOT__u_cluster__DOT__pe_result[3U] 
        = vlTOPp->top_level__DOT__gen_clusters__BRA__0__KET____DOT__u_cluster__DOT____Vcellout__gen_main_pes__BRA__3__KET____DOT__u_pe__acc_result;
    vlTOPp->top_level__DOT__gen_clusters__BRA__1__KET____DOT__u_cluster__DOT__pe_result[0U] 
        = vlTOPp->top_level__DOT__gen_clusters__BRA__1__KET____DOT__u_cluster__DOT____Vcellout__gen_main_pes__BRA__0__KET____DOT__u_pe__acc_result;
    vlTOPp->top_level__DOT__gen_clusters__BRA__1__KET____DOT__u_cluster__DOT__pe_result[1U] 
        = vlTOPp->top_level__DOT__gen_clusters__BRA__1__KET____DOT__u_cluster__DOT____Vcellout__gen_main_pes__BRA__1__KET____DOT__u_pe__acc_result;
    vlTOPp->top_level__DOT__gen_clusters__BRA__1__KET____DOT__u_cluster__DOT__pe_result[2U] 
        = vlTOPp->top_level__DOT__gen_clusters__BRA__1__KET____DOT__u_cluster__DOT____Vcellout__gen_main_pes__BRA__2__KET____DOT__u_pe__acc_result;
    vlTOPp->top_level__DOT__gen_clusters__BRA__1__KET____DOT__u_cluster__DOT__pe_result[3U] 
        = vlTOPp->top_level__DOT__gen_clusters__BRA__1__KET____DOT__u_cluster__DOT____Vcellout__gen_main_pes__BRA__3__KET____DOT__u_pe__acc_result;
    vlTOPp->top_level__DOT__gen_clusters__BRA__2__KET____DOT__u_cluster__DOT__pe_result[0U] 
        = vlTOPp->top_level__DOT__gen_clusters__BRA__2__KET____DOT__u_cluster__DOT____Vcellout__gen_main_pes__BRA__0__KET____DOT__u_pe__acc_result;
    vlTOPp->top_level__DOT__gen_clusters__BRA__2__KET____DOT__u_cluster__DOT__pe_result[1U] 
        = vlTOPp->top_level__DOT__gen_clusters__BRA__2__KET____DOT__u_cluster__DOT____Vcellout__gen_main_pes__BRA__1__KET____DOT__u_pe__acc_result;
    vlTOPp->top_level__DOT__gen_clusters__BRA__2__KET____DOT__u_cluster__DOT__pe_result[2U] 
        = vlTOPp->top_level__DOT__gen_clusters__BRA__2__KET____DOT__u_cluster__DOT____Vcellout__gen_main_pes__BRA__2__KET____DOT__u_pe__acc_result;
    vlTOPp->top_level__DOT__gen_clusters__BRA__2__KET____DOT__u_cluster__DOT__pe_result[3U] 
        = vlTOPp->top_level__DOT__gen_clusters__BRA__2__KET____DOT__u_cluster__DOT____Vcellout__gen_main_pes__BRA__3__KET____DOT__u_pe__acc_result;
    vlTOPp->top_level__DOT__gen_clusters__BRA__3__KET____DOT__u_cluster__DOT__pe_result[0U] 
        = vlTOPp->top_level__DOT__gen_clusters__BRA__3__KET____DOT__u_cluster__DOT____Vcellout__gen_main_pes__BRA__0__KET____DOT__u_pe__acc_result;
    vlTOPp->top_level__DOT__gen_clusters__BRA__3__KET____DOT__u_cluster__DOT__pe_result[1U] 
        = vlTOPp->top_level__DOT__gen_clusters__BRA__3__KET____DOT__u_cluster__DOT____Vcellout__gen_main_pes__BRA__1__KET____DOT__u_pe__acc_result;
    vlTOPp->top_level__DOT__gen_clusters__BRA__3__KET____DOT__u_cluster__DOT__pe_result[2U] 
        = vlTOPp->top_level__DOT__gen_clusters__BRA__3__KET____DOT__u_cluster__DOT____Vcellout__gen_main_pes__BRA__2__KET____DOT__u_pe__acc_result;
    vlTOPp->top_level__DOT__gen_clusters__BRA__3__KET____DOT__u_cluster__DOT__pe_result[3U] 
        = vlTOPp->top_level__DOT__gen_clusters__BRA__3__KET____DOT__u_cluster__DOT____Vcellout__gen_main_pes__BRA__3__KET____DOT__u_pe__acc_result;
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
    vlTOPp->top_level__DOT__gen_clusters__BRA__0__KET____DOT__u_cluster__DOT__logical_lane = 0U;
    if (vlTOPp->top_level__DOT__gen_clusters__BRA__0__KET____DOT__u_cluster__DOT__pe_done
        [0U]) {
        vlTOPp->top_level__DOT__gen_clusters__BRA__0__KET____DOT__u_cluster__DOT__accum_next[(3U 
                                                                                & vlTOPp->top_level__DOT__gen_clusters__BRA__0__KET____DOT__u_cluster__DOT__logical_lane)] 
            = vlTOPp->top_level__DOT__gen_clusters__BRA__0__KET____DOT__u_cluster__DOT__pe_result
            [0U];
    }
    vlTOPp->top_level__DOT__gen_clusters__BRA__0__KET____DOT__u_cluster__DOT__logical_lane = 1U;
    if (vlTOPp->top_level__DOT__gen_clusters__BRA__0__KET____DOT__u_cluster__DOT__pe_done
        [1U]) {
        vlTOPp->top_level__DOT__gen_clusters__BRA__0__KET____DOT__u_cluster__DOT__accum_next[(3U 
                                                                                & vlTOPp->top_level__DOT__gen_clusters__BRA__0__KET____DOT__u_cluster__DOT__logical_lane)] 
            = vlTOPp->top_level__DOT__gen_clusters__BRA__0__KET____DOT__u_cluster__DOT__pe_result
            [1U];
    }
    vlTOPp->top_level__DOT__gen_clusters__BRA__0__KET____DOT__u_cluster__DOT__logical_lane = 2U;
    if (vlTOPp->top_level__DOT__gen_clusters__BRA__0__KET____DOT__u_cluster__DOT__pe_done
        [2U]) {
        vlTOPp->top_level__DOT__gen_clusters__BRA__0__KET____DOT__u_cluster__DOT__accum_next[(3U 
                                                                                & vlTOPp->top_level__DOT__gen_clusters__BRA__0__KET____DOT__u_cluster__DOT__logical_lane)] 
            = vlTOPp->top_level__DOT__gen_clusters__BRA__0__KET____DOT__u_cluster__DOT__pe_result
            [2U];
    }
    vlTOPp->top_level__DOT__gen_clusters__BRA__0__KET____DOT__u_cluster__DOT__logical_lane = 3U;
    if (vlTOPp->top_level__DOT__gen_clusters__BRA__0__KET____DOT__u_cluster__DOT__pe_done
        [3U]) {
        vlTOPp->top_level__DOT__gen_clusters__BRA__0__KET____DOT__u_cluster__DOT__accum_next[(3U 
                                                                                & vlTOPp->top_level__DOT__gen_clusters__BRA__0__KET____DOT__u_cluster__DOT__logical_lane)] 
            = vlTOPp->top_level__DOT__gen_clusters__BRA__0__KET____DOT__u_cluster__DOT__pe_result
            [3U];
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
    vlTOPp->top_level__DOT__gen_clusters__BRA__1__KET____DOT__u_cluster__DOT__logical_lane = 0U;
    if (vlTOPp->top_level__DOT__gen_clusters__BRA__1__KET____DOT__u_cluster__DOT__pe_done
        [0U]) {
        vlTOPp->top_level__DOT__gen_clusters__BRA__1__KET____DOT__u_cluster__DOT__accum_next[(3U 
                                                                                & vlTOPp->top_level__DOT__gen_clusters__BRA__1__KET____DOT__u_cluster__DOT__logical_lane)] 
            = vlTOPp->top_level__DOT__gen_clusters__BRA__1__KET____DOT__u_cluster__DOT__pe_result
            [0U];
    }
    vlTOPp->top_level__DOT__gen_clusters__BRA__1__KET____DOT__u_cluster__DOT__logical_lane = 1U;
    if (vlTOPp->top_level__DOT__gen_clusters__BRA__1__KET____DOT__u_cluster__DOT__pe_done
        [1U]) {
        vlTOPp->top_level__DOT__gen_clusters__BRA__1__KET____DOT__u_cluster__DOT__accum_next[(3U 
                                                                                & vlTOPp->top_level__DOT__gen_clusters__BRA__1__KET____DOT__u_cluster__DOT__logical_lane)] 
            = vlTOPp->top_level__DOT__gen_clusters__BRA__1__KET____DOT__u_cluster__DOT__pe_result
            [1U];
    }
    vlTOPp->top_level__DOT__gen_clusters__BRA__1__KET____DOT__u_cluster__DOT__logical_lane = 2U;
    if (vlTOPp->top_level__DOT__gen_clusters__BRA__1__KET____DOT__u_cluster__DOT__pe_done
        [2U]) {
        vlTOPp->top_level__DOT__gen_clusters__BRA__1__KET____DOT__u_cluster__DOT__accum_next[(3U 
                                                                                & vlTOPp->top_level__DOT__gen_clusters__BRA__1__KET____DOT__u_cluster__DOT__logical_lane)] 
            = vlTOPp->top_level__DOT__gen_clusters__BRA__1__KET____DOT__u_cluster__DOT__pe_result
            [2U];
    }
    vlTOPp->top_level__DOT__gen_clusters__BRA__1__KET____DOT__u_cluster__DOT__logical_lane = 3U;
    if (vlTOPp->top_level__DOT__gen_clusters__BRA__1__KET____DOT__u_cluster__DOT__pe_done
        [3U]) {
        vlTOPp->top_level__DOT__gen_clusters__BRA__1__KET____DOT__u_cluster__DOT__accum_next[(3U 
                                                                                & vlTOPp->top_level__DOT__gen_clusters__BRA__1__KET____DOT__u_cluster__DOT__logical_lane)] 
            = vlTOPp->top_level__DOT__gen_clusters__BRA__1__KET____DOT__u_cluster__DOT__pe_result
            [3U];
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
    vlTOPp->top_level__DOT__gen_clusters__BRA__2__KET____DOT__u_cluster__DOT__logical_lane = 0U;
    if (vlTOPp->top_level__DOT__gen_clusters__BRA__2__KET____DOT__u_cluster__DOT__pe_done
        [0U]) {
        vlTOPp->top_level__DOT__gen_clusters__BRA__2__KET____DOT__u_cluster__DOT__accum_next[(3U 
                                                                                & vlTOPp->top_level__DOT__gen_clusters__BRA__2__KET____DOT__u_cluster__DOT__logical_lane)] 
            = vlTOPp->top_level__DOT__gen_clusters__BRA__2__KET____DOT__u_cluster__DOT__pe_result
            [0U];
    }
    vlTOPp->top_level__DOT__gen_clusters__BRA__2__KET____DOT__u_cluster__DOT__logical_lane = 1U;
    if (vlTOPp->top_level__DOT__gen_clusters__BRA__2__KET____DOT__u_cluster__DOT__pe_done
        [1U]) {
        vlTOPp->top_level__DOT__gen_clusters__BRA__2__KET____DOT__u_cluster__DOT__accum_next[(3U 
                                                                                & vlTOPp->top_level__DOT__gen_clusters__BRA__2__KET____DOT__u_cluster__DOT__logical_lane)] 
            = vlTOPp->top_level__DOT__gen_clusters__BRA__2__KET____DOT__u_cluster__DOT__pe_result
            [1U];
    }
    vlTOPp->top_level__DOT__gen_clusters__BRA__2__KET____DOT__u_cluster__DOT__logical_lane = 2U;
    if (vlTOPp->top_level__DOT__gen_clusters__BRA__2__KET____DOT__u_cluster__DOT__pe_done
        [2U]) {
        vlTOPp->top_level__DOT__gen_clusters__BRA__2__KET____DOT__u_cluster__DOT__accum_next[(3U 
                                                                                & vlTOPp->top_level__DOT__gen_clusters__BRA__2__KET____DOT__u_cluster__DOT__logical_lane)] 
            = vlTOPp->top_level__DOT__gen_clusters__BRA__2__KET____DOT__u_cluster__DOT__pe_result
            [2U];
    }
    vlTOPp->top_level__DOT__gen_clusters__BRA__2__KET____DOT__u_cluster__DOT__logical_lane = 3U;
    if (vlTOPp->top_level__DOT__gen_clusters__BRA__2__KET____DOT__u_cluster__DOT__pe_done
        [3U]) {
        vlTOPp->top_level__DOT__gen_clusters__BRA__2__KET____DOT__u_cluster__DOT__accum_next[(3U 
                                                                                & vlTOPp->top_level__DOT__gen_clusters__BRA__2__KET____DOT__u_cluster__DOT__logical_lane)] 
            = vlTOPp->top_level__DOT__gen_clusters__BRA__2__KET____DOT__u_cluster__DOT__pe_result
            [3U];
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
    vlTOPp->top_level__DOT__gen_clusters__BRA__3__KET____DOT__u_cluster__DOT__logical_lane = 0U;
    if (vlTOPp->top_level__DOT__gen_clusters__BRA__3__KET____DOT__u_cluster__DOT__pe_done
        [0U]) {
        vlTOPp->top_level__DOT__gen_clusters__BRA__3__KET____DOT__u_cluster__DOT__accum_next[(3U 
                                                                                & vlTOPp->top_level__DOT__gen_clusters__BRA__3__KET____DOT__u_cluster__DOT__logical_lane)] 
            = vlTOPp->top_level__DOT__gen_clusters__BRA__3__KET____DOT__u_cluster__DOT__pe_result
            [0U];
    }
    vlTOPp->top_level__DOT__gen_clusters__BRA__3__KET____DOT__u_cluster__DOT__logical_lane = 1U;
    if (vlTOPp->top_level__DOT__gen_clusters__BRA__3__KET____DOT__u_cluster__DOT__pe_done
        [1U]) {
        vlTOPp->top_level__DOT__gen_clusters__BRA__3__KET____DOT__u_cluster__DOT__accum_next[(3U 
                                                                                & vlTOPp->top_level__DOT__gen_clusters__BRA__3__KET____DOT__u_cluster__DOT__logical_lane)] 
            = vlTOPp->top_level__DOT__gen_clusters__BRA__3__KET____DOT__u_cluster__DOT__pe_result
            [1U];
    }
    vlTOPp->top_level__DOT__gen_clusters__BRA__3__KET____DOT__u_cluster__DOT__logical_lane = 2U;
    if (vlTOPp->top_level__DOT__gen_clusters__BRA__3__KET____DOT__u_cluster__DOT__pe_done
        [2U]) {
        vlTOPp->top_level__DOT__gen_clusters__BRA__3__KET____DOT__u_cluster__DOT__accum_next[(3U 
                                                                                & vlTOPp->top_level__DOT__gen_clusters__BRA__3__KET____DOT__u_cluster__DOT__logical_lane)] 
            = vlTOPp->top_level__DOT__gen_clusters__BRA__3__KET____DOT__u_cluster__DOT__pe_result
            [2U];
    }
    vlTOPp->top_level__DOT__gen_clusters__BRA__3__KET____DOT__u_cluster__DOT__logical_lane = 3U;
    if (vlTOPp->top_level__DOT__gen_clusters__BRA__3__KET____DOT__u_cluster__DOT__pe_done
        [3U]) {
        vlTOPp->top_level__DOT__gen_clusters__BRA__3__KET____DOT__u_cluster__DOT__accum_next[(3U 
                                                                                & vlTOPp->top_level__DOT__gen_clusters__BRA__3__KET____DOT__u_cluster__DOT__logical_lane)] 
            = vlTOPp->top_level__DOT__gen_clusters__BRA__3__KET____DOT__u_cluster__DOT__pe_result
            [3U];
    }
}

void Vtop_level::_eval_initial(Vtop_level__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop_level::_eval_initial\n"); );
    Vtop_level* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->_initial__TOP__2(vlSymsp);
    vlTOPp->__Vclklast__TOP__clk = vlTOPp->clk;
}

void Vtop_level::final() {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop_level::final\n"); );
    // Variables
    Vtop_level__Syms* __restrict vlSymsp = this->__VlSymsp;
    Vtop_level* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
}

void Vtop_level::_eval_settle(Vtop_level__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop_level::_eval_settle\n"); );
    Vtop_level* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->_settle__TOP__1(vlSymsp);
    vlTOPp->_settle__TOP__4(vlSymsp);
}

void Vtop_level::_ctor_var_reset() {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop_level::_ctor_var_reset\n"); );
    // Body
    clk = VL_RAND_RESET_I(1);
    rst = VL_RAND_RESET_I(1);
    start = VL_RAND_RESET_I(1);
    done = VL_RAND_RESET_I(1);
    busy = VL_RAND_RESET_I(1);
    debug_cycle_count = VL_RAND_RESET_I(32);
    top_level__DOT__clear_acc = VL_RAND_RESET_I(1);
    top_level__DOT__compute_en = VL_RAND_RESET_I(1);
    top_level__DOT__write_en = VL_RAND_RESET_I(1);
    top_level__DOT__current_k = VL_RAND_RESET_I(2);
    top_level__DOT__cycle_count = VL_RAND_RESET_I(32);
    { int __Vi0=0; for (; __Vi0<4; ++__Vi0) {
            top_level__DOT__a_read_addr[__Vi0] = VL_RAND_RESET_I(6);
    }}
    { int __Vi0=0; for (; __Vi0<4; ++__Vi0) {
            top_level__DOT__b_read_addr[__Vi0] = VL_RAND_RESET_I(6);
    }}
    { int __Vi0=0; for (; __Vi0<4; ++__Vi0) {
            top_level__DOT__a_row_data[__Vi0] = VL_RAND_RESET_I(16);
    }}
    { int __Vi0=0; for (; __Vi0<4; ++__Vi0) {
            top_level__DOT__b_col_data[__Vi0] = VL_RAND_RESET_I(16);
    }}
    { int __Vi0=0; for (; __Vi0<16; ++__Vi0) {
            top_level__DOT__lane_a[__Vi0] = VL_RAND_RESET_I(16);
    }}
    { int __Vi0=0; for (; __Vi0<16; ++__Vi0) {
            top_level__DOT__lane_b[__Vi0] = VL_RAND_RESET_I(16);
    }}
    { int __Vi0=0; for (; __Vi0<4; ++__Vi0) {
            { int __Vi1=0; for (; __Vi1<4; ++__Vi1) {
                    top_level__DOT__cluster_accum[__Vi0][__Vi1] = VL_RAND_RESET_I(32);
            }}
    }}
    { int __Vi0=0; for (; __Vi0<64; ++__Vi0) {
            top_level__DOT__output_mem[__Vi0] = VL_RAND_RESET_I(32);
    }}
    { int __Vi0=0; for (; __Vi0<4; ++__Vi0) {
            top_level__DOT____Vcellout__u_a_buffer__read_data[__Vi0] = VL_RAND_RESET_I(16);
    }}
    { int __Vi0=0; for (; __Vi0<4; ++__Vi0) {
            top_level__DOT____Vcellinp__u_a_buffer__read_addr[__Vi0] = VL_RAND_RESET_I(6);
    }}
    { int __Vi0=0; for (; __Vi0<4; ++__Vi0) {
            top_level__DOT____Vcellout__u_b_buffer__read_data[__Vi0] = VL_RAND_RESET_I(16);
    }}
    { int __Vi0=0; for (; __Vi0<4; ++__Vi0) {
            top_level__DOT____Vcellinp__u_b_buffer__read_addr[__Vi0] = VL_RAND_RESET_I(6);
    }}
    { int __Vi0=0; for (; __Vi0<16; ++__Vi0) {
            top_level__DOT____Vcellout__u_interconnect__lane_b[__Vi0] = VL_RAND_RESET_I(16);
    }}
    { int __Vi0=0; for (; __Vi0<16; ++__Vi0) {
            top_level__DOT____Vcellout__u_interconnect__lane_a[__Vi0] = VL_RAND_RESET_I(16);
    }}
    { int __Vi0=0; for (; __Vi0<4; ++__Vi0) {
            top_level__DOT____Vcellinp__u_interconnect__b_col_data[__Vi0] = VL_RAND_RESET_I(16);
    }}
    { int __Vi0=0; for (; __Vi0<4; ++__Vi0) {
            top_level__DOT____Vcellinp__u_interconnect__a_row_data[__Vi0] = VL_RAND_RESET_I(16);
    }}
    { int __Vi0=0; for (; __Vi0<4; ++__Vi0) {
            top_level__DOT____Vcellout__u_interconnect__b_read_addr[__Vi0] = VL_RAND_RESET_I(6);
    }}
    { int __Vi0=0; for (; __Vi0<4; ++__Vi0) {
            top_level__DOT____Vcellout__u_interconnect__a_read_addr[__Vi0] = VL_RAND_RESET_I(6);
    }}
    { int __Vi0=0; for (; __Vi0<4; ++__Vi0) {
            top_level__DOT__gen_clusters__BRA__0__KET____DOT__cluster_lane_a[__Vi0] = VL_RAND_RESET_I(16);
    }}
    { int __Vi0=0; for (; __Vi0<4; ++__Vi0) {
            top_level__DOT__gen_clusters__BRA__0__KET____DOT__cluster_lane_b[__Vi0] = VL_RAND_RESET_I(16);
    }}
    { int __Vi0=0; for (; __Vi0<4; ++__Vi0) {
            top_level__DOT____Vcellout__gen_clusters__BRA__0__KET____DOT__u_cluster__accum_out[__Vi0] = VL_RAND_RESET_I(32);
    }}
    { int __Vi0=0; for (; __Vi0<4; ++__Vi0) {
            top_level__DOT____Vcellinp__gen_clusters__BRA__0__KET____DOT__u_cluster__lane_b[__Vi0] = VL_RAND_RESET_I(16);
    }}
    { int __Vi0=0; for (; __Vi0<4; ++__Vi0) {
            top_level__DOT____Vcellinp__gen_clusters__BRA__0__KET____DOT__u_cluster__lane_a[__Vi0] = VL_RAND_RESET_I(16);
    }}
    { int __Vi0=0; for (; __Vi0<4; ++__Vi0) {
            top_level__DOT__gen_clusters__BRA__1__KET____DOT__cluster_lane_a[__Vi0] = VL_RAND_RESET_I(16);
    }}
    { int __Vi0=0; for (; __Vi0<4; ++__Vi0) {
            top_level__DOT__gen_clusters__BRA__1__KET____DOT__cluster_lane_b[__Vi0] = VL_RAND_RESET_I(16);
    }}
    { int __Vi0=0; for (; __Vi0<4; ++__Vi0) {
            top_level__DOT____Vcellout__gen_clusters__BRA__1__KET____DOT__u_cluster__accum_out[__Vi0] = VL_RAND_RESET_I(32);
    }}
    { int __Vi0=0; for (; __Vi0<4; ++__Vi0) {
            top_level__DOT____Vcellinp__gen_clusters__BRA__1__KET____DOT__u_cluster__lane_b[__Vi0] = VL_RAND_RESET_I(16);
    }}
    { int __Vi0=0; for (; __Vi0<4; ++__Vi0) {
            top_level__DOT____Vcellinp__gen_clusters__BRA__1__KET____DOT__u_cluster__lane_a[__Vi0] = VL_RAND_RESET_I(16);
    }}
    { int __Vi0=0; for (; __Vi0<4; ++__Vi0) {
            top_level__DOT__gen_clusters__BRA__2__KET____DOT__cluster_lane_a[__Vi0] = VL_RAND_RESET_I(16);
    }}
    { int __Vi0=0; for (; __Vi0<4; ++__Vi0) {
            top_level__DOT__gen_clusters__BRA__2__KET____DOT__cluster_lane_b[__Vi0] = VL_RAND_RESET_I(16);
    }}
    { int __Vi0=0; for (; __Vi0<4; ++__Vi0) {
            top_level__DOT____Vcellout__gen_clusters__BRA__2__KET____DOT__u_cluster__accum_out[__Vi0] = VL_RAND_RESET_I(32);
    }}
    { int __Vi0=0; for (; __Vi0<4; ++__Vi0) {
            top_level__DOT____Vcellinp__gen_clusters__BRA__2__KET____DOT__u_cluster__lane_b[__Vi0] = VL_RAND_RESET_I(16);
    }}
    { int __Vi0=0; for (; __Vi0<4; ++__Vi0) {
            top_level__DOT____Vcellinp__gen_clusters__BRA__2__KET____DOT__u_cluster__lane_a[__Vi0] = VL_RAND_RESET_I(16);
    }}
    { int __Vi0=0; for (; __Vi0<4; ++__Vi0) {
            top_level__DOT__gen_clusters__BRA__3__KET____DOT__cluster_lane_a[__Vi0] = VL_RAND_RESET_I(16);
    }}
    { int __Vi0=0; for (; __Vi0<4; ++__Vi0) {
            top_level__DOT__gen_clusters__BRA__3__KET____DOT__cluster_lane_b[__Vi0] = VL_RAND_RESET_I(16);
    }}
    { int __Vi0=0; for (; __Vi0<4; ++__Vi0) {
            top_level__DOT____Vcellout__gen_clusters__BRA__3__KET____DOT__u_cluster__accum_out[__Vi0] = VL_RAND_RESET_I(32);
    }}
    { int __Vi0=0; for (; __Vi0<4; ++__Vi0) {
            top_level__DOT____Vcellinp__gen_clusters__BRA__3__KET____DOT__u_cluster__lane_b[__Vi0] = VL_RAND_RESET_I(16);
    }}
    { int __Vi0=0; for (; __Vi0<4; ++__Vi0) {
            top_level__DOT____Vcellinp__gen_clusters__BRA__3__KET____DOT__u_cluster__lane_a[__Vi0] = VL_RAND_RESET_I(16);
    }}
    top_level__DOT__u_control__DOT__state_q = VL_RAND_RESET_I(3);
    top_level__DOT__u_control__DOT__state_d = VL_RAND_RESET_I(3);
    top_level__DOT__u_control__DOT__compute_iter_q = VL_RAND_RESET_I(32);
    top_level__DOT__u_control__DOT__compute_iter_d = VL_RAND_RESET_I(32);
    top_level__DOT__u_control__DOT__drain_iter_q = VL_RAND_RESET_I(32);
    top_level__DOT__u_control__DOT__drain_iter_d = VL_RAND_RESET_I(32);
    top_level__DOT__u_control__DOT__cycle_count_d = VL_RAND_RESET_I(32);
    { int __Vi0=0; for (; __Vi0<64; ++__Vi0) {
            top_level__DOT__u_a_buffer__DOT__mem[__Vi0] = VL_RAND_RESET_I(16);
    }}
    { int __Vi0=0; for (; __Vi0<64; ++__Vi0) {
            top_level__DOT__u_b_buffer__DOT__mem[__Vi0] = VL_RAND_RESET_I(16);
    }}
    top_level__DOT__u_interconnect__DOT__a_addr_calc = VL_RAND_RESET_I(32);
    top_level__DOT__u_interconnect__DOT__b_addr_calc = VL_RAND_RESET_I(32);
    { int __Vi0=0; for (; __Vi0<4; ++__Vi0) {
            top_level__DOT__gen_clusters__BRA__0__KET____DOT__u_cluster__DOT__accum_bank[__Vi0] = VL_RAND_RESET_I(32);
    }}
    { int __Vi0=0; for (; __Vi0<4; ++__Vi0) {
            top_level__DOT__gen_clusters__BRA__0__KET____DOT__u_cluster__DOT__pe_a[__Vi0] = VL_RAND_RESET_I(16);
    }}
    { int __Vi0=0; for (; __Vi0<4; ++__Vi0) {
            top_level__DOT__gen_clusters__BRA__0__KET____DOT__u_cluster__DOT__pe_b[__Vi0] = VL_RAND_RESET_I(16);
    }}
    { int __Vi0=0; for (; __Vi0<4; ++__Vi0) {
            top_level__DOT__gen_clusters__BRA__0__KET____DOT__u_cluster__DOT__pe_seed[__Vi0] = VL_RAND_RESET_I(32);
    }}
    { int __Vi0=0; for (; __Vi0<4; ++__Vi0) {
            top_level__DOT__gen_clusters__BRA__0__KET____DOT__u_cluster__DOT__pe_valid[__Vi0] = VL_RAND_RESET_I(1);
    }}
    { int __Vi0=0; for (; __Vi0<4; ++__Vi0) {
            top_level__DOT__gen_clusters__BRA__0__KET____DOT__u_cluster__DOT__pe_done[__Vi0] = VL_RAND_RESET_I(1);
    }}
    { int __Vi0=0; for (; __Vi0<4; ++__Vi0) {
            top_level__DOT__gen_clusters__BRA__0__KET____DOT__u_cluster__DOT__pe_result[__Vi0] = VL_RAND_RESET_I(32);
    }}
    { int __Vi0=0; for (; __Vi0<4; ++__Vi0) {
            top_level__DOT__gen_clusters__BRA__0__KET____DOT__u_cluster__DOT__accum_next[__Vi0] = VL_RAND_RESET_I(32);
    }}
    top_level__DOT__gen_clusters__BRA__0__KET____DOT__u_cluster__DOT__logical_lane = VL_RAND_RESET_I(32);
    top_level__DOT__gen_clusters__BRA__0__KET____DOT__u_cluster__DOT____Vcellout__gen_main_pes__BRA__0__KET____DOT__u_pe__acc_result = VL_RAND_RESET_I(32);
    top_level__DOT__gen_clusters__BRA__0__KET____DOT__u_cluster__DOT____Vcellout__gen_main_pes__BRA__1__KET____DOT__u_pe__acc_result = VL_RAND_RESET_I(32);
    top_level__DOT__gen_clusters__BRA__0__KET____DOT__u_cluster__DOT____Vcellout__gen_main_pes__BRA__2__KET____DOT__u_pe__acc_result = VL_RAND_RESET_I(32);
    top_level__DOT__gen_clusters__BRA__0__KET____DOT__u_cluster__DOT____Vcellout__gen_main_pes__BRA__3__KET____DOT__u_pe__acc_result = VL_RAND_RESET_I(32);
    top_level__DOT__gen_clusters__BRA__0__KET____DOT__u_cluster__DOT__gen_main_pes__BRA__0__KET____DOT__u_pe__DOT__product_full = VL_RAND_RESET_I(32);
    top_level__DOT__gen_clusters__BRA__0__KET____DOT__u_cluster__DOT__gen_main_pes__BRA__0__KET____DOT__u_pe__DOT__product_scaled = VL_RAND_RESET_I(32);
    top_level__DOT__gen_clusters__BRA__0__KET____DOT__u_cluster__DOT__gen_main_pes__BRA__1__KET____DOT__u_pe__DOT__product_full = VL_RAND_RESET_I(32);
    top_level__DOT__gen_clusters__BRA__0__KET____DOT__u_cluster__DOT__gen_main_pes__BRA__1__KET____DOT__u_pe__DOT__product_scaled = VL_RAND_RESET_I(32);
    top_level__DOT__gen_clusters__BRA__0__KET____DOT__u_cluster__DOT__gen_main_pes__BRA__2__KET____DOT__u_pe__DOT__product_full = VL_RAND_RESET_I(32);
    top_level__DOT__gen_clusters__BRA__0__KET____DOT__u_cluster__DOT__gen_main_pes__BRA__2__KET____DOT__u_pe__DOT__product_scaled = VL_RAND_RESET_I(32);
    top_level__DOT__gen_clusters__BRA__0__KET____DOT__u_cluster__DOT__gen_main_pes__BRA__3__KET____DOT__u_pe__DOT__product_full = VL_RAND_RESET_I(32);
    top_level__DOT__gen_clusters__BRA__0__KET____DOT__u_cluster__DOT__gen_main_pes__BRA__3__KET____DOT__u_pe__DOT__product_scaled = VL_RAND_RESET_I(32);
    { int __Vi0=0; for (; __Vi0<4; ++__Vi0) {
            top_level__DOT__gen_clusters__BRA__1__KET____DOT__u_cluster__DOT__accum_bank[__Vi0] = VL_RAND_RESET_I(32);
    }}
    { int __Vi0=0; for (; __Vi0<4; ++__Vi0) {
            top_level__DOT__gen_clusters__BRA__1__KET____DOT__u_cluster__DOT__pe_a[__Vi0] = VL_RAND_RESET_I(16);
    }}
    { int __Vi0=0; for (; __Vi0<4; ++__Vi0) {
            top_level__DOT__gen_clusters__BRA__1__KET____DOT__u_cluster__DOT__pe_b[__Vi0] = VL_RAND_RESET_I(16);
    }}
    { int __Vi0=0; for (; __Vi0<4; ++__Vi0) {
            top_level__DOT__gen_clusters__BRA__1__KET____DOT__u_cluster__DOT__pe_seed[__Vi0] = VL_RAND_RESET_I(32);
    }}
    { int __Vi0=0; for (; __Vi0<4; ++__Vi0) {
            top_level__DOT__gen_clusters__BRA__1__KET____DOT__u_cluster__DOT__pe_valid[__Vi0] = VL_RAND_RESET_I(1);
    }}
    { int __Vi0=0; for (; __Vi0<4; ++__Vi0) {
            top_level__DOT__gen_clusters__BRA__1__KET____DOT__u_cluster__DOT__pe_done[__Vi0] = VL_RAND_RESET_I(1);
    }}
    { int __Vi0=0; for (; __Vi0<4; ++__Vi0) {
            top_level__DOT__gen_clusters__BRA__1__KET____DOT__u_cluster__DOT__pe_result[__Vi0] = VL_RAND_RESET_I(32);
    }}
    { int __Vi0=0; for (; __Vi0<4; ++__Vi0) {
            top_level__DOT__gen_clusters__BRA__1__KET____DOT__u_cluster__DOT__accum_next[__Vi0] = VL_RAND_RESET_I(32);
    }}
    top_level__DOT__gen_clusters__BRA__1__KET____DOT__u_cluster__DOT__logical_lane = VL_RAND_RESET_I(32);
    top_level__DOT__gen_clusters__BRA__1__KET____DOT__u_cluster__DOT____Vcellout__gen_main_pes__BRA__0__KET____DOT__u_pe__acc_result = VL_RAND_RESET_I(32);
    top_level__DOT__gen_clusters__BRA__1__KET____DOT__u_cluster__DOT____Vcellout__gen_main_pes__BRA__1__KET____DOT__u_pe__acc_result = VL_RAND_RESET_I(32);
    top_level__DOT__gen_clusters__BRA__1__KET____DOT__u_cluster__DOT____Vcellout__gen_main_pes__BRA__2__KET____DOT__u_pe__acc_result = VL_RAND_RESET_I(32);
    top_level__DOT__gen_clusters__BRA__1__KET____DOT__u_cluster__DOT____Vcellout__gen_main_pes__BRA__3__KET____DOT__u_pe__acc_result = VL_RAND_RESET_I(32);
    top_level__DOT__gen_clusters__BRA__1__KET____DOT__u_cluster__DOT__gen_main_pes__BRA__0__KET____DOT__u_pe__DOT__product_full = VL_RAND_RESET_I(32);
    top_level__DOT__gen_clusters__BRA__1__KET____DOT__u_cluster__DOT__gen_main_pes__BRA__0__KET____DOT__u_pe__DOT__product_scaled = VL_RAND_RESET_I(32);
    top_level__DOT__gen_clusters__BRA__1__KET____DOT__u_cluster__DOT__gen_main_pes__BRA__1__KET____DOT__u_pe__DOT__product_full = VL_RAND_RESET_I(32);
    top_level__DOT__gen_clusters__BRA__1__KET____DOT__u_cluster__DOT__gen_main_pes__BRA__1__KET____DOT__u_pe__DOT__product_scaled = VL_RAND_RESET_I(32);
    top_level__DOT__gen_clusters__BRA__1__KET____DOT__u_cluster__DOT__gen_main_pes__BRA__2__KET____DOT__u_pe__DOT__product_full = VL_RAND_RESET_I(32);
    top_level__DOT__gen_clusters__BRA__1__KET____DOT__u_cluster__DOT__gen_main_pes__BRA__2__KET____DOT__u_pe__DOT__product_scaled = VL_RAND_RESET_I(32);
    top_level__DOT__gen_clusters__BRA__1__KET____DOT__u_cluster__DOT__gen_main_pes__BRA__3__KET____DOT__u_pe__DOT__product_full = VL_RAND_RESET_I(32);
    top_level__DOT__gen_clusters__BRA__1__KET____DOT__u_cluster__DOT__gen_main_pes__BRA__3__KET____DOT__u_pe__DOT__product_scaled = VL_RAND_RESET_I(32);
    { int __Vi0=0; for (; __Vi0<4; ++__Vi0) {
            top_level__DOT__gen_clusters__BRA__2__KET____DOT__u_cluster__DOT__accum_bank[__Vi0] = VL_RAND_RESET_I(32);
    }}
    { int __Vi0=0; for (; __Vi0<4; ++__Vi0) {
            top_level__DOT__gen_clusters__BRA__2__KET____DOT__u_cluster__DOT__pe_a[__Vi0] = VL_RAND_RESET_I(16);
    }}
    { int __Vi0=0; for (; __Vi0<4; ++__Vi0) {
            top_level__DOT__gen_clusters__BRA__2__KET____DOT__u_cluster__DOT__pe_b[__Vi0] = VL_RAND_RESET_I(16);
    }}
    { int __Vi0=0; for (; __Vi0<4; ++__Vi0) {
            top_level__DOT__gen_clusters__BRA__2__KET____DOT__u_cluster__DOT__pe_seed[__Vi0] = VL_RAND_RESET_I(32);
    }}
    { int __Vi0=0; for (; __Vi0<4; ++__Vi0) {
            top_level__DOT__gen_clusters__BRA__2__KET____DOT__u_cluster__DOT__pe_valid[__Vi0] = VL_RAND_RESET_I(1);
    }}
    { int __Vi0=0; for (; __Vi0<4; ++__Vi0) {
            top_level__DOT__gen_clusters__BRA__2__KET____DOT__u_cluster__DOT__pe_done[__Vi0] = VL_RAND_RESET_I(1);
    }}
    { int __Vi0=0; for (; __Vi0<4; ++__Vi0) {
            top_level__DOT__gen_clusters__BRA__2__KET____DOT__u_cluster__DOT__pe_result[__Vi0] = VL_RAND_RESET_I(32);
    }}
    { int __Vi0=0; for (; __Vi0<4; ++__Vi0) {
            top_level__DOT__gen_clusters__BRA__2__KET____DOT__u_cluster__DOT__accum_next[__Vi0] = VL_RAND_RESET_I(32);
    }}
    top_level__DOT__gen_clusters__BRA__2__KET____DOT__u_cluster__DOT__logical_lane = VL_RAND_RESET_I(32);
    top_level__DOT__gen_clusters__BRA__2__KET____DOT__u_cluster__DOT____Vcellout__gen_main_pes__BRA__0__KET____DOT__u_pe__acc_result = VL_RAND_RESET_I(32);
    top_level__DOT__gen_clusters__BRA__2__KET____DOT__u_cluster__DOT____Vcellout__gen_main_pes__BRA__1__KET____DOT__u_pe__acc_result = VL_RAND_RESET_I(32);
    top_level__DOT__gen_clusters__BRA__2__KET____DOT__u_cluster__DOT____Vcellout__gen_main_pes__BRA__2__KET____DOT__u_pe__acc_result = VL_RAND_RESET_I(32);
    top_level__DOT__gen_clusters__BRA__2__KET____DOT__u_cluster__DOT____Vcellout__gen_main_pes__BRA__3__KET____DOT__u_pe__acc_result = VL_RAND_RESET_I(32);
    top_level__DOT__gen_clusters__BRA__2__KET____DOT__u_cluster__DOT__gen_main_pes__BRA__0__KET____DOT__u_pe__DOT__product_full = VL_RAND_RESET_I(32);
    top_level__DOT__gen_clusters__BRA__2__KET____DOT__u_cluster__DOT__gen_main_pes__BRA__0__KET____DOT__u_pe__DOT__product_scaled = VL_RAND_RESET_I(32);
    top_level__DOT__gen_clusters__BRA__2__KET____DOT__u_cluster__DOT__gen_main_pes__BRA__1__KET____DOT__u_pe__DOT__product_full = VL_RAND_RESET_I(32);
    top_level__DOT__gen_clusters__BRA__2__KET____DOT__u_cluster__DOT__gen_main_pes__BRA__1__KET____DOT__u_pe__DOT__product_scaled = VL_RAND_RESET_I(32);
    top_level__DOT__gen_clusters__BRA__2__KET____DOT__u_cluster__DOT__gen_main_pes__BRA__2__KET____DOT__u_pe__DOT__product_full = VL_RAND_RESET_I(32);
    top_level__DOT__gen_clusters__BRA__2__KET____DOT__u_cluster__DOT__gen_main_pes__BRA__2__KET____DOT__u_pe__DOT__product_scaled = VL_RAND_RESET_I(32);
    top_level__DOT__gen_clusters__BRA__2__KET____DOT__u_cluster__DOT__gen_main_pes__BRA__3__KET____DOT__u_pe__DOT__product_full = VL_RAND_RESET_I(32);
    top_level__DOT__gen_clusters__BRA__2__KET____DOT__u_cluster__DOT__gen_main_pes__BRA__3__KET____DOT__u_pe__DOT__product_scaled = VL_RAND_RESET_I(32);
    { int __Vi0=0; for (; __Vi0<4; ++__Vi0) {
            top_level__DOT__gen_clusters__BRA__3__KET____DOT__u_cluster__DOT__accum_bank[__Vi0] = VL_RAND_RESET_I(32);
    }}
    { int __Vi0=0; for (; __Vi0<4; ++__Vi0) {
            top_level__DOT__gen_clusters__BRA__3__KET____DOT__u_cluster__DOT__pe_a[__Vi0] = VL_RAND_RESET_I(16);
    }}
    { int __Vi0=0; for (; __Vi0<4; ++__Vi0) {
            top_level__DOT__gen_clusters__BRA__3__KET____DOT__u_cluster__DOT__pe_b[__Vi0] = VL_RAND_RESET_I(16);
    }}
    { int __Vi0=0; for (; __Vi0<4; ++__Vi0) {
            top_level__DOT__gen_clusters__BRA__3__KET____DOT__u_cluster__DOT__pe_seed[__Vi0] = VL_RAND_RESET_I(32);
    }}
    { int __Vi0=0; for (; __Vi0<4; ++__Vi0) {
            top_level__DOT__gen_clusters__BRA__3__KET____DOT__u_cluster__DOT__pe_valid[__Vi0] = VL_RAND_RESET_I(1);
    }}
    { int __Vi0=0; for (; __Vi0<4; ++__Vi0) {
            top_level__DOT__gen_clusters__BRA__3__KET____DOT__u_cluster__DOT__pe_done[__Vi0] = VL_RAND_RESET_I(1);
    }}
    { int __Vi0=0; for (; __Vi0<4; ++__Vi0) {
            top_level__DOT__gen_clusters__BRA__3__KET____DOT__u_cluster__DOT__pe_result[__Vi0] = VL_RAND_RESET_I(32);
    }}
    { int __Vi0=0; for (; __Vi0<4; ++__Vi0) {
            top_level__DOT__gen_clusters__BRA__3__KET____DOT__u_cluster__DOT__accum_next[__Vi0] = VL_RAND_RESET_I(32);
    }}
    top_level__DOT__gen_clusters__BRA__3__KET____DOT__u_cluster__DOT__logical_lane = VL_RAND_RESET_I(32);
    top_level__DOT__gen_clusters__BRA__3__KET____DOT__u_cluster__DOT____Vcellout__gen_main_pes__BRA__0__KET____DOT__u_pe__acc_result = VL_RAND_RESET_I(32);
    top_level__DOT__gen_clusters__BRA__3__KET____DOT__u_cluster__DOT____Vcellout__gen_main_pes__BRA__1__KET____DOT__u_pe__acc_result = VL_RAND_RESET_I(32);
    top_level__DOT__gen_clusters__BRA__3__KET____DOT__u_cluster__DOT____Vcellout__gen_main_pes__BRA__2__KET____DOT__u_pe__acc_result = VL_RAND_RESET_I(32);
    top_level__DOT__gen_clusters__BRA__3__KET____DOT__u_cluster__DOT____Vcellout__gen_main_pes__BRA__3__KET____DOT__u_pe__acc_result = VL_RAND_RESET_I(32);
    top_level__DOT__gen_clusters__BRA__3__KET____DOT__u_cluster__DOT__gen_main_pes__BRA__0__KET____DOT__u_pe__DOT__product_full = VL_RAND_RESET_I(32);
    top_level__DOT__gen_clusters__BRA__3__KET____DOT__u_cluster__DOT__gen_main_pes__BRA__0__KET____DOT__u_pe__DOT__product_scaled = VL_RAND_RESET_I(32);
    top_level__DOT__gen_clusters__BRA__3__KET____DOT__u_cluster__DOT__gen_main_pes__BRA__1__KET____DOT__u_pe__DOT__product_full = VL_RAND_RESET_I(32);
    top_level__DOT__gen_clusters__BRA__3__KET____DOT__u_cluster__DOT__gen_main_pes__BRA__1__KET____DOT__u_pe__DOT__product_scaled = VL_RAND_RESET_I(32);
    top_level__DOT__gen_clusters__BRA__3__KET____DOT__u_cluster__DOT__gen_main_pes__BRA__2__KET____DOT__u_pe__DOT__product_full = VL_RAND_RESET_I(32);
    top_level__DOT__gen_clusters__BRA__3__KET____DOT__u_cluster__DOT__gen_main_pes__BRA__2__KET____DOT__u_pe__DOT__product_scaled = VL_RAND_RESET_I(32);
    top_level__DOT__gen_clusters__BRA__3__KET____DOT__u_cluster__DOT__gen_main_pes__BRA__3__KET____DOT__u_pe__DOT__product_full = VL_RAND_RESET_I(32);
    top_level__DOT__gen_clusters__BRA__3__KET____DOT__u_cluster__DOT__gen_main_pes__BRA__3__KET____DOT__u_pe__DOT__product_scaled = VL_RAND_RESET_I(32);
}
