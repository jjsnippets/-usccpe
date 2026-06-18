% CPE 3102 - FEEDBACK AND CONTROL SYSTEMS
% Group 3       TTh 10:30 AM - 1:30 PM LB285 TC
% Team 5: Cabigon, Timothy Chad; Sarcol, Joshua         BS-CpE 3        2025/10/04
% LE3 | Time Response - First-Order System 

clear
clc
format bank                         % 2 decimal places display

% Table 1 value generation
K1 = 1:10;                          % values of K
popTable(K1)

% Table 2 value verification
K2 = [27.5 74.07 220 133.33];       % values of K that were calculated by hand
popTable(K2)

function popTable (K)
    Table = zeros([numel(K) 4]);    % variable for final results (array)
    
    for i = 1:length(K)             % for each K value
        indiv = stepinfo(tf(K(i), [1 K(i)]));
                                    % calculate each performance specification
        Table(i, :) = [K(i) 1/K(i) indiv.RiseTime indiv.SettlingTime];
    end
                                    
    disp(array2table(Table, ...     % display results in a table
        VariableNames = {'K', 'Time Constant', 'Rise Time','Settling Time'}))
end