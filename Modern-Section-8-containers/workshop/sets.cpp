#include <iostream>
#include <fstream>
#include <set>
#include <string>

using std::cout, std::cin, std::endl;
using std::string;

template <typename T>
void print(const T &list)
{
  for (auto el : list)
    cout << el << ", ";
}

void store_set()
{
  std::set<string> list;
  string word;

  cout << "\nSet: ";

  while (cin >> word)
  {
    if (word == "stop")
      break;

    list.insert(word);
  }

  print(list);
  cout << endl;
}

void count_words()
{
  std::ifstream ifile("words.txt");
  std::set<string> words{std::istream_iterator<string>(ifile), std::istream_iterator<string>()};

  cout << "\nThere are " << words.size() << " unique words in words.txt";
}

int main()
{
  store_set();
  count_words();
}
