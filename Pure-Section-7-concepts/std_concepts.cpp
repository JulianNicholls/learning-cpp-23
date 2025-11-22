#include <concepts>
#include <iostream>
#include <vector>

template <typename FloatType>
  requires std::floating_point<FloatType>
FloatType divide(FloatType a, FloatType b)
{
  return a / b;
}

class Immovable
{
public:
  Immovable() = default;
  Immovable(Immovable &&) = delete;
  Immovable(const Immovable &) = delete;
};

template <typename T>
void insert(T &&arg)
  requires std::move_constructible<T>
{
  std::vector<T> v;

  v.emplace_back(std::forward<T>(arg));
}

template <std::move_constructible T>
void emplaceBack(T &&arg)
{
  std::vector<T> v;

  v.emplace_back(std::forward<T>(arg));
}

template <typename T>           // Concept could be used here too
  requires std::integral<T>
class IntNumber
{
public:
  IntNumber(T num) : num_(num) {}

private:
  T num_;
};

// Abbreviated function type
// equivalent to template<typename T1, typename T2> max(T1 a, T2 b)
auto max(auto a, auto b)
{
  return a > b ? a : b;
}

int main()
{
  // divide(5, 2);   // doesn't compile, not floating point values

  divide(5.0f, 2.0f);
  divide(5.0, 2.0);

  // insert(Immovable{});   // Cannot be done because move construction is required
  // emplaceBack(Immovable{});   // Cannot be done because move construction is required

  insert(5);
  emplaceBack(5.3f);

  IntNumber i(34);
  // IntNumber f(34.1);     // Prevented

  max(2, 3);
  max(2.1, 3.4);
  max(2.1, 3);
}
