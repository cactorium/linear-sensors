#include "trig.h"
#include "trig_consts.h"

static int32_t trig_normalize(int32_t x) {
  while (x >= 100) {
    x -= 100;
  }
  while (x < 0) {
    x += 100;
  }

  return x;
}

int32_t sin32(int32_t x_) {
  const int32_t x = trig_normalize(x_);
  if (x < 25) {
    return trig_quadrant[x];
  } else if (x < 50) {
    return trig_quadrant[50-x];
  } else if (x < 75) {
    return -trig_quadrant[x-50];
  } else {
    return -trig_quadrant[100-x];
  }
}

int32_t cos32(int32_t x_) {
  const int32_t x = trig_normalize(x_);
  if (x < 25) {
    return trig_quadrant[25-x];
  } else if (x < 50) {
    return -trig_quadrant[x-25];
  } else if (x < 75) {
    return -trig_quadrant[75-x];
  } else {
    return -trig_quadrant[x-75];
  }
}

