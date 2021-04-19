#include <iostream>
#include "../src/mc.hpp"

int main() {

  std::cout << "Running test...\n" << std::flush;
  constexpr double expected = -2.52149398231496e7;

  // set up integrator
  auto [result, stddev] = mc::Integrate2D(
       [](double x, double y) {
         return x*y*y - x*x*x * sin(x*y)/y;
       },
       [] (double x) { return 1.;    },
       [] (double x) { return 100.;  },
       -12.3, 0.007, 
       1E-12,
       true,1000000
      );

  auto d = fabs((result - expected)/expected);
  
  if ( d > 0.01 ) {
    std::cout << "Test failed!\n"
              << "int_-12.3^0.0007 dx int_1^100 dy x*y^2 - x^3 * sin(x*y)/y = -2.52149398231496e7\n"
              << "MC result: = "    << result  << "\n"
              << "Relative error: " << d*100   << "%\n" 
              << std::flush;
    return 1;
  }
  else {
    std::cout << "Tests passed!\n" << std::flush;
    return 0;
  }
    
}
