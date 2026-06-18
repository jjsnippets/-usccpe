// CPE 3101L - INTRODUCTION TO HDL
// Group 1		F 7:30 - 10:30 AM LB285TC
// Lab Exercise #6
// Sarcol, Joshua S.		BS CpE - 3		2025/10/05

//
// Verilog HDL code for a JK Flip-flop
// negative edge triggered, active high asyncronous reset
//
module JK_FF (
	input wire J, K, Reset, Clk,
	output reg Q,
	output wire Q_bar						);
	
	assign Q_bar = ~Q;
	
	always @(negedge Clk, posedge Reset)
	begin
		if (Reset)		// asyncronous reset
			Q <= 1'b0;	
		else 				// JK flip-flop characteristic equation
			Q <= (J & ~Q) | (~K & Q);
	end
endmodule
