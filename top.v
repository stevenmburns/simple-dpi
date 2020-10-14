
module top(clk, reset, acc_ps, acc_ns);

   input clk;
   input reset;
   
   output reg [31:0] acc_ps;
   output reg [31:0] acc_ns;

   import "DPI-C" function int incr (input int a);

   always_comb begin
      acc_ns = incr(acc_ps);
   end

   always_ff @(posedge(clk)) begin
      if ( reset) begin
	 acc_ps <= 0;
      end else begin
	 acc_ps <= acc_ns;
      end
   end

endmodule
