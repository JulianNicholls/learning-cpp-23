#include <iostream>
#include <string>

using std::cout, std::endl;
using std::string;

void func(int &&val) { cout << val << endl; }

void sfunc(string &&s) { cout << "RValue s: " << s << endl; }

void sfunc(string &s) { cout << "LValue s: " << s << endl; }

int main() {
  int y{2000};

  func(2); // OK, rvalue reference
  // func(y);    // Not OK, y is an lvalue
  func(std::move(y)); // OK, y is an lvalue cast ro an rvalue

  // Strictly speaking, this is undefined behaviour, y has been destroyed by the
  // move
  cout << "y after func: " << y << endl;

  string s("Hello");
  string &rs = s;

  cout << "\nTemporary ";
  sfunc(string{"Temp"});

  cout << "LValue Variable ";
  sfunc(s);

  cout << "LValue Reference ";
  sfunc(rs);

  cout << "std::move ";
  sfunc(std::move(s));

  cout << "\ns after move: " << s << endl;

  string &&rv(string(
      "Temp")); // Defined as an RValue reference, but it's still an LValue
  cout << "\nRValue variable: ";
  sfunc(rv);

  cout << "std::move ";
  sfunc(std::move(rv));

  cout << "\nrv after move: " << rv << endl;
}
