#include <iostream>
#include <memory>

class DateImpl;

class Date
{
public:
  Date(unsigned day, unsigned month, unsigned year);
  ~Date();

  Date(Date &&) noexcept;
  Date &operator=(Date &&) noexcept;

  void set_day(unsigned d);
  void set_month(unsigned m);
  void set_year(unsigned y);

  void print(std::ostream &os = std::cout) const;

  friend std::ostream &operator<<(std::ostream &os, const Date &b);

private:
  std::unique_ptr<DateImpl> pimpl_;
};
