import sys

import numpy as np

import matplotlib.pyplot as plt

l = next(sys.stdin)
ys = np.array([int(d, 0) for d in l.split(',') if len(d) > 2])
xs = np.arange(0, ys.shape[0], 1)

save_fig = False

plt.plot(xs, ys)
if save_fig:
  plt.savefig(args.input + '.png')
else:
  plt.show()


