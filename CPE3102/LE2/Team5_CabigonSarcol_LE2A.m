% CPE 3102 - FEEDBACK AND CONTROL SYSTEMS
% Group 3   TTh 10:30 AM - 1:30 PM LB265 TC
% Cabigon, Timothy Chad; Sarcol, Joshua      BS-CpE 3        2025/09/11
% LE2 | Symbolic Math and LTI system Analysis in MATLAB

clear
clc

syms x(t) X(s)

%% Equation 1
eqn1 = diff(x, t, 2) + 6 * diff(x, t) + 8 * x == 6 * sin(4*t)

% perform laplace transform
eqn1LT = laplace(eqn1)
eqn1LT = subs(eqn1LT, laplace(x(t), t, s), X(s))

% initial conditions 0
eqn1LT = subs(eqn1LT, x(0), 0);
eqn1LT = subs(eqn1LT, subs(diff(x(t), t), t, 0), 0)

% solve for X(s)
eqn1LTsol = solve(eqn1LT, X(s))

% perform the inverse transform
xt1 = ilaplace(eqn1LTsol)
pretty(xt1)

%% Equation 2
eqn2 = diff(x, t, 2) + 8 * diff(x, t) + 25 * x == 10

% perform laplace transform
eqn2LT = laplace(eqn2)
eqn2LT = subs(eqn2LT, laplace(x(t), t, s), X(s))

% initial conditions 0
eqn2LT = subs(eqn2LT, x(0), 0);
eqn2LT = subs(eqn2LT, subs(diff(x(t), t), t, 0), 0)

% solve for X(s)
eqn2LTsol = solve(eqn2LT, X(s))

% perform the inverse transform
xt2 = ilaplace(eqn2LTsol)
pretty(xt2)