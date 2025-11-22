#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <algorithm>

using std::cout, std::endl;
using std::string;

// Simple predicate for sort by length
bool is_shorter(const string &a, const string &b)
{
  return a.size() < b.size();
};

// Functor predicate for sort by length
class Shorter
{
public:
  bool operator()(const string &lhs, const string &rhs)
  {
    return lhs.size() < rhs.size();
  }
};

// Functor predicate for length - Possible with a parameterised lambda since C++14
class Longer
{
public:
  Longer(size_t length = 5) : length_{length} {}

  bool operator()(const string &str)
  {
    return str.size() > length_;
  }

private:
  size_t length_ = 5;
};

void show_sort()
{
  std::vector<string> names = {"Dilbert", "Dogbert", "Catbert", "PHB", "Asok", "Ted", "Alice", "Wally"};

  cout << "Original:    ";

  for (auto name : names)
    cout << name << ", ";

  std::sort(names.begin(), names.end());

  cout << "\n\nAlphabetic:  ";

  for (auto name : names)
    cout << name << ", ";

  // std::sort(names.begin(), names.end(), is_shorter);
  std::sort(names.begin(), names.end(), Shorter());

  cout << "\nBy length:   ";

  for (auto name : names)
    cout << name << ", ";
}

void show_find_if()
{
  std::vector<string> names = {"Dilbert", "Dogbert", "Catbert", "PHB", "Asok", "Ted", "Alice", "Wally"};

  Longer ge_5(5);

  for (auto name : names)
  {
    if (ge_5(name))
      cout << "\n\nLoop:         First entry at least 5 characters is " << name << endl;
    break;
  }

  auto result7 = std::find_if(names.cbegin(), names.cend(), Longer(7));

  if (result7 != names.cend())
    cout << "find_if:      First entry at least 8 characters is " << *result7 << endl;
  else
    cout << "find_if:      No entry is more than 7 characters\n";

  auto result5 = std::find_if_not(names.cbegin(), names.cend(), Longer(5));

  if (result5 != names.cend())
    cout << "find_if_not:  First entry with <= 5 characters is " << *result5 << endl;
  else
    cout << "find_if_not:  No entry is less than 5 characters\n";
}

void show_with_lambdas()
{
  std::vector<string> names = {"Dilbert", "Dogbert", "Catbert", "PHB", "Asok", "Ted", "Alice", "Wally"};

  // Lambda expressions are led in with [] as the function name
  auto result5 = std::find_if(names.cbegin(), names.cend(),
                              [](const string &str)
                              { return str.size() <= 5; });

  if (result5 != names.cend())
    cout << "\nfind_if_lambda:  First entry with <= 5 characters is " << *result5 << "\n\n";
  else
    cout << "\nfind_if_lambda:  No entry is less than 5 characters\n\n";
}

// Case-insensitive string equal
bool ci_match(const string &a, const string &b)
{
  return std::equal(a.cbegin(), a.cend(), b.cbegin(), b.cend(),
                    [](char a, char b)
                    { return tolower(a) == tolower(b); });
}

void show_equal_strings()
{
  const string lam1{"lambda"};
  const string lam2{"Lambda"};
  const string lam3{"Lambada"};

  cout << lam1 << " == " << lam2 << std::boolalpha << "  " << ci_match(lam1, lam2) << endl; // Should match
  cout << lam2 << " == " << lam3 << " " << ci_match(lam2, lam3) << endl;                    // Should NOT match
}

const string global{"Global"};

void show_lambda_access()
{
  static string static_1{"Static"}; // Static in containing scope
  const string local{"Local"};      // Local in containing scope
  const string &ref = local;        // Local reference in containing scope

  cout << "\nLambda access\n";

  [local, ref]()
  {
    cout << global << endl;   // Global is accessible
    cout << static_1 << endl; // Static is accessible
    cout << local << endl;    // Local is accessible, if captured
    cout << ref << endl;      // Local Reference is accessible, if captured
  }();
}

void show_lambda_update_access()
{
  std::vector<string> list{"short", "longer", "even longer", "tiny", "wee"};

  size_t first_min = 6;
  size_t idx = -1; // So first inc goes to 0

  cout << "\nLambda update access\n";

  auto res1 = std::find_if(list.cbegin(), list.cend(),
                           [first_min, &idx](const string &str)
                           { ++idx; return str.size() >= first_min; });

  if (res1 != list.cend())
    cout << "The first string as long  as " << first_min << " is " << *res1 << " at index " << idx << endl;
  else
    cout << "There's no string as long as " << first_min << endl;

  size_t first_max = 4;
  idx = -1; // Reset

  auto res2 = std::find_if(list.cbegin(), list.cend(),
                           [first_max, &idx](const string &str)
                           { ++idx; return str.size() <= first_max; });

  if (res2 != list.cend())
    cout << "The first string as short as " << first_max << " is " << *res2 << " at index " << idx << endl;
  else
    cout << "There's no string as short as " << first_max << endl;
}

void show_generic_lambdas() {
  const string str1("Hello ");
  const string str2("World ");

  // C++14 and above allow for adding new local variables in the capture
  auto add = [y = 0](auto a, auto b) { return a + b; };

  cout << "\nGeneric Lambdas\n";
  cout << "\ntype of add lambda " << typeid(add).name() << "\n\n";

  cout << "Calling add(2, 5) = " << add(2, 5) << endl;
  cout << "Calling add(2.2, 5.3) = " << add(2.2, 5.3) << endl;
  cout << "Calling add(str1, str2) = " << add(str1, str2) << endl;
}

// It's possible to embed a lamdda expression inside a class.
// this can be captured by reference with [this]
// this by value, preventing update, can be captured with [*this] in C++17 or above.

void show_library_lambdas() {
  // This shows less and greater, there are a lot more minus, plus ; bit_and, bit_not etc

  std::vector<string> names = {"Dilbert", "Dogbert", "Catbert", "PHB", "Asok", "Ted", "Alice", "Wally"};

  cout << "\nLibrary Lambdas\nOriginal:  ";

  for (auto name : names)
    cout << name << ", ";

  std::sort(names.begin(), names.end(), std::less{});

  cout << "\n\nAlphabetic using less:  ";
  for (auto name : names)
    cout << name << ", ";

  std::sort(names.begin(), names.end(), std::greater{});

  cout << "\n\nReverse using greater:  ";
  for (auto name : names)
    cout << name << ", ";
}

int main()
{
  show_sort();
  show_find_if();
  show_with_lambdas();
  show_equal_strings();
  show_lambda_access();
  show_lambda_update_access();
  show_generic_lambdas();
  show_library_lambdas();

  cout << endl;
}
