#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using std::cin, std::cout, std::endl;
using std::string, std::vector;

using namespace std::placeholders;

bool match(const string& animal, const string& species)
{
  cout << R"(1st argument is ")" << animal << R"(", second argument is ")" << species << "\"" << endl;
  return animal == species;
}

// bind is less useful since C++14, sinc e lambdas can do all the things that previously needed bind
int main() {
  auto match_cat = std::bind(match, _1, "cat");
  auto match_cat_lambda = [species="cat"](const string& animal) { return match(animal, species); };

  if(match_cat("dog"))
  cout << "Matched\n";
  else
  cout << "Not Matched\n";

  vector<string> animals{"cat", "dog", "tiger", "lion", "bear", "cat", "giraffe"};

  cout << "The vector contains\n" << count_if(cbegin(animals), cend(animals), match_cat) << " occurrences of the word cat\n";

  cout << "\nUsing a lambda, the vector contains\n" << count_if(cbegin(animals), cend(animals), match_cat_lambda) << " cats\n";
}
