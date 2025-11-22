#include <iostream>
#include <complex>

using std::cin, std::cout, std::endl;
using namespace std::literals;    // Needed for the C++14 complex syntax

void valarray_type() {
  cout << "Don't use valarray :)\n\n";
}

void complex_type() {
  std::complex<double> c{3.1, 4.2};
  auto c2 = 3.0 + 4.5i;   // C++14 and above

  cout << c << " :: " << c.real() << " + " << c.imag() << "j\n\n";
  cout << c2 << " :: " << c2.real() << " + " << c2.imag() << "j\n";

  cout << "abs(c2):  " << abs(c2) << endl;
  cout << "arg(c2):  " << arg(c2) << endl;
  cout << "conj(c2): " << conj(c2) << endl;

  // This does work, enter as (r.r, i.i)
  // cout << "Enter a complex number: ";
  // cin >> c2;

  // cout << c2 << " :: " << c2.real() << " + " << c2.imag() << "j\n";
}

int main()
{
  valarray_type();
  complex_type();
}
