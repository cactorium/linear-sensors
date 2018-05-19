#!/usr/bin/env python3
# TODO: make sure it also works in python2

import argparse

MANUFACTURER_VALUES = ["\"Mouser\""]

class Component(object):
  def __init__(self, start):
    self.designator = None
    self.value = None
    self.footprint = None
    self.footprint_row = None
    # manufacturer ids, mapped to (line_num, value, all fields
    # (to make reconstruction easier)
    self.manufacturers = dict()
    self.cls = None
    self.last_value = None
    self.num_fields = 0

    # used mainly for parser debugging
    self.start = start

class ManufacturerData(object):
  def __init__(self, line_num, id, row):
    self.line_num = line_num
    self.id = id
    self.row = row

def quotesplit(line):
  parts = line.split(" ")
  ret = []
  num_quotes = 0
  incomplete_part = None
  for part in parts:
    num_quotes += len([None for c in part if c == '"'])
    if num_quotes % 2 == 1:
      if incomplete_part is None:
        # just started a quoted section
        incomplete_part = part
      else:
        incomplete_part += " " + part
    else:
      if incomplete_part is not None:
        # ending quote is in this part
        ret.append(incomplete_part + " " + part)
        incomplete_part = None
      else:
        # normal case; pass through
        ret.append(part)
  return ret

def main():
  parser = argparse.ArgumentParser(description="Autofills components in an Eeschema schematic")
  parser.add_argument("input", help="file to autofill")
  parser.add_argument("output", help="file to write autofilled schematic to")

  args = parser.parse_args()

  lines = []
  components = []

  with open(args.input, 'r') as f:
    component_start = False
    component = None
    for i, line in enumerate(f):
      if component_start:
        if line.startswith("L"):
          parts = quotesplit(line)
          component.designator = parts[2].rstrip()
          component.cls = component.designator[0]
        elif line.startswith("F"):
          parts = quotesplit(line)
          component.num_fields += 1
          component.last_value = i
          if parts[1].isdigit():
            field_type = int(parts[1])
            if field_type == 1:
              component.value = parts[2]
            elif field_type == 2:
              component.footprint_row = (i, parts)
              if len(parts[2]) > 2:
                component.footprint = parts[2]
            elif field_type > 3:
              # TODO: make case insensitive
              if parts[-1][:-1] in MANUFACTURER_VALUES:
                component.manufacturers[parts[-1][:-1]] = ManufacturerData(i, parts[2], parts)
        elif line.startswith("$EndComp"):
          component_start = False
          # ignore power nodes
          if component.cls != "#":
            components.append(component)

      if line.startswith("$Comp"):
        component_start = True
        component = Component(i)
      lines.append(line)

  print("{} lines".format(len(lines)))
  print("found {} components".format(len(components)))
  without_footprints = len([None for c in components if c.footprint is None])
  print("found {} components without footprints".format(without_footprints))
  # dictionaries in dictionaries:
  # manufacturer = (manufacturer_type, id) so that non-unique ids can be captured
  # filled_values[cls][value] = [(footprint, [designators], [manufacturers])]
  filled_values = dict()

  # first pass to infer footprints and manufacturers, second pass to fill in details
  for c in components:
    if c.cls is None or len(c.cls) == 0:
      print("Component at {} incorrectly parsed; no cls set".format(c.start))
    else:
      if c.cls not in filled_values:
        filled_values[c.cls] = dict()

      if c.value is not None and len(c.value) > 2:
        if c.value not in filled_values[c.cls]:
          filled_values[c.cls][c.value] = []

        if c.footprint is not None and len(c.footprint) > 2:
          print(c.designator, c.value, c.footprint, c.manufacturers)
          tosearch = filled_values[c.cls][c.value]
          # find element with matching footprint
          found = None
          for i, fp in enumerate(tosearch):
            if fp[0] == c.footprint:
              found = i
              break

          if found is None:
            manufacturers = []
            for mfg in c.manufacturers:
              if len(c.manufacturers[mfg].id) > 2 and len(mfg) > 2:
                manufacturers.append((mfg, c.manufacturers[mfg].id))
            tosearch.append((c.footprint, [c.designator], manufacturers))
          else:
            tosearch[i][1].append(c.designator)
            # append any new manufacturers
            for mfg in c.manufacturers:
              if len(c.manufacturers[mfg].id) > 2 and len(mfg) > 2:
                if not any([mfg == m[0] and c.manufacturers[mfg].id == m[1] 
                    for m in tosearch[i][2]]):
                  tosearch[i][2].append((mfg, c.manufacturers[mfg].id))

  entry_count = 0
  conflicts = []
  for cls in filled_values:
    for val in filled_values[cls]:
      for _ in filled_values[cls][val]:
        # TODO: check for conflicts
        entry_count += 1
  print("found {} filled unique component classes".format(entry_count))

  # TODO: allow interactive manufacturer choice to resolve conflicts
  while len(conflicts) > 0:
    print("found conflicting information, cannot autofill")
    for conflict in conflicts:
      pass
    return

  # autofill
  autofill_fp = 0
  autofill_mfg = 0
  to_append = []
  for c in components:
    if c.cls in filled_values:
      if c.value in filled_values[c.cls]:
        matches = []
        if c.footprint is not None:
          matches = [t for t in filled_values[c.cls][c.value] if t[0] == c.footprint]
        else:
          matches = filled_values[c.cls][c.value]
        if len(matches) == 1:
          # autofill
          match = matches[0]
          print("matched {} with {}".format(c.designator, match))
          if ((c.footprint is None or len(c.footprint) <= 2) and 
              c.footprint_row is not None):
            # rewrite footprint
            c.footprint = match[0]
            row = c.footprint_row[1]
            row[2] = match[0]
            lines[c.footprint_row[0]] = " ".join(row)
            autofill_fp += 1
            print("autofilled fp for {}".format(c.designator))
          # add in manufacturers 
          mfg_added = 0
          for mfg in match[2]:
            if mfg[0] not in c.manufacturers:
              # append to the field list
              template_row = quotesplit(lines[c.last_value])
              row = [
                  template_row[0],
                  str(c.num_fields),
                  mfg[1]] + template_row[3:10] + [mfg[0] + "\n"]
              c.num_fields += 1
              to_append.append((c.last_value, row))
              mfg_added += 1
              # mark as something to do, because appending now would
              # cause the row numbers to shift for all the components after this one,
              # invalidating their indices
          if mfg_added > 0:
            autofill_mfg += 1

    # print(c.designator, c.value, c.footprint, c.manufacturers)
  for ta in reversed(to_append):
    idx = ta[0]
    row = ta[1]
    lines = lines[0:idx+1] + [" ".join(row)] + lines[idx+1:]

  print("autofilled {} fp, {} mfg".format(autofill_fp, autofill_mfg))
  # dictionary of dictionaries of components without footprints
  # missing[cls][value] = [designators]
  missing = dict()

  for c in components:
    if c.cls is not None:
      if c.cls not in missing:
        missing[c.cls] = dict()
      if c.value is not None:
        if c.value not in missing[c.cls]:
          missing[c.cls][c.value] = []
        missing[c.cls][c.value].append(c.designator)

  for cls in missing:
    for value in missing[cls]:
      print("NOTE: no unique footprint found for {} {}".format(value, missing[cls][value]))

  output = args.output or args.input
  print("outputting to {}...".format(output))
  with open(output, "w+") as f:
    for line in lines:
      f.write(line)

if __name__ == "__main__":
  main()
