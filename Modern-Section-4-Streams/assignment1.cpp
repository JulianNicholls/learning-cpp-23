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
  std::ifstream ifile{"languages.txt"};
  std::string line;
  LanguageVec list;

  while (getline(ifile, line))
  {
    std::istringstream ssline{line};
    Language l;

    ssline >> l.lang >> l.designer >> l.date;
    list.push_back(l);
  }

  for (const auto &item : list)
  {
    // The way I'd present it
    //    std::cout << std::left << std::setw(6) << item.lang << std::setw(20) << item.designer << item.data << std::endl;

    // The assignment requirement
    std::cout << item.lang << ", " << item.designer << ", " << item.date << std::endl;
  }
}
