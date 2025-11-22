#include <format>
#include <iostream>

struct A
{
  virtual int get() const
  {
    return 'A';
  }
};

struct B : A
{
  // This is a valid override, despite the base class function not being constexpr
  constexpr int get() const override
  {
    return 'B';
  }
};

constexpr int invoke(const A *a)
{
  return a->get(); // Invokes virtual function, C++20 only
};

constexpr int square(int x)
{
  try
  { // Only allowed in C++20
    return x * x;
  }
  catch (...)
  {
    return 0;
  }
}

int main()
{
  auto result = square(17);

  constexpr B b{};
  static_assert(invoke(&b) == 'B');
}
