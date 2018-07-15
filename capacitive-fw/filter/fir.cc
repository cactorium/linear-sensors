#include <array>
#include <vector>

#include <fstream>
#include <iostream>
#include <sstream>

#define FIR_HP_BUFFER_SZ 100
#define FIR_LP_BUFFER_SZ1 64
#define FIR_LP_BUFFER_SZ2 32

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
  for (auto i: data) {
    int32_t fir1_out = feed_fir1(i);
    int32_t fir2_out = feed_fir2(fir1_out);
    int64_t out = feed_fir3(fir2_out);
    if (count > (FIR_HP_BUFFER_SZ + FIR_LP_BUFFER_SZ1 + FIR_LP_BUFFER_SZ2)) {
      std::cout << out << ",";
    }
    ++count;
  }
  std::cout << std::endl;
  return 0;
}
