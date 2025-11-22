#include <iostream>
#include <map>
#include <string>
#include <vector>

using std::cout, std::cin, std::endl;
using std::string;

class Family
{
public:
  Family() : children_{} {}

  void add_child(string name) { children_.push_back(name); }
  string children() const;

private:
  std::vector<string> children_;
};

string Family::children() const
{
  string result;

  for (auto name : children_)
    result += name + ", ";

  return result;
}

using FamilyMap = std::map<string, Family>;

void print_families(const FamilyMap &map)
{
  for (auto [name, family] : map)
  {
    cout << name << ": " << family.children() << endl;
  }
}

int main()
{
  FamilyMap families;

  Family family1;
  Family family2;

  family1.add_child("Steve");
  family1.add_child("Teal");
  family1.add_child("Achilles");

  family2.add_child("Graeme");
  family2.add_child("Ian");

  families.insert({"Norman", family1});
  families.insert({"Hayfield", family2});

  print_families(families);
}
