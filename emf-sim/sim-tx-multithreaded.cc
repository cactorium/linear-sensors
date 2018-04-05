#include <atomic>
#include <cmath>
#include <functional>
#include <iostream>
#include <thread>
#include <vector>

#include <Eigen/Dense>

constexpr double mu = 1.2566370614e-6;
constexpr double PI = 3.14159265358979323846;

constexpr double kLength = 49.53;
constexpr double kWidth = 10.16;

template <typename F> double IterateCurve(double increment, F &&f) {
  double accum = 0.0;
  double x = -kLength/2.0, y = -kWidth/2.0;
  const double numDivisionWidth = ceil(kWidth/increment);
  const double numDivisionLength = ceil(kLength/increment);
  // split summations into smaller groups to avoid truncation
  double subsum = 0.0;
  for (int idx = 0; idx < numDivisionLength; ++idx) {
    const double nx = -kLength/2.0 + ((idx + 1)*kLength)/numDivisionLength;
    const double ny = -kWidth/2.0;
    subsum += f(x, y, nx, ny);
    x = nx, y = ny;
  }
  accum += subsum;
  subsum = 0;
  for (int idx = 0; idx < numDivisionWidth; ++idx) {
    const double nx = kLength/2.0;
    const double ny = -kWidth/2.0 + ((idx+1)*kWidth)/numDivisionWidth;
    subsum += f(x, y, nx, ny);
    x = nx, y = ny;
  }
  accum += subsum;
  subsum = 0;
  for (int idx = 0; idx < numDivisionLength; ++idx) {
    const double nx = kLength/2.0 - ((idx+1)*kLength)/numDivisionLength;
    const double ny = kWidth/2.0;
    subsum += f(x, y, nx, ny);
    x = nx, y = ny;
  }
  accum += subsum;
  subsum = 0;
  for (int idx = 0; idx < numDivisionWidth; ++idx) {
    const double nx = -kLength/2.0;
    const double ny = kWidth/2.0 - ((idx+1)*kWidth)/numDivisionWidth;
    subsum += f(x, y, nx, ny);
    x = nx, y = ny;
  }
  accum += subsum;
  // scale for units; sq mm to sq m
  return accum;
}

template <typename F> double IterateArea(double increment, F &&f) {
  double accum = 0.0;
  const double numDivisionWidth = ceil(kWidth/increment);
  const double numDivisionLength = ceil(kLength/increment);
  const double area = (kWidth/numDivisionWidth)*(kLength/numDivisionLength);
  const int numCores = std::thread::hardware_concurrency();

  std::cerr << "numDivisionWidth: " << numDivisionWidth << std::endl;
  std::cerr << "numDivisionLength: " << numDivisionLength << std::endl;
  if (numCores > 0) {
    std::vector<std::thread> workers;
    std::vector<std::atomic<double>> rets(numCores);

    for (int i = 0; i < numCores; ++i) {
      rets[i] = 0.0;
      workers.push_back(std::thread([&](int offset, std::atomic<double>& ret) {
        double localSum = 0.0;
        std::cerr << "thread " << offset << " spawned" << std::endl;
        for (int idxX = offset; idxX < numDivisionLength; idxX += numCores) {
          const double x = -kLength/2.0 + ((idxX + 0.5)*kLength)/numDivisionLength;
          double subsum = 0.0;
          for (int idxY = 0; idxY < numDivisionWidth; ++idxY) {
            const double y = -kWidth/2.0 + ((idxY + 0.5)*kWidth)/numDivisionWidth;
            subsum += area*f(x, y);
          }
          // std::cout << "subsum " << idxX << " " << subsum << std::endl;
          localSum += subsum;
        }
        ret = localSum;
      }, i, std::ref(rets[i])));
    }

    for (int i = 0; i < numCores; ++i) {
      workers[i].join();
      std::cout << "worker " << i << " exited" << std::endl;
      accum += rets[i].load();
    }
  } else {
    std::cerr << "numCores not detected, falling back to single threaded" << std::endl;
    // subdivide by half wavelengths
    for (int idxX = 0; idxX < numDivisionLength; idxX++) {
      const double x = -kLength/2.0 + ((idxX + 0.5)*kLength)/numDivisionLength;
      double subsum = 0.0;
      for (int idxY = 0; idxY < numDivisionWidth; ++idxY) {
        const double y = -kWidth/2.0 + ((idxY + 0.5)*kWidth)/numDivisionWidth;
        subsum += area*f(x, y);
      }
      std::cerr << "subsum " << idxX << " " << subsum << std::endl;
      accum += subsum;
    }
  }
  return 1.0e-6*accum;
}

int main() {
  const double incr = 0.01;

#if 0
  IterateCurve(incr, [&](double x0, double y0, double x1, double y1) {
          std::cout << "(" << x0 << ", " << y0 << "), ";
          return 0.0;
  });
  return 0;
#endif

  const double result = IterateArea(incr, [&](double rx, double ry) {
      return IterateCurve(0.05*incr, [&](double x0, double y0, double x1, double y1) {
          // divide all units by a thousand because they're all in millimeters
          // std::cout << "(" << rx << ", " << ry << ", " << x0 << ", " << y0 << ", " << x1 << ", " << y1 << "), ";
          Eigen::Vector3d r = Eigen::Vector3d(rx, ry, 0.0)/1000.0;
          Eigen::Vector3d l = Eigen::Vector3d(0.5*(x0+x1), 0.5*(y0+y1), 0.0)/1000.0;
          Eigen::Vector3d dl = Eigen::Vector3d(x1-x0, y1-y0, 0.0)/1000.0;
          Eigen::Vector3d rp = r - l;
          Eigen::Vector3d dB = dl.cross(rp)/pow(rp.norm(), 3.0);
          return (mu/(4.0*PI))*dB.z();
      });
  });
  std::cout << "L = " << result << std::endl;
  return 0;
}
