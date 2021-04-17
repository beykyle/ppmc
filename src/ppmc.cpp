#include <ios>
#include <iostream>
#include <cmath>
#include <iomanip>

#include "elhq.hpp"
#include "mc.hpp"

int main() {
  
  // 13 TeV pp collisions
  constexpr double s      = 13*13;
  constexpr double alpha  = 1./137;
  constexpr double pi     = M_PI;
  constexpr double factor = (4 * pi * alpha * alpha) / 
                            (9 * s);
  
  std::cout << "Calculating pp->mu+mu-...\n" << std::flush;
  
  // set up ELHQ parton distribution functions
  auto up_quark_pdf = elhq::Uv{} + elhq::Us{};
  auto down_quark_pdf = elhq::Dv{} + elhq::Ds{};
  auto anti_up_quark_pdf = elhq::Ubars{};
  auto anti_down_quark_pdf =  elhq::Dbars{};

  // set up integrator
  auto [result, stddev] = mc::Integrate2D(
       [&up_quark_pdf     , &down_quark_pdf,
        &anti_up_quark_pdf, &anti_down_quark_pdf]
       (double x, double y) {
         return x*y;
       },
       [&](double x) { return 0.;},
       [] (double x) { return 1.;  },
       0,1,0.001
      );

  //result *=  factor;
  //stddev *=  factor;

  std::cout << "sigma [fb]: " 
            << std::scientific
            << std::setprecision(7)
            << result << " +/- " 
            << std::scientific
            << std::setprecision(7)
            << stddev << " +/- " << "\n";
  
  // convergence test
  // TODO
}
