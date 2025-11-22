#include <iostream>
#include <format>
#include <compare>
#include <set>
#include <string>

class Number
{
public:
  Number() = default;
  constexpr Number(int in) : value_{in} {}

  constexpr void set(int in) { value_ = in; }
  constexpr int get() const { return value_; }

  friend bool operator==(const Number& lhs, const Number &rhs) { return lhs.value_ == rhs.value_; }
  friend bool operator<(const Number& lhs, const Number &rhs) { return lhs.value_ < rhs.value_; }

private:
  int value_;
};

struct Person
{
  char name[16]{};
  Number age{};
  char gender{};

  // Compare Age, then Gender, the Name
  auto operator <=> (const Person& rhs) const {
    // The code that the course suggests doesn't compile because no
    // default constructor exists

    // This code can be replaced with...
    // std::strong_ordering ordering{std::strong_ordering::greater};

    // if(age == rhs.age) {
    //   ordering = std::strong_ordering::equal;
    // } else if (age < rhs.age) {
    //   ordering = std::strong_ordering::less;
    // }

    // ... this
    auto ordering = std::compare_strong_order_fallback(age, rhs.age);

    if(ordering != 0) return ordering;       // Age ordered

    auto g_order = gender <=> rhs.gender;

    if (g_order != 0) return g_order;       // Gender ordered

    return std::lexicographical_compare_three_way(std::cbegin(name), std::cend(name), std::cbegin(rhs.name), std::cend(rhs.name)); // Finally compare names
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
    std::cout << std::format("{:<10}  {}  {}\n", std::string(p.name), p.age.get(), p.gender);
  }
}
