#include <iostream>

#include "our_string.h"

void OurString::print(std::ostream &os = std::cout) const
{
  os << data_;
}

// Original standard implementation
// OurString &OurString::operator=(const OurString &other)
// {
//   // std::cout << "Assignment operator called\n";

//   if (&other != this) // Ignore self-assignment
//   {
//     // In order to give a strong exception guarantee, we need to
//     // allocate new memory before releasing the old
//     char* newAlloc = new char[other.size_];

//     delete[] data_; // deleting nullptr is legal

//     size_ = other.size_;
//     data_ = newAlloc;

//     memcpy(data_, other.data_, size_);
//   }

//   return *this;
// }

// Bait and switch version, err, I mean copy and swap
OurString &OurString::operator=(const OurString &other) {
  OurString temp{other};

  swap(*this, temp);

  return *this;
}

std::ostream &operator<<(std::ostream &os, const OurString &str)
{
  str.print(os);

  return os;
}

inline void swap(OurString&l, OurString& r) noexcept
{
  std::swap(l.size_, r.size_);
  std::swap(l.data_, r.data_);
}
