#include <iostream>
#include <vector>
#include <string_view>

using std::cout;
using std::endl;

using IntVec = std::vector<int>; // Replaces / Enhances C typedef

void print(const std::string_view &leadin, const IntVec &vec)
{
  cout << leadin << " [";

  for (auto e : vec)
    cout << e << ", ";

  cout << "]" << endl;
}

int main()
{
  IntVec vec1(4);    // 4 0s
  IntVec vec2(4, 2); // 4 2s
  IntVec vec3{4};    // 4 exactly
  IntVec vec4{4, 2}; // 4 & 2 exactly

  std::string s{"vec4 ="};

  print("vec1 =", vec1);
  print("vec2 =", vec2);
  print("vec3 =", vec3);
  print(s, vec4);
}
