#include <string_view>
#include <iostream>

std::string exclaim(std::string_view str)
{
  std::string result;

  for (auto it : str)
  {
    if (ispunct(it))
      result += '!';
    else
      result += std::string{it};
  }

  return result;
}

std::string exclaim_in_place(std::string str)
{
  std::string result = str;

  for (auto &it : result)
  {
    if (ispunct(it))
      it = '!';
  }

  return result;
}

int main()
{
  const std::string str("To be, or not to be, that is the question:");

  std::cout << str << " :: " << exclaim(str) << std::endl;
  std::cout << exclaim_in_place(str) << std::endl;
  std::cout << (exclaim(str) == exclaim_in_place(str) ? "\nThey match\n" : "\nOops!\n");
}
