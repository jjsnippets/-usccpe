// CPE 3101L - INTRODUCTION TO HDL
// Group 1      F 7:30 - 10:30 AM LB285TC
// Lab Exercise #6.2
// Sarcol, Joshua S.        BS CpE - 3      2025/11/14

//
// Verilog HDL code for a JK Flip-flop
// negative edge triggered, active high asyncronous reset
//
module JK_FF #(parameter oldHz = 50_000_000, newHz = 2) (
    input wire J, K, Reset, Clk,
    output reg Q,
    output wire Q_bar, div_clock                        );
    
    Clock_Divider #(oldHz, newHz) CDiv (Clk, !Reset, 1, div_clock);
                                            // disable bypass functionality 

    //
    // JK Flip-flop logic
    //
    assign Q_bar = ~Q;
    
    always @(negedge div_clock, posedge Reset)
    begin
        if (Reset)          // asyncronous reset
            Q <= 1'b0;  
        else                // JK flip-flop characteristic equation
            Q <= (J & ~Q) | (~K & Q);
    end
endmodule
