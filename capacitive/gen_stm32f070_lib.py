import csv

STM32_PINOUT_CSV = "./stm32f070.csv"

# TODO replace
PROLOGUE = """EESchema-LIBRARY Version 2.3
#encoding utf-8
#
# STM32F070C6T6
#
DEF STM32F070C6T6 U 0 40 Y Y 4 L N
F0 "U" 0 0 60 H V C CNN
F1 "STM32F070C6T6" 0 150 60 H V C CNN
F2 "" 0 0 60 H I C CNN
F3 "" 0 0 60 H I C CNN
DRAW
S 0 -50 1600 -1350 0 1 0 N"""

EPILOGUE = """ENDDRAW
ENDDEF
#
#End Library"""

nbanks = 4
pinsperbank = 12

with open(STM32_PINOUT_CSV, "r") as f:
  data = dict()
  reader = csv.reader(f, delimiter=' ')
  for i, row in enumerate(reader):
    if row[1] == '-':
      continue
    num = int(row[1])
    name = row[3]
    typ = row[4]
    additional_names = []
    if len(row) > 7:
      additional_names = row[7].split(',')
    if len(additional_names) > 0:
      for n in additional_names:
        if any([part in n for part in ['TX', 'RX', 'SPI', 'I2C', 'SDIO', 'USB', 'OSC', 'SWDIO', 'SWCLK', 'ADC_IN', 'TIM']]):
          name = name + '/' + n
    t = 'B'
    if typ == 'I':
      t = 'I'
    if typ == 'S':
      if name == 'VDD' or name == "VDDA":
        t = 'W'
      elif name == 'VSS' or name == "VSSA":
        t = 'P'
    data[num] = [name, t]

  print(PROLOGUE)
  for b in range(nbanks):
    for p in range(pinsperbank*b, pinsperbank*(b + 1)):
      name = data[p + 1][0]
      x = -200
      y = -150 - 100 * (p - pinsperbank*b)
      ty = data[p + 1][1]
      print("X {} {} {} {} 200 R 50 50 {} 1 {}".format(name, p + 1, x, y, b + 1, ty))
  print(EPILOGUE)
