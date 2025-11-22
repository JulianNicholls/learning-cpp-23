#include "date.h"
#include "date_impl.h"

Date::Date(unsigned d, unsigned m, unsigned y)
{
  pimpl_ = std::make_unique<DateImpl>(d, m, y);
}

Date::~Date() = default;

Date::Date(Date &&) noexcept = default;
Date &Date::operator=(Date &&) noexcept = default;

void Date::set_day(unsigned d)
{
  pimpl_->set_day(d);
}

void Date::set_month(unsigned m)
{
  pimpl_->set_month(m);
}

void Date::set_year(unsigned y)
{
  pimpl_->set_year(y);
}

void Date::print(std::ostream &os) const
{
  pimpl_->print(os);
}

std::ostream &operator<<(std::ostream &os, const Date &b)
{
  b.pimpl_->print(os);

  return os;
}
