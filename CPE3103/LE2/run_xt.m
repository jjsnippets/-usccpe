% CPE 3103 - FUNDAMENTALS OF MIXED SIGNALS AND SENSORS
% Group 1   MW 10:30 AM - 1:30 PM LBCEAC2 TC
% Sarcol, Joshua S      BS-CpE 3        2025/09/10
% Laboratory Exercise 2 (Item 3C)

% original code as dictated by the lab exercise
t = -5 : 0.001 : 5;
x = zeros(size(t));

for i = 1:1:length(x)
    x(i) = xt(t(i));
end

plot(t, x);
axis equal;
grid on;
