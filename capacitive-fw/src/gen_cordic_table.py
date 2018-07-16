import math

NUM_BITS = 32

print("""#include <stdint.h>
#include <math.h>
""")
cordic_consts = [math.atan(1/2**i) for i in range(32)]
print("const int64_t cordic_consts[32] = {")
for c in cordic_consts:
  print("  {}*HALF_SCALE_PHASE_UNITS/M_PI,".format(str(c), str(2**31)))
print("};")
