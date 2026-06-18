// CPE 3101L - INTRODUCTION TO HDL
// Group 1      F 7:30 - 10:30 AM LB285TC
// Lab Exercise #6.2
// Sarcol, Joshua S.        BS CpE - 3      2025/11/14

// 
// Testbench file for Hex_Counter.v (unit test)
// Minimally modified test of Counter_4bit.v 
// 
`timescale 1 ns / 1 ps
module tb_Hex_Counter ();
    reg         iClk, inReset, iLoad, iCount_en, iUp, iDP;
    reg [3:0]   iCount_in;
    wire [7:0]  oSSeg;
    wire        odiv_clock;
    
    // 10x reduction in rate
    localparam simOldHz = 10, simNewHz = 1, div = (simOldHz/simNewHz);
    
    Hex_Counter #(simOldHz, simNewHz)
        UUT (iClk, inReset, iLoad, iCount_en, iUp, iDP, iCount_in, oSSeg, odiv_clock);
    
    // initial values for clock and decimal point
    initial begin
        iClk = 1'b0;
        iDP = 1'b0;
    end
    
    // clock generator
    always
        #2.5            iClk = ~iClk;
    
    // decimal point toggle every now and then
    always
        #(8*div)        iDP = ~iDP;
        
    // test inputs
    initial begin
        $display(" time | rst ld en up DP   in |      out");
        $display("Initialize to 0");
        inReset = 1'b0; iLoad = 1'b0;   iCount_en = 1'b1;   iUp = 1'b1; iCount_in = 4'b0000;
        #(3*div)
        
        $display("Count up");
        inReset = 1'b1;                                 #(12*div)
        
        $display("Pause counting");
        iCount_en = 1'b0;                               #(7*div)
        $display("Resume counting");
        iCount_en = 1'b1;                               #(5*div)
        
        $display("Load value close to maximum");
        iLoad = 1'b1;       iCount_in = 4'b1101;        #(4*div)
        iLoad = 1'b0;                                   #(25*div)
        
        $display("Reset to 0");
        inReset = 1'b0;                                 #(3*div)
        inReset = 1'b1;                                 #(7*div)
        
        $display("Count down");
        iUp = 1'b0;                                     #(13*div)
        
        $display("Pause counting");
        iCount_en = 1'b0;                               #(5*div)
        $display("Resume counting");
        iCount_en = 1'b1;                               #(12*div)
        
        $display("Load value");
        iLoad = 1'b1;       iCount_in = 4'b0110;        #(5*div)
        iLoad = 1'b0;                                   #(14*div)
        
        $display("Simulation finished at %0d ns", $time);
        $stop;
    end
    
    // monitor display
    // print for each change of input
    always @(inReset, iLoad, iCount_en, iUp, iDP)
        #0.1 $display(" %4d |   %1b  %1b  %1b  %1b  %1b %4b | %8b", $time - 0.1, inReset, iLoad, iCount_en, iUp, iDP, iCount_in, oSSeg);
    
    // indicate falling-edge divided clock by >
    always @(negedge odiv_clock)
        #0.1 $display(" %4d |   %1b  %1b  %1b  %1b  %1b %4b > %8b", $time - 0.1, inReset, iLoad, iCount_en, iUp, iDP, iCount_in, oSSeg);
        
endmodule

