// CPE 3101L - INTRODUCTION TO HDL
// Group 1		F 7:30 - 10:30 AM LB285TC
// LabExercise #4
// Sarcol, Joshua S.		BS CpE - 3		2025/09/19

//
// Verilog HDL code for a 4-bit comparator circuit
//
module comparator_4b (
	input  [3:0] A, B,	
	output [2:0] R		);
	
	// Unique 1 output:
	// R[2] == 1 when A > B
	// R[1] == 1 when A = B
	// R[0] == 1 when A < B
	
	assign R[2] = A > B;
	assign R[1] = A == B;
	assign R[0] = A < B;
	
endmodule
	
	