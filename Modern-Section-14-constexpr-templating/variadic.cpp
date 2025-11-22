#include <iostream>
#include <string>
#include <tuple>
#include <type_traits>

using std::cout, std::endl;
using std::string;

template <typename... Args>
void func(Args... args)
{
  cout << "func has been deduced as " << sizeof...(args) << " arguments\n";
}

template <typename... Args>
void func_with_tuple(Args... args)
{
  auto arg_tuple = std::make_tuple(args...);
  auto first = get<0>(arg_tuple);
  cout << "\nfunc_with_tuple:  " << sizeof...(args) << " arguments\n";
  cout << "First argument:   " << first << endl;
}

// When recursion is wanted, first you must define the terminating template...
template <typename T>
void func_recurse(T last)
{
  cout << "func_recurse (final):  " << last << endl;
}

// ...then you can define the recursive one
template <typename T, typename... Args>
void func_recurse(T first, Args... args)
{
  cout << "func_recurse:    " << sizeof...(args) << " variable arguments\n";
  cout << "First argument:  " << first << endl;

  func_recurse(args...);
}

template <typename T, typename... Args>
void recurse17(T first, Args... args)
{
  cout << "recurse17:       " << sizeof...(args) << " variable arguments\n";
  cout << "First argument:  " << first << endl;

  if constexpr (sizeof...(args) > 0)
    recurse17(args...);
}

template <typename T>
void func_asserted(T value)
{
  static_assert(!std::is_pointer<T>::value, "Uh uh, no pointers allowed");

  cout << "Not a pointer: " << value << endl;
}

int main()
{
  int i{42};
  double d{3.1415};
  string s{"text"};

  func(s);
  func(d, i, s);

  func_with_tuple(d, i, s);

  cout << endl;
  func_recurse(d, i, s);

  cout << endl;
  recurse17(d, i, s);

  cout << endl;
  func_asserted(23);
  // func_asserted(&i);    // This will not compile (correctly)
}
