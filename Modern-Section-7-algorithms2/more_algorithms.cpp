#include <algorithm>
#include <iomanip>
#include <iostream>
#include <numeric>
#include <string>
#include <vector>

void print(const std::vector<int> &v)
{
  for (int i : v)
  {
    std::cout << i << ", ";
  }

  std::cout << std::endl;
}

void show_replacement()
{
  std::vector<int> vec{2, 2, 4, 6, 6, 8, 10, 12, 12, 14, 15, 16, 16, 17};
  std::vector<int> vec2;

  std::cout << "\nReplacement\n";

  print(vec);

  // replace has all combinations of copy and if
  // replace, replace_if, replace_copy, and replace_copy_if

  std::replace_copy(vec.cbegin(), vec.cend(), std::back_inserter(vec2), 12, 99);
  print(vec2);

  std::replace_if(vec.begin(), vec.end(), [](int n)
                  { return n % 3 == 0; }, 999);
  print(vec);
}

void show_removal()
{
  std::vector<int> vec{1, 6, 2, 6, 3, 6, 4, 6, 5};

  std::cout << "\nRemoval\n";

  print(vec);

  auto rest = std::remove(vec.begin(), vec.end(), 6);
  print(vec); // Interestingly, it doesn't remove them (I knew that), but it also doesn't move them to the end
  std::cout << "Removed items start at offset " << std::distance(vec.begin(), rest) << std::endl;

  vec.erase(rest, vec.end());
  std::cout << "Now, they're gone: ";
  print(vec);

  // remove also has friends, remove_if, remove_copy, and remove_if_copy.
  // The copies copy the elements that are not ebing removed.
  std::vector<int> vec2(20);
  std::iota(vec2.begin(), vec2.end(), 1);
  vec2.erase(std::remove_if(vec2.begin(), vec2.end(),
                            [](int n)
                            { return n % 2 == 1; }),
             vec2.end());

  print(vec2);

  // unique removes adjacent duplicate elements, and can take a predicate with two items,
  // and will remove the second if the predicate is true
  // There is also an _copy version
  std::vector<int> vec3{2, 2, 4, 6, 6, 8, 10, 12, 12, 14, 15, 16, 16, 17};

  print(vec3);

  vec3.erase(unique(vec3.begin(), vec3.end()), vec3.end());

  print(vec3);
}

void show_transform()
{
  using StatPair = std::pair<std::string_view, int>;

  std::vector<StatPair> stats{{"score", 5020}, {"rank", 2}, {"years", 10}};
  std::vector<std::string_view> titles;
  std::vector<int> values;

  std::cout << "\nTransform\nStats:  ";

  std::transform(stats.cbegin(), stats.cend(), std::back_inserter(titles), [](const StatPair &item)
                 { return item.first; });
  std::transform(stats.cbegin(), stats.cend(), std::back_inserter(values), [](const StatPair &item)
                 { return item.second; });

  for (const auto &item : stats)
  {
    std::cout << item.first << ": " << item.second << ", ";
  }

  std::cout << "\ntitles: ";

  for (const auto &item : titles)
  {
    std::cout << item << ", ";
  }

  std::cout << "\nvalues: ";

  for (auto item : values)
  {
    std::cout << item << ", ";
  }

  std::cout << std::endl;

  // It is possible to do an in-place transformation
}

void show_merging()
{
  std::vector<int> vec1{2, 4, 6, 8, 10, 12, 14, 15, 16, 17};
  std::vector<int> vec2{1, 2, 4, 5, 6};
  std::vector<int> vec3;

  std::cout << "\nMerging\n";

  std::cout << "vec1: ";
  print(vec1);
  std::cout << "vec2: ";
  print(vec2);

  // Merge merges two SORTED vectors.
  std::merge(vec1.cbegin(), vec1.cend(), vec2.cbegin(), vec2.cend(), std::back_inserter(vec3));

  std::cout << "\nmerge:        ";
  print(vec3);

  vec3.erase(vec3.begin(), vec3.end());
  std::set_intersection(vec1.cbegin(), vec1.cend(), vec2.cbegin(), vec2.cend(), std::back_inserter(vec3));

  std::cout << "intersection: ";
  print(vec3);

  vec3.erase(vec3.begin(), vec3.end());
  std::set_union(vec1.cbegin(), vec1.cend(), vec2.cbegin(), vec2.cend(), std::back_inserter(vec3));

  std::cout << "union:        ";
  print(vec3);

  // rotate, swaps elements before and after a pivot
  // 1, 2, 4, 5, 6 => 4, 5, 6, 1, 2
  std::rotate(vec2.begin(), vec2.begin() + 2, vec2.end());
  std::cout << "rotate vec2:  ";
  print(vec2);
}

class Parter
{
public:
  Parter(int low, int high) : low_(low), high_(high) {}

  bool operator()(int n) const { return n >= low_ && n <= high_; };

private:
  int low_;
  int high_;
};

void show_partitioning()
{
  std::vector<int> vec1{2, 4, 6, 8, 10, 12, 14, 15, 16, 17};
  std::vector<int> vec2(15);

  std::cout << "\nPartitioning\n";

  std::cout << "vec1: ";
  print(vec1);

  // Partition is pretty unstable, it completely scrambles vec1 here, albeit with the correct ones at the front.
  Parter part1014(10, 14);

  std::partition(vec1.begin(), vec1.end(), part1014);

  std::cout << "partitioned on 10 - 14: ";
  print(vec1);

  // stable_partition retains ordering in the two groups at the expense of speed.
  Parter part712(7, 12);

  std::iota(vec2.begin(), vec2.end(), 1);
  std::stable_partition(vec2.begin(), vec2.end(), part712);

  std::cout << "vec2 stable_partitioned on 7 - 12: ";
  print(vec2);

  std::cout << "vec2 Partitioned: " << std::boolalpha << std::is_partitioned(vec2.cbegin(), vec2.cend(), part712) << std::endl;
}

void show_permutations() {
  std::string str("ABCD");    // To get all permutations, it must be pre-sorted
  std::string left{"qwertyuiopasdfghjklzxcvbnm"};
  std::string right{"abcdefghijklmnopqrstuvwxyz"};

  std::cout << "\nPermutations: ";

  do {
    std::cout << str << ", ";
  }
  while(std::next_permutation(str.begin(), str.end()));

  // There is also a prev_permutation, which requires it to be pre-sorted in reverse order to begin with

  std::cout << "\nLeft is a permutation of Right: " << std::is_permutation(left.cbegin(), left.cend(), right.cbegin(), right.cend());

  std::cout << std::endl;
}

void show_min_max() {
  std::string left{"qwertyuiopasdfghjklzxcvbnm"};
  std::string right{"abcdefghijklmnopqrstuvwxyz"};
  std::vector<int> vec{2, 6, 5, 3, 10, 8, 11, 12, 19, 14, 15, 16, 16, 17};

  std::cout << "\nmin / max\n";

  std::cout << "Left:  " << left << std::endl;
  std::cout << "Right: " << right << std::endl;

  std::cout << "\nmin:   " << std::min(left, right) << std::endl;
  std::cout << "max:   " << std::max(left, right) << std::endl;

  std::cout << "min of: ";
  print(vec);
  std::cout << "via initialiser list = " << std::min({2, 6, 5, 3, 10, 8, 11, 12, 19, 14, 15, 16, 16, 17}) << std::endl;
  std::cout << "via interators       = " << *std::min(vec.cbegin(), vec.cend()) << std::endl;
  std::cout << "via max_element      = " << *std::max_element(vec.cbegin(), vec.cend()) << std::endl;

  // std::min and std::max seem to be synonyms of std::min_element and std::max_element if passed two iterators
  // There is also a minmax / minmax_element which returns a pair.
}

std::string stripped(std::string_view s)
{
  std::string retval;

  std::copy_if(s.cbegin(), s.cend(), std::back_inserter(retval), [](char c)
               { return isalpha(c); });

  return retval;
}

void palindromes()
{
  std::string p1("Madam, I'm Adam");
  std::string p2("Able was I ere I saw Elba");
  std::string p3("A man, a plan, a canal, Panama");
  std::string n1("Contrived, devitrenc"); // NOT

  std::vector<std::string> pals{p1, p2, n1, p3};

  std::cout << "\nPalindromes\n";

  auto lower = [](char c) { return tolower(c); };

  for(const auto& v : pals)  {
    std::string cand = stripped(v);

    std::transform(cand.cbegin(), cand.cend(), cand.begin(), lower);

    auto check = std::mismatch(cand.cbegin(), cand.cend(), cand.crbegin());

    if(check.first == cand.cend())
      std::cout << v << " is a palindrome\n";
    else
      std::cout << v << " is not a palindrome\n";
  }
}

int main()
{
  show_replacement();
  show_removal();
  show_transform();
  show_merging();
  show_partitioning();
  show_permutations();
  show_min_max();
  palindromes();

  // Other algorithms:
  //  reverse, reverse_copy
  //  sort, stable_sort, is_sorted, is_sorted_until,
  //  partial_sort, partial_sort_copy
  //  nth_element()

  std::cout << std::endl;
}
