
clear
clc

syms t s theta1(t) theta2(t) Tau(t) O1(s) O2(s) T(s)

% system of equations
j1 = 0 == 5*diff(theta1,t,2) + 9*diff(theta1,t) + 9*theta1 ...
           - diff(theta2,t) - 9*theta2;
j2 = Tau(t) == -diff(theta1,t) - 9*theta1 ...
                + 3*diff(theta2,t,2) + diff(theta2,t) + 12*theta2;

% perform laplace transform
J1 = laplace(j1, t, s);
J2 = laplace(j2, t, s);

% substitute transforms
J1 = subs(J1, laplace(theta1(t), t, s), O1(s));
J1 = subs(J1, laplace(theta2(t), t, s), O2(s));
J2 = subs(J2, laplace(theta1(t), t, s), O1(s));
J2 = subs(J2, laplace(theta2(t), t, s), O2(s));
J2 = subs(J2, laplace(Tau(t), t, s), T(s));

% zero initial conditions
J1 = subs(J1, [theta1(0), subs(diff(theta1(t),t), t, 0), theta2(0)], [0, 0, 0]);
J2 = subs(J2, [theta1(0), theta2(0), subs(diff(theta2(t),t), t, 0)], [0, 0, 0]);

% put coefficients into a matrix
[As, bs] = equationsToMatrix([J1, J2], [O1(s), O2(s)]);

% solve for O1(s) and O2(s)
sol = linsolve(As, bs);

% transform function G(s) = O1(s)/T(s)
G = simplifyFraction(sol(1)/T(s));
pretty(G)
