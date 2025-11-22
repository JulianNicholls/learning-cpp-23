#include <algorithm>
#include <iostream>
#include <list>
#include <string>
#include <string_view>

using std::cout, std::endl;

class URL
{
public:
  URL(const std::string_view &protocol, const std::string_view &resource)
      : protocol_{protocol}, resource_{resource} {};

  std::string full_url() const;
  bool operator==(const URL &other) const;

private:
  std::string protocol_;
  std::string resource_;
};

std::string URL::full_url() const
{
  return protocol_ + "://" + resource_;
}

bool URL::operator==(const URL &other) const
{
  return protocol_ == other.protocol_ && resource_ == other.resource_;
}

// I swent way too much time choosing between a std::list and a std::deque
// and arrived at the conclusion that for a small list, either is good and
// probably for a large list, the deque may win out.

class URLList
{
public:
  URLList() : list_{} {};

  void add(const URL &url);
  void print() const;

private:
  std::list<URL> list_;
};

void URLList::add(const URL &url)
{
  auto pos = std::find(list_.cbegin(), list_.cend(), url);

  if (pos == list_.cend())
    list_.push_front(url);
  else
    list_.splice(list_.begin(), list_, pos);
}

void URLList::print() const
{
  for (auto el : list_)
  {
    cout << el.full_url() << ", ";
  }
}

int main()
{
  URLList url_list;

  url_list.add({"https", "google.com"});
  url_list.add({"https", "maps.google.co.uk"});
  url_list.add({"https", "reallybigshoe.co.uk"});

  cout << "Original:    ";
  url_list.print();

  url_list.add({"http", "bing.com"});

  cout << "\nAfter Add:   ";
  url_list.print();

  url_list.add({"https", "google.com"});

  cout << "\nAfter Shift: ";
  url_list.print();
}
