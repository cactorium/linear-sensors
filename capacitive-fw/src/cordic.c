#include "cordic_consts.h"

#define CORDIC_POW2(i)         (1 << i)
#define CORDIC_LOOP_ITER(i)     do { \
                                  if (y < 0) { \
                                    int64_t newx = x - y / CORDIC_POW2(i); \
                                    int64_t newy = y + x / CORDIC_POW2(i); \
                                    x = newx; y = newy; \
                                    ret -= cordic_consts[i]; \
                                  } else { \
                                    int64_t newx = x + y / CORDIC_POW2(i); \
                                    int64_t newy = y - x / CORDIC_POW2(i); \
                                    x = newx; y = newy; \
                                    ret += cordic_consts[i]; \
                                  } \
                                } while (0)

// algorithm from https://www.mathworks.com/help/fixedpoint/examples/calculate-fixed-point-arctangent.html
// returns 2**31*atan(x, y)*HALF_SCALE/(math.pi), where HALF_SCALE is half the period
// of the capacitive scales
static int64_t cordic_scaled_atan(int64_t x, int64_t y) {
  uint8_t x_neg = x < 0;
  uint8_t y_neg = y < 0;
  if (x_neg) {
    x = -x;
  }
  int64_t ret = 0;
  CORDIC_LOOP_ITER(0);
  CORDIC_LOOP_ITER(1);
  CORDIC_LOOP_ITER(2);
  CORDIC_LOOP_ITER(3);
  CORDIC_LOOP_ITER(4);
  CORDIC_LOOP_ITER(5);
  CORDIC_LOOP_ITER(6);
  CORDIC_LOOP_ITER(7);
  CORDIC_LOOP_ITER(8);
  CORDIC_LOOP_ITER(9);
  CORDIC_LOOP_ITER(10);
  CORDIC_LOOP_ITER(11);
  /*
  CORDIC_LOOP_ITER(12);
  CORDIC_LOOP_ITER(13);
  CORDIC_LOOP_ITER(14);
  CORDIC_LOOP_ITER(15);
  CORDIC_LOOP_ITER(16);
  CORDIC_LOOP_ITER(17);
  CORDIC_LOOP_ITER(18);
  CORDIC_LOOP_ITER(19);
  CORDIC_LOOP_ITER(20);
  CORDIC_LOOP_ITER(21);
  CORDIC_LOOP_ITER(22);
  CORDIC_LOOP_ITER(23);
  CORDIC_LOOP_ITER(24);
  CORDIC_LOOP_ITER(25);
  CORDIC_LOOP_ITER(26);
  CORDIC_LOOP_ITER(27);
  CORDIC_LOOP_ITER(28);
  CORDIC_LOOP_ITER(29);
  CORDIC_LOOP_ITER(30);
  CORDIC_LOOP_ITER(31);
  */
  if (x_neg) {
    if (y_neg) {
      return -HALF_SCALE_PHASE_UNITS - ret;
    } else {
      return HALF_SCALE_PHASE_UNITS - ret;
    }
  } else {
    return ret;
  }
}

#undef CORDIC_POW2
#undef CORDIC_LOOP_ITER
