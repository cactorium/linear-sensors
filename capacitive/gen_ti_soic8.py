prologue = """(module TI_SOIC-8 (layer F.Cu) (tedit 5B00C6CE)
  (fp_text reference REF** (at 0 0.5) (layer F.SilkS)
    (effects (font (size 1 1) (thickness 0.15)))
  )
  (fp_text value TI_SOIC-8 (at 0 -0.5) (layer F.Fab)
    (effects (font (size 1 1) (thickness 0.15)))
  )"""

epilogue = """)"""

# Using the data from http://www.tevetron.hr/upload_data/site_files/ref02ap-tex.pdf
# The pad drawing isn't included in the TLV6092


package_x = 5.00
package_y = 4.00

width = 5.40
spacing = 1.27
X = 0.60
Y = 1.55

print(prologue)

circle_size = 0.25
print(" (fp_circle (center {} {}) (end {} {}) (layer F.SilkS) (width 0.15))""".format(
  -package_x/2 - 2*circle_size,
  package_y/2 - circle_size,
  -package_x/2 - 2*circle_size,
  package_y/2 - 2*circle_size))

# size of first pin designator
angle = 0.15
for x, y, nx, ny in [
    (-package_x/2+angle, package_y/2, -package_x/2, package_y/2-angle),
    (-package_x/2, package_y/2 - angle, -package_x/2, -package_y/2),
    (-package_x/2, -package_y/2, -package_x/2+angle, -package_y/2),
    (package_x/2-angle, -package_y/2, package_x/2, -package_y/2),
    (package_x/2, -package_y/2, package_x/2, package_y/2),
    (package_x/2, package_y/2, package_x/2-angle, package_y/2)]:
  print("""  (fp_line (start {} {}) (end {} {}) (layer F.SilkS) (width 0.15))""".
      format(x, y, nx, ny))

# print fab outline
fab_width = package_x+0.4
fab_height = width+Y+0.2

x = -fab_width/2
y = fab_height/2
nx = -fab_width/2
ny = -fab_height/2
for _ in range(0, 4):
  print("""  (fp_line (start {} {}) (end {} {}) (layer F.Fab) (width 0.15))""".
      format(x, y, nx, ny))
  x, y, nx, ny = nx, ny, -x, -y

courtyard_width = package_x + 0.2
courtyard_height = package_y + 0.2

x = -courtyard_width/2
y = courtyard_height/2
nx = -courtyard_width/2
ny = -courtyard_height/2
for _ in range(0, 4):
  print("""  (fp_line (start {} {}) (end {} {}) (layer F.CrtYd) (width 0.15))""".
      format(x, y, nx, ny))
  x, y, nx, ny = nx, ny, -x, -y


pad = """  (pad {} smd rect (at {} {}) (size {} {}) (layers F.Cu F.Paste F.Mask)
    (solder_mask_margin 0.07))"""

offset = 1
for i in range(0, 4):
  print(pad.format(i + offset, -1.5*spacing + i*spacing, width/2, X, Y))
offset = offset + 4

for i in range(0, 4):
  print(pad.format(i + offset, 1.5*spacing - i*spacing, -width/2, X, Y))
offset = offset + 4

print(epilogue)
