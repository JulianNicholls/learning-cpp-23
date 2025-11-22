#include "date_impl.h"

// Implementing these not in the header means that a shared resource could be shipped
// instead of having to update the main executable.

void DateImpl::set_day(unsigned d) { day_ = d; }
void DateImpl::set_month(unsigned m) { month_ = m; }
void DateImpl::set_year(unsigned y) { year_ = y; }

void DateImpl::print(std::ostream &os) const { os << day_ << "/" << month_ << "/" << year_; }
