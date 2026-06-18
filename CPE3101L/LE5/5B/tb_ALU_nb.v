// CPE 3101L - INTRODUCTION TO HDL
// Group 1		F 7:30 - 10:30 AM LB285TC
// Lab Exercise #5
// Sarcol, Joshua S.		BS CpE - 3		2025/09/30

// 
// Testbench file for ALU_nb.v (unit test)
// 
`timescale 1 ns / 1 ps
module tb_ALU_nb ();
	
	reg [3:0]	iA, iB;
	reg			iCB_in;
	reg [2:0]	iMode;
	
	wire [3:0]	oResult;
	wire			oCB_out;
	
	// 4-bit wide ALU
	ALU_nb #(4) UUT_4b (iA, iB, iCB_in, iMode, oResult, oCB_out);
	
	// input tests
	initial begin
		$display(" time  |  mode || c aaaa bbbb || c rrrr");
		
		$display("Mode 000: Addition (A + B) with carry");
		iMode = 3'b000;
			iCB_in = 0;		iA = 05;		iB = 09;		#5;	// 5 + 9 = 14
			iCB_in = 1;		iA = 15;		iB = 01;		#5;	// 15 + 1 + 1 = 17 (carry)
			iCB_in = 0;		iA = 10;		iB = 05;		#5;	// 10 + 5 = 15	
		
		$display("\nMode 001: Subtract (A - B) with borrow");
		iMode = 3'b001;
			iCB_in = 0;		iA = 10;		iB = 03;		#5;	// 10 - 3 = 7
			iCB_in = 1;		iA = 00;		iB = 01;		#5;	// 0 - 1 - 1 = 14 (borrow)
			iCB_in = 0;		iA = 15;		iB = 15;		#5;	// 15 - 15 = 0	
		
		$display("\nMode 010: Bitwise AND of A and B");
		iMode = 3'b010;
			iA = 4'b1010;		iB = 4'b1000;			#5;	// 1010 & 1100 = 1000
			iA = 4'b1111;		iB = 4'b0000;			#5;	// 1111 & 1100 = 0000
			iA = 4'b1111;		iB = 4'b1111;			#5;	// 1111 & 1111 = 1111
			
		$display("\nMode 011: Bitwise OR of A and B");
		iMode = 3'b011;
			iA = 4'b1010;		iB = 4'b1100;			#5;	// 1010 | 1100 = 1110
			iA = 4'b1111;		iB = 4'b1100;			#5;	// 1111 | 1100 = 1111
			iA = 4'b0000;		iB = 4'b0000;			#5;	// 0000 | 0000 = 0000

		$display("\nMode 100: Bitwise XOR of A and B");
		iMode = 3'b100;
			iA = 4'b1010;		iB = 4'b1100;			#5;	// 1010 ^ 1100 = 0110
			iA = 4'b1111;		iB = 4'b1111;			#5;	// 1111 ^ 1111 = 0000
			iA = 4'b1111;		iB = 4'b0000;			#5;	// 1111 ^ 0000 = 1111
		
		$display("\nMode 101: Complement of A");
		iMode = 3'b101;
			iA = 4'b0000;									#5;	// ~0000 = 1111
			iA = 4'b1111;									#5;	// ~1111 = 0000
			iA = 4'b1010;									#5;	// ~1010 = 0101	
		
		$display("\nMode 110: Increment A");
		iMode = 3'b110;
			iA = 4'b0000;									#5;	// 0000++ = 0001
			iA = 4'b1111;									#5;	// 1111++ = 0000
			iA = 4'b1010;									#5;	// 1010++ = 1011	
			
		$display("\nMode 111: Decrement A");
		iMode = 3'b111;
			iA = 4'b0000;									#5;	// 0000-- = 1111
			iA = 4'b1111;									#5;	// 1111-- = 1110
			iA = 4'b1010;									#5;	// 1010-- = 1001		
		
		$display("\nSimulation finished at %0d ns", $time);
		$stop;	
	end
	
	// monitor display
	initial begin
		$monitor("%3d ns |   %3b || %1b %4b %4b || %1b %4b", $time, iMode, iCB_in, iA, iB, oCB_out, oResult);
	end 

endmodule
