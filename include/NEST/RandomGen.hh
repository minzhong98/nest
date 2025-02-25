//
// RandomGen.hh
//
// Created by Jacob Cutter, May 10 2018

#ifndef RANDOMGEN_HH
#define RANDOMGEN_HH 1
#include "xoroshiro.hh"
#include "gcem.hpp"
#include <cmath>
#include <cstdlib>
#include <random>
#include <vector>

using namespace std;

class RandomGen {
 public:
  static RandomGen* rndm();
  void SetSeed(uint64_t s);
  double rand_uniform();
  double rand_gauss(double mean, double sigma, bool zero_min=false);
  double rand_zero_trunc_gauss(double mean, double sigma);
  double FindNewMean(double sigma); //shift Gaussian of mean 1 for 0 truncation
  double rand_exponential(double half_life, double t_min=-1, double t_max=-1);
  double rand_skewGauss(double xi, double omega, double alpha);
  int poisson_draw(double mean);
  int64_t binom_draw(int64_t N0, double prob);
  int integer_range(int min, int max);
  vector<double> VonNeumann(double xMin, double xMax, double yMin, double yMax,
                            double xTest, double yTest, double fValue);
  int SelectRanXeAtom();

 private:
  // Random number generator object for this class only
  //  std::ranlux24 rng;
  xoroshiro128plus64 rng;

  static constexpr double xoroshiro128plus64_min =
      static_cast<double>(xoroshiro128plus64::min());
  static constexpr double xoroshiro128plus64_minmax = static_cast<double>(
      xoroshiro128plus64::max() - xoroshiro128plus64::min());

  static constexpr double two_PI = 2. * M_PI;
  static constexpr double four_minus_PI_div_2 = 0.5 * (4. - M_PI);
  static constexpr double sqrt2 = gcem::sqrt(2.);
  static constexpr double sqrt2_PI = gcem::sqrt(2. * M_PI);
  static constexpr double sqrt2_div_PI = gcem::sqrt(2. / M_PI);
  static constexpr double log2 = gcem::log(2.);

  RandomGen() = default;        // private so that it cannot be manually called
  RandomGen(RandomGen const&);  // copy constructor is private
  void operator=(RandomGen const&);  // assignment operator is private
  static RandomGen* m_pInstance;     // private class pointer instance
};

#endif
