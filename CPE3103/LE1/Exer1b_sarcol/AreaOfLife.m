% CPE 3103 - FUNDAMENTALS OF MIXED SIGNALS AND SENSORS
% Group 1   MW 10:30 AM - 1:30 PM LBCEAC2 TC
% Sarcol, Joshua S      BS-CpE 3        2025/09/03
% Laboratory Exercise 1.b (Area of your life)

function area = AreaOfLife(shape, args)
    % only accepts the shapes listed
    arguments
        shape (1,1) string {mustBeMember(shape, ["circle", "square", ...
            "triangle", "rectangle", "ellipse"])}
    end

    % values must be positive real numbers
    arguments (Repeating)
        args (1,1) double {mustBePositive}
    end

    % counts the number of values entered by the user after the shape
    % argument
    n = numel(args);

    switch shape
        % circle = pi * r^2
        % expected no. of arguments: 1
        case "circle"
            argcount(n, 1)
            area = pi * (args{1} ^ 2);
        
        % square = s^2
        % expected no. of arguments: 1     
        case "square"
            argcount(n, 1)
            area = args{1} ^ 2;

        % triangle = 0.5 * b * h
        % expected no. of arguments: 2    
        case "triangle"
            argcount(n, 2)
            area = 0.5 * args{1} * args{2};
        
        % rectangle = l * w
        % expected no. of arguments: 2    
        case "rectangle"
            argcount(n, 2)
            area = args{1} * args{2};
        
        % ellipse = pi * a * b
        % expected no. of arguments: 2   
        case "ellipse"
            argcount(n, 2)
            area = pi * args{1} * args{2};
    end
end

% helper function to show an error if the expected number of arguments does
% not match the user input
function argcount(n, t)
    if n ~= t
        error("Expected number of variables is " + t + ", provided is " ...
                    + n)
    end
end