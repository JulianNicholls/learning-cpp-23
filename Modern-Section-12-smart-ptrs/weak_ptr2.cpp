#include <iostream>
#include <memory>
#include <vector>

using std::cout, std::endl;
using std::shared_ptr, std::weak_ptr, std::make_shared;
using std::vector;

void print(vector<shared_ptr<int>> vec)
{
  cout << "Vector elements: ";

  for (weak_ptr<int> p : vec)
  {
    auto ptr = p.lock();

    if (ptr)
      cout << *ptr << ", ";
    else
      cout << "(deleted), ";
  }

  cout << endl;
}

int main()
{
  vector<shared_ptr<int>> vec{
      make_shared<int>(42),
      make_shared<int>(47),
      make_shared<int>(43),
      make_shared<int>(19)};

  print(vec);

  cout << "Deleting vec2\n";
  vec[2] = nullptr;

  print(vec);
}
