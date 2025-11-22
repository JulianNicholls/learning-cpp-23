#include <iomanip>
#include <iostream>
#include <map>
#include <string>
#include <vector>

using std::cout, std::cin, std::endl;
using PairVector = std::vector<std::pair<std::string, int>>;
using StringMap = std::map<std::string, int>;

void print(const PairVector &list)
{
  for (auto el : list)
  {
    cout << el.first << ": " << el.second << ", ";
  }

  cout << endl;
}

void print_map(const StringMap &m)
{
  for (auto el : m)
  {
    cout << el.first << ": " << el.second << ", ";
  }

  cout << endl;
}

void store_as_vector()
{
  PairVector words;
  std::string word;

  while (cin >> word)
  {
    if (word == "stop")
      break;

    words.push_back({word, word.size()});
  }

  print(words);
}

void store_as_map()
{
  StringMap words;
  std::string word;

  while (cin >> word)
  {
    if (word == "stop")
      break;

    words[word] = word.size();
  }

  print_map(words);
}

int main()
{
  std::string choice;
  char lower;

  do
  {
    cout << "(v)ector, (m)ap, or (q)uit? ";
    getline(cin, choice);

    lower = tolower(choice[0]);
    if (lower == 'v')
      store_as_vector();
    else if (lower == 'm')
      store_as_map();
  } while (lower != 'q');
}
