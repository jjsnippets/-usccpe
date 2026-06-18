% CPE 3102 - FEEDBACK AND CONTROL SYSTEMS
% Group 3   TTh 10:30 AM - 1:30 PM LB265 TC
% Cabigon, Timothy Chad; Sarcol, Joshua      BS-CpE 3        2025/09/10
% LE1 | Introduction to Matlab #1b

% Palindrome
function x = Palindrome(str)
    % type cast input(s) to string
    arguments
        str string
    end

    % strip any leading and trailing spaces 
    str = strip(str);

    % case-insensitive comparison
    x = strcmpi(str, reverse(str));
end