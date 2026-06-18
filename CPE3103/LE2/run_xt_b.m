% CPE 3103 - FUNDAMENTALS OF MIXED SIGNALS AND SENSORS
% Group 1   MW 10:30 AM - 1:30 PM LBCEAC2 TC
% Sarcol, Joshua S      BS-CpE 3        2025/09/10
% Laboratory Exercise 2 (Item 5)

% plots the function xt(-(t - 1) / 2)
t = -7 : 0.001 : 7;
x = zeros(size(t));

tm = (t - 1) .* -0.5;   % "re-mapped" values of t to -(t - 1) / 2

for i = 1:1:length(x)
    x(i) = xt(tm(i));   % indexing from mapped values
end

plot(t, x);
axis equal;
grid on;
