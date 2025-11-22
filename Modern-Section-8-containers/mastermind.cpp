#include <algorithm>
#include <iostream>
#include <random>
#include <string>

#include "constants.h"

using std::cin, std::cout, std::endl;
using std::string;

static std::random_device rd;
static std::mt19937 mt(rd());
static std::uniform_int_distribution<int> ud(0, constants::ncolours - 1);

PegArray populate()
{
  PegArray code;

  std::generate(begin(code), end(code), [&]()
                { return constants::colours[ud(mt)]; });

  return code;
}

string normalise(const string &input)
{
  string result;

  copy_if(input.cbegin(), input.cend(), std::back_inserter(result), [](char c)
          { return isalpha(c); });
  std::transform(result.cbegin(), result.cend(), result.begin(), [](char c)
                 { return toupper(c); });

  return result;
}

PegArray get_input()
{
  string input, normal;
  PegArray result;

  do
  {
    cout << "\nEnter " << constants::npegs << " characters (";
    for (auto c : constants::colours)
      cout << c;
    cout << ")\n";

    getline(cin, input);
    normal = normalise(input);
  } while (normal.size() != constants::npegs);

  for (size_t i = 0; i < normal.size(); ++i)
    result[i] = normal[i];

  return result;
}

int exact_matches(const PegArray& guess, const PegArray& solution)
{
  PegArray matches;
  std::transform(guess.cbegin(), guess.cend(), solution.cbegin(), matches.begin(), [](char c1, char c2) {return (c1 == c2) ? c1 : '\0'; });

  return std::count_if(matches.cbegin(), matches.cend(), [](char c) { return c != '\0'; });
}

int loose_matches(const PegArray& guess, const PegArray& solution)
{
  string temp;
  int count{0};

  std::copy(guess.cbegin(), guess.cend(), std::back_inserter(temp));

  for(auto peg: solution)
  {
    if(auto it = std::find(temp.begin(), temp.end(), peg); it != temp.end())
    {
      ++count;
      temp.erase(it);
    }
  }

  return count;
}

int main()
{
  PegArray pegs = populate();
  // PegArray pegs = {'R', 'G', 'B', 'B'};

  bool win{false};

  for (int i = 0; i < constants::nturns; ++i)
  {
    PegArray input = get_input();

    auto exact = exact_matches(input, pegs);
    auto loose = loose_matches(input, pegs) - exact;

    cout << exact << " exact matches, " << loose << " near matches\n";

    if (exact == constants::npegs)
    {
      cout << "\nYou found the correct solution: ";
      for (auto peg : pegs)
        cout << peg;

      cout << endl;
      win = true;
      break;
    }
  }

  if (!win)
  {
    cout << "\nYou lose! The correct solution was: ";
    for (auto peg : pegs)
      cout << peg;

    cout << endl;
  }
}
