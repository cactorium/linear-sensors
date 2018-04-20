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

width = 0.340*25.4
l = 0.200*25.4

step_size = 0.05

perp_clearance = (0.00325 + 0.006) * 25.4
thickness = 0.0065 * 25.4 # 6.5 wide so that it'll definitely pass DRC

print(prologue)

poly_format = "  (fp_poly (pts {} ) (layer F.Cu) (width 0.001))"
point_format = "(xy {} {})"

segments = [(-45, 0, -l/8), (0, 45, 0), (45, 135, -l/8), (-45, 0, l/4-l/8), (0, 45, l/4+0), (45, 135, l/4-l/8)]

for (start, end, offset) in segments:
  start = start*math.pi/180
  end = end*math.pi/180
  points = []
  return_points = []

  alpha = math.atan(width*math.pi*math.cos(start)/l)
  beta = math.atan(width*math.pi*math.cos(end)/l)
  # calculate clearances at the ends of the segments
  start_x = 0 + abs(perp_clearance*math.cos(math.pi/2 - alpha))
  end_x = (end - start)*l/(2.0*math.pi) - abs(perp_clearance*math.cos(math.pi/2 - beta))

  alpha = math.atan(width*math.pi*math.cos(start_x*2.0*math.pi/l + start)/l)
  beta = math.atan(width*math.pi*math.cos(end_x*2.0*math.pi/l + start)/l)
  
  x = start_x
  off = start

  # prepend start point to get the angle right
  y = 0.5*width*math.sin(2.0*math.pi*x/l + start)
  points.append((x + offset, y))
  edge = thickness/math.sin(math.pi-2*alpha)
  return_points.append((x+offset-edge*math.cos(alpha), y+edge*math.sin(alpha)))

  # hack to ensure a straight edge at the end
  x = x + 2*step_size

  while x < end_x - step_size:
    # NOTE: starting point may be a little too close, because the minimum
    # clearance conditions assumed a first order approximation of sine
    y = 0.5*width*math.sin(2.0*math.pi*x/l + off)
    points.append((x + offset, y))

    # project along the normal of the sine function to find the point the appropriate
    # distance away
    slope = width*math.pi/l * math.cos(2.0*math.pi*x/l + off)
    dx = -slope/math.sqrt(1+slope*slope)
    dy = 1/math.sqrt(1+slope*slope)
    return_points.append((x+offset+thickness*dx, y+thickness*dy))
    x = x + step_size

  # append end point
  x = end_x
  y = 0.5*width*math.sin(2.0*math.pi*x/l + off)
  points.append((x + offset, y))
  edge = thickness/math.sin(math.pi-2*beta)
  return_points.append((x+offset-edge*math.cos(beta), y+edge*math.sin(beta)))


  points.extend(reversed(return_points))

  print(poly_format.format(" ".join(map(lambda p: point_format.format(p[0], p[1]), points))))
  # reflect along y axis
  print(poly_format.format(" ".join(map(lambda p: point_format.format(p[0], -p[1]), points))))

print(epilogue)
