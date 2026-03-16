// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Symbol table implementation internals

#include "Vtop_level__Syms.h"
#include "Vtop_level.h"
#include "Vtop_level_cluster__pi4.h"



// FUNCTIONS
Vtop_level__Syms::Vtop_level__Syms(Vtop_level* topp, const char* namep)
    // Setup locals
    : __Vm_namep(namep)
    , __Vm_didInit(false)
    // Setup submodule names
    , TOP__top_level__DOT__gen_clusters__BRA__0__KET____DOT__u_cluster(Verilated::catName(topp->name(), "top_level.gen_clusters[0].u_cluster"))
    , TOP__top_level__DOT__gen_clusters__BRA__1__KET____DOT__u_cluster(Verilated::catName(topp->name(), "top_level.gen_clusters[1].u_cluster"))
    , TOP__top_level__DOT__gen_clusters__BRA__2__KET____DOT__u_cluster(Verilated::catName(topp->name(), "top_level.gen_clusters[2].u_cluster"))
    , TOP__top_level__DOT__gen_clusters__BRA__3__KET____DOT__u_cluster(Verilated::catName(topp->name(), "top_level.gen_clusters[3].u_cluster"))
    , TOP__top_level__DOT__gen_clusters__BRA__4__KET____DOT__u_cluster(Verilated::catName(topp->name(), "top_level.gen_clusters[4].u_cluster"))
    , TOP__top_level__DOT__gen_clusters__BRA__5__KET____DOT__u_cluster(Verilated::catName(topp->name(), "top_level.gen_clusters[5].u_cluster"))
    , TOP__top_level__DOT__gen_clusters__BRA__6__KET____DOT__u_cluster(Verilated::catName(topp->name(), "top_level.gen_clusters[6].u_cluster"))
    , TOP__top_level__DOT__gen_clusters__BRA__7__KET____DOT__u_cluster(Verilated::catName(topp->name(), "top_level.gen_clusters[7].u_cluster"))
{
    // Pointer to top level
    TOPp = topp;
    // Setup each module's pointers to their submodules
    TOPp->__PVT__top_level__DOT__gen_clusters__BRA__0__KET____DOT__u_cluster = &TOP__top_level__DOT__gen_clusters__BRA__0__KET____DOT__u_cluster;
    TOPp->__PVT__top_level__DOT__gen_clusters__BRA__1__KET____DOT__u_cluster = &TOP__top_level__DOT__gen_clusters__BRA__1__KET____DOT__u_cluster;
    TOPp->__PVT__top_level__DOT__gen_clusters__BRA__2__KET____DOT__u_cluster = &TOP__top_level__DOT__gen_clusters__BRA__2__KET____DOT__u_cluster;
    TOPp->__PVT__top_level__DOT__gen_clusters__BRA__3__KET____DOT__u_cluster = &TOP__top_level__DOT__gen_clusters__BRA__3__KET____DOT__u_cluster;
    TOPp->__PVT__top_level__DOT__gen_clusters__BRA__4__KET____DOT__u_cluster = &TOP__top_level__DOT__gen_clusters__BRA__4__KET____DOT__u_cluster;
    TOPp->__PVT__top_level__DOT__gen_clusters__BRA__5__KET____DOT__u_cluster = &TOP__top_level__DOT__gen_clusters__BRA__5__KET____DOT__u_cluster;
    TOPp->__PVT__top_level__DOT__gen_clusters__BRA__6__KET____DOT__u_cluster = &TOP__top_level__DOT__gen_clusters__BRA__6__KET____DOT__u_cluster;
    TOPp->__PVT__top_level__DOT__gen_clusters__BRA__7__KET____DOT__u_cluster = &TOP__top_level__DOT__gen_clusters__BRA__7__KET____DOT__u_cluster;
    // Setup each module's pointer back to symbol table (for public functions)
    TOPp->__Vconfigure(this, true);
    TOP__top_level__DOT__gen_clusters__BRA__0__KET____DOT__u_cluster.__Vconfigure(this, true);
    TOP__top_level__DOT__gen_clusters__BRA__1__KET____DOT__u_cluster.__Vconfigure(this, false);
    TOP__top_level__DOT__gen_clusters__BRA__2__KET____DOT__u_cluster.__Vconfigure(this, false);
    TOP__top_level__DOT__gen_clusters__BRA__3__KET____DOT__u_cluster.__Vconfigure(this, false);
    TOP__top_level__DOT__gen_clusters__BRA__4__KET____DOT__u_cluster.__Vconfigure(this, false);
    TOP__top_level__DOT__gen_clusters__BRA__5__KET____DOT__u_cluster.__Vconfigure(this, false);
    TOP__top_level__DOT__gen_clusters__BRA__6__KET____DOT__u_cluster.__Vconfigure(this, false);
    TOP__top_level__DOT__gen_clusters__BRA__7__KET____DOT__u_cluster.__Vconfigure(this, false);
}
