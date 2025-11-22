#include <iostream>

#include "our_string.h"

using std::cout, std::endl;

int main() {
  OurString left("Left String");
  OurString right("Right String");

  cout << "A: " << left << ", B: " << right << endl;

  std::swap(left, right);

  cout << "A: " << left << ", B: " << right << endl;

  OurString a = right;
  OurString b = left;

  cout << "\nAssigned A: " << a << ", Assigned B: " << b << endl;
}
