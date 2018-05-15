pkg load signal;
pkg load control;

% N = number of duty cycles/second
% M = effective PWM resolution
N=16;M=1024;
t=linspace(0, 100, 100*M*N);
%t=linspace(0, 100, 100*M*N);
sample_time=floor(M*t)/M;
offset = M*(t-sample_time);
% 1 Hz PWM signal
y = (0.5*sin(2*pi*sample_time) + 0.5 < offset)-0.5;
n=[0:size(y)(2)-1]*N*M/size(y)(2);

% plot spectrum
% TODO trim off second half of spectrum because of the sampling limit stuff
plot(n, 20*log10(abs(fft(y))));
figure;

L=1/(2*pi);
C=1/(2*pi);
R=1;
Rl=100;

s = tf('s');
%filt = 1/(1+s/(2*pi));
%filt = 1/((1+s/(2*pi))^2);
filt = 1/(C*s)/(L*s+1/(C*s+1/Rl)+R);
[y_filtered, t_sim] = lsim(filt,y,t);
%disp(zerocrossing(t_sim, y_filtered));

plot(t, y_filtered)

figure;
plot(n, 20*log10(abs(fft(y_filtered))));
