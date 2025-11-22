#include <iostream>

#include "our_string.h"

void OurString::print(std::ostream &os = std::cout) const
{
  os << "Size: " << size_ << " content: " << data_ << " (" << static_cast<void *>(data_) << ")";
}

// Copy and swap, allows for a strong exception guarantee at the expense of
// doubling the memory usage.
OurString &OurString::operator=(const OurString &other)
{
  OurString temp{other};

  swap(*this, temp);

  return *this;
}

OurString &OurString::operator=(OurString &&other) noexcept
{
  OurString temp(std::move(other));

  swap(*this, temp);

  return *this;
}

