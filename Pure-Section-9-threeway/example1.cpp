#include <iostream>

// Member comparison operators
class Number
{
public:
  Number() = default;
  constexpr Number(int in) : value_{in} {}
  constexpr void set(int in) { value_ = in; }
  constexpr int get() const { return value_; }

  bool operator==(const Number &other) const { return value_ == other.value_; }
  bool operator!=(const Number &other) const { return !(*this == other); }
  bool operator<(const Number &other) const { return value_ < other.value_; }
  bool operator>(const Number &other) const { return other < *this; }
  bool operator<=(const Number &other) const { return !(other < *this); }
  bool operator>=(const Number &other) const { return !(*this < other); }

private:
  int value_;
};

int main()
{
  Number x{5}, y{6};

  std::cout << std::boolalpha << "x == y: " << (x == y) << std::endl;
  std::cout << "x != y: " << (x != y) << std::endl;
  std::cout << "x <  y: " << (x < y) << std::endl;
  std::cout << "x >  y: " << (x > y) << std::endl;
  std::cout << "x <= y: " << (x <= y) << std::endl;
  std::cout << "x >= y: " << (x >= y) << std::endl;

  std::cout << "x >  3: " << (x > 3) << std::endl;

  // This won't work this way because 3 is not a Number
  // std::cout << "3 >  x: " << (3 > x) << std::endl;
}
