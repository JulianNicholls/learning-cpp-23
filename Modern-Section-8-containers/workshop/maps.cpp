#include <iostream>
#include <map>
#include <vector>
#include <string>

using std::cout, std::cin, std::endl;
using std::string;

using WordLengthVector = std::vector<std::pair<string, size_t>>;
using WordLengthMap = std::map<string, size_t>;

void print(const WordLengthVector &vec)
{
  for (auto [word, length] : vec)
    cout << "(" << word << ": " << length << "), ";
}

void print(const WordLengthMap& map)
{
  for (auto [word, length] : map)
    cout << "(" << word << ": " << length << "), ";
}

void store()
{
  WordLengthVector vec;
  WordLengthMap map;

  string word;

  cout << "\nVector and Map: ";

  while (cin >> word)
  {
    if (word == "stop")
      break;

    vec.emplace_back(word, word.size());
    map.try_emplace(word, word.size());
  }

  cout << "\nVector of words and lengths: ";
  print(vec);

  cout << "\nSet    of words and lengths: ";
  print(map);
  cout << endl;
}

int main()
{
  store();
}
