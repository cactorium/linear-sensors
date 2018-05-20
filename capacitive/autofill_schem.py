#!/usr/bin/env python3
# TODO: make sure it also works in python2

import argparse

DISTRIBUTOR_VALUES = ["\"Mouser\""]

class Component(object):
  def __init__(self, start):
    self.designator = None
    self.value = None
    self.footprint = None
    self.footprint_row = None
    # distributor ids, mapped to (line_num, value, all fields
    # (to make reconstruction easier)
    self.distributors = dict()
    self.cls = None
    self.last_value = None
    self.num_fields = 0

    # used mainly for parser debugging
    self.start = start

class DistributorData(object):
  def __init__(self, id):
    self.id = id

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

def parse_lines(f):
  lines = []
  components = []
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
            if parts[-1][:-1] in DISTRIBUTOR_VALUES:
              component.distributors[parts[-1][:-1]] = DistributorData(parts[2])
      elif line.startswith("$EndComp"):
        component_start = False
        # ignore power nodes
        if component.cls != "#":
          components.append(component)

    if line.startswith("$Comp"):
      component_start = True
      component = Component(i)
    lines.append(line)
  return (lines, components)

def infer_components(components):
  # dictionaries in dictionaries:
  # distributor = (distributor_type, id) so that non-unique ids can be captured
  # filled_values[cls][value] = [(footprint, [designators], [distributors])]
  filled_values = dict()

  # first pass to infer footprints and distributors, second pass to fill in details
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
          # print(c.designator, c.value, c.footprint, c.distributors)
          tosearch = filled_values[c.cls][c.value]
          # find element with matching footprint
          found = None
          for i, fp in enumerate(tosearch):
            if fp[0] == c.footprint:
              found = i
              break

          if found is None:
            distributors = []
            for dist in c.distributors:
              if len(c.distributors[dist].id) > 2 and len(dist) > 2:
                distributors.append((dist, c.distributors[dist].id))
            tosearch.append((c.footprint, [c.designator], distributors))
          else:
            tosearch[i][1].append(c.designator)
            # append any new distributors
            for dist in c.distributors:
              if len(c.distributors[dist].id) > 2 and len(dist) > 2:
                if not any([dist == m[0] and c.distributors[dist].id == m[1] 
                    for m in tosearch[i][2]]):
                  tosearch[i][2].append((dist, c.distributors[dist].id))
  return filled_values

def main():
  parser = argparse.ArgumentParser(description="Autofills components in an Eeschema schematic")
  parser.add_argument("input", help="file to autofill")
  parser.add_argument("output", help="file to write autofilled schematic to")

  args = parser.parse_args()

  lines = None
  components = None

  with open(args.input, 'r') as f:
    (lines, components) = parse_lines(f)

  print("{} lines".format(len(lines)))
  print("found {} components".format(len(components)))
  without_footprints = len([None for c in components if c.footprint is None])
  print("found {} components without footprints".format(without_footprints))

  filled_values = infer_components(components)

  entry_count = 0
  conflicts = []
  for cls in filled_values:
    for val in filled_values[cls]:
      for _ in filled_values[cls][val]:
        # TODO: check for conflicts
        entry_count += 1
  print("found {} filled unique component classes".format(entry_count))

  # TODO: allow interactive distributor choice to resolve conflicts
  while len(conflicts) > 0:
    print("found conflicting information, cannot autofill")
    for conflict in conflicts:
      pass
    return

  # autofill
  autofill_fp = 0
  autofill_dist = 0
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
          if ((c.footprint is None or len(c.footprint) <= 2) and 
              c.footprint_row is not None):
            print("matched {} {} with {}".format(c.designator, c.value, match))
            # rewrite footprint
            c.footprint = match[0]
            row = c.footprint_row[1]
            row[2] = match[0]
            lines[c.footprint_row[0]] = " ".join(row)
            autofill_fp += 1
          # add in distributors 
          dist_added = 0
          for dist in match[2]:
            if dist[0] not in c.distributors:
              c.distributors[dist[0]] = DistributorData(dist[1])
              # append to the field list
              template_row = quotesplit(lines[c.last_value])
              row = [
                  template_row[0],
                  str(c.num_fields),
                  dist[1]] + template_row[3:10] + [dist[0] + "\n"]
              c.num_fields += 1
              to_append.append((c.last_value, row))
              dist_added += 1
              # mark as something to do, because appending now would
              # cause the row numbers to shift for all the components after this one,
              # invalidating their indices
          if dist_added > 0:
            autofill_dist += 1

    # print(c.designator, c.value, c.footprint, c.distributors)
  for ta in reversed(to_append):
    idx = ta[0]
    row = ta[1]
    lines = lines[0:idx+1] + [" ".join(row)] + lines[idx+1:]

  print("autofilled {} fp, {} dist".format(autofill_fp, autofill_dist))
  # dictionary of dictionaries of components without footprints
  # missing[cls][value] = [designators]
  missing = dict()

  for c in components:
    if c.cls is not None:
      if c.cls not in missing:
        missing[c.cls] = dict()
      if c.value is not None and c.footprint is None:
        if c.value not in missing[c.cls]:
          missing[c.cls][c.value] = []
        missing[c.cls][c.value].append(c.designator)

  for cls in missing:
    for value in missing[cls]:
      print("NOTE: no unique footprint found for {} {}".format(value, missing[cls][value]))

  # repeat for manufacturer info
  missing = dict()

  for c in components:
    if c.cls is not None:
      if c.cls not in missing:
        missing[c.cls] = dict()
      if c.value is not None and not bool(c.distributors):
        if c.value not in missing[c.cls]:
          missing[c.cls][c.value] = []
        missing[c.cls][c.value].append(c.designator)

  for cls in missing:
    for value in missing[cls]:
      print("NOTE: no distributor data found for {} {}".format(value, missing[cls][value]))


  output = args.output or args.input
  print("outputting to {}...".format(output))
  with open(output, "w+") as f:
    for line in lines:
      f.write(line)

if __name__ == "__main__":
  main()
