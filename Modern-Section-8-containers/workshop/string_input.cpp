#include <array>
#include <deque>
#include <iostream>
#include <list>
#include <string>

using std::cout, std::cin, std::endl;
using std::string;

template <typename T>
void print(const T &list)
{
  for (auto el : list)
    cout << el << ", ";
}

void store_vector()
{
  std::vector<string> list;
  string word;

  cout << "Vector: ";

  while (cin >> word)
  {
    if (word == "stop")
      break;

    list.push_back(word);
  }

  print(list);
}

void store_list()
{
  std::list<string> list;
  string word;

  cout << "\nList: ";

  while (cin >> word)
  {
    if (word == "stop")
      break;

    list.push_back(word);
  }

  print(list);
}

void store_set()
{
  std::deque<string> list;
  string word;

  cout << "\nDeque: ";

  while (cin >> word)
  {
    if (word == "stop")
      break;

    list.push_back(word);
  }

  print(list);
}

void reverse_list()
{
  std::list<string> list;
  string word;

  cout << "\nReversed List: ";

  while (cin >> word)
  {
    if (word == "stop")
      break;

    list.push_front(word);
  }

  print(list);
}

void reverse_deque()
{
  std::deque<string> list;
  string word;

  cout << "\nReversed Deque: ";

  while (cin >> word)
  {
    if (word == "stop")
      break;

    list.push_front(word);
  }

  print(list);
}

int main()
{
  store_vector();
  store_list();
  store_set();

  reverse_list();
  reverse_deque();
}
