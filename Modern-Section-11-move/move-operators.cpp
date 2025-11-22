#include <iostream>
#include <string>

using std::cout, std::string;

class MyClass {};

class Test {
public:
  Test() = default;

  Test(const Test &other) : i{other.i}, m{other.m} {
    cout << "Test Copy constructor called\n";
  }

  Test(Test &&other) noexcept : i{other.i}, m{std::move(other.m)} {
    cout << "Test Move constructor called\n";
  }

  Test &operator=(const Test &other) {
    cout << "Test copy assignment operator called\n";

    if (this != &other) {
      i = other.i;
      m = other.m;
    }

    return *this;
  }

  Test &operator=(Test &&other) {
    cout << "Test move assignment operator called\n";

    if (this != &other) {
      i = other.i;
      m = std::move(other.m);
    }

    return *this;
  }

private:
  int i{0};
  MyClass m;
};

int main() {
  Test test; // Default constructor

  cout << "Copying: ";
  Test test2 = test;

  cout << "Moving temporary: ";
  Test test3 = Test(); // This is optimised away

  cout << "\nMoving rvalue ref: ";
  Test test4(std::move(test3));

  Test test5;
  cout << "\nAssigning: ";
  test5 = test2;

  Test test6;
  cout << "Assigning from temporary: ";
  test6 = Test();
}
