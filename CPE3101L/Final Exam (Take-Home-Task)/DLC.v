// CPE 3101L - INTRODUCTION TO HDL
// Group 1                  F 7:30 - 10:30 AM LB285TC
// Final Exam (Take-Home-Task) 
// Dotillos, Jeff Thomas; Sarcol, Joshua        BS CpE - 3      2025/12/18

// Digital Lock Controller (DLC)
// Design a Verilog module for a digital lock controller that accepts two inputs, X and Y,
// and controls the UNLOCK actuator output. The module must implement a Finite State Machine
// (FSM) to detect the specific input sequence X -> Y -> X -> X -> Y. The logic must be
// designed to handle variable timing: each step in the sequence is valid as long as the input
// is held for at least one clock cycle, and the system must maintain its current state 
// (without resetting) if both inputs go low for any number of cycles between valid sequence
// elements. Upon successful observation of the full sequence, the UNLOCK output should be
// asserted high and the GREEN light indicator should also be asserted high. The system must
// remain in the unlocked state (GREEN light is off) until a change occurs on either input
// or when LOCK is asserted: any subsequent transition on X or Y or trigger in LOCK must
// immediately cause UNLOCK and GREEN to go low, and reset the detection logic. The nRESET
// will also reset the detection logic. 

module DLC #(parameter oldHz = 50_000_000, newHz = 1, stateView = 1)    (
    input wire          CLK, nRESET, X, Y, LOCK,
    output reg          UNLOCK, GREEN,
    output wire [3:0]   oCSTATE, oNSTATE,                                
    output wire         oclk_div                                        );
    
// Clock divider logic
    // New divided clock
    reg clk_div;

    // Counter
    reg [25:0] cntr;    // (50,000,000 / 2) < 2^26
    
    // Comparator for half of the counter states
    wire cmpr;
    assign cmpr = (cntr == (oldHz / (newHz * 2)) - 1);
    
    // Initialize to 0
    initial begin
        clk_div = 1'b0;
        cntr = 26'b0;
    end
    
    // Counter increment and reset logic
    always @(negedge CLK)
        // Reset if counter reached half of the counter states
        if (cmpr)   cntr <= 26'b0;
        // Otherwise increment counter by 1
        else        cntr <= cntr + 1'b1;
    
    // 2 full comparator hits == 1 full period
    always @(negedge CLK)
        if (cmpr)   clk_div <= !clk_div;
    
// FSM logic    
    // Internal declaration for state machine viewer
    reg [3:0]   cstate, nstate;
    
    // For-convenience declarations
    wire [1:0]   inputs;
    assign inputs = {X, Y};
    localparam zz = 2'b00, xx = 2'b10, yy = 2'b01, aa = 2'b11;
    
    // State encoding
    localparam S  = 4'b0000;
    localparam A1 = 4'b0001, A2 = 4'b0010, B1 = 4'b0011, B2 = 4'b0100;
    localparam C1 = 4'b0101, C2 = 4'b0110, D1 = 4'b0111, D2 = 4'b1000;
    localparam U1 = 4'b1001, U2 = 4'b1010;
    
    // State transitions
    always @(negedge clk_div, negedge nRESET)
        // Asyncronous reset (condition is triggered immediately)
        if (!nRESET)        cstate <= S;
        // Syncronous reset (condition is triggered only after negedge clk_div)
        else if (LOCK)      cstate <= S;
        // Otherwise, proceed normally
        else                cstate <= nstate;
    
    // Next state assignments
    always @(cstate, inputs)
        case (cstate)
            S:  case (inputs)       // Starting state
                    xx:         nstate <= A1;
                    default:    nstate <= S ;
                endcase
            A1: case (inputs)       // X
                    zz:         nstate <= A2;
                    xx:         nstate <= A1;
                    default:    nstate <= S ;
                endcase
            A2: case (inputs)
                    yy:         nstate <= B1;
                    zz:         nstate <= A2;
                    default:    nstate <= S ;
                endcase
            B1: case (inputs)       // X -> Y
                    zz:         nstate <= B2;
                    yy:         nstate <= B1;
                    default:    nstate <= S ;
                endcase
            B2: case (inputs)
                    xx:         nstate <= C1;
                    zz:         nstate <= B2;
                    default:    nstate <= S ;
                endcase
            C1: case (inputs)       // X -> Y -> X
                    zz:         nstate <= C2;
                    xx:         nstate <= C1;
                    default:    nstate <= S ;
                endcase
            C2: case (inputs)
                    xx:         nstate <= D1;
                    zz:         nstate <= C2;
                    default:    nstate <= S ;
                endcase
            D1: case (inputs)       // X -> Y -> X -> X
                    zz:         nstate <= D2;
                    xx:         nstate <= D1;
                    default:    nstate <= S ;
                endcase
            D2: case (inputs)
                    yy:         nstate <= U1;
                    zz:         nstate <= D2;
                    default:    nstate <= S ;
                endcase
            U1, U2: case (inputs)   // X -> Y -> X -> X -> Y
                    yy:         nstate <= U2;
                    default:    nstate <= S ;
                endcase
            default:            nstate <= S ;
        endcase
    
    // Output assignments
    always @(*)
        case (cstate)
            U1:         begin UNLOCK <= 1'b1; GREEN <= 1'b1; end
            U2:         begin UNLOCK <= 1'b1; GREEN <= 1'b0; end
            default:    begin UNLOCK <= 1'b0; GREEN <= 1'b0; end
        endcase
    assign oCSTATE = (stateView) ? cstate : 4'b000;
    assign oNSTATE = (stateView) ? nstate : 4'b000;
    assign oclk_div = (stateView) ? clk_div : 1'b0;

endmodule
