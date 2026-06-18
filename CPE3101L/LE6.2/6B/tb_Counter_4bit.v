// CPE 3101L - INTRODUCTION TO HDL
// Group 1      F 7:30 - 10:30 AM LB285TC
// Lab Exercise #6.2
// Sarcol, Joshua S.        BS CpE - 3      2025/11/14

// 
// Testbench file for Counter_4bit.v (unit test)
// 
`timescale 1 ns / 1 ps
module tb_Counter_4bit ();
    reg         iClk, inReset, iLoad, iCount_en, iUp;
    reg [3:0]   iCount_in;
    wire [3:0]  oCount_out;
    wire        oclk_div;

    localparam simOldHz = 10, simNewHz = 1, div = (simOldHz/simNewHz);  // 10x reduction in rate
    
    Counter_4bit #(simOldHz, simNewHz) UUT (iClk, inReset, iLoad, iCount_en, iUp, iCount_in, oCount_out, oclk_div);

    // initial value for clock
    initial
        iClk = 1'b0;
    
    // clock generator
    always
        #2.5    iClk = ~iClk;
        
    // test inputs
    initial begin
        $display(" time | rst ld en up   in |  out");
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
    always @(inReset, iLoad, iCount_en, iUp)
        #0.1 $display(" %4d |   %1b  %1b  %1b  %1b %4b | %4b", $time - 0.1, inReset, iLoad, iCount_en, iUp, iCount_in, oCount_out);
    
    // indicate falling-edge divided clock by >
    always @(negedge oclk_div)
        #0.1 $display(" %4d |   %1b  %1b  %1b  %1b %4b > %4b", $time - 0.1, inReset, iLoad, iCount_en, iUp, iCount_in, oCount_out);
        
endmodule
