#include <algorithm>
#include <iostream>
#include <set>
#include <unordered_map>
#include <vector>

using std::cin, std::cout, std::endl;
using std::set, std::unordered_map, std::vector;

extern "C" void print(int* array, size_t size);

void show_set()
{
  set<int> s{1, 3, 5, 7, 9, 11, 13};
  vector<int> temp;

  // Because set doesm't have a data() member function, we need
  // to copy it to a vector to print it

  std::copy(cbegin(s), cend(s), std::back_inserter(temp));

  print(temp.data(), temp.size());

  cout << endl;
}

void show_map()
{
  unordered_map<int, int> m{{1, -1}, {2, -2}, {3, -3}, {4, -4}};
  vector<int> keys, values;

  // We need to decompose the map into twp vectors this time

  for(auto [key, value] : m) {
    keys.push_back(key);
    values.push_back(value);
  }

  cout << "Keys:   ";
  print(keys.data(), keys.size());

  cout << "\nValues: ";
  print(values.data(), values.size());

  cout << endl;
}

int main()
{
  show_set();
  show_map();
}
