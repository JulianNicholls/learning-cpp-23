#include <iostream>

using std::cout, std::endl;

class Employee
{
public:
  void address()
  {
    cout << "Employee: " << static_cast<void *>(this) << endl;
  }
};

class BadSalesPerson : public Employee {};

class BadManager : public Employee {};

class BadSalesManager : public BadSalesPerson, public BadManager {};

class GoodSalesPerson : public virtual Employee {};

class GoodManager : public virtual Employee {};

class GoodSalesManager : public GoodSalesPerson, public GoodManager {};

int main()
{
  BadSalesManager bad;
  GoodSalesManager good;

  BadSalesPerson *bsp = static_cast<BadSalesPerson *>(&bad);
  BadManager *bm = static_cast<BadManager *>(&bad);

  GoodSalesPerson *gsp = static_cast<GoodSalesPerson *>(&good);
  GoodManager *gm = static_cast<GoodManager *>(&good);

  cout << "BadSalesPerson ";
  bsp->address();
  cout << "BadManager     ";
  bm->address();

  cout << "\nGoodSalesPerson ";
  gsp->address();
  cout << "GoodManager     ";
  gm->address();
}
