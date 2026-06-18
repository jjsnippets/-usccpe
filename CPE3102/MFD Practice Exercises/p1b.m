
clear
clc

syms s V(s) I1(s) I2(s) I3(s)

% s-domain equations
E1 = (s^2 + 7*s + 5)*I1 - (s^2 + 2*s)*I2 - (5*s)*I3 == s*V;
E2 = -(s^2 + 2*s)*I1 + (2*s^2 + 4*s + 3)*I2 - (s + 2)*I3 == 0;
E3 = -5*s*I1 - (s^2 + 2*s)*I2 + (s^2 + 8*s + 4)*I3 == 0;

% put coefficients into a matrix
[As, bs] = equationsToMatrix([E1, E2, E3], [I1(s), I2(s), I3(s)]);

% solve for X1(s), X2(s), X3(s)
sol = linsolve(As, bs);

% transfer function G(s) = I1(s)/V(s)
G = simplifyFraction(sol(1)/V(s));
pretty(G)
