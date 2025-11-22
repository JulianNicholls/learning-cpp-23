#include <iostream>
#include <utility>

class Number
{
public:
  Number() = default;
  constexpr Number(int in) : value_{in} {}
  constexpr void set(int in) { value_ = in; }
  constexpr int get() const { return value_; }

  // The default works and creates both <=> and ==, but...
  // auto operator<=>(const Number &rhs) const = default;

  // ...if we do it, we have to provide both separately
  auto operator<=>(const Number &rhs) const { return value_ <=> rhs.value_; }
  bool operator==(const Number &rhs) const { return value_ == rhs.value_; }

  // Alternatively, they can be provided as 2 argument friends
private:
  int value_;
};

int main()
{
  constexpr Number x{5}, y{6};

  std::cout << std::boolalpha << "x == y: " << (x == y) << std::endl;
  std::cout << "x != y: " << (x != y) << std::endl;
  std::cout << "x <  y: " << (x < y) << std::endl;
  std::cout << "x >  y: " << (x > y) << std::endl;
  std::cout << "x <= y: " << (x <= y) << std::endl;
  std::cout << "x >= y: " << (x >= y) << std::endl;

  std::cout << "x >  3: " << (x < 3) << std::endl;
  std::cout << "3 >  x: " << (3 < x) << std::endl;
}
