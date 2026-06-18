
// Practice Problem:
// 3.37  A majority logic function is a Boolean function that is 
// equal to 1 if the majority of the variables are equal to 1, equal 
// to 0 otherwise. 
// (a)   Write a truth table for a four-bit majority function.  
// (b)   Write a Verilog user-defined primitive for a four-bit
//       majority function. 

// Boolean equation
// z = ABC + ABD + ACD + BCD
//     AB(C + D) + CD(A +D)

module majority4(
	input [3:0]	I, // 4 inputs
	output		O);
	
	wire 	w1, w2, w3, w4, w5, w6;
	
	// First level
	and		g1 (w1, I[0], I[1]);
	or			g2 (w2, I[0], I[1]);
	and		g3 (w3, I[2], I[3]);
	or			g4 (w4, I[2], I[3]);
	
	// Second level
	and		g5 (w5, w1, w4);
	and		g6 (w6, w2, w3);
	
	// Third level
	or			g7 (O, w5, w6);
	
endmodule
	