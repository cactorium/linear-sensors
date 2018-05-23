pkg load signal;
pkg load control;

% N = number of duty cycles/second
% M = effective PWM resolution
N=64;M=256;
t=linspace(0, 100, 100*M*N);
%t=linspace(0, 100, 100*M*N);
sample_time=floor(N*t)/N;
offset = N*(t-sample_time);
% 1 Hz PWM signal
y = (0.5*sin(2*pi*sample_time) + 0.5 < offset)-0.5;
n=[0:size(y)(2)-1]*N*M/size(y)(2);

% plot spectrum
% TODO trim off second half of spectrum because of the sampling limit stuff
%plot(n, 20*log10(abs(fft(y))));
%figure;
%plot(t, y);

s = tf('s');
C1=100e-9;R1=1.59e+3;C2=10e-9;R2=15.9e+3;
Z2=R2+1/(C2*s);
H2=1/(C2*s)/(1/(C2*s)+R2);
Zp=1/(1/Z2+C1*s);
H1=Zp/(Zp+R1);
Cs=10e-12;Rs=10e+6;
Cf=16e-12;
Hin=1/(1/Rs+Cf*s)/(1/(1/Rs+Cf*s)+1/(Cs*s));
H=minreal(Hin*H1*H2);

[y_filtered, t_sim] = lsim(H,y,t/1e+3);
%disp(zerocrossing(t_sim, y_filtered));

figure;
plot(t_sim, y_filtered);
%compare = 0.5.*sin(2.*pi.*t_sim+pi/2);
%figure;
%plot(t_sim, y_filtered-compare);

phaseshifts = [];
mags = [];
for i=1:64
  phasor=sum(exp(1.0j*2*pi*i*1e+3*t_sim).*y_filtered);
  phaseshifts(i)=180/pi*angle(phasor);
  mags(i)=20*log10(abs(phasor));
end
phaseshifts
mags

figure;
plot(n, 20*log10(abs(fft(y_filtered))));
