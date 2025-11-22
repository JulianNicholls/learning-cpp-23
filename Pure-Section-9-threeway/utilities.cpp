#include <iostream>
#include <format>
#include <set>
#include <string>

struct Person
{
  std::string name{};
  int age{};
  char gender{};

  // Compare Age, then Gender, then Name
  auto operator <=> (const Person& rhs) const {
    auto age_order = age <=> rhs.age;

    if(age_order != 0) return age_order;    // Age ordered

    auto g_order = gender <=> rhs.gender;

    if (g_order != 0) return g_order;       // Gender ordered

    return name <=> rhs.name;               // Finally compare names
  }
};

int main()
{
  std::set<Person> people;

  people.insert({"Julian", 58, 'M'});
  people.insert({"Steve", 28, 'M'});
  people.insert({"Clara", 54, 'F'});
  people.insert({"Josie", 31, 'F'});
  people.insert({"MacDara", 32, 'M'});

  // Sprinkle in some confounding ones, since those all have a diffferent age
  people.insert({"Darina", 32, 'F'});
  people.insert({"Clark", 54, 'M'});
  people.insert({"Colin", 54, 'M'});

  for (const auto &p : people)
  {
    std::cout << std::format("{:<10s}  {}  {}\n", p.name, p.age, p.gender);
  }
}
