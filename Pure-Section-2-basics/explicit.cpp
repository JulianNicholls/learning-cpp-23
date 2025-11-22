#include <iostream>
#include <string>

using namespace std;
using std::string;

template <typename T>
class String
{
public:
  template <typename U, std::enable_if_t<!std::is_convertible_v<U, T>> * = nullptr>
  explicit String(const U &str) : str_(str) { std::cout << "Explicit "; }

  template <typename U, std::enable_if_t<std::is_convertible_v<U, T>> * = nullptr>
  String(const U &str) : str_(str) { std::cout << "Non-Explicit "; }

  const T &get() const
  {
    return str_;
  }

private:
  T str_{};
};

namespace UsingConcepts
{
  template <typename T>
  class String
  {
  public:
    template <typename U>
      requires(!std::is_convertible_v<U, T>)
    explicit String(const U &str) : str_(str)
    {
      std::cout << "Explicit ";
    }

    template <typename U>
      requires std::is_convertible_v<U, T>
    String(const U &str) : str_(str)
    {
      std::cout << "Non-Explicit ";
    }

    const T &get() const
    {
      return str_;
    }

  private:
    T str_{};
  };
}

namespace ExplicitBool
{
  template <typename T>
  class String
  {
  public:
    template <typename U>
    explicit(!std::is_convertible_v<U, T>) String(const U &str) : str_(str)
    {
    }

    const T &get() const
    {
      return str_;
    }

  private:
    T str_{};
  };
}

void print(const ExplicitBool::String<std::string> &str)
{
  std::cout << str.get() << std::endl;
};

int main()
{
  ExplicitBool::String<std::string> s1 = "C++11";  // Copy init
  ExplicitBool::String<std::string> s2 = "C++14"s; // Copy init
  ExplicitBool::String<std::string> s3{"C++20"sv}; // Must be initialised from a string_view, because the constructor is explicit

  print(s1);
  print(s2);
  print(s3);
}
