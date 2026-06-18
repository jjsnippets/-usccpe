// CPE 3101L - INTRODUCTION TO HDL
// Group 1		F 7:30 - 10:30 AM LB285TC
// LabExercise #4
// Sarcol, Joshua S.		BS CpE - 3		2025/09/19

// 
// Testbench file for comparator_4b.v (unit test)
// 
`timescale 1 ns / 1 ps
module tb_comparator_4b ();
	
	reg [3:0]	iA, iB;
	wire [2:0]	oR;
	
	comparator_4b UUT (iA, iB, oR);
	
	// input tests
	initial begin
		$display("time:  A:xx B:xx G:? E:? L:?");
		$display("Testing with various inputs:");

		iA = 4;	iB = 7;	#10
		iA = 3;	iB = 1;	#10
		iA = 9;	iB = 12;	#10
		iA = 13;	iB = 6;	#10
		iA = 4;	iB = 0;	#10
		iA = 4;	iB = 4;	#10
		iA = 7;	iB = 7;	#10
		iA = 14;	iB = 2;	#10
		iA = 1;	iB = 1;	#10
		iA = 2;	iB = 2;	#10
		iA = 13;	iB = 12;	#10
		iA = 5;	iB = 6;	#10
		iA = 7;	iB = 5;	#10
		iA = 8;	iB = 4;	#10
		iA = 7;	iB = 8;	#10
		iA = 9;	iB = 2;	#10
		
		$display("Simulation finished at %0d ns", $time);
		$stop;
	end
	
	// monitor display
	initial begin
		$monitor("%3d ns: A:%2d B:%2d G:%1b E:%1b L:%1b", 
						$time, iA, iB, oR[2], oR[1], oR[0]);
	end
endmodule
