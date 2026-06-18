% CPE 3103 - FUNDAMENTALS OF MIXED SIGNALS AND SENSORS
% Group 1   MW 10:30 AM - 1:30 PM LBCEAC2 TC
% Sarcol, Joshua S      BS-CpE 3        2025/09/03
% Laboratory Exercise 1.a

clc
clear

%% 1a
A = [2 1 1;
     0 -3 4];

B = [3 -1 3;
     2 0 5];
no1a = A - B

%% 1b
A = [1 2;
     3 0];

B = [1 3;
    0 -4];

no1b = 3 * A - 2 * B

%% 1c
A = [2 1 1;
     0 -3 4];

B = [3 -1 3;
     2 0 5];

no1c = 5 * A - 2 * B

%% 2
A = [1 2;
     3 0];

B = [2 -1;
     3 4];

C = [2 -2;
     1 3;
     4 -1];

no2 = C * (A + B)

%% 3
no3 = C * A + C * B

%% 4
x = -2:0.01:2;
a = polyval([2 5 3], x);
b = polyval([1 0 0 4], x);

figure(1)
plot(x, a, "r")
hold on
plot(x, b, "b--")
legend(["y = x^2 + 5x + 3" "y = x^3 + 4"])
title("no4")
hold off

%% 5
figure(2)
subplot(2, 1, 1)
plot(x, a, "r")
title("y = x^2 + 5x + 3")

subplot(2, 1, 2)
plot(x, b, "r")
title("y = x^3 + 4")

sgtitle("no5")

%% 6a
p1 = [1 32 8 85 4 1 3 1];
no6a = roots(p1)

%% 6b
p2 = [3 -1 24 9 6 2];
no6b = roots(p2)

%% 6c
p3 = [1 77 11 1];
no6c = roots(p3)

%% 7a
no7a = conv(p1, p2)

%% 7b
no7b = conv(p1, p3)

%% 7c
no7c = conv(p2, p3)