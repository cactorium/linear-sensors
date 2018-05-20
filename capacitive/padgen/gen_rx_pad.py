prologue = """(module RX_PAD (layer F.Cu) (tedit {})
  (fp_text reference REF** (at 11.05 -0.05 90) (layer F.SilkS) hide
    (effects (font (size 1 1) (thickness 0.15)))
  )
  (fp_text value RX_PAD (at 0 -0.5) (layer F.Fab)
    (effects (font (size 1 1) (thickness 0.15)))
  )
"""

epilogue = """)"""

from pad_config import *
print(prologue.format(gen_time))

pad = """  (pad {} smd rect (at {} {}) (size {} {}) (layers F.Cu F.Paste F.Mask)
    (solder_mask_margin 0.07))"""

width = width_ratio*W
print(pad.format(1, 0.5*clearance+0.5*width, 0, width, (wavenumber+1)*l))

print(epilogue)
