//
// Verilog HDL code for a two-way light controller
//
module LightControl (x1, x2, f);

	input		x1, x2;
	output	f;
	
	wire		wN1_out, wN2_out, wA1_out, wA2_out;
	
	not		N1 (wN1_out, x1);
	not		N2 (wN2_out, x2);
	and		A1 (wA1_out, x1, wN2_out);
	and		A2 (wA2_out, wN1_out, x2);
	or			O1 (f, wA1_out, wA2_out);
	
endmodule
