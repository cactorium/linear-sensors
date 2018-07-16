import sys

import numpy as np

import matplotlib.pyplot as plt

save_fig = False

for l in sys.stdin:
  ys_raw = [int(d, 0) for d in l.split(',') if len(d) > 2]
  ys = np.array([d if d < 2**31 else d-2**31 for d in ys_raw])
  xs = np.arange(0, ys.shape[0], 1)

  plt.plot(xs, ys)

if save_fig:
  plt.savefig('test.png')
else:
  plt.show()


