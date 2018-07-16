#include "trig.h"
#include "trig_consts.h"

static int32_t trig_normalize(int32_t x) {
  while (x >= 4*quadrant_size) {
    x -= 4*quadrant_size;
  }
  while (x < 0) {
    x += 4*quadrant_size;
  }

  return x;
}

static int32_t sin32(int32_t x_) {
  const int32_t x = trig_normalize(x_);
  if (x < quadrant_size) {
    return trig_quadrant[x];
  } else if (x < 2*quadrant_size) {
    return trig_quadrant[2*quadrant_size-x];
  } else if (x < 3*quadrant_size) {
    return -trig_quadrant[x-2*quadrant_size];
  } else {
    return -trig_quadrant[4*quadrant_size-x];
  }
}

static int32_t cos32(int32_t x_) {
  const int32_t x = trig_normalize(x_);
  if (x < quadrant_size) {
    return trig_quadrant[quadrant_size-x];
  } else if (x < 2*quadrant_size) {
    return -trig_quadrant[x-quadrant_size];
  } else if (x < 3*quadrant_size) {
    return -trig_quadrant[3*quadrant_size-x];
  } else {
    return trig_quadrant[x-3*quadrant_size];
  }
}

