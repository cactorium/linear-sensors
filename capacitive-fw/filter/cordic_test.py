import math

import matplotlib.pyplot as plt
import numpy as np

cordic_consts = [int(2**31*math.atan(1/2**i)) for i in range(32)]

def cordic_atan(x, y):
  x_neg = x < 0
  y_neg = y < 0
  if x_neg:
    x = -x
  acc = 0
  for i in range(12):
    if y < 0:
      x, y = x - (y >> i), y + (x >> i)
      acc = acc - cordic_consts[i]
    else:
      x, y = x + (y >> i), y - (x >> i)
      acc = acc + cordic_consts[i]
    if x > 2**63-1 or x < -2**63:
      print("overflow")
    if y > 2**63-1 or y < -2**64:
      print("overflow")

  if not x_neg:
    return acc
  else:
    if y_neg:
      return -math.pi*2**31-acc
    else:
      return math.pi*2**31 - acc

thetas = np.linspace(-math.pi, math.pi, 2000)
x = (2**54*np.cos(thetas)).astype(int)
y = (2**54*np.sin(thetas)).astype(int)

approx = np.array([cordic_atan(x[i], y[i]) for i in range(thetas.shape[0])])
real = (2**31*np.arctan2(y, x)).astype(int)

error = approx - real
plt.plot(thetas, 6.25*error/2**31/(2*math.pi))
# plt.plot(thetas, approx/2**31)
# plt.plot(thetas, approx/2**31-thetas)
# plt.plot(thetas, real/2**31)
plt.show()
