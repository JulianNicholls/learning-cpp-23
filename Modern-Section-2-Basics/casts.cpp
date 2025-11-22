#include <iostream>

void print(char *str)   // Badly specified, should be const char *
{
  std::cout << str << std::endl;
}

int main() {
  const int a = 'A';
  const char* msg = "Hello World";

  // static_case converts an expression to a different type like old-style cast
  auto charA = static_cast<char>(a);

  std::cout << "a:       " << a <<  std::endl;
  std::cout << "charA:   " << charA << std::endl;

  // const_cast can convert an expression to non-const, but it's a risky thing to do.
 std::cout <<  "message: ";
 print(const_cast<char *>(msg));

 // reinterpret_cast is used to convert data in a buffer to untyped binary data

 // dynamic_cast is used to convert a pointer or reference to a base class object
 // to a pointer or reference to a derived object
}
