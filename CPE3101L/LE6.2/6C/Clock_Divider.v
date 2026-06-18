// CPE 3101L - INTRODUCTION TO HDL
// Group 1      F 7:30 - 10:30 AM LB285TC
// Lab Exercise #6.2
// Sarcol, Joshua S.        BS CpE - 3      2025/11/14

//
// Verilog HDL code for a Clock Divider Circuit
// negative edge triggered, active low asyncronous reset
//
module Clock_Divider #(parameter oldHz = 50_000_000, newHz = 2) ( // Maximum clock cycle count to be divided by
    input wire          Clock_in, nReset, Clk,
    output reg          Clock_out                                       );
    
    //
    // Clock divider logic
    // Assuming maximum frequency is 50MHz
    //
    
    // Counter
    reg [25:0] cntr;        // (50,000,000 / 2) < 2^26
    
    // Comparator for half of the counter states
    wire cmpr;
    assign cmpr = (cntr == (oldHz / (newHz * 2)) - 1);
     
    // Counter increment and reset logic
    always @(posedge Clock_in, negedge nReset)
    begin
        if (!nReset)        // asyncronous reset
            cntr <= 26'b0;
        else if (cmpr)      // reset if counter reached half of the counter states
            cntr <= 26'b0;
        else                // increment by 1
            cntr <= cntr + 1'b1;
    end
    
    // new clock frequency generator
    reg divided_clock;
    
    // 2 full comparator hits == 1 full period
    always @(posedge Clock_in, negedge nReset)
    begin
        if (!nReset)
            divided_clock <= 1'b0;
        else if (cmpr)
            divided_clock <= !divided_clock;
    end
    
    always @(*)
    begin
        Clock_out = (!Clk) ? Clock_in : divided_clock;
    end

endmodule
