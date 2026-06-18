// CPE 3101L - INTRODUCTION TO HDL
// Group 1		F 7:30 - 10:30 AM LB285TC
// Lab Exercise #5
// Sarcol, Joshua S.		BS CpE - 3		2025/09/29

//
// Verilog HDL code for a common-anode 7-segment decoder from a Hex digit
//
module Hex_to_7Seg_Anode (
	input wire [3:0]	Hex, 	// 4-bit digit (0-F)
	input wire			DP,	// 1 = with decimal point
	output reg [7:0]	SSeg 	// A-B-C_D-E-F_G_DP
	);
	
	always @(*)
	begin
		SSeg[0] = ~DP;
		
		case (Hex)
			4'h0: SSeg[7:1] = 7'b000_000_1;
			4'h1: SSeg[7:1] = 7'b100_111_1;
			4'h2: SSeg[7:1] = 7'b001_001_0;
			4'h3: SSeg[7:1] = 7'b000_011_0;
			4'h4: SSeg[7:1] = 7'b100_110_0;
			4'h5: SSeg[7:1] = 7'b010_010_0;
			4'h6: SSeg[7:1] = 7'b010_000_0;
			4'h7: SSeg[7:1] = 7'b000_111_1;
			4'h8: SSeg[7:1] = 7'b000_000_0;
			4'h9: SSeg[7:1] = 7'b000_010_0;
			4'hA: SSeg[7:1] = 7'b000_100_0;
			4'hB: SSeg[7:1] = 7'b110_000_0;
			4'hC: SSeg[7:1] = 7'b011_000_1;
			4'hD: SSeg[7:1] = 7'b100_001_0;
			4'hE: SSeg[7:1] = 7'b011_000_0;
			4'hF: SSeg[7:1] = 7'b011_100_0;		
		endcase	
	
	end
endmodule
	