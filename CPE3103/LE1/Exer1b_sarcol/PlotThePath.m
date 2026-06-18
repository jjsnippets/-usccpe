% CPE 3103 - FUNDAMENTALS OF MIXED SIGNALS AND SENSORS
% Group 1   MW 10:30 AM - 1:30 PM LBCEAC2 TC
% Sarcol, Joshua S      BS-CpE 3        2025/09/04
% Laboratory Exercise 1.b (Plot the path)

function PlotThePath (signal, args)
    % only accepts the signals listed
    arguments
        signal (1,1) string {mustBeMember(signal, ["step", "sin", "exp"])}
    end

    % values must be real numbers
    arguments (Repeating)
        args (1,1) double {mustBeReal}
    end

    % counts the number of values entered by the user after the signal
    % argument
    n = numel(args);

    x = -5:0.01:5;      % x ranges from -5 to 5
    y = zeros(size(x)); % y is the same size as x

    % fill-out the values of y depending on the signal formula
    switch signal
        % step = u(t)
        % 1 for t >= arg and 0 otherwise
        % expected no. of arguments: 1
        case "step"
            argcount(n, 1)
            y(x >= args{1}) = 1;
        
        % sinusoidal = A * sin(omega * t + theta)
        % expected no. of arguments: 3
        case "sin"
            argcount(n, 3)
            y = args{1} * sin(args{2} * x * pi + args{3});

        % exponential = A * e^(-b * t)
        % expected no. of arguments: 2
        case "exp"
            argcount(n, 2)
            y = args{1} * exp(-1 * args{2} * x);
    end

    % plot the signal
    plot(x, y);
    grid on
    axis square
    title(signal + " signal")
    xlabel("x-axis")
    ylabel("y-axis")

end

% helper function to show an error if the expected number of arguments does
% not match the user input
function argcount(n, t)
    if n ~= t
        error("Expected number of variables is " + t + ", provided is " ...
                    + n)
    end
end