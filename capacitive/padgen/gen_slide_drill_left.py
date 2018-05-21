prologue = """(module SLIDE_DRILL_LEFT (layer F.Cu) (tedit {})
  (fp_text reference REF** (at 11.05 -0.05 90) (layer F.SilkS) hide
    (effects (font (size 1 1) (thickness 0.15)))
  )
  (fp_text value SLIDE_DRILL_LEFT (at 0 -0.5) (layer F.Fab)
    (effects (font (size 1 1) (thickness 0.15)))
  )"""

epilogue = """)"""

from pad_config import *
print(prologue.format(gen_time))

pad = """  (pad {} smd rect (at {} {}) (size {} {}) (layers F.Cu F.Paste F.Mask)
    (solder_mask_margin 0.07))"""
pad = """  (pad {} thru_hole circle (at {} {}) (size {} {}) (drill {}) (layers *.Cu *.Mask))"""

total_dia = slide_drill_dia + slide_drill_ring_dia
print(pad.format(1, 0.5*total_dia + scale_left, 0, total_dia, total_dia, slide_drill_dia))

print(epilogue)
