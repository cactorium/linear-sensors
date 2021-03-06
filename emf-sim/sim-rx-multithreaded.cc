#include <cmath>

#include <atomic>
#include <functional>
#include <iostream>
#include <mutex>
#include <thread>
#include <vector>

#include <Eigen/Dense>

constexpr double PI = 3.14159265358979323846;

constexpr double kLambda = 5.00;
constexpr double kWidth = 8.636;
constexpr double mu = 1.2566370614e-6;
constexpr int kNumWavelengths = 8;

template <typename F> double IterateCurve(double increment, F &&f) {
  struct Segment {
    double x0, y0, x1, y1;
  };
  static std::vector<Segment> pointStore;
  static std::mutex pointStoreLock;

  if (pointStore.size() == 0) {
    std::lock_guard<std::mutex> ul(pointStoreLock);

    // std::cerr << "ps lock" << std::endl;
    if (pointStore.size() == 0) {
      // std::cerr << "ps write" << std::endl;
      double x = 0.0, y = 0.0;
      const double numDivision = ceil(kLambda*kNumWavelengths/increment);
      int idx = 0;
      for (int wavenumber = 0; wavenumber < kNumWavelengths; ++wavenumber) {
        const int limit = (int)((((double)wavenumber+1.0)*numDivision)/kNumWavelengths);
        for (; idx < limit; ++idx) {
          const double nx = kLambda*kNumWavelengths*((double)idx + 1.0)/numDivision;
          const double ny = 0.5*kWidth * sin(2*PI*nx/kLambda);
          pointStore.push_back(Segment{x, y, nx, ny});
          x = nx, y = ny;
        }
      }
      idx = 0;
      for (int wavenumber = 0; wavenumber < kNumWavelengths; ++wavenumber) {
        double subsum = 0.0;
        const int limit = (int)((((double)wavenumber+1.0)*numDivision)/kNumWavelengths);
        for (; idx < limit; ++idx) {
          const double nx = kLambda*kNumWavelengths*(1.0 - ((double)idx + 1.0)/numDivision);
          const double ny = -0.5*kWidth * sin(2*PI*nx/kLambda);
          pointStore.push_back(Segment{x, y, nx, ny});
          x = nx, y = ny;
        }
      }
    }

    // std::cerr << "ps unlock" << std::endl;
  }

  // lock and unlock to make sure no one else is writing to it
  pointStoreLock.lock();
  pointStoreLock.unlock();

  double accum = 0.0;
  double x = 0.0, y = 0.0;
  const double numDivision = ceil(kLambda*kNumWavelengths/increment);
  // split summations into smaller groups to avoid truncation
  int idx = 0;
  for (int wavenumber = 0; wavenumber < 2*kNumWavelengths; ++wavenumber) {
    double subsum = 0.0;
    const int limit = (int)((((double)wavenumber+1.0)*pointStore.size())/(2*kNumWavelengths));
    for (; idx < limit && idx < pointStore.size(); ++idx) {
      auto &segment = pointStore[idx];
      subsum += f(segment.x0, segment.y0, segment.x1, segment.y1);
    }
    accum += subsum;
  }
  return accum;
}

template <typename F> double IterateArea(double increment, F &&f) {
  double accum = 0.0;
  const double numDivision = ceil(kLambda/(2.0*increment));
  std::cerr << "numDivision: " << numDivision << std::endl;

  const int numCores = std::thread::hardware_concurrency();
  if (numCores > 0) {
    std::vector<std::thread> workers;
    std::vector<std::atomic<double>> rets(numCores);
    std::cerr << "splitting off " << numCores << " threads" << std::endl;
    for (int i = 0; i < numCores; ++i) {
      rets[i] = 0.0;
      workers.push_back(std::thread([&](int offset, std::atomic<double> &retVal) {
        std::cout << "thread " << offset << " spawned" << std::endl;
        // subdivide by half wavelengths
        double localAccum = 0.0;
        for (int cross = offset; cross < 2*kNumWavelengths; cross += numCores) {
          const bool isPositive = (cross % 2) == 0;
          double subsum = 0.0;

          for (int idx = 0; idx < numDivision; ++idx) {
            const double x = 0.5*kLambda*((double)idx + 0.5)/numDivision + 0.5*cross*kLambda;
            const double amp = abs(0.5*kWidth*sin(2.0*PI*x/kLambda));
            const int numDivisionY = ceil(2*amp/increment);
            const double area = (kLambda/2.0/numDivision)*(2.0*amp/numDivisionY);
            // std::cerr << "y divisions: " << numDivisionY << std::endl;
            for (int idx2 = 0; idx2 < numDivisionY; ++idx2) {
              // reordered version of -amp + (idx + 0.5)*(2.0*amp/numDivisionY)
              const double y = amp*(2.0*((double)idx + 0.5)/(double)numDivisionY - 1.0);
              if (isPositive) {
                subsum += area*f(x, y);
              } else {
                subsum -= area*f(x, y);
              }
            }
          }

          std::cerr << "subsum " << cross << ": " << subsum << std::endl;
          localAccum += subsum;
        }
        retVal = localAccum;
      }, i, std::ref(rets[i])));
    }

    for (int i = 0; i < numCores; i++) {
      workers[i].join();
      std::cout << "worker " << i << " exited" << std::endl;
      accum += rets[i].load();
    }
  } else {
    std::cerr << "unable to detect number of cores, falling back to normal concurrency" << std::endl;

    // subdivide by half wavelengths
    for (int cross = 0; cross < 2*kNumWavelengths; ++cross) {
      const bool isPositive = (cross % 2) == 0;
      double subsum = 0.0;

      for (int idx = 0; idx < numDivision; ++idx) {
        const double x = 0.5*kLambda*((double)idx + 0.5)/numDivision + 0.5*cross*kLambda;
        const double amp = 0.5*kWidth*sin(2.0*PI*x/kLambda);
        const int numDivisionY = ceil(2*amp/increment);
        const double area = (kLambda/2.0/numDivision)*(2.0*amp/numDivisionY);
        // std::cerr << "y divisions: " << numDivisionY << std::endl;
        for (int idx2 = 0; idx2 < numDivisionY; ++idx2) {
          // reordered version of -amp + (idx + 0.5)*(2.0*amp/numDivisionY)
          const double y = amp*(2.0*((double)idx + 0.5)/(double)numDivisionY - 1.0);
          if (isPositive) {
            subsum += area*f(x, y);
          } else {
            subsum -= area*f(x, y);
          }
        }
      }
      std::cerr << "subsum " << cross << ": " << subsum << std::endl;
      accum += subsum;
    }
  }
  return 1.0e-6*accum;
}

template <typename F> double IterateCircle(double increment, F&& f) {
  const double kRadius = 10.0;
  double accum = 0.0;
  double x = -kRadius, y = 0.0;
  const double numDivision = ceil(2.0*kRadius/increment);
  // split summations into smaller groups to avoid truncation
  int idx = 0;
  for (int wavenumber = 0; wavenumber < 2; ++wavenumber) {
    double subsum = 0.0;
    const int limit = (int)((((double)wavenumber+1.0)*numDivision)/2.0);
    for (; idx < limit; ++idx) {
      const double nx = kRadius*2.0*((double)idx + 1.0)/numDivision - kRadius;
      const double ny = sqrt(kRadius*kRadius - nx*nx);
      subsum += f(x, y, nx, ny);
      x = nx, y = ny;
    }
    accum += subsum;
  }
  idx = 0;
  for (int wavenumber = 0; wavenumber < 2; ++wavenumber) {
    double subsum = 0.0;
    const int limit = (int)((((double)wavenumber+1.0)*numDivision)/2.0);
    for (; idx < limit; ++idx) {
      const double nx = kRadius*2.0*(1.0 - ((double)idx + 1.0)/numDivision) - kRadius;
      const double ny = -sqrt(kRadius*kRadius - nx*nx);
      subsum += f(x, y, nx, ny);
      x = nx, y = ny;
    }
    accum += subsum;
  }
  return accum;
}

int main() {
  const double incr = 0.01;

#if 0
  // test loop around circle to make sure the math works out
  const double testResult = IterateCircle(incr, [&](double x0, double y0, double x1, double y1) {
      const double rx = 0.0;
      const double ry = 0.0;
      Eigen::Vector3d r(rx, ry, 0.0);
      Eigen::Vector3d l(0.5*(x0+x1), 0.5*(y0+y1), 0.0);
      Eigen::Vector3d dl(x1-x0, y1-y0, 0.0);
      Eigen::Vector3d rp = r - l;
      Eigen::Vector3d dB = dl.cross(rp)/pow(rp.norm(), 3.0);
      return (mu/(4.0*PI))*dB[2];
  });
  std::cout << "test result: " << testResult << std::endl;
  const double testResult2 = IterateCircle(incr, [&](double x0, double y0, double x1, double y1) {
      const double rx = -20.0;
      const double ry = 0.0;
      Eigen::Vector3d r(rx, ry, 0.0);
      Eigen::Vector3d l(0.5*(x0+x1), 0.5*(y0+y1), 0.0);
      Eigen::Vector3d dl(x1-x0, y1-y0, 0.0);
      Eigen::Vector3d rp = r - l;
      Eigen::Vector3d dB = dl.cross(rp)/pow(rp.norm(), 3.0);
      return (mu/(4.0*PI))*dB[2];
  });
  std::cout << "test result 2: " << testResult2 << std::endl;

#endif

  const double result = IterateArea(incr, [&](double rx, double ry) {
      return IterateCurve(0.05*incr, [&](double x0, double y0, double x1, double y1) {
          // divide all units by a thousand because they're all in millimeters
          Eigen::Vector3d r = Eigen::Vector3d(rx, ry, 0.0)/1000.0;
          Eigen::Vector3d l = Eigen::Vector3d(0.5*(x0+x1), 0.5*(y0+y1), 0.0)/1000.0;
          Eigen::Vector3d dl = Eigen::Vector3d(x1-x0, y1-y0, 0.0)/1000.0;
          Eigen::Vector3d rp = r - l;
          Eigen::Vector3d dB = dl.cross(rp)/pow(rp.norm(), 3.0);
          return (mu/(4.0*PI))*dB[2];
      });
  });
  std::cout << "L = " << result << std::endl;
  return 0;
}
