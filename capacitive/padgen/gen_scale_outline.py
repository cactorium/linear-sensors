prologue = """(module SCALE_OUTLINE (layer F.Cu) (tedit {})
  (fp_text reference REF** (at 11.05 -0.05 90) (layer F.SilkS) hide
    (effects (font (size 1 1) (thickness 0.15)))
  )
  (fp_text value SCALE_OUTLINE (at 0 -0.5) (layer F.Fab)
    (effects (font (size 1 1) (thickness 0.15)))
  )
"""

epilogue = """)"""

from pad_config import *
print(prologue.format(gen_time))

line = """  (fp_line (start {} {}) (end {} {}) (layer F.Fab) (width 0.15))"""

print(line.format(-scale_left, 0, -scale_left, 1))
print(line.format(scale_right, 0, scale_right, 1))

print(epilogue)
