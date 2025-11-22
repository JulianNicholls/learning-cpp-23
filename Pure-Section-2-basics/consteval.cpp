#include <iostream>

consteval int sum(int x, int y)  {
  return x + y;
}

consteval int product(int x, int y) {
  return x * y;
}

consteval int subtract(int x, int y) {
  return x - y;
}

consteval int divide(int x, int y)
{
  return x / y;
}

// An immediate function can only call other consteval or constexpr functions
consteval int operate(int x, int y, char op)
{
  switch(op) {
    case 'A': return sum(x, y);
    case 'S': return subtract(x, y);
    case 'M': return product(x, y);
    case 'D': return divide(x, y);
  }

  return 0;
}

int main()
{
  std::cout << sum(3, 5) << std::endl;

  const int a = 10;
  std::cout << operate(a, 5, 'A') << std::endl;
  std::cout << operate(a, 5, 'S') << std::endl;
  std::cout << operate(a, 5, 'M') << std::endl;
  std::cout << operate(a, 5, 'D') << std::endl;
}
