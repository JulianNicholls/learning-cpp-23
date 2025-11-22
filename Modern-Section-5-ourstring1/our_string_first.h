#include <iostream>
#include <string>
#include <string_view>

using std::string;

class OurString
{
public:
  OurString() : s_("") {}   // Default would work here
  OurString(const std::string_view &str) : s_(str) {}
  OurString(const OurString &other) : s_(other.s_) {} // Copy constructor, here, default would work

  void print() const
  {
    std::cout << s_ << std::endl;
  }

  OurString &operator=(const OurString &other)
  { // Again, the default would suffice
    s_ = other.s_;

    return *this;
  }

private:
  string s_;
};
