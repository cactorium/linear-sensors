import math

trig_consts = [str(int((2**31-1)*math.sin(math.pi/2*(x/25.)))) for x in range(25+1)]

print("const int32_t trig_quadrant[] = {")
print("  {}".format(", ".join(trig_consts)))
print("};")
