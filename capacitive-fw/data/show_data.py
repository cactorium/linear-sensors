import argparse
import csv

import matplotlib.pyplot as plt

parser = argparse.ArgumentParser(description="plots data")
parser.add_argument("input")
args = parser.parse_args()

with open(args.input, 'r') as f:
  l = f.readline()
  ys = [int(d, 0) for d in l.split(',') if len(d) > 2]
  print(ys)
  xs = [x for x in range(len(ys))]
  plt.plot(xs, ys)
  plt.show()
