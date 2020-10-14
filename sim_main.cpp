#include <iostream>
#include <memory>

#include "svdpi.h"
#include "Vtop__Dpi.h"
#include "Vtop.h"
#include "verilated.h"

extern int incr(int a) { return a+1; }

vluint64_t main_time = 0;
double sc_time_stamp() { return main_time; }

int main(int argc, char** argv, char** env) {
    Verilated::commandArgs(argc, argv);

    const int period = 2;

    std::unique_ptr<Vtop> top(new Vtop);
    while (!Verilated::gotFinish()) {
      if ( main_time == 0*period) {
	top->reset = 1;
      }
      if ( main_time == 2*period) {
	top->reset = 0;
      }
      if ( main_time % period == period/2) {
	top->clk = 1;
      }
      if ( main_time % period == 0) {
	top->clk = 0;
      }
      if ( main_time == 20*period) {
	break;
      }

      top->eval();

      std::cout << main_time << ": " << (int) top->clk << " " << (int) top->reset << " " << top->acc_ps << " " << top->acc_ns << std::endl;
      ++main_time;
    }

    top->final();
    std::cout << "After final" << std::endl;
    exit(0);
}
