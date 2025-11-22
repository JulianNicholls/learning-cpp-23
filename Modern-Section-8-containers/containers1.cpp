#include <iomanip>
#include <iostream>
#include <string>
#include <array>
#include <forward_list>
#include <list>
#include <deque>

using std::cout, std::endl;

template <typename T> void print(const T& list) {
  for (auto el : list)
  {
    cout << el << ", ";
  }
}

void arrays() {
  std::array<int, 5> list{1, 2, 3, 4, 5};  // Length is part of the type

  cout << "Arrays\n";
  cout << "Element 3: " << list[3] << endl;

  list[3] = 99;
  cout << "Element 3: " << list[3] << endl;

  print(list);
  // Has functions size(), empty(), at() (bounds-checked), front() / back(), data()
  // Advantage is that you can pass a std::array to a function without having to commmunicate its length.
}

// Singly-linked list
void forward_list() {
  std::forward_list list{4, 3, 1};
  std::forward_list list2{7, 8, 9};

  cout << "\n\nforward_lists\nBefore Insertion: ";
  print(list);

  auto second = std::next(list.begin());
  list.insert_after(second, 2);

  cout << "\nAfter Insertion:  ";
  print(list);

  list.erase_after(second);

  cout << "\nAfter Erasure:    ";
  print(list);

  // forward_list has splice_after(), but the new elements come after the iterator.

  list.splice_after(list.begin(), list2);   // Importantly, list2 IS NOW EMPTY

  cout << "\nAfter Splice:     ";
  print(list);
  cout << "  (list2: ";
  print(list2);
  cout << ")\n";
}

// Doubly-linked list
void list()
{
  std::list list{5, 4, 3, 1};

  cout << "\nlists\nBefore Insertion: ";
  print(list);

  auto last = std::prev(list.end());
  auto inserted = list.insert(last, 2);   // Insert before

  cout << "\nAfter Insertion:  ";
  print(list);

  list.erase(inserted);

  cout << "\nAfter Erasure:    ";
  print(list);

  // Operations
  // sort() is a member function, the std algorithm does not work because it is not random-access.
  // remove actually removes, no need for a followup erase.
  // reverse(), remove_if(), unique() (from a sorted list only)

  // std::sort(list.begin(),list.end());    // Doesn't compile, but no error in here.
  list.sort();

  cout << "\nAfter Sort:       ";
  print(list);

  list.remove(3);    // Remove the value 3, not offset 3

  cout << "\nAfter Remove:     ";
  print(list);

  list.insert(list.begin(), 4);
  list.sort();
  list.unique();
  cout << "\nAfter Unique:     ";
  print(list);

  std::list list2{5, 7, 9, 11};
  std::list list3{6, 8, 10, 12};
  std::list list4{16, 17, 18, 19};

  list2.merge(list3);   // Importantly, list3 IS NOW EMPTY

  cout << "\nAfter Merge:      ";
  print(list2);
  cout << "  (list3: ";
  print(list3);
  cout << ")\n";

  auto p = std::next(std::next(list2.begin()));
  list2.splice(p, list4);   // Again, list4 IS NOW EMPTY

  cout << "After Splice:     ";
  print(list2);
  cout << "  (list4: ";
  print(list4);
  cout << ")\n";

  // List is much slower and uses more memory than vector or deque for most operations,
  // but it shines at adding and removing as long as one doesn't have to search.
}

// Double-ended queue
void deque() {
  std::deque<int> list{1, 2, 3, 4, 5};

  list.push_front(0);
  list.push_front(-1);

  list.push_back(6);
  list.push_back(7);
  list.push_back(8);

  cout << "\nDeques:\n";
  print(list);

  // Deque is slightly slower for most operations, but adding and removing at the front is faster
}

int main() {
  arrays();
  forward_list();
  list();
  deque();
}
