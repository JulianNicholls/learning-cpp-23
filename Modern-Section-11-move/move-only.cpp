#include <iostream>

using std::cout, std::endl;

class MyClass {};

// Examples of std move only classes are:
//    fstream, iostream, some multithreading classes, and smart pointer class
// This is for RAII reasons, they all get hold of a unique resource in the
// constructor and release it in the destructor.

// Move-only objects cannot be captured by value in C++11
// C++14 allows this
//  fstream fs("file.txt")
//  [ifs = std::move(fs)]

class MoveOnly {
public:
  MoveOnly() = default;

  MoveOnly(const MoveOnly &) = delete;
  MoveOnly operator=(const MoveOnly &) = delete;

  MoveOnly(MoveOnly &&) noexcept;
  MoveOnly &operator=(MoveOnly &&) noexcept;

private:
  int i_{0};
  MyClass my_;
};

MoveOnly::MoveOnly(MoveOnly &&other) noexcept : i_{other.i_}, my_{other.my_} {
  cout << "Move constructor called\n";
}

MoveOnly &MoveOnly::operator=(MoveOnly &&other) noexcept {
  cout << "Move assignment operator called\n";

  if (this != &other) {
    i_ = other.i_;
    my_ = other.my_;
  }

  return *this;
}

int main() {
  MoveOnly m;

  cout << "Moving temporary: ";
  MoveOnly m3 = MoveOnly(); // This is optimised away

  cout << "\nMoving rvalue: ";
  MoveOnly m4(std::move(m));
  MoveOnly m5(std::move(m3));

  cout << endl;

  MoveOnly m6;
  cout << "Assigning from temporary: ";
  m6 = MoveOnly();
}
