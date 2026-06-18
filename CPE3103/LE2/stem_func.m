% CPE 3103 - FUNDAMENTALS OF MIXED SIGNALS AND SENSORS
% Group 1   MW 10:30 AM - 1:30 PM LBCEAC2 TC
% Sarcol, Joshua S      BS-CpE 3        2025/09/10
% Laboratory Exercise 2 (Item 6)

% Item 6A
n = -4:5;
y = [-3 -1 -1 0 1 1 2 2 -1 1];

stem(n, y);

% Item 6B
nf = floor(n/2);
ny = y(nf + 5);

figure;
stem(n, ny);