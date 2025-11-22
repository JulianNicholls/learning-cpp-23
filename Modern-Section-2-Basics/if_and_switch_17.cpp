#include <iostream>
#include <string>

int main()
{
  std::string str("several words");
  std::string empty; // I'm guessing...

  // C++17 allows us to do this...
  if (auto it = str.begin(); it != end(str))
  {
    std::cout << "First char: " << *it << std::endl;
  }
  else
    std::cout << "string is empty\n";

  if (auto it = empty.begin(); it != end(empty))
  {
    std::cout << "First char: " << *it << std::endl;
  }
  else
    std::cout << "string is empty\n";

  std::cout << "Press a key and enter ";

  // ...and this
  switch (const auto key = std::cin.get(); key)
  {
  case 'q':
    std::cout << "(Q)uit\n";
    break;

  case 'w':
    std::cout << "(W)ide\n";
    // I expected a warning about falling through

  default:
    std::cout << "You pressed " << static_cast<char>(key) << std::endl;
  }
}
