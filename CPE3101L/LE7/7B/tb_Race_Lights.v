// CPE 3101L - INTRODUCTION TO HDL
// Group 1                  F 7:30 - 10:30 AM LB285TC
// Lab Exercise #7
// Sarcol, Joshua S.        BS CpE - 3      2025/12/17

//
// Testbench file for Race_Lights.v (unit test)
//
`timescale 1 ns / 1 ps
module tb_Race_Lights ();
    reg         iCLOCK, inRESET, iSTART;
    wire [2:0]  olights, ocstate, onstate;
    wire        onew_clk;
    
    // 2x reduction in rate
    localparam simOldHz = 2, simNewHz = 1, div = (simOldHz/simNewHz);
    
    Race_Lights #(simOldHz, simNewHz)
        UUT (iCLOCK, inRESET, iSTART, olights, ocstate, onstate, onew_clk);
    
    // Initial values
    initial
        iCLOCK = 1'b0;
        
    // Clock generator
    always
        #2.5    iCLOCK = ~iCLOCK;
        
    // Test inputs
    initial begin
        $display("time | r S | RYG cur nxt ");
        $display("Initialize to 0");
        inRESET = 1'b0; iSTART = 1'b0;  #(8*div)
        
        $display("Enable START");
        inRESET = 1'b1; iSTART = 1'b1;  #(40*div)
        
        $display("Force Reset");
        inRESET = 1'b0;                 #(10*div)
        
        $display("Unhold Reset");
        inRESET = 1'b1;                 #(20*div) 
        
        $display("Disable START");
                        iSTART = 1'b0;  #(20*div)
        
        $display("Simulation finished at %0d ns", $time);
        $stop;
    end
    
    // Monitor display
    // Change of input
    always @(inRESET, iSTART)
        #0.1 $display(" %3d | %1b %1b | %3b %3b %3b", $time - 0.1, inRESET, iSTART, olights, ocstate, onstate);
    
    // Clock pulse
    always @(negedge onew_clk)
        #0.1 $display(" %3d | %1b %1b > %3b %3b %3b", $time - 0.1, inRESET, iSTART, olights, ocstate, onstate);

endmodule
