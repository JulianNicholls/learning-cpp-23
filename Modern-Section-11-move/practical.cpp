#include <iostream>
#include <string>

using std::cout, std::endl;
using std::string;

class Test
{
public:
  Test(const string &str) : str_{str}
  {
    cout << "const string& constructor called\n";
  }

  Test(string &&str) : str_{std::move(str)}
  {
    cout << "string&& constructor called\n";
  }

private:
  string str_;
};

void g(string &x)
{
  cout << "Mutable g version called, x: " << x << endl;
}

void g(string &&x)
{
  cout << "Move g version called, x: " << x << endl;
}

template <class T>
Test make_test(T &&x)
{
  g(std::forward<T>(x));

  return Test(std::forward<T>(x));
}

int main()
{
  string hello{"Hello"};

  cout << "Calling make_test with lvalue\n";
  Test t1 = make_test(hello);

  cout << "Calling make_test with rvalue\n";
  Test t2 = make_test(std::move(hello));

  cout << endl;
}
