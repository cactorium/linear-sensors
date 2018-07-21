### NOTE: center line of all generated models should be on the edge between
# the scale root and tooth

## caliper geometry
wavenumber = 6
l = 6.25
W = 5.0
g = 0.16

width_ratio = 1
clearance = 4*g

## scale geometry
scale_ground_trace_width = 0.300
# size of the holes for mounting the scales to whatever
scale_drill_dia = 0.125*25.4
scale_drill_ring_dia = 1.000
# clearance from the edge of the scale copper to the edge of the mounting holes
scale_mount_clearance = 4.00

## slide geometry
slide_drill_dia = 0.125*25.4
slide_drill_ring_dia = 1.000

## fab settings
min_drill_dia = 0.3302 
min_annular_ring_dia = 0.3556
min_via = 0.635
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
    0.5*scale_drill_ring_dia + scale_drill_dia)

scale_left = (scale_hole_to_edge + scale_mount_clearance +
    scale_ground_trace_width + min_clearance + scale_tooth_width)
scale_right = scale_root_width + scale_mount_clearance + scale_hole_to_edge
scale_edge = scale_left + scale_right

# used to set tedit parameter in footprints
import time
gen_time = hex(int(time.time()))[2:].upper()

assert l/8 > min_via # pad length must be larger than minimum via diameter
assert W > 0
assert g > 0
assert width_ratio > 0
assert clearance > 0

assert scale_ground_trace_width > 0.006*25.4 # ground trace must be greater than minimum width
assert scale_drill_dia > min_drill_dia
assert scale_drill_ring_dia > min_annular_ring_dia
assert scale_mount_clearance > 0.5*(scale_drill_dia + scale_drill_ring_dia) + min_clearance
assert board_edge_clearance > 0

# TODOs
# scale outline helper(left, right)
