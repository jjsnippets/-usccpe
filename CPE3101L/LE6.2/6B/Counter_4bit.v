// CPE 3101L - INTRODUCTION TO HDL
// Group 1      F 7:30 - 10:30 AM LB285TC
// Lab Exercise #6.2
// Sarcol, Joshua S.        BS CpE - 3      2025/11/14

//
// Verilog HDL code for a 4-bit binary up/down counter
// negative edge triggered, active low asyncronous reset
//
module Counter_4bit #(parameter oldHz = 50_000_000, newHz = 2)  (
    input wire          Clk, nReset, Load, Count_en, Up,
    input wire [3:0]    Count_in,
    output reg [3:0]    Count_out,
    output wire         div_clock                               );
    
    wire on;
    assign on = 1;              // disable bypass functionality 
    
    Clock_Divider #(oldHz, newHz) CDiv (Clk, nReset, on, div_clock);
    
    //
    // Counter logic
    //
    always @(negedge div_clock, negedge nReset)
    begin
        if (!nReset)                // asyncronous reset
            Count_out <= 4'b0000;
        else if (Load)              // load inputs
            Count_out <= Count_in;
        else if (Count_en & Up)     // count up
            Count_out <= Count_out + 1'b1;
        else if (Count_en & ~Up)    // count down
            Count_out <= Count_out - 1'b1;
                                    // else no change (latch)
    end
endmodule
