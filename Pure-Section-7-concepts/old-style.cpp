#include <iostream>
#include <vector>

template <typename FloatType, std::enable_if_t<std::is_floating_point_v<FloatType>> * = nullptr>
FloatType divide(FloatType a, FloatType b)
{
  return a / b;
}

template <typename T>
T divide2(T a, T b)
{
  static_assert(std::is_floating_point_v<T>, "Arguments must be floating point");

  return a / b;
}

class Immovable {
  public:

  Immovable() = default;
  Immovable(Immovable&&) = delete;
  Immovable(const Immovable&) = delete;
};

template <typename T, std::enable_if_t<std::is_move_constructible_v<T>> * = nullptr>
void insert(T &&arg)
{
  std::vector<T> v;

  v.emplace_back(std::forward<T>(arg));
}

int main()
{
  // divide(5, 2);   // doesn't compile, not floating point values
  // divide2(5, 2);  // doesn't compile, not floating point values

  divide(5.0f, 2.0f);
  divide(5.0, 2.0);

  divide2(5.0f, 2.0f);
  divide2(5.0, 2.0);

  // insert(Immovable{});   // Cannot be done because move construction is required

  insert(5);
}
