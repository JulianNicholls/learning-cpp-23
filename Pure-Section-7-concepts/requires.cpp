#include <concepts>
#include <iostream>
#include <vector>

template <typename FloatType>
requires std::floating_point<FloatType>
FloatType divide(FloatType a, FloatType b)
{
  return a / b;
}

class Immovable {
  public:

  Immovable() = default;
  Immovable(Immovable&&) = delete;
  Immovable(const Immovable&) = delete;
};

template <typename T>
requires std::move_constructible<T>
void insert(T &&arg)
{
  std::vector<T> v;

  v.emplace_back(std::forward<T>(arg));
}

int main()
{
  // divide(5, 2);   // doesn't compile, not floating point values

  divide(5.0f, 2.0f);
  divide(5.0, 2.0);

  // insert(Immovable{});   // Cannot be done because move construction is required

  insert(5);
}
