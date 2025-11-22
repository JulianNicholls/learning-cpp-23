#include <iostream>
#include <string>
#include <format>

int main()
{
  // Creating and initializing strings
  std::string greeting = "Hello, ";
  std::string name = "World";

  // Concatenation
  std::string fullGreeting = greeting + name + "!";
  std::cout << fullGreeting << std::endl;

  // Accessing characters
  std::cout << "First character: " << fullGreeting[0] << std::endl;

  // Modifying strings
  fullGreeting[7] = 'w';
  std::cout << "Modified greeting: " << fullGreeting << std::endl;

  // String length
  std::cout << "Length of the string: " << fullGreeting.length() << std::endl;

  // Substrings
  std::string sub = fullGreeting.substr(7, 5);
  std::cout << "Substring: " << sub << std::endl;

  // Comparing strings
  std::string anotherGreeting = "Hello, world!";
  if (fullGreeting == anotherGreeting)
  {
    std::cout << "Strings are equal" << std::endl;
  }
  else
  {
    std::cout << "Strings are not equal" << std::endl;
  }

  // Searching
  const auto idx1 = fullGreeting.find('o');
  const auto idx2 = fullGreeting.find('o', idx1 + 1);
  const auto idx3 = fullGreeting.find('x');
  const auto idx4 = fullGreeting.rfind('l');

  const auto vowels{"aeiouAEIOU"};

  std::cout << "\nSearching for 'o': " << idx1 << std::endl;
  std::cout << "Searching for 'o' again: " << idx2 << std::endl;
  std::cout << "Searching for 'x': " << (idx3 == fullGreeting.npos ? -1 : static_cast<int>(idx3)) << std::endl;
  std::cout << "Searching for last 'l': " << idx4 << std::endl;

  std::cout << "first vowel: " << fullGreeting.find_first_of(vowels) << std::endl;
  std::cout << "last vowel:  " << fullGreeting.find_last_of(vowels) << std::endl;

  std::cout << "first consonant: " << fullGreeting.find_first_not_of(vowels) << std::endl;
  std::cout << "last consonant:  " << fullGreeting.find_last_not_of(vowels) << std::endl;

  // Adding stuff
  std::string str{"for"};
  str.insert(2, "lde");

  std::cout << "\nInserting 'lde' into 'for': " << str << std::endl;

  std::string str2{"care"};
  str2.append("less");
  std::cout << "Appending 'less' to 'care': " << str2 << std::endl;

  // Erasing stuff
  std::string str3{"careless"};
  str3.erase(4, 3);
  std::cout << "Erasing 'les' from 'careless': " << str3 << std::endl;

  // Replacing stuff
  std::string str4{"careless"};
  str4.replace(4, 4, "free");
  std::cout << "Replacing 'less' with 'free' in 'careless': " << str4 << std::endl;

  // String to number conversion
  std::string numStr = "12345.23Pie";
  size_t n;
  auto num = std::stoi(numStr, &n);
  auto hexnum = std::stoi(numStr, nullptr, 16);
  auto dblnum = std::stod(numStr);

  std::cout << "String to int: " << num << " 1st non-numeric index " << n << std::endl;
  std::cout << "String to hex int: " << hexnum << std::endl;
  std::cout << std::format("String to double: {0:.2f}", dblnum) << std::endl;

  return 0;
}
