#ifndef FIR_H_
#define FIR_H_

#include <stdint.h>

#define FIR_HP_BUFFER_SZ 100
#define FIR_LP_BUFFER_SZ1 64
#define FIR_LP_BUFFER_SZ2 32

int32_t feed_fir1(uint16_t i);
int32_t feed_fir2(int32_t i);
int32_t feed_fir3(int32_t i);

#endif
