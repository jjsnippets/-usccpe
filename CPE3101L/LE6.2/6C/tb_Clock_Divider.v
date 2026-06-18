// CPE 3101L - INTRODUCTION TO HDL
// Group 1      F 7:30 - 10:30 AM LB285TC
// Lab Exercise #6.2
// Sarcol, Joshua S.        BS CpE - 3      2025/11/14

// 
// Testbench file for Clock_Divider.v (unit test)
// 
`timescale 1 ns / 1 ps
module tb_Clock_Divider ();
    reg         iClock_in, inReset, iClk;
    wire            oClock_out;

    localparam simOldHz = 10, simNewHz = 1, div = (simOldHz/simNewHz);  // 10x reduction in rate
    
    Clock_Divider #(simOldHz, simNewHz) UUT (iClock_in, inReset, iClk, oClock_out);

    // initial value for clock
    initial
        iClock_in = 1'b0;
    
    // clock generator
    always
        #2.5    iClock_in = ~iClock_in;
        
    // test inputs
    initial begin
        $display("time | rst clk | out");
        $display("Reset to 0");
        inReset = 0;        iClk = 1;                   #(5*div)
        
        $display("Enable Clock Divide");
        inReset = 1;        iClk = 1;                   #(10*div)
        
        $display("Disable Clock Divide");
        inReset = 1;        iClk = 0;                   #(2*div)
        
        $display("Reenable Clock Divide");
        inReset = 1;        iClk = 1;                   #(10*div)
        
        $display("Simulation finished at %0d ns", $time);
        $stop;
    end
    
    // monitor display
    // print for each change of input
    always @(inReset, iClk)
        #0.1 $display(" %3d |   %1b   %1b |   %1b", $time - 0.1, inReset, iClk, oClock_out);
    
    // indicate change in clock output by >
    always @(oClock_out)
        #0.1 $display(" %3d |   %1b   %1b >   %1b", $time - 0.1, inReset, iClk, oClock_out);
        
endmodule

