import numpy as np

k=1
e=8.854e-12
z=np.array([0.1e-3,0.2e-3,0.5e-3])

from pad_config import *

R=10e+6

A_tx=wavenumber*(1.0e-3*W)*(1.0e-3*l)/8
A_rx=(width_ratio*(1.0e-3*W))*(wavenumber)*(1.0e-3*(l-g))

C_tx = k*e*A_tx/z
C_rx = k*e*A_rx/z

# add in loading effect of other capacitors
C_tx_comp = 1/(1/C_tx+1/(3*C_tx+C_rx))
C_rx_comp = 1/(1/C_rx+1/(4*C_tx))

print("C_tx:", C_tx_comp)
print("C_rx:", C_rx_comp)

# fc = 1./(R*C_rx_comp)/(2*np.pi)
attenuation = ((2*np.pi*1e+3)*R*C_rx_comp)/np.sqrt(((2*np.pi*1e+3)*R*C_rx_comp)**2+1)
print("rx attenuation:", attenuation)
