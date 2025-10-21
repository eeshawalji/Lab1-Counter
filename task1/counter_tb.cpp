#include "Vcounter.h"
#include "verilated.h"
#include "verilated_vcd_c.h"

int main(int argc, char **argv, char **env){
    int i;
    int clk;

    Verilated::commandArgs(argc, argv);
    //init top verilog instance
    Vcounter* top = new Vcounter;
    //init trace dump
    Verilated::traceEverOn(true);
    VerilatedVcdC* tfp = new VerilatedVcdC;
    top->trace (tfp, 99);
    tfp->open ("counter.vcd");

    //initialise simulation inputs
    top->clk = 1;
    top->rst = 1;
    top->en = 0;

    int count_val = top->count;
    int pause = 3;

    for (i=0; i<300; i++){
        //run simulation for many clock cycles
        for (clk = 0; clk < 2; clk++){
            tfp->dump (2*i+clk);
            top->clk = !top->clk;
            top->eval();
        }  
        top->rst = (i<2) | (i==18);
        top->en = (i>4);


        if(count_val == 9){
            if (pause == 0) top->en = 1;
            else{
                top->en = 0;
                pause--;
            }
        }
        if (Verilated::gotFinish()) exit(0);
    }
    tfp->close();
    exit(0);

}