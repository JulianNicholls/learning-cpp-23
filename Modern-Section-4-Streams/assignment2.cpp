#include <iostream>
#include <iomanip>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>

struct Language
{
  std::string lang;
  std::string designer;
  int date;
};

using LanguageVec = std::vector<Language>;

int main()
{
  std::ifstream ifile{"languages2.txt"};
  std::string line;
  LanguageVec languages;

  while (getline(ifile, line))
  {
    std::istringstream ssline{line};
    Language l;
    std::string word;

    // Format is now 'language_name' 'designer_maybe_multiple_words' 'date'
    ssline >> l.lang >> l.designer; // First (or only) word of designer

    bool found_date = false;

    while (ssline >> word && !found_date)
    {
      if (isdigit(word[0]))
      {
        l.date = stoi(word);
        found_date = true;
      }
      else
        l.designer = l.designer + " " + word;
    }

    languages.push_back(l);
  }

  for (const auto &item : languages)
  {
    // The assignment requirement
    std::cout << item.lang << ", " << item.designer << ", " << item.date << std::endl;
  }
}
