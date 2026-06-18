// CPE 3101L - INTRODUCTION TO HDL
// Group 1                  F 7:30 - 10:30 AM LB285TC
// Lab Exercise #7
// Sarcol, Joshua S.        BS CpE - 3      2025/11/14

//
// Verilog HDL code for a race light (Mealy)
// Negative edge triggered, active low syncronous reset
//
module Race_Lights #(parameter oldHz = 50_000_000, newHz = 1)   (
    input wire          CLOCK, nRESET, START,       // Light assignments:
    output reg [2:0]    lights,                     // RED    = lights[2]
    output wire [2:0]   cstate, nstate,             // YELLOW = lights[1]
    output wire         new_clk                 );  // GREEN  = lights[0]
    
    // Internal declaration for state machine viewer
    reg [2:0]   CSTATE, NSTATE;
    
    // Divided clock signal
    clkdiv_negedge #(oldHz, newHz)
        clk_div (CLOCK, new_clk);

    // State parmeters
    localparam A = 3'b000;
    localparam B = 3'b001;
    localparam C = 3'b010;
    localparam D = 3'b011;
    localparam E = 3'b100;
    localparam F = 3'b101;
    localparam G = 3'b110;
    
    // State transistions
    always  @(negedge new_clk, negedge nRESET)
        if (!nRESET)    CSTATE <= A;
        else            CSTATE <= NSTATE;
    
    // Next state transitions
    always @(*)
        case (CSTATE)
            A:          NSTATE <= (START) ? B : A;
            B:          NSTATE <=           C    ;
            C:          NSTATE <=           D    ;
            D:          NSTATE <=           E    ;
            E:          NSTATE <=           F    ;
            default:    NSTATE <=           A    ;
        endcase
    
    // Output assignments
    always @(*)
        case (CSTATE)
            A:          lights <= 3'b100;
            B:          lights <= 3'b100;
            C:          lights <= 3'b010;
            D:          lights <= 3'b001;
            E:          lights <= 3'b001;
            F:          lights <= 3'b001;
            default:    lights <= 3'b100;
        endcase
    
    assign cstate = CSTATE;
    assign nstate = NSTATE;
    
endmodule
