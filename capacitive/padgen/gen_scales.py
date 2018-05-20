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

# TODO
test_poly = [(0, 0), (0, 10), (15, 15), (15, 0)]
print(scale.format(" ".join(map(lambda pt: xy.format(pt[0], pt[1]), test_poly))))

print(epilogue)
