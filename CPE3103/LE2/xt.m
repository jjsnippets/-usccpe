% CPE 3103 - FUNDAMENTALS OF MIXED SIGNALS AND SENSORS
% Group 1   MW 10:30 AM - 1:30 PM LBCEAC2 TC
% Sarcol, Joshua S      BS-CpE 3        2025/09/10
% Laboratory Exercise 2 (Item 3B)

% piecewise definition of xt(t)
function x = xt(t)
   
    if (t <= -2)
        x = 0;

    elseif (t <= -1)
        x = t + 3;

    elseif (t <= 0)
        x = -2 * t;

    elseif (t <= 1)
        x = -1;

    elseif (t <= 2)
        x = t - 1;

    elseif (t <= 3)
        x = -t + 3;
    
    else
        x = 0;
    end
end