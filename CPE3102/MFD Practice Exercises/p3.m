
clear
clc

syms t s x1(t) X1(s) x2(t) X2(s) x3(t) X3(s) f(t) F(s)

% system of equations (m1 and m2 are massless nodes)
m1 = f(t) == 2*x1 - 2*x2;
m2 = 0 == -2*x1 + 2*x2 + 4*diff(x2,t) - 4*diff(x3,t);
m3 = 0 == -4*diff(x2,t) + 4*diff(x3,t) + 8*diff(x3,t,2) + 2*diff(x3,t);

% perform laplace transform
M1 = laplace(m1, t, s);
M2 = laplace(m2, t, s);
M3 = laplace(m3, t, s);

% substitute transforms
M1 = subs(M1, laplace(x1(t),t,s), X1(s));
M1 = subs(M1, laplace(x2(t),t,s), X2(s));
M1 = subs(M1, laplace(f(t),t,s), F(s));
M2 = subs(M2, laplace(x1(t),t,s), X1(s));
M2 = subs(M2, laplace(x2(t),t,s), X2(s));
M2 = subs(M2, laplace(x3(t),t,s), X3(s));
M3 = subs(M3, laplace(x2(t),t,s), X2(s));
M3 = subs(M3, laplace(x3(t),t,s), X3(s));

% zero initial conditions
M1 = subs(M1, [x1(0), x2(0)], [0,0]);
M2 = subs(M2, [x1(0), x2(0), x3(0), subs(diff(x2(t),t),t,0), subs(diff(x3(t),t),t,0)], [0,0,0,0,0]);
M3 = subs(M3, [x2(0), x3(0), subs(diff(x2(t),t),t,0), subs(diff(x3(t),t),t,0)], [0,0,0,0]);

% put coefficients into a matrix
[As, bs] = equationsToMatrix([M1, M2, M3], [X1(s), X2(s), X3(s)]);

% solve for X1(s), X2(s), X3(s)
sol = linsolve(As, bs);

% transfer function G(s) = X2(s)/F(s)
G = simplifyFraction(sol(2)/F(s));
pretty(G)
