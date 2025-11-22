#include <iostream>
#include <memory>
#include <vector>

using std::cout, std::endl;
using std::shared_ptr, std::weak_ptr, std::make_shared;
using std::vector;

struct Son;

struct Father
{
  ~Father() {
    cout << "Father destructor\n";
  }

  void set_son(const shared_ptr<Son>& s)
  {
    sptr = s;
  }

  shared_ptr<const Son> sptr;
};

struct Son
{
  Son(const shared_ptr<Father>& f) : fptr(f) {}

  ~Son(){
      cout << "Son destructor\n";
  }

  // Making this a weak_ptr breaks the cycle of shared_ptrs, allowing detruction
  weak_ptr<const Father> fptr;
};

int main()
{
  cout << endl;
  {
    auto f = make_shared<Father>();
    auto s = make_shared<Son>(f);

    f->set_son(s);
  }

  cout << endl;
}
