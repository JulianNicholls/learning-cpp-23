#include <iostream>
#include <utility>

class Number
{
public:
  Number() = default;
  constexpr Number(int in) : value_{in} {}
  constexpr void set(int in) { value_ = in; }
  constexpr int get() const { return value_; }

  // These being external now means that 3 < x works as well as x > 3
  friend constexpr bool operator==(const Number &lhs, const Number &rhs) { return lhs.value_ == rhs.value_; }
  friend constexpr bool operator<(const Number &lhs, const Number &rhs) { return lhs.value_ < rhs.value_; }

private:
  int value_;
};

int main()
{
  using namespace std::rel_ops;

  constexpr Number x{5}, y{6};

  std::cout << std::boolalpha << "x == y: " << (x == y) << std::endl;
  std::cout << "x != y: " << (x != y) << std::endl;
  std::cout << "x <  y: " << (x < y) << std::endl;
  std::cout << "x >  y: " << (x > y) << std::endl;
  std::cout << "x <= y: " << (x <= y) << std::endl;
  std::cout << "x >= y: " << (x >= y) << std::endl;

  std::cout << "x >  3: " << (x < 3) << std::endl;

  // This now works, because both sides can be changed to class Number
  std::cout << "3 >  x: " << (3 < x) << std::endl;
}
