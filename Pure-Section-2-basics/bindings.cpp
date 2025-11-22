#include <iostream>
#include <format>

struct Point {
  int x; int y;
};

class Person {
  std::string  name_;
  int id_;

  public:
    void foo(const Person& p) {
      auto n = p.name_;
      auto [name, id] = p;   // Can't do this in C++17
    }

    friend void print(const Person& p);
};

void print(const Person& p) {
  auto n = p.name_;
  auto [name, id] = p; // Can't do this in C++17
}

int main() {
  Point p{3, 5};

  auto [a, b] = p;

  std::cout << std::format("a: {}, b: {}\n", a, b);
}
