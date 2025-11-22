#include <iostream>
#include <string>
#include <vector>

int main()
{
  const std::string str{"this text is const"};
  std::string str2("This text isn't");
  const std::vector<int> intvector{1, 2, 3, 4, 5};
  const int array[] = {6, 7, 8, 9, 10};

  // Because str is const, auto here and below will make a string::const_iterator
  std::string::const_iterator it = str.begin();

  while (it != str.end())
  {
    std::cout << *it << ' ';
    ++it;
  }

  std::cout << std::endl;

  for (auto it2 = str.begin(); it2 != str.end(); ++it2)
    std::cout << *it2 << ',';

  std::cout << std::endl;

  // Normally it5 here would be a non-const string::iterator,
  // but cbegin() returns a const_iterator
  // likewise crbegin() returns a const_reverse_iterator
  for (auto it5 = str2.cbegin(); it5 != str2.cend(); ++it5)
    std::cout << *it5 << ',';

  std::cout << std::endl;

  for (auto it3 = intvector.begin(); it3 != intvector.end(); ++it3)
    std::cout << *it3 << ',';

  std::cout << std::endl;

  // vector<int>::reverse_iterator
  for (auto it4 = intvector.rbegin(); it4 != intvector.rend(); ++it4)
    std::cout << *it4 << ',';

  std::cout << std::endl;

  // Non-member begin() and end(), liewise cbegin(), rbegin(), and crbegin()
  // Also orks with C-style arrays
  // std:: is implied for vector etc, but must be specified for C-style arrays
  for (auto it4 = std::begin(array); it4 != std::end(array); ++it4)
    std::cout << *it4 << ',';

  std::cout << std::endl;

  // Concise syntax
  for (auto elem : array) // elem is a copy, so const auto& elem may be better in most cases
    std::cout << elem << ',';

  std::cout << std::endl;

  // Maths can be done on iterators, i.e. it + 2
  // next(it) and prev(it) can be called to get the next and prev item
  // distance(it, it) measures the distance in items between
  // advance(it, how_far) moves an iterator by how_far
}
