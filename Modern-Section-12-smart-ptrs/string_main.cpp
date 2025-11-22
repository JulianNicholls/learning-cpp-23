#include "String.h"

int main()
{
	String a{5};
	cout << "a: ";
	a.print();

	String b{6};
	cout << "b: ";
	b.print();
	cout << endl;
	cout << "Move construction of c from b\n";
	String c{std::move(b)};

  cout << endl;
  cout << "Copy construction of d from c\n";
  String d{c};

  cout << "b: ";
	b.print();
	cout << "c: ";
	c.print();
	cout << endl;

	cout << "Move assigning a from c\n";
	a = std::move(c);

  cout << "Copy assigning d from a\n";
  d = a;

  cout << "a: ";
	a.print();
	cout << "c: ";
	c.print();
	cout << endl;
	cout << "Exiting program...\n";
}
