#include "mc.hpp"

using namespace mc;


double mc::mean(double r, uint64_t count) {
  return r/static_cast<double>(count);
};

double mc::stddev(double r, double r2, uint64_t count){
  const double ccount = static_cast<double>(count);
  return std::sqrt((r2 - r * r / ccount ) / (ccount*ccount));
};

double mc::relError(double r, double r2, uint64_t count) {
  const double ccount = static_cast<double>(count);
  return fabs(stddev(r,r2,count) * ccount / r);
};

double mc::vol(double length_tally, double height_tally, double width, uint64_t count) {
  return mean(length_tally,count) * mean(height_tally,count) * width;
};

double mc::stddevVol(double length, double height, 
                     double length2, double height2, 
                     double width, uint64_t count) {
  const double l = mean(length,count);
  const double h = mean(height,count);
  const double dl = stddev(length,length2,count);
  const double dh = stddev(height,height2,count);
  return width * sqrt(l*l*dh*dh + h*h*dl*dl);
};
