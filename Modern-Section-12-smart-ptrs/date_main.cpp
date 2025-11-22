#include <iostream>

#include "date.h"

using std::cout, std::endl;

int main()
{
  Date date(10, 5, 2025);

  cout << date << endl;

  date.set_day(11);
  date.set_month(6);
  date.set_year(2026);

  cout << date << endl;
}
