#ifndef OUR_STRING_H
#define OUR_STRING_H

#include <iostream>
#include <string_view>

using std::string;

class OurString
{
public:
  OurString() {}
  OurString(const std::string_view &str) : size_(str.size()), data_(new char[size_])
  {
    memcpy(data_, str.data(), size_);
  }

  ~OurString() noexcept
  {
    // std::cout << "Destructor called\n";

    delete[] data_;
  }

  OurString(const OurString &other) : size_(other.size_), data_(new char[size_])
  {
    // std::cout << "Copy constructor called\n";

    memcpy(data_, other.data_, size_);
  }

  OurString& operator=(const OurString &other);

  // Strictly speaking, this should be broken because there is no terminating null
  void print(std::ostream &os) const;

  friend void swap(OurString& l, OurString&r) noexcept;

  size_t size() const { return size_; }

private:
  size_t size_ = 0;
  char *data_ = nullptr;
};

std::ostream &operator<<(std::ostream &os, const OurString &str);

#endif  // OUR_STRING_H
