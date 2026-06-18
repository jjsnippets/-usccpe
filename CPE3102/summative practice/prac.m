
clc
clear

% syms s V I1 I2
% 
% eqn1 = s*V == (4*s + 4)*I1 - (2*s + 2)*I2;
% eqn2 = 0 == -(2*s + 2)*I1 + (2*s^2 + 4*s + 4)*I2;
% 
% sol = solve([eqn1, eqn2], [I1, I2]);
% 
% 
% I2 = simplify(sol.I2);
% 
% VL = 2*s*I2;
% 
% G = simplify(VL/V);
% 
% pretty(G)

% syms s X1 X2 X3 F
% 
% eqn1 = F == (4*s^2 + 8*s + 5)*X1 - (8*s)*X2 - 5*X3;
% eqn2 = 0 == -(8*s)*X1 + (4*s^2 + 16*s)*X2 - 4*s*X3;
% eqn3 = 0 == -5*X1 - 4*s*X2 + (4*s + 5)*X3;
% 
% sol = solve([eqn1, eqn2, eqn3], [X1, X2, X3]);
% X3_sol = simplify(sol.X3);
% 
% G = simplify(X3_sol/F);
% pretty(G)

% syms s O1 O2 T
% 
% eqn1 = T == (s^2 + 2*s + 1)*O1 - (s + 1)*O2;
% eqn2 = 0 == -(s + 1)*O1 + (2*s + 1)*O2;
% 
% sol = solve([eqn1 eqn2], [O1 O2]);
% O2_sol = simplify(sol.O2);
% G = simplify(O2_sol/T);
% pretty(G)

syms s F X1 X2

eqn1 = F == (s^2 + s + 1)*X1 - (s + 1)*X2;
eqn2 = 0 == -(s + 1)*X1 + (s^2 + s + 1)*X2;

sol = solve([eqn1 eqn2], [X1 X2]);
X2_sol = simplify(sol.X2);
G = simplify(X2_sol/F);
pretty(G)