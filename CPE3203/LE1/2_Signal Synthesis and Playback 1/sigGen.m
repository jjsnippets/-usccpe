clear
Fs = 8192;  % sampling frequency
dt = 1/Fs;  % sampling interval

t = 0:dt:4;

F1 = 440;
xt = 0.5*sin(2*pi*F1*t) + 0.25*sin(2*pi*F1*3*t) + 0.125*sin(2*pi*F1*5*t);
sound(xt, Fs);