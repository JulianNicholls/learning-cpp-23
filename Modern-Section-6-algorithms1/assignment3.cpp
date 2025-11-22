#include <iostream>

int main()
{
  int y = 1;

  auto lam = [y = y+1](int x) { return x + y; };

  std::cout << "lam result = " << lam(5) << ", y = " << y << std::endl;
}
