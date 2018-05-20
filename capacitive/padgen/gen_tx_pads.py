prologue = """(module TX_PADS (layer F.Cu) (tedit {})
  (fp_text reference REF** (at 0 0.5) (layer F.SilkS)
    (effects (font (size 1 1) (thickness 0.15)))
  )
  (fp_text value TX_PADS (at 0 -0.5) (layer F.Fab)
    (effects (font (size 1 1) (thickness 0.15)))
  )
"""

epilogue = """)"""

from pad_config import *

print(prologue.format(gen_time))

pad = """  (pad {} smd rect (at {} {}) (size {} {}) (layers F.Cu F.Paste F.Mask)
    (solder_mask_margin 0.07))"""

for i in range(0, wavenumber):
  for j in range(1, 9):
    if j % 2 == 0:
      xpos = -0.5*clearance - W - 0.5*g + (W+g)/2
    else:
      xpos = -0.5*clearance - W - 0.5*g - (W+g)/2
    ypos = l*(i-(wavenumber/2))+(j-0.5)*l/8
    print(pad.format(j, xpos, ypos, W, l/8))

print(epilogue)
