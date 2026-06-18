// CPE 3101L - INTRODUCTION TO HDL
// Group 1		F 7:30 - 10:30 AM LB285TC
// Lab Exercise #6
// Sarcol, Joshua S.		BS CpE - 3		2025/10/05

// 
// Testbench file for JK_FF.v (unit test)
// 
`timescale 1 ns / 1 ps
module tb_JK_FF ();
	reg	iJ, iK, iClk, iReset;
	wire	oQ, oQ_bar;
	
	JK_FF UUT (	iJ, iK, iReset, iClk, oQ, oQ_bar);
	
	// initial value for clock
	initial
		iClk = 1'b0;
	
	// clock generator
	always
		#2.5	iClk = ~iClk;
	
	// reset held high for a few clock cycles
	initial begin
		$display("time | rst J K | Q ~Q");
		$display("Reset enabled");
		iReset = 1'b1;		#17
		$display("Reset disabled");
		iReset = 1'b0;
	end
	
	// random test inputs
	initial begin
		{iJ, iK} = 2'b01;	#3
		{iJ, iK} = 2'b01; #5
		{iJ, iK} = 2'b11; #7
		{iJ, iK} = 2'b00; #9
		{iJ, iK} = 2'b10; #5
		{iJ, iK} = 2'b01; #6
		{iJ, iK} = 2'b11; #8
		{iJ, iK} = 2'b00; #4
		{iJ, iK} = 2'b10; #7
		{iJ, iK} = 2'b11; #5
		{iJ, iK} = 2'b01; #9
		
		$display("Simulation finished at %0d ns", $time);
		$stop;
	end
	
	// monitor display
	// print for each change of input
	always @(iJ, iK, iReset)
		$display(" %3d |   %1b %1b %1b | %1b %1b", $time, iReset, iJ, iK, oQ, oQ_bar);
	
	// indicate negedge by >
	// wait for a brief delay before print-out
	always @(negedge iClk)
		#0.1 $display(" %3d |   %1b %1b %1b > %1b %1b", $time - 0.1, iReset, iJ, iK, oQ, oQ_bar);
		
endmodule
	