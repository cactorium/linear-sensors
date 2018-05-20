### NOTE: center line of all generated models should be on the edge between
# the scale root and tooth

## caliper geometry
wavenumber = 6
# I guess we're an imperial caliper now
l = 5.08
W = 10.0
g = 0.16

width_ratio = 1
clearance = 4*g

## scale geometry
scale_length = 200.00
scale_ground_trace_width = 0.300
# size of the holes for mounting the scales to whatever
scale_drill_dia = 0.125*25.4
scale_drill_ring_dia = 0.500
# clearance from the edge of the scale copper to the edge of the mounting holes
scale_mount_clearance = 0.5*scale_drill_dia

## slide geometry
slide_drill_dia = 0.125*25.4

## fab settings
min_drill_dia = 0.3302 
min_annular_ring_dia = 0.3556
board_edge_clearance = 0.020*25.4
min_trace_width = 0.006*25.4
min_clearance = 0.006*25.4

## generated constants
# scale teeth and base are padded with 0.5*clearance on each side to allow for some
# vertical misalignment
#                   ground + clearance + tx pads + clearance + rx pads + matching clearance
scale_tooth_width = 0.5*clearance + (2*W+g) + 0.5*clearance
scale_root_width = 0.5*clearance + width_ratio*W + 0.5*clearance
scale_copper_width = (scale_ground_trace_width + min_clearance + scale_tooth_width +
    scale_root_width)

scale_hole_to_edge = max(board_edge_clearance + 0.5*(scale_drill_dia + scale_drill_ring_dia),
    scale_drill_ring_dia)

scale_edge = (scale_hole_to_edge + scale_mount_clearance +
    scale_copper_width + scale_mount_clearance + scale_hole_to_edge)

# used to set tedit parameter in footprints
import time
gen_time = hex(int(time.time()))[2:].upper()

assert l/8 > 0.6285 # pad length must be larger than minimum via diameter
assert W > 0
assert g > 0
assert width_ratio > 0
assert clearance > 0

assert scale_length > 0
assert scale_ground_trace_width > 0.006*25.4 # ground trace must be greater than minimum width
assert scale_drill_dia > min_drill_dia
assert scale_drill_ring_dia > min_annular_ring_dia
assert scale_mount_clearance > 0.5*scale_drill_ring_dia
assert board_edge_clearance > 0

# TODOs
# scales
# scale ground
# scale drill (left, right)
# scale outline helper(left, right)
# slide drill (left, right)
