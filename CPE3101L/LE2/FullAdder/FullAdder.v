// CPE 3101L - INTRODUCTION TO HDL
// Group 1		F 7:30 - 10:30 AM LB285TC
// LabExercise #2
// Sarcol, Joshua S.		BS CpE - 3		2025/08/29

//
// Verilog HDL code for a full adder circuit
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
