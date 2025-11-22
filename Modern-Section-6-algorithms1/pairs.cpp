#include <iostream>
#include <string>
#include <utility>
#include <vector>

void pairs()
{
  std::pair<std::string, std::string> wordpair{"Hello", "World"};
  auto pair2{std::make_pair("variable ", 1)};
  std::pair pair3{"A string ", 2.3f}; // This works in C++17 and above

  std::cout << wordpair.first << " " << wordpair.second << std::endl;
  std::cout << pair2.first << " " << pair2.second << std::endl;
  std::cout << pair3.first << " " << pair3.second << std::endl;
}

auto find_index(const std::vector<std::string> &vec, size_t max)
{
  size_t idx = -1;

  auto res = std::find_if(vec.cbegin(), vec.cend(),
                          [max, &idx](const std::string &str)
                          { ++idx; return str.size() > max; });

  if (res != vec.cend())
    return std::pair{*res, idx};
  else
    return std::pair{std::string("''"), idx};
}

void return_pair() {
  std::vector<std::string> list{"short", "longer", "even longer", "tiny", "wee"};

  auto success = find_index(list, 5);

  std::cout << "find_index(list, 5) = " << success.first << ", " << success.second << std::endl;

  auto fail = find_index(list, 12);

  std::cout << "find_index(list, 12) = " << fail.first << ", " << fail.second << std::endl;
}

int main()
{
  pairs();
  return_pair();
}
