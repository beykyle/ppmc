#pragma once
#include <iostream>
#include <cinttypes>
#include <limits>
#include <cmath>
#include <random>

namespace mc {

  using Uniform = std::uniform_real_distribution<>;

  template<class Func, class YBoundLow, class YBoundUp>
  std::pair<double,double> 
  Integrate2D(Func f, 
              YBoundLow lower, YBoundUp upper, 
              double x_lower, double x_upper,
              double tol) {
    
    // initialize RNG
    std::random_device rd;  
    std::mt19937 gen(rd()); 
    Uniform dx(x_lower, x_upper);

    // initialize tallies
    uint64_t count  = 0;
    double   res    = 0;
    double   res_2  = 0;
    double   old_res = std::numeric_limits<double>::max();

    auto stddev = [](double r, double r2, uint64_t count){
      const double ccount = static_cast<double>(count);
      return (r2 - r * r / ccount ) / (ccount*ccount);
    };
    
    // loop unitl convergence
    do{
      // sample independent vars
      const auto x = dx(gen);
      const auto y = Uniform{lower(x),upper(x)}(gen);

      // score tallies
      const auto val = f(x,y);
      old_res = res;
      res    += val;
      res_2  +=  val*val;
      ++count;

      // print progress
      if (count % 100 == 0) 
        std::cout << "N  : " << count 
                  << "\ntol: " << tol << "\n" << std::flush; 
    }
    while ( stddev(res, res_2, count) > tol );
    
    return {res, stddev(res, res_2, count)};
  }

}
