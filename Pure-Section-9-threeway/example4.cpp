#include <iostream>
#include <utility>

struct ArrayContainer
{
  // This will work, but for this class will be very inefficient
  // auto operator<=>(const ArrayContainer &rhs) const = default;

  bool operator==(const ArrayContainer &rhs) const
  {
    const auto l1 = strlen(value_);
    const auto l2 = strlen(rhs.value_);

    // If the lengths differ, there's no point in comparing
    // the strings lexicographically
    return l1 == l2 && strcmp(value_, rhs.value_) == 0;
  }

  // Another way to do this would be use the default, but add a length or size variable before the array
  // that would short-circuit the comparison

  char value_[255];
};

int main()
{
  constexpr ArrayContainer str1{"C++ is great, but will be inefficent here"};             // \
                                                                                          //  > Lengths different, no comparison
  constexpr ArrayContainer str2{"C++ is great, but we'll need to override the Defaults"}; // /  \
                                                                                          //     > Lengths equal, text is compared
  constexpr ArrayContainer str3{"C++ is great, but we'll need to override the defaults"}; //    /

  std::cout << std::boolalpha << "srt1 == str2: " << (str1 == str2) << std::endl;
  std::cout << "str1 != str2: " << (str1 != str2) << std::endl;

  std::cout << "srt2 == str3: " << (str2 == str3) << std::endl;
  std::cout << "str2 != str3: " << (str2 != str3) << std::endl;
}
