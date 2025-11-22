#include <cstddef>
#include <vector>
#include <iostream>

using std::cout;

enum class [[nodiscard("Error code must be noted")]] ErrorCode
{
  SUCCESS,
  FAILURE,
  WARNING
};

enum class Alpha
{
  OPAQUE,
  TRANSLUCENT,
  TRANSPARENT
};

struct DbInfo
{
  [[nodiscard]] DbInfo() {}
};

class Empty {

};

class Child: public Empty {
  int x;
};

struct Container {
  int x;
  [[no_unique_address]] Empty e;
  [[no_unique_address]] Empty e1;
};

[[nodiscard("Database operation details lost")]] DbInfo get()
{
  DbInfo db;

  return db;
}

[[nodiscard("Potential memory leak")]] void *rawAlloc(size_t size)
{
  return operator new(size);
}

[[nodiscard("Token must be retained")]] int regResource()
{
  return 100;
}

void deregResource([[maybe_unused]] int token)
{
}

ErrorCode createComponent()
{
  return ErrorCode::FAILURE;
}

void useDbInfo([[maybe_unused]] const DbInfo &db)
{
}

void displayImage(Alpha alpha)
{
  switch (alpha)
  {
  [[likely]] case Alpha::OPAQUE:
    // Whatever
    break;

  case Alpha::TRANSLUCENT:
    // Whatever
    break;

  [[unlikely]] case Alpha::TRANSPARENT:
    // Whatever;

    break;
  }
}

int total(const std::vector<int>& values)
{
  int accum{0};

  for(size_t idx = 0; idx < values.size(); ++idx) {
    [[likely]] if(values[idx] > 0) accum += values[idx];
    else {
      //summat else
    }
  }

  return accum;
}

// Many of these lines will be warned about deliberately
int main()
{
  get();
  rawAlloc(99);
  regResource();
  createComponent();

  DbInfo{};            // This is not fine, the temp is not being used
  useDbInfo(DbInfo{}); // This is fine, we're using the DbInfo

  cout << "Empty:     " << sizeof(Empty)  << "\n";
  cout << "Child:     " << sizeof(Child)  << "\n";
  cout << "Container: " << sizeof(Container)  << "\n\n";

  Container c;
  cout << "x:     " << &c.x << "\n";
  cout << "e:     " << &c.e << "\n";
  cout << "e1:    " << &c.e1 << std::endl;
}
