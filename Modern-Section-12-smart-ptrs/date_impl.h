#include <iostream>

class DateImpl
{
public:
  DateImpl(unsigned d, unsigned m, unsigned y) : day_{d}, month_{m}, year_{y} {}

  void set_day(unsigned d);
  void set_month(unsigned m);
  void set_year(unsigned y);

  void print(std::ostream &os) const;

private:
  unsigned day_;
  unsigned month_;
  unsigned year_;
};
