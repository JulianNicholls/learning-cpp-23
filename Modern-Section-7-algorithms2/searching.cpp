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

void show_searching()
{
  std::string str{"This is the voice of the Mysterons for a change"};
  std::string hello{"Hello"};
  std::string rhythm{"rhythm"};
  std::string vowels{"aeiou"};
  std::string is{"is"};

  // Equivalent to str.find_first_of
  auto first_vowel = std::find_first_of(str.cbegin(), str.cend(), vowels.cbegin(), vowels.cend());
  auto first_rhythm_vowel = std::find_first_of(rhythm.cbegin(), rhythm.cend(), vowels.cbegin(), vowels.cend());
  auto adjacency = std::adjacent_find(hello.cbegin(), hello.cend());
  auto isi = std::search(str.cbegin(), str.cend(), is.cbegin(), is.cend());

  if (first_vowel != str.cend())
  {
    std::cout << "First vowel in " << str << ": " << *first_vowel << " at offset " << std::distance(str.cbegin(), first_vowel) << std::endl;

    auto next_vowel = std::find_first_of(std::next(first_vowel), str.cend(), vowels.cbegin(), vowels.cend());
    std::cout << "Next vowel: " << *next_vowel << " at offset " << std::distance(str.cbegin(), next_vowel) << std::endl;
  }

  if (first_rhythm_vowel != rhythm.cend())
    std::cout << "First vowel in " << str << ": " << *first_rhythm_vowel << " at offset " << std::distance(str.cbegin(), first_rhythm_vowel) << std::endl;
  else
    std::cout << "There are no vowels in " << rhythm << std::endl;

  if (adjacency != hello.cend())
  {
    std::cout << "adjacent elements in " << hello << ": " << *adjacency << " at offset " << std::distance(hello.cbegin(), adjacency) << std::endl;
  }

  if (isi != str.cend())
  {
    std::cout << "'is' in " << str << ": " << *isi << " at offset " << std::distance(str.cbegin(), isi) << std::endl;

    auto next_is = std::find_first_of(std::next(isi), str.cend(), vowels.cbegin(), vowels.cend());
    std::cout << "Next 'is': " << *next_is << " at offset " << std::distance(str.cbegin(), next_is) << std::endl;
  }
}

void more_searching()
{
  std::vector<int> vec1{1, 2, 2, 3, 4, 6, 4, 5, 6};
  std::vector<int> vec2{1, 2, 2, 4, 6, 6, 4, 5, 6};
  std::vector<int> vec3{2, 2, 4, 6, 6, 8, 10};

  std::cout << "\nMore searching\n";

  // mismatch returns a pair of iterators
  auto elems = std::mismatch(vec1.cbegin(), vec1.cend(), vec2.cbegin(), vec2.cend());

  if (elems.first != vec1.cend() && elems.second != vec2.cend())
  {
    std::cout << "There was a mismatch at index " << std::distance(vec1.cbegin(), elems.first) << std::endl;
    std::cout << "vec1 has " << *elems.first << " and vec2 has " << *elems.second << std::endl;
  }

  std::cout << "\nall_of, any_of, none_of\n";

  auto is_odd = [](int x)
  { return x % 2 == 1; };
  auto is_even = [](int x)
  { return x % 2 == 0; };

  if (std::all_of(vec1.cbegin(), vec1.cend(), is_odd))
    std::cout << "All of vec1 is odd\n";
  if (std::all_of(vec2.cbegin(), vec2.cend(), is_odd))
    std::cout << "All of vec2 is odd\n";
  if (std::all_of(vec3.cbegin(), vec3.cend(), is_odd))
    std::cout << "All of vec3 is odd\n";

  if (std::all_of(vec1.cbegin(), vec1.cend(), is_even))
    std::cout << "All of vec1 is even\n";
  if (std::all_of(vec2.cbegin(), vec2.cend(), is_even))
    std::cout << "All of vec2 is even\n";
  if (std::all_of(vec3.cbegin(), vec3.cend(), is_even))
    std::cout << "All of vec3 is even\n";

  if (std::any_of(vec1.cbegin(), vec1.cend(), is_odd))
    std::cout << "Some of vec1 is odd\n";
  if (std::any_of(vec2.cbegin(), vec2.cend(), is_odd))
    std::cout << "Some of vec2 is odd\n";
  if (std::any_of(vec3.cbegin(), vec3.cend(), is_odd))
    std::cout << "Some of vec3 is odd\n";

  if (std::any_of(vec1.cbegin(), vec1.cend(), is_even))
    std::cout << "Some of vec1 is even\n";
  if (std::any_of(vec2.cbegin(), vec2.cend(), is_even))
    std::cout << "Some of vec2 is even\n";
  if (std::any_of(vec3.cbegin(), vec3.cend(), is_even))
    std::cout << "Some of vec3 is even\n";

  if (std::none_of(vec1.cbegin(), vec1.cend(), is_odd))
    std::cout << "None of vec1 is odd\n";
  if (std::none_of(vec2.cbegin(), vec2.cend(), is_odd))
    std::cout << "None of vec2 is odd\n";
  if (std::none_of(vec3.cbegin(), vec3.cend(), is_odd))
    std::cout << "None of vec3 is odd\n";

  if (std::none_of(vec1.cbegin(), vec1.cend(), is_even))
    std::cout << "None of vec1 is even\n";
  if (std::none_of(vec2.cbegin(), vec2.cend(), is_even))
    std::cout << "None of vec2 is even\n";
  if (std::none_of(vec3.cbegin(), vec3.cend(), is_even))
    std::cout << "None of vec3 is even\n";
}

void again_searching()
{
  std::vector<int> vec3{2, 2, 4, 6, 6, 8, 10, 12, 12, 14, 15, 16, 16, 17};
  std::vector<int> sample{2, 6, 17};

  std::cout << "\nEven more...\n";

  // Disappointingly, binary_search returns boolm like find
  if (std::binary_search(vec3.cbegin(), vec3.cend(), 6))
  {
    std::cout << "vec3 contains 6\n";
  }

  // includes is also bool, both vectors must be sorted.
  if (std::includes(vec3.cbegin(), vec3.cend(), sample.cbegin(), sample.cend()))
  {
    std::cout << "vec3 contains all of sample\n";
  }
}

int main()
{
  show_searching();
  more_searching();
  again_searching();

  std::cout << std::endl;
}
