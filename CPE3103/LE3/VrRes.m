% CPE 3103 - FUNDAMENTALS OF MIXED SIGNALS AND SENSORS
% Group 1   MW 10:30 AM - 1:30 PM LBCEAC2 TC
% Sarcol, Joshua S      BS-CpE 3        2025/09/24
% Laboratory Exercise 3 (Item 5)

% Output response VR(t) via superposition of individual responses
clear
clc

% time in y-axis
t = -5:0.01:20;

% VR = R*q'(t)
VR = 0.4 .* (ImpulseRes(t+1) + StepRes(t) - StepRes(t-1) - StepRes(t-2) ...
              + StepRes(t-3) - ImpulseRes(t-4));

% plot output
plot(t, VR)
title("Voltage across the resistor VR(t) using input response Vin(t)")
xlabel("q(t)")
ylabel("time [seconds]")
grid on
