import math

FREQUENCY = 1e+3
SAMPLE_RATE = 96e+3

trig_consts = [str(int((2**31-1)*math.sin(2*math.pi*x*FREQUENCY/SAMPLE_RATE))) for x in range(int(SAMPLE_RATE/FREQUENCY/4)+1)]

print("#define quadrant_size {}".format(int(SAMPLE_RATE/FREQUENCY/4)));
print()
print("const int32_t trig_quadrant[quadrant_size+1] = {")
print("  {}".format(", ".join(trig_consts)))
print("};")
