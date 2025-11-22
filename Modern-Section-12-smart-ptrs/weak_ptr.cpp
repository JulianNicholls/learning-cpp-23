#include <iostream>
#include <memory>
#include <exception>

using std::cout, std::endl;
using std::shared_ptr, std::weak_ptr, std::make_shared;

int main()
{
  auto ptr(make_shared<int>(36));

  cout << "shared_ptr data is " << *ptr << endl;

  weak_ptr wptr = ptr;

  cout << "weak_ptr data is " << *wptr.lock() << endl;

  ptr = nullptr;

  shared_ptr<int> sp1 = wptr.lock();

  if(sp1) {
    cout << "shared_ptr data is " << *sp1 << endl;
  }
  else {
    cout << "shared_ptr sp1 not valid\n";
  }

  try {
    shared_ptr<int> sp2(wptr);
    cout << "Shared ptr sp2 data: " << *sp2 << endl;
  }
  catch(std::exception& e) {
    cout << "Exception: " << e.what() << endl;
  }
}
