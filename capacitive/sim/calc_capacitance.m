k=1;
e=8.854e-12;
z=[0.1e-3,0.2e-3,0.5e-3]

wavenumber=6;
l=5.0e-3;
W=10.0e-3;
g=0.16e-3;

R=10e+6;

width_ratio = 1;

A_tx=wavenumber*W*l/8;
A_rx=(width_ratio*W)*(wavenumber)*l;

C_tx = k*e*A_tx./z
C_rx = k*e*A_rx./z

C_tx_comp = 1./(1./C_tx+1./(3*C_tx+C_rx))
C_rx_comp = 1./(1./C_rx+1./(4*C_tx))

% fc = 1./(R*C_rx_comp)./(2*pi)
attenuation = ((2*pi*1e+3)*R*C_rx_comp)./sqrt(((2*pi*1e+3)*R*C_rx_comp).^2+1)
