function [x, y, c] = gap(g, h, w, z);
%g = 0.1524;
%h = 0.2 - g;
%W = 20.00;

x = linspace(0, h + g, 1000);
y = zeros(1,length(x));
overlap = zeros(1,length(x));

A = exp(-2i*pi*0/8);
B = exp(-2i*pi*1/8);
C = exp(-2i*pi*2/8);
D = exp(-2i*pi*3/8);
E = exp(-2i*pi*4/8);

overlap(x<g) = 3 + (h-x(x<g))/h;
overlap(x>=g) = 3 + (h-g)/h;
overlap(x>=h) = 3 + (h-g+(x(x>=h)-h))/h;

y(x < g) = angle((A*(h-x(x<g))/h+B+C+D)./overlap(x<g));
y(x >= g) = angle((A*(h-x(x>=g))/h+B+C+D+E*(x(x>=g)-g)/h)./overlap(x>=g));
y(x >= h) = angle((B+C+D+E*(x(x>=h)-g)/h)./overlap(x>=h));

k=1;
e=8.854e-12;
A=w*h*overlap;

c = k*e*A/z;
