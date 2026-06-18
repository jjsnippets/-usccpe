// CPE 3101L - INTRODUCTION TO HDL
// Group 1                  F 7:30 - 10:30 AM LB285TC
// Final Exam (Take-Home-Task) 
// Dotillos, Jeff Thomas; Sarcol, Joshua        BS CpE - 3      2025/12/18

//
// Testbench file for DLC.v (unit test)
//
`timescale 1 ns / 1 ps
module tb_DLC ();
    reg         iCLK, inRESET, iX, iY, iLOCK;
    wire        oUNLOCK, oGREEN;
    wire [3:0]  oCSTATE, oNSTATE;                                
    wire        oclk_div;
    
    // 2x reduction in rate
    localparam simOldHz = 2, simNewHz = 1, div = (simOldHz/simNewHz);
    
    DLC #(simOldHz, simNewHz, 1)
        UUT (iCLK, inRESET, iX, iY, iLOCK, oUNLOCK, oGREEN, oCSTATE, oNSTATE, oclk_div);
    
    // Initial values
    initial
        iCLK = 1'b0;
    
    // Clock generator
    always
        #2.5    iCLK = ~iCLK;
        
    // Test inputs
    initial begin
        $display("time | r L X Y | U G curr next");
        $display("Initialize to 0");
        inRESET = 1'b0; iLOCK = 1'b0;
        iX = 1'b0;      iY = 1'b0;      #(5*div)
        
        $display("Enable sequence detection logic");
        inRESET = 1'b1;                 #(5*div)
        
        $display("Correct sequence: X -> Y -> X -> X -> Y");
        iX = 1'b1;      iY = 1'b0;      #(6*div)    // X
        iX = 1'b0;      iY = 1'b0;      #(6*div)
        iX = 1'b0;      iY = 1'b1;      #(6*div)    // Y
        iX = 1'b0;      iY = 1'b0;      #(6*div)
        iX = 1'b1;      iY = 1'b0;      #(6*div)    // X
        iX = 1'b0;      iY = 1'b0;      #(6*div)
        iX = 1'b1;      iY = 1'b0;      #(6*div)    // X
        iX = 1'b0;      iY = 1'b0;      #(6*div)
        iX = 1'b0;      iY = 1'b1;      #(12*div)   // Y
        iX = 1'b0;      iY = 1'b0;      #(6*div)    // Y

        $display("Incorrect sequence: X -> Y -> Y -> X");
        iX = 1'b1;      iY = 1'b0;      #(6*div)    // X
        iX = 1'b0;      iY = 1'b0;      #(6*div)
        iX = 1'b0;      iY = 1'b1;      #(6*div)    // Y
        iX = 1'b0;      iY = 1'b0;      #(6*div)
        iX = 1'b0;      iY = 1'b1;      #(6*div)    // X
        iX = 1'b0;      iY = 1'b0;      #(6*div)
        iX = 1'b1;      iY = 1'b0;      #(6*div)    // X
        iX = 1'b0;      iY = 1'b0;      #(12*div)
        
        $display("LOCK as syncronous reset");
        iLOCK = 1'b1;                   #(6*div)
        iLOCK = 1'b0;                   #(6*div)
        
        $display("Incomplete sequence: X -> Y");
        iX = 1'b1;      iY = 1'b0;      #(6*div)    // X
        iX = 1'b0;      iY = 1'b0;      #(6*div)
        iX = 1'b0;      iY = 1'b1;      #(6*div)    // Y
        iX = 1'b0;      iY = 1'b0;      #(6*div)

        $display("nRESET as asyncronous reset");
        inRESET = 1'b0;                 #(6*div)        
           
        $display("Simulation finished at %0d ns", $time);
        $stop;    
    end
          
    // Monitor display
    // Change of input
    always @(inRESET, iX, iY, iLOCK)
        #0.1 $display(" %3d | %1b %1b %1b %1b | %1b %1b %4b %4b",
                $time - 0.1, inRESET, iLOCK, iX, iY, oUNLOCK, oGREEN, oCSTATE, oNSTATE);
    
    // Clock pulse
    always @(negedge oclk_div)
        #0.1 $display(" %3d | %1b %1b %1b %1b > %1b %1b %4b %4b",
                $time - 0.1, inRESET, iLOCK, iX, iY, oUNLOCK, oGREEN, oCSTATE, oNSTATE);
    
endmodule
