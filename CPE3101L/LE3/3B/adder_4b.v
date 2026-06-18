// CPE 3101L - INTRODUCTION TO HDL
// Group 1		F 7:30 - 10:30 AM LB285TC
// LabExercise #3
// Sarcol, Joshua S.		BS CpE - 3		2025/09/05

//
// Verilog HDL code for a 4-bit ripple-carry adder circuit
//
module adder_4b (
	input [3:0]	A,
	input [3:0]	B,
	input			C_in,
	output[3:0] S,
	output		C_out	);
	
	wire c1, c2, c3;
	
	// individual full-adders where each carry is connected in series
	FullAdder	F0 (A[0], B[0], C_in, S[0], c1);
	FullAdder	F1 (A[1], B[1], c1,   S[1], c2);
	FullAdder	F2 (A[2], B[2], c2, 	 S[2], c3);
	FullAdder	F3 (A[3], B[3], c3,   S[3], C_out);
endmodule


//
// Full-adder module from Lab exercise 2B
//
module FullAdder (A, B, C_in, S, C_out);
	input		A, B, C_in;
	output	S, C_out;
	
	wire		s1, c1, c2;
	
	// half-adder 1
	xor		G1 (s1, A, B);
	and		G2 (c1, A, B);
	
	// half-adder 2
	xor		G3 (S, s1, C_in);
	and		G4 (c2, s1, C_in);
	
	// final carry
	or			G5 (C_out, c1, c2);
endmodule
