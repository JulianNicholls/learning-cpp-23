#include <iostream>

using std::cout, std::endl;

constexpr double miles_to_km(double miles) { return miles * 1.6093; };    // Pure function

const double dist1 = miles_to_km(40);

double arg{37};
double dist2 = miles_to_km(arg);

// This is not valid because arg is not const, and so can't be evaluated at compile time
// constexpr double dist4 = miles_to_km(arg);

// This is, because it will be evaluated at runtime
const double dist4 = miles_to_km(arg);

// Since C++14, it is possible to have multiple statements, variable declarations and flow control
constexpr long factorial(long n)
{
  long fac = 1;

  for(long i = 2; i < n; ++i) {
    fac *= i;
  }

  return fac;
}

constexpr long fac17 = factorial(17);

int main() {
  cout << "dist1:  " << dist1 << endl;
  cout << "dist2:  " << dist2 << endl;
  cout << "fac17:  " << fac17 << endl;
}
