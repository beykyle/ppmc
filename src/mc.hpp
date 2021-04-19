#pragma once
#include <iostream>
#include <cinttypes>
#include <limits>
#include <cmath>
#include <random>
#include <cassert>

namespace mc {
//helpers
double mean(double r, uint64_t count);

double stddev(double r, double r2, uint64_t count);

double relError(double r, double r2, uint64_t count);

double vol(double length_tally, double height_tally, 
           double width       , uint64_t count);

double stddevVol(double length  , double height, 
                 double length2 , double height2, 
                 double width   , uint64_t count);

using Uniform = std::uniform_real_distribution<>;

template<class Func, class YBoundLow, class YBoundUp>
std::pair<double,double> 
Integrate2D(Func f, 
            YBoundLow lower, YBoundUp upper, 
            double x_lower, double x_upper,
            double tol, 
            bool loud = false, uint32_t print_freq = 10000) {
  
  // initialize RNG
  std::mt19937 gen(389648901368); 
  Uniform dx(x_lower, x_upper);
  
  // initialize length tallies
  assert(x_upper > x_lower);
  const double width = x_upper - x_lower;
  double length  = 0;
  double length2 = 0;

  // initialize height tallies
  double height  = 0;
  double height2 = 0;
  
  // initialize volume tallies
  double curr_vol   = 0;
  double stddev_vol = 0;
  double old_vol    = std::numeric_limits<double>::max();
  double dvol       = old_vol;
  // initialize counter
  uint64_t count = 0;

  // loop until convergence
  do{
    // sample independent vars
    const auto x = dx(gen);
    const auto y = Uniform{lower(x),upper(x)}(gen);

    // score length tallies
    const double smpl_length = upper(x) - lower(x);
    assert(smpl_length > 0);
    length   += smpl_length;
    length2  += smpl_length*smpl_length;

    // score height tallies
    const auto smpl_height = f(x,y);
    height   += smpl_height;
    height2  += smpl_height*smpl_height;

    // incrememnt counter
    ++count;

    // assess convergence
    curr_vol = vol(length,height,width,count);
    dvol = fabs((curr_vol - old_vol)/old_vol);
    old_vol = curr_vol;

    // print current tallies
    if (loud and count % print_freq == 0) {
      stddev_vol = stddevVol(length,height,
                             length2,height2,
                             width,count);
      std::cout << count 
                << "\nval   : " << curr_vol
                << " +/- "      << stddev_vol
                << "\ntol   : " << dvol << "\n\n" 
                << std::flush; 
    }
  }
  while ( dvol > tol or count < 10);
 
  if (loud)
    std::cout << "Converged in: " << count << " iterations. \n";

  return {curr_vol, 
          stddevVol(length,height,
                    length2,height2,
                    width,count)};
}

}
