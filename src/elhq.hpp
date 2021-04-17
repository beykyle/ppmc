#pragma once
#include <cmath>
#include <experimental/tuple>

// ELHQ parton distribution functions, with arithmetic resolved at compile time
namespace elhq {

template<class ... Funcs>
struct Sum {
private:
  constexpr static std::tuple<Funcs ...> funcs{};
public:
  double operator() (double x) const {
    double sum = 0;
    std::experimental::apply(
        [&sum,&x](Funcs const & ... f){
          ((sum += f(x)),...); 
        },
      funcs
    );
    return sum;
  }
  template<class ... OtherFuncs>
  auto operator+ (const Sum<OtherFuncs ...>& rhs) const {
    return Sum<Funcs ..., OtherFuncs ...>{};
  }
};

struct Uv {
  double operator() (double x) const {
    return ((1.78 / std::sqrt(x)) * std::pow((1 - std::pow(x,1.51)),3.5));
  }
  template<class Func>
  auto operator+(Func f) { return Sum<Uv,Func>{}; }
};

struct Dv {
  double operator() (double x) const {
    return ((0.67 * std::pow(x,-0.6) ) * std::pow((1 - std::pow(x,1.51)),4.5));
  }
  template<class Func>
  auto operator+(Func f) { return Sum<Dv,Func>{}; }
};

struct Us {
  double operator() (double x) const {
    return (0.182  * std::pow((1 - x),8.54))/x;
  }
  template<class Func>
  auto operator+(Func f) { return Sum<Us,Func>{}; }
};

struct Ds {
private:
  const Us f{};
public:
double operator() (double x) const {
  return f(x);
}
  template<class Func>
  auto operator+(Func f) { return Sum<Ds,Func>{}; }
};

struct Ss {
  double operator() (double x) const {
    return (0.081  * std::pow((1 - x),8.54))/x;
  }
  template<class Func>
  auto operator+(Func f) { return Sum<Ss,Func>{}; }
};

struct G {
  double operator() (double x) const {
    return (2.62 + 9.17 *x)*std::pow((1-x),5.9)/x;
  }
  template<class Func>
  auto operator+(Func f) { return Sum<G,Func>{}; }
};

struct Ubars {
private:
  const Us f{};
public:
  double operator() (double x) {
    return f(x);
  }
  template<class Func>
  auto operator+(Func f) { return Sum<Ubars,Func>{}; }
};

struct Dbars {
private:
  const Ds f{};
public:
  double operator() (double x) {
    return f(x);
  }
  template<class Func>
  auto operator+(Func f) { return Sum<Dbars,Func>{}; }
};

struct Sbars {
private:
  const Ss f{};
public:
  double operator() (double x) {
    return f(x);
  }
  template<class Func>
  auto operator+(Func f) { return Sum<Sbars,Func>{}; }
};
}
