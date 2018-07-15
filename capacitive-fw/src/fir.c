#include "fir.h"

// hp, 100 window
int32_t feed_fir1(uint16_t i) {
  static uint16_t buf[FIR_HP_BUFFER_SZ] = {0};
  static uint8_t half_ptr = FIR_HP_BUFFER_SZ/2;
  static uint8_t cur_ptr = 0;
  static uint32_t sum = 0;

  sum += i;
  sum -= buf[cur_ptr];
  buf[cur_ptr] = i;

  ++cur_ptr;
  if (cur_ptr >= FIR_HP_BUFFER_SZ) {
    cur_ptr = 0;
  }
  ++half_ptr;
  if (half_ptr >= FIR_HP_BUFFER_SZ) {
    half_ptr = 0;
  }
  
  return FIR_HP_BUFFER_SZ*buf[half_ptr] - sum;
}

// lp, 64 window
int32_t feed_fir2(int32_t i) {
  static int32_t buf[FIR_LP_BUFFER_SZ1] = {0};
  static uint8_t cur_ptr = 0;
  static int32_t sum = 0;

  sum += i;
  sum -= buf[cur_ptr];
  buf[cur_ptr] = i;

  ++cur_ptr;
  if (cur_ptr >= FIR_LP_BUFFER_SZ1) {
    cur_ptr = 0;
  }
  
  return sum;
}

// lp, 32 window
int32_t feed_fir3(int32_t i) {
  static int32_t buf[FIR_LP_BUFFER_SZ2] = {0};
  static uint8_t cur_ptr = 0;
  static int32_t sum = 0;

  sum += i;
  sum -= buf[cur_ptr];
  buf[cur_ptr] = i;

  ++cur_ptr;
  if (cur_ptr >= FIR_LP_BUFFER_SZ2) {
    cur_ptr = 0;
  }
  
  return sum;
}
