#include "Vcounter.h"
#include "verilated.h"
#include "verilated_vcd_c.h"
#include "vbuddy.cpp"  // include the Vbuddy interface

int main(int argc, char **argv, char **env){
    Verilated::commandArgs(argc, argv);
    Vcounter* top = new Vcounter;

    // --- init trace dump ---
    Verilated::traceEverOn(true);
    VerilatedVcdC* tfp = new VerilatedVcdC;
    top->trace(tfp, 99);
    tfp->open("counter.vcd");

    // --- init Vbuddy ---
    if (vbdOpen() != 1) return (-1);
    vbdHeader("Lab 1: Counter - Load Preset");

    // --- initialize simulation inputs ---
    top->clk = 1;
    top->rst = 1;
    top->ld  = 0;
    top->v   = 0;

    // --- main simulation loop ---
    for (int i = 0; i < 300; i++) {
        // Toggle clock (2 steps per iteration)
        for (int clk = 0; clk < 2; clk++) {
            tfp->dump(2 * i + clk);
            top->clk = !top->clk;
            top->eval();
        }

        // Reset active only for the first few cycles
        top->rst = (i < 2);

        // 🟢 Read inputs from Vbuddy
        top->v = vbdValue();  // knob (preset value)
        top->ld = vbdFlag();  // EC11 pushbutton (load flag)

        // 🟢 Show counter value on Vbuddy display
        vbdHex(4, (int(top->count) >> 12) & 0xF);
        vbdHex(3, (int(top->count) >> 8) & 0xF);
        vbdHex(2, (int(top->count) >> 4) & 0xF);
        vbdHex(1, int(top->count) & 0xF);
        vbdCycle(i + 1);


        if (Verilated::gotFinish()) break;
    }

    // --- cleanup ---
    vbdClose();
    tfp->close();
    delete top;
    return 0;
}
