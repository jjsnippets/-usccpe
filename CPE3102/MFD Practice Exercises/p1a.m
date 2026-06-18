
clear
clc

syms s V(s) I1(s) I2(s) I3(s)

% s-domain equations
E1 = (2*s + 2)*I1(s) - I2(s) - (2*s + 1)*I3(s) == V(s);
E2 = -2*s*I1(s) + (6*s^2 + 6*s + 9)*I2(s) - (6*s^2 + 4*s)*I3(s) == 0;
E3 = -(2*s + 1)*I1(s) - (3*s + 2)*I2(s) + (5*s + 7)*I3(s) == 0;

% put coefficients into a matrix
[As, bs] = equationsToMatrix([E1, E2, E3], [I1(s), I2(s), I3(s)]);

% solve for X1(s), X2(s), X3(s)
sol = linsolve(As, bs);

% transfer function G(s) = Vo(s)/V(s)
G = simplifyFraction(8 * sol(3)/V(s));
pretty(G)
