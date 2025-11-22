#include <iostream>
#include <vector>

using std::cout, std::endl;

int main()
{
  std::vector<int> vec2{0, 1};

  try
  {
    // Interestingly, this doesn't segfault or anything
    // Truly undefined behaviour
    cout << "Element [3]   (Whoops!): " << vec2[3] << "\n\n";

    // This correctly throws a std::out_of_range exception
    // cout << "Element at(3) (Checked): " << vec2.at(3) << endl;

    // throw 42;   // i.e. not a std::exception derived object
    throw "Summat";
  }
  catch (const std::out_of_range &e)
  {
    // what() is not very lucid on clang 17.0.0, and this doesn't help
    cout << "\nCatch (oor): " << e.what() << endl;
  }
  catch (const std::exception &e)
  {
    // what() is not very lucid on clang 17.0.0
    cout << "\nCatch (se): " << e.what() << endl;
  }
  catch (...)
  {
    cout << "\nLast Resort Catcher\n";
  }

  cout << "\nFinished\n";
}
