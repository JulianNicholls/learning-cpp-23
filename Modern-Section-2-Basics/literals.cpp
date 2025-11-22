#include <iostream>
#include <string>

using namespace std::string_literals; // Enables s suffix

// Raw string - delimited by R"(...)"
std::string raw = R"(<a href="file">C:\Windows\System</a>)";

int main()
{
  std::cout << "Literal String: "s << "Hello"s << std::endl;
  std::cout << "Raw: " << raw << std::endl;
}
