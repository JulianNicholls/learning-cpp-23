#include <iostream>
#include <string>
#include <vector>

using std::cout, std::endl;

class AtException : public std::out_of_range
{
public:
  // Need a default constructor, and ones which takes both string styles
  AtException() : std::out_of_range("Out of range. Try again") {}
  AtException(const std::string &what) : std::out_of_range(what) {};
  AtException(const char *what) : std::out_of_range(what) {};

  // Need copy constructor and assignment, but the default is actually fine
  // Therefore this is slight overkill for an exception with no data members.
  AtException(const AtException &other) = default;
  AtException &operator=(const AtException &other) = default;
};

int my_at(const std::vector<int> &vec, size_t idx)
{
  if (idx >= vec.size())
    throw AtException("my_at says " + std::to_string(idx) + " is out of range"); // This string becomes what()
  else
    return vec[idx];
}

void bad_function()
{
  std::vector<int> vec2{0, 1};

  try
  {
    // This correctly throws a std::out_of_range exception, but not a very lucid one by default
    cout << "Element at(3) (Checked): " << vec2.at(3) << endl;
  }
  catch (const std::out_of_range &e)
  {
    // what() is not very lucid on clang 17.0.0, and this doesn't help
    cout << "\nCatch (oor): " << e.what() << endl;

    throw; // Rethrow the same exception
  }
}

int main()
{
  std::vector<int> vec2{0, 1};

  try
  {
    my_at(vec2, 3);
    bad_function();
  }
  catch (const AtException &e)
  {
    // what() is not very lucid on clang 17.0.0, and this doesn't help
    cout << "\nCatch (ae): " << e.what() << endl;
  }
  catch (const std::exception &e)
  {
    // what() is not very lucid on clang 17.0.0
    cout << "\nCatch (se): " << e.what() << endl;
  }
  catch (...)
  {
    cout << "\nLast Resort Catcher\n";
  }

  cout << "\nFinished\n";
}
