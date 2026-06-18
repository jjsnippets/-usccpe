// CPE 3101L - INTRODUCTION TO HDL
// Group 1		F 7:30 - 10:30 AM LB285TC
// LabExercise #3
// Sarcol, Joshua S.		BS CpE - 3		2025/09/05

//
// Verilog HDL code for a 2x4 Decoder circuit with active-enable pin
//
module decoder_2x4 	(
	input [1:0]	A,
	input			E,
	output[3:0]	D		);
	
	wire	[1:0] nA;
	
	// negated selector inputs
	not	nt1 (nA[1], A[1]);
	not	nt0 (nA[0], A[0]);
	
	// and gate outputs
	and	D0 (D[0], nA[1], nA[0], E);
	and	D1 (D[1], nA[1],  A[0], E);
	and	D2 (D[2],  A[1], nA[0], E);
	and	D3 (D[3],  A[1],  A[0], E);
endmodule
