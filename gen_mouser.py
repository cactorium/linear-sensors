import argparse
import csv

def main():
  parser = argparse.ArgumentParser(description="Generates a Mouser BOM from Joost's KiCAD BOM")
  parser.add_argument("input", help="input BOM")
  parser.add_argument("output", help="output BOM")
  parser.add_argument("--m", help="quantity multiplier", default="1")

  args = parser.parse_args()
  multiplier = 1 if args.m is None else int(args.m)

  print("multiplier: {}".format(multiplier))

  mouser_idx = None
  count_idx = None
  components = []
  with open(args.input, 'r') as f:
    header = f.readline()[:-1]
    parts = header.split(',')
    for i, part in enumerate(parts):
      if 'Mouser' == part:
        mouser_idx = i
      elif 'Quantity' == part:
        count_idx = i

    if mouser_idx is None or count_idx is None:
      print("Unable to find headers")
      return

    for i, line in enumerate(f):
      parts = line[:-1].split(',')
      if len(parts) < max(mouser_idx, count_idx):
        print("[WARN] line {} is missing fields".format(i + 1))
        continue
      part_num = parts[mouser_idx][1:-1] # strip start and ending quotes
      count = parts[count_idx][1:-1]
      if len(part_num) == 0:
        print("[WARN] line {} is missing part number".format(i + 1))
        continue
      if count == 0:
        print("[WARN] line {} has zero quantity".format(i + 1))
      if part_num == 'NoPart':
        continue
      components.append((part_num, count))

  with open(args.output, 'w') as f:
    # header is necessary if you don't want to miss the first part
    f.write("Mouser,Quantity")
    for c in components:
      f.write("{},{}\n".format(c[0], multiplier*int(c[1])))

if __name__ == "__main__":
  main()
