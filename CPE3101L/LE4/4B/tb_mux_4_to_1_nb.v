// CPE 3101L - INTRODUCTION TO HDL
// Group 1		F 7:30 - 10:30 AM LB285TC
// LabExercise #4
// Sarcol, Joshua S.		BS CpE - 3		2025/09/19

// 
// Testbench file for mux_4_to_1_nb.v (unit test)
// 
`timescale 1 ns / 1 ps
module tb_mux_4_to_1_nb ();
	
	reg [7:0]	iA, iB, iC, iD;
	reg [1:0]	iS;
	
	wire [3:0]	aY;	// 4-bit wide bus output
	wire [7:0]	bY;	// 8-bit wide bus output
	
	// 4-bit wide 4-to-1 mux
	// lower half of the inputs
	mux_4_to_1_nb #(4) UUT_small (iA[3:0], iB[3:0], iC[3:0], iD[3:0], iS, aY);
	
	// 8-bit wide 4-to-1 mux
	// all bits of the inputs
	mux_4_to_1_nb #(8) UUT_large (iA, iB, iC, iD, iS, bY);
	
	// input tests
	initial begin
		$display("\nSelector input 0:");
		iS = 2'b00;	iA = 8'hA3;	iB = 8'h24;	iC = 8'h7E; iD = 8'h10; #10
						iA = 8'h55;	iB = 8'h99;	iC = 8'hFF; iD = 8'h00; #10
						iA = 8'h0F;	iB = 8'hF0;	iC = 8'hAB; iD = 8'hBC; #10

		$display("\nSelector input 1:");
		iS = 2'b01;	iA = 8'h2C;	iB = 8'hE7;	iC = 8'h08; iD = 8'hAA; #10
						iA = 8'hB5;	iB = 8'h3A;	iC = 8'h99; iD = 8'hC3; #10
						iA = 8'h11;	iB = 8'hD2;	iC = 8'h33; iD = 8'h44; #10

		$display("\nSelector input 2:");
		iS = 2'b10;	iA = 8'h22;	iB = 8'h33;	iC = 8'h44; iD = 8'h55; #10
						iA = 8'h7B;	iB = 8'h6A;	iC = 8'h5C; iD = 8'hC0; #10
						iA = 8'h00;	iB = 8'h67;	iC = 8'h1E; iD = 8'hA8; #10

		$display("\nSelector input 3:");
		iS = 2'b11;	iA = 8'h88;	iB = 8'h77;	iC = 8'h66; iD = 8'h55; #10
						iA = 8'h3C;	iB = 8'h82;	iC = 8'h9A; iD = 8'h7F; #10
						iA = 8'hBE;	iB = 8'hDA;	iC = 8'hCE; iD = 8'hEF; #10
		
		$display("\nSimulation finished at %0d ns", $time);
		$stop;
	end
	
	// monitor display
	initial begin
		$monitor("%3d ns: A = %1h.%1h || B = %1h.%1h || C = %1h.%1h || D = %1h.%1h || S = %1d >> 4Y = %1h || 8Y = %2h",
						$time, iA/16, iA%16, iB/16, iB%16, iC/16, iC%16, iD/16, iD%16, iS, aY, bY);
	end
endmodule
