% CPE 3102 - FEEDBACK AND CONTROL SYSTEMS
% Group 3   TTh 10:30 AM - 1:30 PM LB265 TC
% Cabigon, Timothy Chad; Sarcol, Joshua      BS-CpE 3        2025/09/10
% LE1 | Introduction to Matlab #1b 

% Fibonacci
function x = newFibonacci(a, b)
    % inputs must be positive integers
    arguments
        a (1,1) double {mustBeInteger, mustBePositive}
        b (1,1) double {mustBeInteger, mustBePositive}
    end

    % a must be less than or equal to b
    if a > b
        error("The first argument [" + a + "] is larger than the " + ...
            " second argument [" + b + "]")
    end

    x = [1 1]; % assume f1 = 1 and f2 = 1
    
    % generate all fibonacci numbers up to fn <= b
    while x(end) <= b
        x = [x, x(end-1) + x(end)]; % append the next number in x
    end

    % logical indexing to select numbers in between a and b
    x = x((x >= a) & (x <= b));
end