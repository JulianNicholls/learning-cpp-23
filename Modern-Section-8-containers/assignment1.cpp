#include <array>
#include <deque>
#include <iostream>
#include <list>
#include <string>

using std::cout, std::cin, std::endl; // OK OK, I give in :)

template <typename T>
void print(const T &list)
{
  for (auto el : list)
  {
    cout << el << ", ";
  }
}

void store_vector() {
  std::vector<std::string> list;
  std::string word;

  cout << "Vector: ";
  while(cin >> word) {
    list.push_back(word);
  }

  print(list);
}

void store_list()
{
  std::list<std::string> list;
  std::string word;

  cout << "\nList: ";
  while (cin >> word)
  {
    list.push_back(word);
  }

  print(list);
}

void store_deque()
{
  std::deque<std::string> list;
  std::string word;

  cout << "\nDeque: ";
  while (cin >> word)
  {
    list.push_back(word);
  }

  print(list);
}

void reverse_list()
{
  std::list<std::string> list;
  std::string word;

  cout << "\nReversed List: ";
  while (cin >> word)
  {
    list.push_front(word);
  }

  print(list);
}

void reverse_deque()
{
  std::deque<std::string> list;
  std::string word;

  cout << "\nReversed Deque: ";
  while (cin >> word)
  {
    list.push_front(word);
  }

  print(list);
}

int main() {
  store_vector();
  store_list();
  store_deque();

  reverse_list();
  reverse_deque();
}
