#include <iostream>

using std::cout, std::endl;

class Base
{
public:
  void print() { cout << "Base\n"; }
};

class Child : public Base
{
public:
  void print() { cout << "Child\n"; }
};

class Grandchild : public Child
{
public:
  void print() { cout << "Grandchild\n"; }
};

void print_class(Base b)
{
  b.print();
}

int main()
{
  Base b;
  Child c;
  Grandchild g;

  print_class(b);
  print_class(c);
  print_class(g);
}
