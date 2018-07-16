import math
import sys

import numpy as np

import matplotlib.pyplot as plt

save_fig = False
xs = np.zeros(100)
i_s = np.zeros(100)
q_s = np.zeros(100)
phase = np.zeros(100)
count = 0

def calc_phase(i, q):
  if i > 0:
    if q > 0:
      return math.asin(q)
    else:
      return 2*math.pi + math.asin(q)
  else:
    return math.pi - math.asin(q)

phase_count = 0
cur_phase = 0
for l in sys.stdin:
  parts = l.split(' ')
  i = int(parts[0], 16)
  q = int(parts[1], 16)
  if i > 2**63:
    i = i - 2**64
  if q > 2**63:
    q = q - 2**64

  # print(i, q)

  xs = np.roll(xs, -1)
  i_s = np.roll(i_s, -1)
  q_s = np.roll(q_s, -1)
  phase = np.roll(phase, -1)

  mag = math.sqrt(i*i + q*q)
  local_phase = calc_phase(i/mag, q/mag)
  phase_up = 2*math.pi*(phase_count + 1) + local_phase
  phase_down = 2*math.pi*(phase_count - 1) + local_phase
  phase_same = 2*math.pi*(phase_count) + local_phase

  if ((abs(phase_up - cur_phase) < abs(phase_down - cur_phase)) and 
      (abs(phase_up - cur_phase) < abs(phase_same - cur_phase))):
    phase_count = phase_count + 1
    new_phase = phase_up
  elif ((abs(phase_down - cur_phase) < abs(phase_up - cur_phase)) and 
      (abs(phase_down - cur_phase) < abs(phase_same - cur_phase))):
    phase_count = phase_count - 1
    new_phase = phase_down
  else:
    new_phase = phase_same

  xs[-1] = count
  i_s[-1] = i/mag
  q_s[-1] = q/mag
  phase[-1] = 6.25*new_phase/(2*math.pi)

  cur_phase = new_phase
  # print(xs)

  count += 1
  if count % 10 == 0:
    plt.gcf().clear()
    # plt.plot(xs, i_s)
    # plt.plot(xs, q_s)
    plt.plot(xs, phase)
    plt.pause(0.001)

plt.show()


