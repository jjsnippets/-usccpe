// CPE 3101L - INTRODUCTION TO HDL
// Group 1		F 7:30 - 10:30 AM LB285TC
// LabExercise #2
// Sarcol, Joshua S.		BS CpE - 3		2025/08/29

// 
// Testbench file for FullAdder.v (unit test)
// 
`timescale 1 ns / 1 ps
module tb_FullAdder();

	reg			A, B, C_in;
	wire			S, C_out;

	FullAdder	UUT (A, B, C_in, S, C_out);

	initial
		begin
			A = 0;	B = 0;	C_in = 0;	#10
			A = 0;	B = 0;	C_in = 1;	#10
			A = 0;	B = 1;	C_in = 0;	#10
			A = 0;	B = 1;	C_in = 1;	#10
			A = 1;	B = 0;	C_in = 0;	#10
			A = 1;	B = 0;	C_in = 1;	#10
			A = 1;	B = 1;	C_in = 0;	#10
			A = 1;	B = 1;	C_in = 1;	#30

		$stop;
	end

endmodule
