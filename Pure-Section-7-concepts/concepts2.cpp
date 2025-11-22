#include <concepts>
#include <iostream>
#include <list>
#include <type_traits>
#include <vector>

using std::cout, std::endl;

namespace Concepts
{
  template <typename T>
  concept Pointer = std::is_pointer_v<T>;

  template <typename T>
  concept M1Pointer = Pointer<T> && sizeof(T) == 8;

  template <typename T>
  concept Integral = std::is_integral_v<T>;

  template <typename T>
  concept Floating = std::is_floating_point_v<T>;

  template <typename T>
  concept Arithmetic = Integral<T> || Floating<T>;

}

namespace Functions
{
  template <typename T>
    requires Concepts::M1Pointer<T>
  void apply(T ptr)
  {
    cout << static_cast<void *>(ptr) << endl;
  }

  template <typename T>
    requires Concepts::Arithmetic<T>
  auto add(T a, T b)
  {
    return a + b;
  }

  template <typename T, typename Callable>
    requires std::invocable<Callable>
  void print(T arg, Callable callable)
  {
    callable();
    cout << arg << "\n";
    callable();
  }

  template <typename Callable, typename... Args>
    // requires std::predicate<Callable>      // This just doesn't work :( either with no Args,  Args or Args...
  bool all_of(Callable callable, Args... args)
  {
    return (callable(args) && ...);
  }
}

bool even(int x)
{
  return x % 2 == 0;
}

std::string odd(int x)
{
  return x % 2 != 0 ? "true" : "false";
}

int main()
{
  int t;
  Functions::apply(&t);

  cout << Functions::add(23, 45) << endl;
  cout << Functions::add(23.5, 45.9) << endl;

  Functions::print(100, []()
                   { cout << "==========\n"; });

  cout << std::boolalpha << Functions::all_of(even, 2, 4, 6, 8) << endl;

  cout << std::boolalpha << Functions::all_of(even, 3, 5, 6, 9) << endl;
}
