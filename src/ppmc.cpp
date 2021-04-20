#include <ios>
#include <iostream>
#include <cmath>
#include <iomanip>
#include <vector>

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

  // this integral was calculated in the high energy limit (m_mu ~ mu_q -> 0),
  // so it diverges at low energy. 
  // We need to use low-energy cutoffs for parton COM frame energy^2 (shat)
  std::vector<double> Mcut {0.01, 0.1, 1.0}; // Tev
  
  // set up ELHQ parton distribution functions
  const auto u    = elhq::Uv{} + elhq::Us{};
  const auto d    = elhq::Dv{} + elhq::Ds{};
  const auto dbar = elhq::Dbars{};
  const auto ubar = elhq::Ubars{};

  for (const auto cutoff : Mcut) {
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
         cutoff*cutoff,s,
         1E-14,
         false
        );

    result *=  factor;
    stddev *=  factor;

    std::cout << "Low energy cutoff [TeV]: " << cutoff
              << "\nsigma [fb]: " 
              << std::scientific
              << std::setprecision(7)
              << result << " +/- " 
              << std::scientific
              << std::setprecision(7)
              << stddev << " +/- " << "\n";
  
  }

  // convergence test
  // TODO
}
