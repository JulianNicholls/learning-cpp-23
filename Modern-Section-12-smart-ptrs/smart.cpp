#include <iostream>
#include <memory>

using std::cout, std::endl;
using std::unique_ptr;

int main()
{
  unique_ptr<int> p1(new int{42});      // Points to a single int on the heap;
  unique_ptr<int[]> p2(new int[6]);     // Points to an array of ints

  // For an array it is usually better to use vector or std::array

  auto p3{std::make_unique<int>(42)};   // C++14 make_unique calls new internally
  auto p4{std::make_unique<int[]>(6)};

}
