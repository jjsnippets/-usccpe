% CPE 3103 - FUNDAMENTALS OF MIXED SIGNALS AND SENSORS
% Group 1   MW 10:30 AM - 1:30 PM LBCEAC2 TC
% Sarcol, Joshua S      BS-CpE 3        2025/09/03
% Laboratory Exercise 1.b (Fibonacci on the floor)

function x = Fibonacci(a, b)
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