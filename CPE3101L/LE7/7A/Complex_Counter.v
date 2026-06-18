// CPE 3101L - INTRODUCTION TO HDL
// Group 1                  F 7:30 - 10:30 AM LB285TC
// Lab Exercise #7
// Sarcol, Joshua S.        BS CpE - 3      2025/11/14

//
// Verilog HDL code for a 3-bit binary/gray counter (Moore)
// Negative edge triggered, active low syncronous reset
//
module Complex_Counter #(parameter oldHz = 50_000_000, newHz = 1)   ( 
    input wire          CLOCK, nRESET, M,
    output wire [2:0]   COUNT, NCOUNT,
    output wire         new_clk                                     );
    
    // Internal declaration for state machine viewer
    reg [2:0]   cstate, nstate;
    
    // Divided clock signal
    clkdiv_negedge #(oldHz, newHz)
        clk_div (CLOCK, new_clk);
    
    // State transitions
    always  @(negedge new_clk)
        if (!nRESET)    cstate <= 3'b000;
        else            cstate <= nstate;
    
    // Next state assignments
    // M == 0: binary sequence
    // M == 1: gray code sequence
    always @(*)
        case (cstate)
            3'b000:     nstate <=       3'b001         ;
            3'b001:     nstate <= (M) ? 3'b011 : 3'b010;
            3'b010:     nstate <= (M) ? 3'b110 : 3'b011;
            3'b011:     nstate <= (M) ? 3'b010 : 3'b100;
            3'b100:     nstate <= (M) ? 3'b000 : 3'b101;
            3'b101:     nstate <= (M) ? 3'b100 : 3'b110;
            3'b110:     nstate <=       3'b111         ;
            default:    nstate <= (M) ? 3'b101 : 3'b000;
        endcase
    
    // Output assignments
    assign COUNT = cstate;
    assign NCOUNT = nstate;
    
endmodule
