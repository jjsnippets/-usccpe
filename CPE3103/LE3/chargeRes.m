% CPE 3103 - FUNDAMENTALS OF MIXED SIGNALS AND SENSORS
% Group 1   MW 10:30 AM - 1:30 PM LBCEAC2 TC
% Sarcol, Joshua S      BS-CpE 3        2025/09/24
% Laboratory Exercise 3 (Item 5)

% Output response q(t) via superposition of individual responses
clear
clc

% time in y-axis
t = -5:0.01:20;

% superposition of individual elementary signals
q = StepRes(t+1) + RampRes(t) - RampRes(t-1) - RampRes(t-2) ...
     + RampRes(t-3) - StepRes(t-4);

plot(t, q)
title("Output response q(t) using input response Vin(t)")
xlabel("q(t)")
ylabel("time [seconds]")
grid on
