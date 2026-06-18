// CPE 3101L - INTRODUCTION TO HDL
// Group 1		F 7:30 - 10:30 AM LB285TC
// LabExercise #3
// Sarcol, Joshua S.		BS CpE - 3		2025/09/05

// 
// Testbench file for adder_4b.v (unit test)
// 
`timescale 1 ns / 1 ps
module tb_adder_4b ();

	reg [3:0] 	iA, iB;
	reg			iC_in;
	wire[3:0]	iS;
	wire			iC_out;
	
	adder_4b		UUT (iA, iB, iC_in, iS, iC_out);
	
	// input tests
	initial begin
		$display("Format: C_in + A + B = C_out + S    in both binary and decimal\n");
		$display("Testing with various inputs:");
		
		iA = 3;	iB = 4;	iC_in = 0;	#5
		iA = 9;	iB = 12;	iC_in = 0;	#5
		iA = 7;	iB = 14;	iC_in = 1;	#5
		iA = 14;	iB = 3;	iC_in = 0;	#5		
		iA = 0;	iB = 14;	iC_in = 1;	#5
		iA = 6;	iB = 13;	iC_in = 0;	#5		
		iA = 3;	iB = 13;	iC_in = 1;	#5
		iA = 11;	iB = 1;	iC_in = 1;	#5
		iA = 12;	iB = 7;	iC_in = 0;	#5
		iA = 2;	iB = 12;	iC_in = 1;	#5			
		
		$display("Simulation finished at %0d ns", $time);
		$stop;
	end
	
	// monitor display
	initial begin
		$monitor("%2d ns: %1b + %4b + %4b = %1b%4b    %1b + %2d + %2d = (%1d) + %2d", 
						$time, iC_in, iA, iB, iC_out, iS, iC_in, iA, iB, iC_out, iS);
	end
endmodule
