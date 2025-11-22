#include <algorithm>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <numeric>
#include <random>
#include <string>
#include <vector>

using std::cout, std::endl;
using std::string;
using std::vector;

std::random_device rd;
std::mt19937 mt(rd());
std::uniform_int_distribution<int> filler(1, 1000);

auto is_odd = [](int n)
{ return n % 2 != 0; };

template <class T>
void print(const vector<T> &vec)
{
  std::copy(vec.cbegin(), vec.cend(), std::ostream_iterator<T>(cout, " "));
}

void numeric()
{
  vector<int> vec10(10);

  // 1. Fill with 10 randoms between 1 & 1000
  std::transform(vec10.begin(), vec10.end(), vec10.begin(), [](int)
                 { return filler(mt); });

  // 1. std::generate_n(begin(vec10), 10, filler(mt));

  cout << "Part 1 / 2: ";

  // 2. Recurring output
  print(vec10);

  // 3 / 4. Largest element and its index
  auto largest = std::max_element(vec10.cbegin(), vec10.cend());
  cout << "\nPart 3 / 4: " << *largest << " at offset " << std::distance(vec10.cbegin(), largest) << endl;

  // 5. Sum of the elements
  auto sum = std::accumulate(vec10.cbegin(), vec10.cend(), 0);
  cout << "Part 5:     " << sum << endl;

  // 6. Count the odd numbers in the vector
  int count = std::count_if(vec10.cbegin(), vec10.cend(), is_odd);
  cout << "Part 6:     " << count << " odd elements\n";

  // 7. Normalise into a vector of doubles
  vector<double> vec10d;

  std::transform(vec10.cbegin(), vec10.cend(), std::back_inserter(vec10d),
    [largest](int n) { return (n * 1.0 / *largest); });

  cout << "Part 7:     ";
  print(vec10d);

  // 8. Sort, and then return the first entry greater than 455 and the number of elements > 455
  // This is the one which I really could not do, even after much research.
  // There are obvious ways to do it with a lambda, but that wasn't allowed
  vector<int> sorted = vec10;
  std::sort(sorted.begin(), sorted.end());

  auto it = std::upper_bound(cbegin(sorted), cend(sorted), 455);

  cout << "\nPart 8:     " << "The first element greater than 455 is " << *it << endl
      << "Vector contains " << distance(it, cend(sorted)) << " elements greater than 455\n";

  // 9. Copy the odds to a vector of doubles.
  vector<double> vec10d2;
  std::copy_if(vec10.cbegin(), vec10.cend(), back_inserter(vec10d2), is_odd);

  cout << "Part 9:     ";
  print(vec10d2);

  // 10. Sort into decreasing order
  std::sort(vec10.begin(), vec10.end(), std::greater{});

  cout << "\nPart 10:    ";
  print(vec10);

  // 11. Randomly shuffle, but not the first or last - Could have used next() & prev()
  std::shuffle(vec10.begin() + 1, vec10.end() - 1, mt);

  cout << "\nPart 11:    ";
  print(vec10);

  // 12. Remove all the odd numbers, could have used remove_if
  // Other option
//    auto last = std::remove_if(begin(vec), end(vec), is_odd);
//    vec.erase(last, end(vec));

  auto pivot = std::partition(vec10.begin(), vec10.end(), is_odd);
  vec10.erase(vec10.begin(), pivot);

  cout << "\nPart 12:    ";
  print(vec10);

  // 13. Print all the remaining numbers to a file without a trailing comma

  std::ofstream ofile("numbers.txt");

  string result = std::accumulate(std::next(vec10.begin()), vec10.end(), std::to_string(vec10[0]), [](const string &a, int b)
                                  { return a + ", " + std::to_string(b); });

  ofile << result;

  cout << "\nPart 13:    " << result << endl;

  // A better solution?
  std::ostream_iterator<int> out(ofile, ",");
  std::copy(cbegin(vec10), prev(cend(vec10)), out);

  std::ostream_iterator<int> out2(ofile);
  std::copy(prev(cend(vec10)), cend(vec10), out2);
}

// Return a copy of the argument string
// with non-alphabetical characters removed, converted to lower case
string normalise(const string &s)
{
  string retval;

  copy_if(cbegin(s), cend(s), back_inserter(retval),
          [](char c) { return isalpha(c); });
  transform(begin(retval), begin(retval), begin(retval),
            [](char c) { return tolower(c); });

  return retval;
}

void files() {
  std::ifstream ifile("words.txt");

  vector<string> words;

  // Another way to import the words into a vector
  //  vector<string> in_words(std::istream_iterator<string>(ifile), std::istream_iterator<string>());

  std::copy(std::istream_iterator<string>(ifile), std::istream_iterator<string>(), std::back_inserter(words));
  std::transform(words.cbegin(), words.cend(), words.begin(), normalise);

  // Sort and remove dusplicates

  vector<string> unique_words = words;
  std::sort(unique_words.begin(), unique_words.end());
  auto last = std::unique(unique_words.begin(), unique_words.end());
  unique_words.erase(last, unique_words.end());

  // print(words);

  // 14. Unique words
  cout << "Part 14:   ";
  print(unique_words);

  // 15. Word count
  cout << "\nPart 15:   " << words.size() << endl;

  // 16. lines in the file

  std::ifstream wif("words.txt");
  string in_words{std::istreambuf_iterator<char>(wif), std::istreambuf_iterator<char>()};

  auto nlines = std::count(cbegin(in_words), cend(in_words), '\n');

  cout << "Part 16:   " << nlines << endl;
  cout << "Part 17:   " << in_words.size() << endl;

  std::ifstream wif1{"words.txt"};
  std::ifstream wif2{"words2.txt"};

  std::istream_iterator<string> iit{wif1};
  std::istream_iterator<string> iit2{wif2};
  std::istream_iterator<string> eof;

  vector<string> in_words1{iit, eof};
  vector<string> in_words2{iit, eof};

  // Normalize the words.txt vector
  vector<string> words1, words2;
  transform(cbegin(in_words1), cend(in_words1), back_inserter(words1), normalise);
  sort(begin(words1), end(words1));

  auto last1 = std::unique(begin(words1), end(words1));
  words.erase(last1, end(words1));

  // Normalize the words2.txt vector
  transform(cbegin(in_words2), cend(in_words2), back_inserter(words2), normalise);
  sort(begin(words2), end(words2));
  auto last2 = unique(begin(words2), end(words2));
  words2.erase(last2, end(words2));

  cout << "Part 18:   ";
  std::ostream_iterator<string> out(cout, "\n");
  std::set_intersection(words1.cbegin(), words1.cend(), words2.cbegin(), words2.cend(), out);
}

void final() {
  vector<int> range(6);
  std::iota(range.begin(), range.end(), 1); // fill with 1, 2, ..., n

  cout << "\nPart 19:   " << std::accumulate(range.begin(), range.end(), 1, std::multiplies<>()) << endl;
}

int main()
{
  numeric();
  files();
  final();
}
