% CPE 3102 - FEEDBACK AND CONTROL SYSTEMS
% Group 3       TTh 10:30 AM - 1:30 PM LB285 TC
% Team 5: Cabigon, Timothy Chad; Sarcol, Joshua     BS-CpE 3    2025/10/09
% LE4 | Time Response – Second-Order System 

clear
clc
format short        % 5 decimal places of display

% variable for final results (array)
ansTable = zeros(7, 10);

% initial transfer function
init = tf(25, [1 4 25]);
    % extract parameters of the transfer function
    [wn,zeta,p] = damp(init);
    wn = wn(1);
    zeta = zeta(1);
    preal = real(p);
    pimag = imag(p);
% append values and parameters to array
% as first row
ansTable(1, :) = insTable(init);

% item 1
% Imaginary part of the poles remains the same, but the real part is
% increased twice over the initial value
p1 = 2 * preal + 1i * pimag;
ansTable(2, :) = insTable(zpk([], p1, 1));

% item 2
% Imaginary part of the poles remains the same, but the real part is
% decreased ½ time over the initial value
p2 = 0.5 * preal + 1i * pimag;
ansTable(3, :) = insTable(zpk([], p2, 1));

% item 3
% Real part of the poles remains the same, but the imaginary part is
% increased 2 times over the initial value
p3 = preal + 2i * pimag;
ansTable(4, :) = insTable(zpk([], p3, 1));

% item 4
% Real part of the poles remains the same, but the imaginary part is
% increased 4 times over the initial value
p4 = preal + 4i * pimag;
ansTable(5, :) = insTable(zpk([], p4, 1));

% item 5
% Damping ratio remains the same, but the natural frequency is
% increased 2 times over the initial value
wn5 = 2 * wn;
num5 = wn5 ^ 2;
den5 = [1, 2*zeta*wn5, wn5^2];
ansTable(6, :) = insTable(tf(num5, den5));

% item 6
% Damping ratio remains the same, but the natural frequency is
% increased 4 times over the initial value
wn6 = 4 * wn;
num6 = wn6 ^ 2;
den6 = [1, 2*zeta*wn6, wn6^2];
ansTable(7, :) = insTable(tf(num6, den6));

% display all results in a table
disp(array2table(ansTable, ...
    VariableNames = {'A', 'B', '%OS', 'Ts', 'Tp', 'Tr', 'omega_n', ...
                        'zeta', 'omega_d', 'sigma_d'}))

% helper function to insert all values and parameters of a transfer
% function of interest
function row = insTable(tf)
    % calculate values using built-in functions
    [~, den] = tfdata(tf, 'v');
    [wn,zeta,p] = damp(tf);
    param = stepinfo(tf);
    
    % add all the calculated values in a single row
    row = [den(2) den(3) param.Overshoot param.SettlingTime ... 
        param.PeakTime param.RiseTime wn(1) zeta(1) -1*real(p(1)) ...
        imag(p(1))];
end