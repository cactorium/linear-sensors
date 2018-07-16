import math
import sys

import numpy as np

import matplotlib.pyplot as plt

save_fig = False
xs = np.zeros(100)
poss = np.zeros(100)
count = 0

phase_count = 0
cur_phase = 0
for l in sys.stdin:
  parts = l.split(' ')
  pos = int(parts[0], 16)
  if pos > 2**63:
    pos = pos - 2**64

  xs = np.roll(xs, -1)
  poss = np.roll(poss, -1)

  xs[-1] = count
  poss[-1] = pos/2**31

  count += 1
  if count % 10 == 0:
    plt.gcf().clear()
    # plt.plot(xs, i_s)
    # plt.plot(xs, q_s)
    plt.plot(xs, poss)
    plt.pause(0.001)

plt.show()


