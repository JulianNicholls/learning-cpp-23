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

  auto odd = std::views::filter(data, [](int x)
                                { return x % 2 == 1; });

  auto below_50 = std::views::filter(odd, [](int x)
                                     { return x < 50; });

  auto multiplied = std::views::transform(below_50, [](int x)
                                          { return x * 2; });

  auto reversed = std::views::reverse(multiplied);

  auto composed = data |
                  std::views::filter([](int x) { return x % 2 == 1; }) |
                  std::views::filter([](int x) { return x < 50; }) |
                  std::views::transform([](int x) { return x * 2; }) |
                  std::views::reverse;

  print(odd, "odd", ",");
  print(below_50, "below_50", ",");
  print(multiplied, "multiplied", ",");
  print(reversed, "reversed", ",");

  print(composed, "composed", ",");
}
