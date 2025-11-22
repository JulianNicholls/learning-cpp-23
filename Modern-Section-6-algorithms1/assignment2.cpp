#include <iostream>

int main()
{
  int x{42}, y{99}, z{0};

  // Mutable is significant here because it makes x & y members of the created
  // functor, allowing them to be updated. Hemce, x & y are incremented both times
  // it is called, making them 44 && 101 in the second call, giving z = 145.
  auto lam = [=, &z]() mutable
  { ++x; ++y; z = x + y; };

  lam();
  lam();

  std::cout << "x = " << x << ", y = " << y << ", z = " << z << std::endl;
}
