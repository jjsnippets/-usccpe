// CPE 3101L - INTRODUCTION TO HDL
// Group 1		F 7:30 - 10:30 AM LB285TC
// Lab Exercise #6
// Sarcol, Joshua S.		BS CpE - 3		2025/10/06

// 
// Testbench file for Counter_4bit.v (unit test)
// 
`timescale 1 ns / 1 ps
module tb_Counter_4bit ();
	reg			iClk, inReset, iLoad, iCount_en, iUp;
	reg [3:0]	iCount_in;
	wire [3:0]	oCount_out;
	
	Counter_4bit UUT (iClk, inReset, iLoad, iCount_en, iUp, iCount_in, oCount_out);

	// initial value for clock
	initial
		iClk = 1'b0;
	
	// clock generator
	always
		#2.5	iClk = ~iClk;
		
	// test inputs
	initial begin
		$display("time | rst ld en up   in |  out");
		$display("Initialize to 0");
		inReset = 1'b0;	iLoad = 1'b0;	iCount_en = 1'b1;	iUp = 1'b1; iCount_in = 4'b0000;
		#3
		
		$display("Count up");
		inReset = 1'b1;									#12
		
		$display("Pause counting");
		iCount_en = 1'b0;									#7
		$display("Resume counting");
		iCount_en = 1'b1;									#5
		
		$display("Load value close to maximum");
		iLoad = 1'b1;		iCount_in = 4'b1101;		#4
		iLoad = 1'b0;										#25
		
		$display("Reset to 0");
		inReset = 1'b0;									#3
		inReset = 1'b1;									#7
		
		$display("Count down");
		iUp = 1'b0;											#13
		
		$display("Pause counting");
		iCount_en = 1'b0;									#5
		$display("Resume counting");
		iCount_en = 1'b1;									#12
		
		$display("Load value");
		iLoad = 1'b1;		iCount_in = 4'b0110;		#5
		iLoad = 1'b0;										#14
		
		$display("Simulation finished at %0d ns", $time);
		$stop;
	end
	
	// monitor display
	// print for each change of input
	always @(inReset, iLoad, iCount_en, iUp)
		#0.1 $display(" %3d |   %1b  %1b  %1b  %1b %4b | %4b", $time - 0.1, inReset, iLoad, iCount_en, iUp, iCount_in, oCount_out);
	
	// indicate falling-edge clock by >
	always @(negedge iClk)
		#0.1 $display(" %3d |   %1b  %1b  %1b  %1b %4b > %4b", $time - 0.1, inReset, iLoad, iCount_en, iUp, iCount_in, oCount_out);
		
endmodule
