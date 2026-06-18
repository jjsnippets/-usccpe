// CPE 3101L - INTRODUCTION TO HDL
// Group 1		F 7:30 - 10:30 AM LB285TC
// Lab Exercise #5
// Sarcol, Joshua S.		BS CpE - 3		2025/09/19

// 
// Testbench file for Hex_to_7Seg_Anode.v (unit test)
// 
`timescale 1 ns / 1 ps
module tb_Hex_to_7Seg_Anode ();
	reg [3:0]	iHex;
	reg			iDP;
	wire [7:0]	oSSeg;
	
	Hex_to_7Seg_Anode UUT (iHex, iDP, oSSeg);
	
	// input tests
	initial begin
		$display("All possible inputs");
		$display("time | sym dp | A B C D E F G .");
		
		{iHex, iDP} = 5'b00000;
		
		repeat(32)
			#5		{iHex, iDP} = {iHex, iDP} + 1'b1;
		
		$display("Simulation finished at %0d ns", $time);
		$stop;
	end
	
	// monitor display
	initial begin
		$monitor(" %3d |  %1x   %1b | %1b %1b %1b %1b %1b %1b %1b %1b",
				$time, iHex, iDP, oSSeg[7], oSSeg[6], oSSeg[5], oSSeg[4], oSSeg[3], oSSeg[2], oSSeg[1], oSSeg[0]);
	end	
endmodule
	