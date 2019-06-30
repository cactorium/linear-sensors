import argparse
import csv

import numpy as np

import matplotlib.pyplot as plt

parser = argparse.ArgumentParser(description="plots data")
parser.add_argument("input")
args = parser.parse_args()

def lp(xs, ys, sz):
  s = np.cumsum(ys)
  yw = (s[sz:] - s[:-sz])/sz
  off = int(sz/2)
  xd = xs[off:yw.shape[0]+off]
  return xd, yw

def hp(xs, ys, sz):
  xn, yw = lp(xs, ys, sz)
  # NOTE: ys_term might be off; TODO test to see if different offset improves performance
  return xn, ys[sz:] - yw


def bp(xs, ys, T, w, damping):
  y_d = 0.0
  y_d2 = 0.0
  yw = np.zeros(ys.shape)
  a = 4./(T*T) - 2*damping/T + damping*damping + w*w
  b = -8./(T*T) + 2*(damping*damping + w*w)
  c = 4./(T*T) + 2*damping/T + damping*damping + w*w

  B = b/a
  C = c/a
  print(B, C)
  for i in range(0, ys.shape[0]):
    yw[i] = ys[i] - B*y_d - C*y_d2
    y_d2, y_d = y_d, yw[i]
    #print(yw[i])
  return xs, yw

with open(args.input, 'r') as f:
  l = f.readline()
  ys = np.array([int(d, 0) for d in l.split(',') if len(d) > 2])
  xs = np.arange(0, ys.shape[0], 1)

  xs_bp, ys_bp = bp(xs, ys, 1/96e+3, 2*np.pi*1e+3, -10000)
  ys_bp = ys_bp - np.sum(ys_bp)/ys_bp.shape[0]

  '''
  ys_sum = np.cumsum(ys)
  ys_lp2 = (ys_sum[25:] - ys_sum[:-25])/25
  ys_lp2_sum = np.cumsum(ys_lp2)
  ys_lp_windows = (ys_lp2_sum[50:] - ys_lp2_sum[:-50])/50
  ys_bp = ys_lp2[50:] - ys_lp_windows

  ys_lp3 = (ys_sum[50:] - ys_sum[:-50])/50
  ys_lp3_sum = np.cumsum(ys_lp3)
  ys_lp_windows3 = (ys_lp3_sum[100:] - ys_lp3_sum[:-100])/100
  ys_bp2 = ys_lp3[100:] - ys_lp_windows3
  '''

  # plt.plot(xs[25:-25], ys_lp_filtered)
  # plt.plot(xs, ys, 'black')

  show_fft = True
  show_fft = False
  save_fig = False
  #save_fig = True

  if not show_fft:
    plt.plot(xs, ys, 'black')
    plt.plot(xs_bp, ys_bp, 'r')
  else:
    y_fft = np.fft.fft(ys)
    w = np.fft.fftfreq(ys.shape[-1])

    bp_fft1 = np.fft.fft(ys_bp)
    w1 = np.fft.fftfreq(ys_bp.shape[-1])

    plt.plot(100e+3*w, 20*np.log10(np.absolute(y_fft)), 'black')
    plt.plot(100e+3*w1, 20*np.log10(np.absolute(bp_fft1)), 'g')

  if save_fig:
    plt.savefig(args.input + '.png')
  else:
    plt.show()


