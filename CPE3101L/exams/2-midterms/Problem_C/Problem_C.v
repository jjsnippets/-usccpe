// CPE 3101L - INTRODUCTION TO HDL
// Group 1		F 7:30 - 10:30 AM LB285TC
// Midterm Exam (Set C)
// Sarcol, Joshua S.		BS CpE - 3		2025/09/29

//
// Midterms submission:
// Fuel gauge submodule
//
module Problem_C (
	input wire [3:0]	FLvl_in,
	input 				BMode_in,
	output reg [6:0]	FGauge_out	// ABCDEFG
	);
	
	always @(*)
	begin
		if (BMode_in)										// If BMode_in = 1
			FGauge_out = 7'b0000001;					// Then display only segment g
			
		else 													// Otherwise
			case (FLvl_in)
				4'h0: FGauge_out = 7'b0000000;		// 0000 			-> no segments
				4'h1:	FGauge_out = 7'b1000000;		// 0001 - 0010 -> a
				4'h2:	FGauge_out = 7'b1000000;
				4'h3:	FGauge_out = 7'b1100000;		// 0011 - 0100 -> a, b
				4'h4:	FGauge_out = 7'b1100000;
				4'h5:	FGauge_out = 7'b1110000;		// 0101 - 0110 -> a, b, c
				4'h6:	FGauge_out = 7'b1110000;
				4'h7:	FGauge_out = 7'b1111000;		// 0111 - 1000 -> a, b, c, d
				4'h8:	FGauge_out = 7'b1111000;
				4'h9:	FGauge_out = 7'b1111100;		// 1001 - 1010 -> a, b, c, d, e
				4'hA:	FGauge_out = 7'b1111100;
				4'hB:	FGauge_out = 7'b1111110;		// 1011 - 1100 -> a, b, c, d, e, f
				4'hC:	FGauge_out = 7'b1111110;
				4'hD:	FGauge_out = 7'b1111111;		// 1101 - 1111 -> a, b, c, d, e, f, g
				4'hE:	FGauge_out = 7'b1111111;
				4'hF:	FGauge_out = 7'b1111111;
				default: FGauge_out = 7'b1111111;	// (default) -> a, b, c, d, e, f, g
			endcase
	end
endmodule
