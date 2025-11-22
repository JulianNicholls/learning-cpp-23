#include <iostream>
#include <string>
#include <utility>
#include <vector>
#include <deque>

void print(const std::vector<int>& vec) {
  for(const auto& i : vec) {
    std::cout << i << ", ";
  }
}

void print(const std::deque<int> &vec)
{
  for (const auto &i : vec)
  {
    std::cout << i << ", ";
  }
}

void iterators() {
  std::vector<int> list;    // Empty
  std::deque<int> deck;

  auto bit = std::back_inserter(list);
  auto fit = std::front_inserter(deck);

  *bit = 3;
  *bit = 4;
  *bit = 1;

  std::cout << "list is now " << list.size() << " entries, and contains ";
  print(list);
  std::cout << std::endl;

  *fit = 1;
  *fit = 4;
  *fit = 1;
  *fit = 3;

  std::cout << "deck is now " << deck.size() << " entries, and contains ";
  print(deck);
  std::cout << std::endl;

  auto ait = std::inserter(list, next(list.begin()));

  *ait = 1;

  std::cout << "list is now " << list.size() << " entries, and contains ";
  print(list);
  std::cout << std::endl;
}

int main() {
  iterators();
}
