
clear
clc

syms t s q1(t) Q1(s) q2(t) Q2(s) vin(t) Vin(s) vout(t) Vout(s)

% time domain kvl
v1 = vin == 5E5*diff(q1, t) + (1/2E-6)*q1;
v2 = -vout == 1E5*diff(q2, t) + (1/2E-6)*q2;

% time domain kcl
kcl = diff(q1,t) - diff(q2,t) == 0;

% perform laplace transform
V1 = laplace(v1, t, s);
V2 = laplace(v2, t, s);
KCL = laplace(kcl, t, s);

% substitue transforms
V1 = subs(V1, laplace(vin(t), t, s), Vin);
V1 = subs(V1, laplace(q1(t), t, s), Q1);
V2 = subs(V2, laplace(vout(t), t, s), Vout);
V2 = subs(V2, laplace(q2(t), t, s), Q2);
KCL = subs(KCL, laplace(q1(t), t, s), Q1);
KCL = subs(KCL, laplace(q2(t), t, s), Q2);

% zero initial conditions
V1 = subs(V1, q1(0), 0);
V2 = subs(V2, q2(0), 0);
KCL = subs(KCL, [q1(0), q2(0)], [0, 0]);

% solve for the charges
S1 = solve(V1, Q1);
S2 = solve(V2, Q2);

% enforce KCL
eqG = subs(KCL, [Q1(s), Q2(s)], [S1, S2]);

% transfer function G(s) = Vout(s))/Vin(s)
G = simplifyFraction(solve(eqG, Vout(s))/Vin(s));
pretty(G)
