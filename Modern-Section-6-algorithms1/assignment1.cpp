#include <iostream>
#include <vector>

using IntVec = std::vector<int>;

void descending(IntVec &list)
{
  std::cout << "Original: ";

  for (auto val : list)
    std::cout << val << ", ";

  std::cout << std::endl;

  std::sort(list.begin(), list.end(),
            [](int lhs, int rhs)
            { return rhs < lhs; });

  std::cout << "Sorted:   ";

  for (auto val : list)
    std::cout << val << ", ";

  std::cout << std::endl;
}

int main()
{
  IntVec list{3, 1, 4, 5, 9, 2, 6, 8, 7};

  descending(list);

  return 0;
}
