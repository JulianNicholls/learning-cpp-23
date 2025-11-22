#include <iomanip>
#include <iostream>
#include <string>
#include <tuple>

using namespace std::string_literals;

using std::cout, std::endl;
using std::string;
using std::tuple;

tuple<double, int, string> multi_return()
{
  return tuple{96.8, 36, "Temperature"};
}

void func(double d, int i, string s)
{
  cout << "\nInside func: d: " << d << ", i: " << i << ", s: " << s << endl;
}

class DIS
{
public:
  DIS(double d, int i, string s) : d_{d}, i_{i}, s_{s} {}

  void print() const
  {
    cout << "DIS: d: " << d_ << ", i: " << i_ << ", s: " << s_ << endl;
  }

private:
  double d_;
  int i_;
  string s_;
};

int main()
{
  auto tuple1{std::make_tuple(1.1f, 2, "String"s)};
  tuple<string, double, int> tuple2{"Second", 2.3, 10};
  tuple tuple17{2.3, "C++17"s, 65536}; // C++17 CTAD

  cout << "tuple1 (get)  : (" << std::get<0>(tuple1) << ", "
       << std::get<1>(tuple1) << ", "
       << std::get<2>(tuple1) << ")\n";

  cout << "tuple1 (types): (" << std::get<float>(tuple1) << ", "
       << std::get<int>(tuple1) << ", "
       << std::get<std::string>(tuple1) << ")\n"; // C++14

  float d;
  int i;
  string s;

  std::tie(s, d, i) = tuple2;

  cout << "\ntuple2 (tie)  : (" << s << ", " << d << ", " << i << ")\n";

  // C++17 alows structured binding of the CTAD tuple17
  auto [dbl, str, inte] = tuple17;
  cout << "\ntuple17 (auto): (" << dbl << ", " << str << ", " << inte << ")\n";

  auto [d2, i2, s2] = multi_return();
  cout << "\nmulti (auto)  : (" << d2 << ", " << i2 << ", " << s2 << ")\n";

  std::apply(func, multi_return());

  auto test = std::make_from_tuple<DIS>(multi_return());
  test.print();
}
