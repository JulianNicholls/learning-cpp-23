#include <iostream>
#include <map>
#include <string>
#include <vector>

using std::cout, std::cin, std::endl;
using std::string;

using FamilyMap = std::multimap<string, string>;

void print_families(const FamilyMap &map)
{
  auto it = map.cbegin();

  while (it != map.cend())
  {
    cout << it->first << ": ";

    auto itr = map.equal_range(it->first);

    for (auto itn = itr.first; itn != itr.second; ++itn)
      cout << itn->second << ", ";

    cout << endl;
    it = map.upper_bound(it->first);
  }
}

int main()
{
  FamilyMap families;

  families.emplace("Simpson", "Bart");
  families.emplace("Simpson", "Lisa");
  families.emplace("Simpson", "Maggie");

  families.emplace("Griffin", "Meg");
  families.emplace("Griffin", "Chris");
  families.emplace("Griffin", "Stewie");

  print_families(families);
}
