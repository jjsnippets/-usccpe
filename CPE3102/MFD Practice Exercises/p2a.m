
clear
clc

syms s

% s-domain equations
Z1 = 5 + 5/s;
Z2 = 1 + 5/s;

% transfer function G(s) = -Z2(s)/Z1(s)
G = simplify(-Z2/Z1);
pretty(G)
