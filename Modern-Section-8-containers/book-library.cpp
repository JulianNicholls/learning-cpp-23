#include <iostream>
#include <map>
#include <string>

using std::cout, std::endl;
using std::string, std::string_view;

class Book
{
public:
  Book(string_view publisher, string_view edition, int date) : publisher_{publisher}, edition_{edition}, date_(date) {}

  string to_string() const;

private:
  string publisher_;
  string edition_;
  int date_;
};

string Book::to_string() const
{
  return "(" + publisher_ + ", " + edition_ + ", " + std::to_string(date_) + ")";
}

class BookIndex
{
public:
  BookIndex(string_view author, string_view title) : author_{author}, title_{title} {}
  bool operator<(const BookIndex &other) const;

  string to_string() const;

private:
  string author_;
  string title_;
};

bool BookIndex::operator<(const BookIndex &other) const
{
  if (author_ == other.author_)
    return title_ < other.title_;

  return author_ < other.author_;
}

string BookIndex::to_string() const
{
  return "(" + author_ + ", " + title_ + ")";
}

using Library = std::multimap<BookIndex, Book>;

void library()
{
  Library library;

  Book prog_princs{"Addison-Wesley", "2nd Edition", 2014};
  library.insert({{"Stroustrup, Bjarne", "Programming Principles and Practice"}, prog_princs});

  Book cpp_primer("Addison-Wesley", "5th Edition", 2013);
  library.insert({{"Lippmann, Stanley B.", "C++ Primer"}, cpp_primer});

  Book cpp_prog("Addison-Wesley", "6th Edition", 2013);
  library.insert({{"Stroustrup, Bjarne", "The C++ Programming Language"}, cpp_prog});

  Book cpp_tour("Addison-Wesley", "1st Edition", 2018);
  library.insert({{"Stroustrup, Bjarne", "A Tour of C++"}, cpp_tour});

  for (auto [book, index] : library)
  {
    cout << book.to_string() << ": " << index.to_string() << endl;
  }
}

int main()
{
  library();
}
