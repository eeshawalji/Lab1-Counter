#!/bin/sh

rm -rf obj_dir
rm -f counter.vcd

verilator -Wall --cc --trace \
    counter.sv bin2bcd.sv top.sv \
    --exe top_tb.cpp \
    --top-module top

make -j -C obj_dir -f Vtop.mk Vtop

obj_dir/Vtop


