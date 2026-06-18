// CPE 3101L - INTRODUCTION TO HDL
// Group 1                  F 7:30 - 10:30 AM LB285TC
// Lab Exercise #7
// Sarcol, Joshua S.        BS CpE - 3      2025/12/17

//
// Testbench file for Complex_Counter.v (unit test)
//
`timescale 1 ns / 1 ps
module tb_Complex_Counter();
    reg         iCLOCK, inRESET, iM;
    wire [2:0]  oCOUNT, onstate;
    wire        onew_clk;
    
    // 2x reduction in rate
    localparam simOldHz = 2, simNewHz = 1, div = (simOldHz/simNewHz);
    
    Complex_Counter #(simOldHz, simNewHz)
        UUT (iCLOCK, inRESET, iM, oCOUNT, onstate, onew_clk);
        
    // Initial values
    initial
        iCLOCK = 1'b0;
    
    // Clock generator
    always
        #2.5    iCLOCK = ~iCLOCK;
    
    // Test inputs
    initial begin
        $display("time | r M | cur nxt");
        $display("Initialize to 0");
        inRESET = 1'b0; iM = 1'b0;  #(10*div)
        
        $display("Count in Binary");
        inRESET = 1'b1;             #(50*div)
        
        $display("Count in Gray Code");
                        iM = 1'b1;  #(30*div)
                        
        $display("Reset count");
        inRESET = 1'b0;             #(10*div)           
        
        $display("Continue counting in Gray Code");
        inRESET = 1'b1;             #(8*div)
        
        $display("Switch to Binary");
                        iM = 1'b0;  #(8*div)
        
        $display("Simulation finished at %0d ns", $time);
        $stop;
    end
    
    // Monitor display
    // Change of input
    always @(inRESET, iM)
        #0.1 $display(" %3d | %1b %1b | %3b %3b", $time - 0.1, inRESET, iM, oCOUNT, onstate);
    
    // Clock pulse
    always @(negedge onew_clk)
        #0.1 $display(" %3d | %1b %1b > %3b %3b", $time - 0.1, inRESET, iM, oCOUNT, onstate);
    
endmodule
