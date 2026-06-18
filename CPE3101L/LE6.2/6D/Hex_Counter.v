// CPE 3101L - INTRODUCTION TO HDL
// Group 1      F 7:30 - 10:30 AM LB285TC
// Lab Exercise #6.2
// Sarcol, Joshua S.        BS CpE - 3      2025/11/14

//
// Verilog HDL code for a up-down Hexadecimal digit counter
// combination of #5A and #6B
//
module Hex_Counter #(parameter oldHz = 50_000_000, newHz = 2)   (
    input wire          Clk, nReset, Load, Count_en, Up, DP,
    input wire [3:0]    Count_in,
    output wire [7:0]   SSeg,   // A-B-C_D-E-F_G_DP
    output wire         div_clock                                           );
    
    wire [3:0]  Count_out;      // internal wire from counter to display
    
    // 4-bit counter module (from #6B)
    Counter_4bit #(oldHz, newHz)
        cntr (Clk, nReset, Load, Count_en, Up, Count_in, Count_out, div_clock);
        
    // 7-segment display module (from #5A)
    Hex_to_7Seg_Anode
        disp (Count_out, DP, SSeg);

endmodule
    
    
    
