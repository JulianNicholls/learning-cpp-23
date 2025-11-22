#include <algorithm>
#include <format>
#include <iostream>
#include <random>
#include <ranges>
#include <vector>

template <typename Container>
void print(Container &&container, std::string message = "", std::string separator = ", ")
{
  std::cout << std::format("{:<12}: [", message);

  for (const auto &v : container)
  {
    std::cout << std::format("{:>2}{}", v, separator);
  }

  std::cout << "]\n";
}

int main()
{
  std::vector<int> data(11);

  std::ranges::generate(data, []()
                        { return std::random_device{}() % 10 + 1; });

  print(data, "Vector");

  std::ranges::for_each(data, [](int &elem)
                        { if(elem % 2 == 1) elem *=2; });

  print(data, "Doubled");

  if (auto pos = std::ranges::find(data, 8); pos != data.end())
  {
    std::cout << "Found 8\n";
  }
  else
  {
    std::cout << "Not found\n";
  }

  if (auto pos = std::ranges::find_if(data, [](int elem)
                                      { return elem >= 5 && elem <= 10; });
      pos != data.end())
  {
    std::cout << "First between 5 & 10: " << *pos << "\n";
  }
  else
  {
    std::cout << "Not found\n";
  }

  std::cout << "All between 5 & 10: ";
  std::ranges::for_each(data, [](int &elem)
                        { if(elem >= 5 && elem <= 10) std::cout << elem << ' '; });

  std::ranges::sort(data);
  print(data, "\nSorted");

  std::cout << "\nFirst 5: ";
  auto end = data.begin();
  std::advance(end, 5);
  std::for_each(data.begin(), end, [](int &elem)
                { std::cout << elem << ' '; });

  std::cout << "\nlast 5: ";
  auto begin = data.end();
  std::advance(begin, -5);
  std::for_each(begin, data.end(), [](int &elem)
                { std::cout << elem << ' '; });

  std::cout << "\n";
}
