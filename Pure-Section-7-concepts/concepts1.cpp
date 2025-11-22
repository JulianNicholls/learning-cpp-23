#include <concepts>
#include <iostream>
#include <list>
#include <vector>

using std::cout, std::endl;

// Simple requirement
namespace Simple
{
  template <typename T>
  concept LessThan = requires(T a, T b) {
    a < b;
  };
}

// Compound requirement
namespace Compound
{
  template <typename T>
  concept LessThan = requires(T a, T b) {
    { a < b } noexcept -> std::convertible_to<bool>;
  };
}

// Nested requirements
namespace Nested
{
  template <typename... T>
  concept Addable = requires(T... args) {
    { (... + args) } noexcept;
    requires sizeof...(T) > 1;
  };

  template <typename T>
  concept ContainerType = requires {
    typename T::value_type;
    typename T::iterator;
  };

  template <typename... T>
    requires Addable<T...>
  auto sum(T... args)
  {
    return (... + args);
  };

  // Anonymous concept - 'requires requires'
  template <typename... T>
    requires requires(T... args) {
      { (... + args) } noexcept;
      requires sizeof...(T) > 1;
    }
  auto sum2(T... args)
  {
    return (... + args);
  };

  template <ContainerType Container>
  double average(const Container &vec)
  {
    typename Container::value_type sum{0};

    for (auto v : vec)
    {
      sum += v;
    }

    return static_cast<double>(sum) / vec.size();
  }
}

template <Simple::LessThan T>
auto isGreater(T a, T b)
{
  return a < b;
}

template <Compound::LessThan T>
auto isGreaterNo(T a, T b)
{
  return a < b;
}

class MyType
{
};

class MyType2
{
public:
  bool operator<(const MyType2 &other) const
  {
    return true;
  }
};

class MyType3
{
public:
  bool operator<(const MyType3 &other) const noexcept
  {
    return true;
  }
};

int main()
{
  isGreater(3, 2);
  isGreater(MyType2{}, MyType2{});
  isGreaterNo(MyType3{}, MyType3{});

  // isGreater(MyType{}, MyType{});   // Prevented, MyType has no <
  // isGreaterNo(MyType2{}, MyType2{});   // Prevented, Mytype2 < is not noexcept

  cout << Nested::sum(1, 2, 3, 14) << endl;
  cout << Nested::sum2(1, 3, 3, 18) << endl;

  std::vector<int> vec{1, 4, 8, 3, 6, 10, 4};
  std::list<int> list{1, 4, 7, 3, 6, 12, 4};

  cout << Nested::average(vec) << endl;
  cout << Nested::average(list) << endl;
}
