#include <algorithm>
#include <format>
#include <iostream>
#include <random>
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

  std::generate(data.begin(), data.end(), []()
                { return std::random_device{}() % 10 + 1; });

  print(data, "Vector");

  std::for_each(data.begin(), data.end(), [](int &elem)
                { if(elem % 2 == 1) elem *=2; });

  print(data, "Doubled");

  if (auto pos = std::find(data.begin(), data.end(), 8); pos != data.end())
  {
    std::cout << "Found 8\n";
  }
  else
  {
    std::cout << "Not found\n";
  }

  if (auto pos = std::find_if(data.begin(), data.end(), [](int elem)
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
  std::for_each(data.begin(), data.end(), [](int &elem)
                { if(elem >= 5 && elem <= 10) std::cout << elem << ' '; });

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

  std::sort(data.begin(), data.end());
  print(data, "\nSorted");

  std::cout << "\n";
}
