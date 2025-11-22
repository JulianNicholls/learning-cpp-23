#include <iostream>
#include <string>

struct Department
{
  std::string name;
  std::string manager;
};

struct Employee
{
  std::string name;
  int id;
  Department dept{.name = "unallocated"};
};

int main()
{
  Employee e2{.name = "Julian"};
  Employee e3{.name = "Julian", .id = 100};

  // This next one is not good.
  // Without or without braces around the dept initialiser, there is a warning
  Employee e4{.name = "Julian", .dept = {"Accounts"}};

  Employee e5{.name = "Julian", .dept = {.name = "Accounts", .manager = "Leon"}};

  // Apparently this is not allowed (out of order), but I see no problem in Clang 17.0
  Employee ebad1{.id = 100, .name = "Julian"};
}
