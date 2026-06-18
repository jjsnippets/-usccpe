
clear
clc

syms s

% s-domain impedances
Z1 = 1 + 5/s;
Z2 = 1 + 1/(1 + s/5);

% transfer function G(s) = -Z2(s)/Z1(s)
G = simplify(-Z2/Z1);
pretty(G)