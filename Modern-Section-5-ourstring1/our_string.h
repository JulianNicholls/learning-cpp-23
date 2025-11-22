#include <iostream>
#include <string>
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

  ~OurString()
  {
    // std::cout << "Destructor called\n";

    delete[] data_;
  }

  OurString(const OurString &other) : size_(other.size_), data_(new char[size_])
  {
    // std::cout << "Copy constructor called\n";

    memcpy(data_, other.data_, size_);
  }

  // Strictly speaking, this should be broken because there is no terminating null
  void print(std::ostream& os = std::cout) const
  {
    os << data_ << std::endl;
  }

  OurString &operator =(const OurString &other)
  {
    // std::cout << "Assignment operator called\n";

    if (&other != this) // Ignore self-assignment
    {
      delete[] data_; // deleting nullptr is legal

      size_ = other.size_;
      data_ = new char[size_];

      memcpy(data_, other.data_, size_);
    }

    return *this;
  }

private:
  size_t size_ = 0;
  char *data_ = nullptr;
};

std::ostream& operator <<(std::ostream& os, const OurString& str) {
  str.print(os);

  return os;
}
