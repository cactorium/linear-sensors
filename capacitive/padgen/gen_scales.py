prologue = """(module CAP_SCALES (layer F.Cu) (tedit 5B00EC8B)
  (fp_text reference REF** (at 0 0.5) (layer F.SilkS)
    (effects (font (size 1 1) (thickness 0.15)))
  )
  (fp_text value CAP_SCALES (at 0 -0.5) (layer F.Fab)
    (effects (font (size 1 1) (thickness 0.15)))
  )
"""

epilogue = """)"""

from pad_config import *

print(prologue)

scale = """  (fp_poly (pts {}) (layer F.Cu) (width 0.001))"""
xy = """(xy {} {})"""

num_full_scales = int(scale_length/l)
center = 0.5*(l-g)

scale_edges = []
for i in range(num_full_scales):
  scale_poly = [
      (0, i*l),
      (0, center-l/4+i*l),
      (-2*W-g-clearance, center-l/4+i*l),
      (-2*W-g-clearance, center+l/4+i*l),
      (0, center+l/4+i*l),
      (0, l-g+i*l),
      (width_ratio*W+clearance, l-g+i*l),
      (width_ratio*W+clearance, i*l),
      ]
  scale_edges += [
      (-min_clearance, i*l),
      (-min_clearance, center-l/4+i*l - min_clearance),
      (-2*W-g-clearance - min_clearance, center-l/4+i*l - min_clearance),
      (-2*W-g-clearance - min_clearance, center+l/4+i*l + min_clearance),
      (-min_clearance, center+l/4+i*l + min_clearance),
      (-min_clearance, l-g+i*l)
      ]

  print(scale.format(" ".join(map(lambda pt: xy.format(pt[0], pt[1]), scale_poly))))

# partial scale
scale_left = scale_length - num_full_scales*l
if scale_left > min_trace_width:
  last_scale = []
  last_x = None
  if scale_left <= center-l/4 + min_trace_width + min_clearance:
    last_scale = [(0, num_full_scales*l)]
    scale_edges += [(-min_clearance, num_full_scales*l)]
  elif scale_left <= center+l/4 + min_trace_width + min_clearance:
    last_scale = [
        (0, num_full_scales*l),
        (0, center-l/4+num_full_scales*l),
        (-2*W-g-clearance, center-l/4+num_full_scales*l)
        ]
    scale_edges += [
        (-min_clearance, num_full_scales*l),
        (-min_clearance, center-l/4+num_full_scales*l-min_clearance),
        (-2*W-g-clearance-min_clearance, center-l/4+num_full_scales*l-min_clearance)
        ]
  else:
    last_scale = [
        (0, num_full_scales*l),
        (0, center-l/4+num_full_scales*l),
        (-2*W-g-clearance, center-l/4+num_full_scales*l),
        (-2*W-g-clearance, center+l/4+num_full_scales*l),
        (0, center+l/4+num_full_scales*l)
        ]
    scale_edges += [
        (-min_clearance, num_full_scales*l),
        (-min_clearance, center-l/4+num_full_scales*l-min_clearance),
        (-2*W-g-clearance-min_clearance, center-l/4+num_full_scales*l-min_clearance)
        (-2*W-g-clearance-min_clearance, center+l/4+num_full_scales*l+min_clearance),
        (-min_clearance, center+l/4+num_full_scales*l)
        ]

  last_x = last_scale[-1][0]
  last_scale += [
      (last_x, scale_length),
      (width_ratio*W+clearance, scale_length),
      (width_ratio*W+clearance, num_full_scales*l)
      ]

  print(scale.format(" ".join(map(lambda pt: xy.format(pt[0], pt[1]), last_scale))))

# add ground scale
last_x = scale_edges[-1][0]
scale_edges += [
    (last_x, scale_length),
    (-scale_ground_trace_width - min_clearance - scale_tooth_width, scale_length),
    (-scale_ground_trace_width - min_clearance - scale_tooth_width, 0)
    ]
print(scale.format(" ".join(map(lambda pt: xy.format(pt[0], pt[1]), scale_edges))))

print(epilogue)
