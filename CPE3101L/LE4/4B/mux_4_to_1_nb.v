// CPE 3101L - INTRODUCTION TO HDL
// Group 1		F 7:30 - 10:30 AM LB285TC
// Lab Exercise #4
// Sarcol, Joshua S.		BS CpE - 3		2025/09/19

//
// Verilog HDL code for a n-bit wide 4-to-1 multiplexer
//
module mux_4_to_1_nb #(parameter N = 4) 	(
	input [N-1:0]	A, B, C, D,
	input [1:0]		S,
	output [N-1:0] Y								);
	
	// Function table
	// S == 00 => Y == A
	// S == 01 => Y == B
	// S == 10 => Y == C
	// S == 11 => Y == D
	
	assign Y = 	(S == 2'b00) ? A:
					(S == 2'b01) ? B:
					(S == 2'b10) ? C:
										D; // S == 2'b11

endmodule
