import math

# generate a 6.5 mil (0.16 mm) 

prologue = """(module ANT_RX_45_135 (layer F.Cu)
  (at 0 0)
 (fp_text reference "G***" (at 0 0) (layer F.SilkS) hide
  (effects (font (thickness 0.3)))
  )
  (fp_text value "ANT_RX_45_135" (at 0.75 0) (layer F.SilkS) hide
  (effects (font (thickness 0.3)))
  )"""

epilogue = """)"""

width = 8.363
l = 5.08

start = 45*math.pi/180
end = 135*math.pi/180
step_size = 0.05

alpha = math.atan(width*math.pi*math.cos(start)/l)
perp_clearance = (0.00325 + 0.006) * 25.4
beta = math.atan(width*math.pi*math.cos(end)/l)
thickness = 0.0065 * 25.4 # 6.5 wide so that it'll definitely pass DRC

print(prologue)

poly_format = "  (fp_poly (pts {} ) (layer F.Cu) (width 0.001))"
point_format = "(xy {} {})"
points = []

# calculate clearances at the ends of the segments
start_x = 0 + abs(perp_clearance*math.cos(math.pi/2 - alpha))
end_x = (end - start)*l/(2.0*math.pi) - abs(perp_clearance*math.cos(math.pi/2 - beta))

return_points = []
x = start_x
offset = start

while x <= end_x:
  # NOTE: starting point may be a little too close, because the minimum
  # clearance conditions assumed a first order approximation of sine
  y = 0.5*width*math.sin(2.0*math.pi*x/l + offset)
  points.append((x, y))

  # project along the normal of the sine function to find the point the appropriate
  # distance away
  slope = width*math.pi/l * math.cos(2.0*math.pi*x/l + offset)
  dx = -slope/math.sqrt(1+slope*slope)
  dy = 1/math.sqrt(1+slope*slope)
  return_points.append((x+thickness*dx, y+thickness*dy))
  x = x + 0.05

points.extend(reversed(return_points))

print(poly_format.format(" ".join(map(lambda p: point_format.format(p[0], p[1]), points))))

# reflect along y axis
print(poly_format.format(" ".join(map(lambda p: point_format.format(p[0], -p[1]), points))))

print(epilogue)
