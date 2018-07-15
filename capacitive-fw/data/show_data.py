import argparse
import csv

import numpy as np

import matplotlib.pyplot as plt

parser = argparse.ArgumentParser(description="plots data")
parser.add_argument("input")
args = parser.parse_args()

window_sz = 50

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

def hp_fixed(xs, ys, sz):
  xn, yw = lp(xs, ys, sz)
  off = int(sz/2)
  return xn, ys[off:yw.shape[0]+off] - yw


with open(args.input, 'r') as f:
  l = f.readline()
  ys = np.array([int(d, 0) for d in l.split(',') if len(d) > 2])
  xs = np.arange(0, ys.shape[0], 1)

  xs_lp, ys_lp = lp(xs, ys, 50)
  xs_bp, ys_bp = hp(xs_lp, ys_lp, 200)

  xs_lp2, ys_lp2 = lp(xs, ys, 64)
  xs_lplp2, ys_lplp2 = lp(xs_lp2, ys_lp2, 32)
  xs_bp2, ys_bp2 = hp_fixed(xs_lplp2, ys_lplp2, 100)

  # current best parameters
  xs_hp, ys_hp = hp_fixed(xs, ys, 128)
  xs_bp3, ys_bp3 = lp(xs_hp, ys_hp, 64) # was 32

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
  if not show_fft:
    plt.plot(xs_hp, ys_hp, 'black')
    # plt.plot(xs_bp, ys_bp, 'g')
    plt.plot(xs_bp3, ys_bp3, 'r')
    plt.plot(xs_bp2, ys_bp2, 'b')
  else:
    y_fft = np.fft.fft(ys)
    w = np.fft.fftfreq(ys.shape[-1])

    bp_fft1 = np.fft.fft(ys_bp)
    w1 = np.fft.fftfreq(ys_bp.shape[-1])

    bp_fft2 = np.fft.fft(ys_bp2)
    w2 = np.fft.fftfreq(ys_bp2.shape[-1])

    bp_fft3 = np.fft.fft(ys_bp3)
    w3 = np.fft.fftfreq(ys_bp3.shape[-1])

    plt.plot(100e+3*w, 20*np.log10(np.absolute(y_fft)), 'black')
    # plt.plot(100e+3*w1, 20*np.log10(np.absolute(bp_fft1)), 'g')
    plt.plot(100e+3*w2, 20*np.log10(np.absolute(bp_fft2)), 'b')
    plt.plot(100e+3*w3, 20*np.log10(np.absolute(bp_fft3)), 'r')

  plt.show()


