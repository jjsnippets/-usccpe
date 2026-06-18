// CPE 3101L - INTRODUCTION TO HDL
// Group 1		F 7:30 - 10:30 AM LB285TC
// LabExercise #2
// Sarcol, Joshua S.		BS CpE - 3		2025/08/28

//
// Testbench file for HalfAdder.v (Unit test)
//
`timescale 1 ns / 1 ps
module tb_HalfAdder();

	// all inputs to UUT (HalfAdder.v) are declared as reg type
	reg	x, y;
	// all outputs from UUT (HalfAdder.v) are declared as wire type
	wire	C, S;
	// instantiate UUT with implicit port mapping
	HalfAdder UUT (x, y, C, S);

	// generate stimuli
	initial
		begin
			x = 0;	y = 0;	#10
			x = 0;	y = 1;	#10
			x = 1;	y = 0;	#10
			x = 1;	y = 1;	#50

		$stop;			//system task to end the simulation
	end

endmodule
