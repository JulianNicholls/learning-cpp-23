#include <algorithm>
#include <format>
#include <fstream>
#include <iostream>
#include <random>
#include <ranges>
#include <sstream>
#include <vector>

template <std::ranges::range Range>
void print(Range &&range, std::string_view message = "", std::string_view separator = ", ")
{
  std::cout << std::format("{:<12} => [", message);

  for (const auto &v : range)
  {
    std::cout << std::format("{:>2}{}", v, separator);
  }

  std::cout << "]\n";
}

int main()
{
  std::vector<int> data(11);
  std::ranges::generate(data, []() { return std::random_device{}() % 100; });

  print(data, "Vector");

  auto e = std::views::empty<int>;
  print(e, "Empty");

  auto s = std::views::single(78);
  print(s, "Single");

  auto i = std::views::iota(1, 21);
  print(i, "Iota from 1");

  auto d = std::views::iota(1, 21) | std::views::drop(5);
  print(d, "Iota from 6");

  auto str = "This is a string";
  std::istringstream istream(str);
  auto stream = std::views::istream<std::string>(istream);

  print(stream, "istream");

  std::ifstream input("input.txt");
  stream = std::views::istream<std::string>(input);
  print(stream, "ifstream");
}
