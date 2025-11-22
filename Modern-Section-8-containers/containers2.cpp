#include <iomanip>
#include <iostream>
#include <map>
#include <unordered_map>
#include <set>
#include <string>

using std::cout, std::endl;   // Apparently multiple usings is a C++17 thing

template <typename T>
void print(const T &list)
{
  for (auto el : list)
  {
    cout << el << ", ";
  }
}

void print_map(const std::map<int, std::string> &m)
{
  for (auto [word, length] : m)   // C++17 decomposition
  {
    cout << word << ": " << length << ", ";
  }

  cout << endl;
}

void print_unordered_map(const std::unordered_map<int, std::string> &m)
{
  for (auto [word, length] : m) // C++17 decomposition
  {
    cout << word << ": " << length << ", ";
  }

  cout << endl;
}

void sets()
{
  std::set<int> s;

  cout << "Sets\n";

  s.insert(1);
  s.insert(7);
  s.insert(8);
  s.insert(9);
  s.insert(1);
  s.insert(2);
  s.insert(3);
  s.insert(4);
  s.insert(6);

  // insert() returns a pair,
  //  first is an iterator to the new or existing element
  //  second is a bool which says wheether the element was inserted
  auto [_i1, success] = s.insert(3); // should fail, C++17 decomposition again
  cout << (success ? "3 went in fine first time" : "3 wouldn't go in first time") << endl;

  s.erase(3);

  auto [_i2, ok] = s.insert(3);
  cout << (ok ? "3 went in fine second time" : "3 wouldn't go in second time") << endl;

  print(s);

  // s.find(k) returns an iterator that points to element k
  auto pos = s.find(7);
  cout << endl
       << (pos != s.end() ? "s has a 7" : "s has no 7") << endl;

  // s.count(k) returns the numer of times element k appears (0 or 1)
  auto count = s.count(7);
  cout << "7  appears " << count << " times\n";

  count = s.count(10);
  cout << "10 appears " << count << " times\n";

  // sets don't really work with many algorithms because
  //  (a) All elements are const
  //  (b) Ordfering is internaal
  //
  // Searching, insertion, membership checking, and removal are good, however,
  // because it is likely implemented as a red-black tree.
}

void ordered_maps()
{
  std::map<int, std::string> m;

  cout << "\nMaps\n";

  // Like set, insert() returns a pair,

  std::pair a(1, "Alfa");   // C++17 required

  auto [n, s] = a;          // Definitely C++17
  cout << "n: " << n << ", s: " << s << endl;

  m.insert(a);
  m.try_emplace(2, "Bravo");    // Avoid copy construction
  m.try_emplace(4, "Delta");    // try_emplace avoids construction at all if the key exists

  print_map(m);

  // map has subscripting capabilities, and the contents are not const

  cout << "Element 2: " << m[2] << endl;

  m[3] = "Charles";   // Will create the element
  m[5] = "Eggs";
  print_map(m);

  m[3] = "Charlie";   // Will update the element
  m[5] = "Echo";
  print_map(m);
  cout << endl;

  // C++17
  auto [where, inserted] = m.insert_or_assign(6, "Foxtrot");

  cout << where->second << " was " << (inserted ? "inserted" : "updated") << " at offset " << distance(m.begin(), where) << endl;

  if(auto [pos, in] = m.insert_or_assign(7, "Glof"); in)
    cout << "Inserted " << pos->second << endl;
  else
    cout << pos->second << " isn't new\n";

  if (auto [pos, in] = m.insert_or_assign(7, "Golf"); in)
    cout << "Inserted " << pos->second << endl;
  else
    cout << pos->second << " overwrote element " << pos->first << endl;;

  print_map(m);
  cout << endl;

  // Again, map has only limited use by algorithms because of the internal ordering
}

void unordered_maps()
{
  std::unordered_map<int, std::string> m;

  cout << "\nUnordered Maps\n";

  // Like set, insert() returns a pair,

  std::pair a(1, "Alfa"); // C++17 required

  auto [n, s] = a; // Definitely C++17
  cout << "n: " << n << ", s: " << s << endl;

  m.insert(a);
  m.try_emplace(4, "Delta");
  m.try_emplace(2, "Bravo");

  print_unordered_map(m);

  // map has subscripting capabilities, and the contents are not const

  cout << "Element 2: " << m[2] << endl;

  m[5] = "Eggs";    // Will create the element
  m[3] = "Charles";
  print_unordered_map(m);

  m[5] = "Echo";    // Will update the element
  m[3] = "Charlie";
  print_unordered_map(m);
  cout << endl;

  // C++17
  auto [where, inserted] = m.insert_or_assign(6, "Foxtrot");

  cout << where->second << " was " << (inserted ? "inserted" : "updated") << " at offset " << distance(m.begin(), where) << endl;

  if (auto [pos, in] = m.insert_or_assign(7, "Glof"); in)
    cout << "Inserted " << pos->second << endl;
  else
    cout << pos->second << " isn't new\n";

  if (auto [pos, in] = m.insert_or_assign(7, "Golf"); in)
    cout << "Inserted " << pos->second << endl;
  else
    cout << pos->second << " overwrote element " << pos->first << endl;
  ;

  print_unordered_map(m);
  cout << endl;

  // There are unordered_multimaps too
}

// There are multisets and multimaps (doesn't allow subscripting).
// These both allow duplicate keys, which rather goes against the point of a set in my book...
// In multimaps, you can use member functions lower_bound(), upper_cound() and equal_range()

int main()
{
  sets();
  ordered_maps();
  unordered_maps();
}
