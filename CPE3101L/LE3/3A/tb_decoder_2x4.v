// CPE 3101L - INTRODUCTION TO HDL
// Group 1		F 7:30 - 10:30 AM LB285TC
// LabExercise #3
// Sarcol, Joshua S.		BS CpE - 3		2025/09/05

// 
// Testbench file for decoder_2x4.v (unit test)
// 
`timescale 1 ns / 1 ps
module tb_decoder_2x4 ();

	reg	[1:0] iA;
	reg			iE;
	wire	[3:0]	oD;
	
	decoder_2x4	UUT (iA, iE, oD);
	
	// input tests
	initial begin
		$display("Varying input selectors while enable is low");
		iE = 1'b0;	iA = 2'b00;		#5
						iA = 2'b01;		#5
						iA = 2'b10;		#5
						iA = 2'b11;		#15
						
		$display("Varying input selectors while enable is high");
		iE = 1'b1;	iA = 2'b00;		#5
						iA = 2'b01;		#5
						iA = 2'b10;		#5
						iA = 2'b11;		#15
		
		$display("Simulation finished at %0d ns", $time);
		$stop;
	end
	
	// monitor display
	initial begin
		$monitor("Time = %2d ns\tE = %1b\tA = %2b\tE = %4b", $time, iE, iA, oD);
	end
endmodule
