#include <iostream>

using std::cout, std::endl;

class Base
{
public:
  Base(int value) : value_(value) {}

  virtual void print() { cout << "Base: " << value_ << endl; }

protected:
  int value_;
};

class Child : public Base
{
public:
  Child(int value) : Base(value) {}
  virtual void print() { cout << "Child: " << value_ << endl; }
};

class Grandchild : public Child
{
public:
  Grandchild(int value) : Child(value) {}

  virtual void print() { cout << "Grandchild: " << value_ << endl; }
};

void print_class(Base &b)
{
  b.print();
}

int main()
{
  Base b{10};
  Child c{12};
  Grandchild g{14};

  print_class(b);
  print_class(c);
  print_class(g);
}
