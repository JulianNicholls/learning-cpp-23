#include <iostream>
#include <string>

#include "our_string.h"

using namespace std::literals;

int main()
{
  OurString wcs{"world c_string"};
  OurString ws("world string"s);

  OurString bang(wcs);
  OurString bang2("A longer string to see if we can break it");

  bang2 = ws;

  std::cout << "wcs   = " << wcs;
  std::cout << "ws    = " << ws;

  std::cout << "bang  = " << bang;
  std::cout << "bang2 = " << bang2;
}
