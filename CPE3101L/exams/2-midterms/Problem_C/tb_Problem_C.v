// CPE 3101L - INTRODUCTION TO HDL
// Group 1		F 7:30 - 10:30 AM LB285TC
// Midterm Exam (Set C)
// Sarcol, Joshua S.		BS CpE - 3		2025/09/29

//
// Midterms submission:
// Fuel gauge submodule
// Unit test for Problem_C.v
//
`timescale 1 ns / 1 ps
module tb_ProblemC ();
	reg [3:0]	iFLvl_in;
	reg 			iBMode_in;
	wire [6:0]	oFGauge_out;
	
	Problem_C UUT (iFLvl_in, iBMode_in, oFGauge_out);
	
	// input tests
	initial begin
		$display("Input tests");
		$display("time | BM  FL | A B C D E F G");
		
		$display("Battery Mode");
		iBMode_in = 1'b1;		iFLvl_in = 4'h3;		#5
									iFLvl_in = 4'h7;		#5
									iFLvl_in = 4'hF;		#5
		
		$display("Fuel Mode");
		iBMode_in = 1'b0;		iFLvl_in = 4'h0;
		
		repeat(20)
			#5		iFLvl_in = iFLvl_in + 1'b1;
		
		$display("Simulation finished at %0d ns", $time);
		$stop;
	end
	
	// monitor display
	initial begin
		$monitor(" %3d |  %1x   %1h | %1b %1b %1b %1b %1b %1b %1b",
				$time, iBMode_in, iFLvl_in, oFGauge_out[6], oFGauge_out[5], oFGauge_out[4], oFGauge_out[3], oFGauge_out[2], oFGauge_out[1], oFGauge_out[0]);
	end	

endmodule
