#include <iostream>
#include <type_traits>

using std::cout, std::endl;

class A
{
};

int main()
{
  cout << std::boolalpha;
  cout << "is_arithmetic<int>: " << std::is_arithmetic<int>::value << endl;
  cout << "is_floating_point<int>: " << std::is_floating_point<int>::value << endl;
  cout << "is_class<A>: " << std::is_class<A>::value << endl;
  cout << "is_pointer<const char*>: " << std::is_pointer<const char *>::value << endl;

  // There are dozens of others...
}
