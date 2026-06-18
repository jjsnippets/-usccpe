Fs = 8192;  %sampling frequency
dt = 1/Fs;  %sampling interval

t1 = 0:dt:1.65;
t2 = 0:dt:0.65;
t3 = 0:dt:1.00;

F1 = 300;
F2 = 400;
F3 = 500;

xt = sin(2*pi*F1*t1);
env = (sin(2*10*pi*t1)+abs(1*sin(2*10*pi*t1)))/2;
out = xt.*env;

xt = sin(2*pi*F2*t2);
env = (sin(2*10*pi*t2)+abs(1*sin(2*10*pi*t2)))/2;
out = [out xt.*env];

xt = sin(2*pi*F3*t3);
env = (sin(2*10*pi*t3)+abs(1*sin(2*10*pi*t3)))/2;
out = [out xt.*env];

sound(out,Fs)