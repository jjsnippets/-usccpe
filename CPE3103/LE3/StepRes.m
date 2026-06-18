% CPE 3103 - FUNDAMENTALS OF MIXED SIGNALS AND SENSORS
% Group 1   MW 10:30 AM - 1:30 PM LBCEAC2 TC
% Sarcol, Joshua S      BS-CpE 3        2025/09/24
% Laboratory Exercise 3 (Item 4)

% Output response q(t) for input V_in(t) = unit step
function st = StepRes(t)
    st = zeros(size(t));    % vector the same size as t
    idx = (t >= 0);         % logical indexing for t values; implements u(t)
                            % formula from 2B
    st(idx) = (1/20) * (1 - exp(-t(idx)/2) .* ...
              (cos(sqrt(199)*t(idx)/2) + (1/sqrt(199)) * sin(sqrt(199)*t(idx)/2)));
end