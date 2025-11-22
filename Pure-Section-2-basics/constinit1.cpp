#include <iostream>
#include <format>


// Like this, the order of linking is important.
// run2 constinit1 constinit2 yields b = 0
// run2 constinit2 constinit1 yields b = 10
// extern int a;
// int b = a;

// This fixes it.
int& getA();
int bok = getA();

// But, with C++20 constinit, we can go back to
extern int a;
int b = a;

int main() {
  std::cout << std::format("a:    {}\n", a);
  std::cout << std::format("getA: {}\n", getA());
  std::cout << std::format("bok:  {}\n", bok);
  std::cout << std::format("b:    {}\n", b);
}
