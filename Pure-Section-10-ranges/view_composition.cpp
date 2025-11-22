#include <algorithm>
#include <format>
#include <iostream>
#include <random>
#include <ranges>
#include <vector>

using Pair = std::pair<int, std::string>;
using PairVector = std::vector<Pair>;

template <typename Container>
void print(Container &&container, std::string message = "", std::string separator = ", ")
{
  std::cout << std::format("====== {} ======\n", message);

  for (const auto &v : container)
  {
    std::cout << std::format("{:>3}{}", v, separator);
  }

  std::cout << '\n';
}

int main()
{
  std::vector<int> data(20);

  std::ranges::generate(data, []()
                        { return std::random_device{}() % 100; });

  print(data, "Vector", ",");

  auto take_5 = std::views::take(data, 5);
  auto odd = std::views::filter(take_5, [](int x)
                                { return x % 2 == 1; });

  auto odd2 = std::views::filter(std::views::take(data, 5), [](int x)
                                 { return x % 2 == 1; });

  print(take_5, "take 5", ",");
  print(odd, "odd", ",");
  print(odd2, "odd2", ",");
}
