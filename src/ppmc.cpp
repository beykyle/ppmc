#include <ios>
#include <iostream>
#include <cmath>
#include <iomanip>

#include "elhq.hpp"
#include "mc.hpp"

int main() {
  
  // 13 TeV pp collisions
  constexpr double s      = 13*13; // [TeV^2]
  constexpr double alpha  = 1./137;
  constexpr double pi     = M_PI;
  constexpr double factor = (4 * pi * alpha * alpha * 1.537E7) / 
                            (9 * s); // [fb/TeV]
  
  std::cout << "Calculating pp->mu+mu-...\n" << std::flush;
  
  // set up ELHQ parton distribution functions
  const auto u    = elhq::Uv{} + elhq::Us{};
  const auto d    = elhq::Dv{} + elhq::Ds{};
  const auto dbar = elhq::Dbars{};
  const auto ubar = elhq::Ubars{};

  // set up integrator
  auto [result, stddev] = mc::Integrate2D(
       [u,d,dbar,ubar,s](double shat, double x) -> double
       {
         const double sfrac = shat/(x*s);
         return 1/(x*shat) * 
                (   (4.0/9.0) * ( u(x) * ubar(sfrac) + ubar(x) * u(sfrac)) 
                  + (1.0/9.0) * ( d(x) * dbar(sfrac) + dbar(x) * d(sfrac))
                );
       },
       [s](double shat) { return shat/s; },
       [ ](double shat) { return 1.;     },
       1,s,
       1E-14,
       false
      );

  result *=  factor;
  stddev *=  factor;

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
