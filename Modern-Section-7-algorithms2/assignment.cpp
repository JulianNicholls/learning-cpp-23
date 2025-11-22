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

  std::transform(vec10.cbegin(), vec10.cend(), std::back_inserter(vec10d), [largest](int n)
                 { return (n * 1.0 / *largest); });
  cout << "Part 7:     ";
  print(vec10d);

  // 8. Sort, and then return the first entry greater than 455 and the number of elements > 455
  // vector<int> sorted = vec10;
  // vector<int> {455};
  // std::sort(sorted.begin(), sorted.end());

  // auto gt = std::find_first_of(sorted.cbegin(), sorted.cend(), greaterThan455);
  // auto it = std::stable_partition(sorted.begin(), sorted.end(), greaterThan455);
  cout << "\nPart 8:     " << "I have no idea how to do this with no lambda or functor\n";

  // After consulting the instructor's code, I found the function std::upper_bound which will return exactly this
  // but I'm not going to cheat.

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
}

std::string stripped(std::string_view s)
{
  std::string retval;

  std::copy_if(s.cbegin(), s.cend(), std::back_inserter(retval), [](char c)
               { return isalpha(c); });

  return retval;
}

int count_lines(const string& filename) {
  std::ifstream ifile(filename);

  int line_count = 0;
  string temp;

  while (getline(ifile, temp))
  {
    ++line_count;
  }

  ifile.close();

  return line_count;
}

int count_chars(const string &filename)
{
  std::ifstream ifile(filename);

  int char_count = 0;
  char temp;

  while (ifile >> temp)
  {
    ++char_count;
  }

  ifile.close();

  return char_count;
}

void files() {
  std::ifstream ifile("words.txt");
  std::ifstream ifile2("words2.txt");

  vector<string> words;
  vector<string> words2;
  vector<string> unique_words;
  vector<string> unique_words2;

  // auto lower = [](char c) { return tolower(c); };

  std::copy(std::istream_iterator<string>(ifile), std::istream_iterator<string>(), std::back_inserter(words));
  std::transform(words.cbegin(), words.cend(), words.begin(), [](const string& word) { return stripped(word); });
  std::copy_if(words.cbegin(), words.cend(), back_inserter(unique_words), [&unique_words](const string &word)
               { return std::find(unique_words.cbegin(), unique_words.cend(), word) == unique_words.end(); });

  std::sort(unique_words.begin(), unique_words.end());

  // print(words);

  // 14. Unique words
  cout << "Part 14:   ";
  print(unique_words);

  // 15. Word count
  cout << "\nPart 15:   " << words.size() << endl;

  cout << "Part 16:   " << count_lines("words.txt") << endl;

  cout << "Part 17:   " << count_chars("words.txt") << endl;

  std::copy(std::istream_iterator<string>(ifile2), std::istream_iterator<string>(), std::back_inserter(words2));
  std::transform(words2.cbegin(), words2.cend(), words2.begin(), [](const string &word)
                 { return stripped(word); });
  std::copy_if(words2.cbegin(), words2.cend(), back_inserter(unique_words2), [&unique_words2](const string &word)
               { return std::find(unique_words2.cbegin(), unique_words2.cend(), word) == unique_words2.end(); });

  std::sort(unique_words2.begin(), unique_words2.end());

  vector<string> common;

  std::set_intersection(unique_words.cbegin(), unique_words.cend(), unique_words2.cbegin(), unique_words2.cend(), std::back_inserter(common));

  cout << "Part 18:   ";
  print(common);
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
