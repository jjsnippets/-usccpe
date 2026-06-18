// CPE 3101L - INTRODUCTION TO HDL
// Group 1		F 7:30-10:30 AM LB285TC
// LabExercise #1
// Sarcol, Joshua S.		BS CpE - 3		2025/08/22

//
// Verilog HDL code for a half adder circuit
//
module HalfAdder (x, y, C, S);

	input		x, y;
	output	C, S;

	xor		X1 (S, x, y);
	and		A1 (C, x, y);

endmodule
