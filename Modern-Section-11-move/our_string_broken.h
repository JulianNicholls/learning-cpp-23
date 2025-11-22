#ifndef OUR_STRING_H
#define OUR_STRING_H

#include <iostream>
#include <string_view>

using std::string;

class OurString
{
public:
  OurString(size_t size) : size_{size}, data_{new char[size]} {}
  OurString(const std::string_view &str) : size_(str.size()), data_(new char[str.size()])
  {
    memcpy(data_, str.data(), size_);
  }

  ~OurString() noexcept
  {
    std::cout << "Destructor called: " << static_cast<void *>(data_) << std::endl;

    delete[] data_;
  }

  OurString(const OurString &other)
  {
    std::cout << "Copy constructor called\n";

    size_ = other.size_;
    data_ = new char[other.size_];

    memcpy(data_, other.data_, size_);
  }

  OurString(OurString &&other) noexcept : size_{other.size_}, data_{other.data_}
  {
    // It's important to nullify the other string, because otherwise the
    // same memory will be deleted twice.

    std::cout << "Move constructor called\n";

    other.size_ = 0;
    other.data_ = nullptr;

    std::cout << "this:  " << size_ << " content: " << (data_ == nullptr ? "NULL" : data_) << " (" << static_cast<void *>(data_) << ")" << std::endl;

    std::cout << "other: " << other.size_ << " content: " << (other.data_ == nullptr ? "NULL" : other.data_) << " (" << static_cast<void *>(other.data_) << ")" << std::endl;
  }

  OurString &operator=(const OurString &other);
  OurString &operator=(OurString &&other) noexcept;

  // Strictly speaking, this should be broken because there is no terminating null
  void print(std::ostream &os) const;

  friend void swap(OurString &l, OurString &r) noexcept;

  size_t size() const { return size_; }

private:
  size_t size_ = 0;
  char *data_ = nullptr;
};

inline std::ostream &operator<<(std::ostream &os, const OurString &str)
{
  str.print(os);

  return os;
}

inline void swap(OurString &l, OurString &r) noexcept
{
  std::swap(l.size_, r.size_);
  std::swap(l.data_, r.data_);
}

#endif // OUR_STRING_H
