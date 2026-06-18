// CPE 3101L - INTRODUCTION TO HDL
// Group 1		F 7:30 - 10:30 AM LB285TC
// Lab Exercise #5
// Sarcol, Joshua S.		BS CpE - 3		2025/09/30

//
// Verilog HDL code for an n-bit ALU
//
module ALU_nb #(parameter N = 3) (
	input wire [N-1: 0]	A, B,
	input wire				CB_in,
	input wire [2:0]		Mode,		
	output reg [N-1: 0]	Result,
	output reg				CB_out	);
	
	always @(*)
	begin
		case (Mode)
			3'b000:			// Addition (A + B) with carry
				{CB_out, Result} = CB_in + A + B;
			
			3'b001:			// Subtract (A – B) with borrow
				{CB_out, Result} = A - B - CB_in;
				
			3'b010: begin	// Bitwise AND of A and B
				CB_out = 0;
				Result = A & B;
				end
			
			3'b011: begin	// Bitwise OR of A and B
				CB_out = 0;
				Result = A | B;
				end
			
			3'b100: begin	// Bitwise XOR of A and B
				CB_out = 0;
				Result = A ^ B;
				end
				
			3'b101: begin	// Complement of A 
				CB_out = 0;
				Result = ~A;
				end
			
			3'b110: begin	// Increment A
				CB_out = 0;
				Result = A + 1'b1;
				end
				
			3'b111: begin	// Decrement A
				CB_out = 0;
				Result = A - 1'b1;
				end
				
			default: 		// Prevent latching
				{CB_out, Result} = {N+1 {1'bx}};
				
		endcase
	end
endmodule
	