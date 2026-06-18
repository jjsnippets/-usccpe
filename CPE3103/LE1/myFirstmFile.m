% CPE 3103 - FUNDAMENTALS OF MIXED SIGNALS AND SENSORS
% Group 1   MW 10:30 AM - 1:30 PM LBCEAC2 TC
% Sarcol, Joshua S      BS-CpE 3        2025/09/03
% Laboratory Exercise 1

clc
clear

disp("Hello World!");

matA = rand(4);
matA .* 3

t = 0:0.5:10;
y = cos(t * pi);
plot(t, y)