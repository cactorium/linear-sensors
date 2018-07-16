#include <array>
#include <vector>

#include <fstream>
#include <iostream>
#include <sstream>

#define FIR_HP_BUFFER_SZ 100/2
#define FIR_LP_BUFFER_SZ1 64/2
#define FIR_LP_BUFFER_SZ2 32/2

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

static int32_t trig_normalize(int32_t x) {
  while (x >= 100) {
    x -= 100;
  }
  while (x < 0) {
    x += 100;
  }

  return x;
}

const int32_t trig_quadrant[] = {
  0, 134841613, 269151069, 402398308, 534057465, 663608942, 790541456, 914354065, 1034558137, 1150679279, 1262259217, 1368857594, 1470053715, 1565448206, 1654664588, 1737350765, 1813180412, 1881854265, 1943101298, 1996679798, 2042378316, 2080016499, 2109445807, 2130550097, 2143246078, 2147483647
};

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
    return trig_quadrant[x-75];
  }
}

int64_t phase_i = 0;
int64_t phase_q = 0;
uint16_t phase_calc_count = 0;

static void feed_phase_calc(int32_t val) {
  phase_i += (((int64_t)sin32(2*phase_calc_count))*val)/2048;
  phase_q += (((int64_t)cos32(2*phase_calc_count))*val)/2048;
  phase_calc_count++;
}

int main(int argc, char** argv) {
  if (argc < 2) {
    std::cerr << "USAGE: " << argv[0] << " INPUT" << std::endl;
    return 0;
  }
  std::ifstream f(argv[1]);
  std::string s;

  std::getline(f, s);

  std::vector<uint16_t> data;
  int previous = 0;
  int pos = s.find(',');
  while (pos != std::string::npos) {
    auto numstr = s.substr(previous, pos-previous);
    auto val = std::stoul(numstr, nullptr, 16);
    // std::cout << previous << " " << pos << " " << numstr << " " << val << std::endl;
    data.push_back(val);
    previous = pos + 1;
    pos = s.find(',', previous);
  }

  int count = 0;
  std::vector<int32_t> fs;
  std::vector<int64_t> is, qs;
  for (auto i: data) {
    if (count % 2 == 0) {
      int32_t fir1_out = feed_fir1(i);
      int32_t fir2_out = feed_fir2(fir1_out);
      int32_t out = feed_fir3(fir2_out);
      fs.push_back(out);
      if (count > (FIR_HP_BUFFER_SZ +FIR_LP_BUFFER_SZ1 + FIR_LP_BUFFER_SZ2)) {
        feed_phase_calc(out);
        is.push_back(phase_i);
        qs.push_back(phase_q);
      }
    }
    ++count;
  }

#if 1
  for (auto v : fs) {
    std::cout << v << ",";
  }
  std::cout << std::endl;

  for (int i = 0; i < is.size(); ++i) {
    std::cout << cos32(i) << ",";
  }
  std::cout << std::endl;
  for (int i = 0; i < is.size(); ++i) {
    std::cout << sin32(i) << ",";
  }
  std::cout << std::endl;
#else
  for (auto v : is) {
    std::cout << v << ",";
  }
  std::cout << std::endl;

  for (auto v : qs) {
    std::cout << v << ",";
  }
  std::cout << std::endl;
#endif
  return 0;
}
