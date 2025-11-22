// asv.cpp

#include <iostream>
#include <string>
#include <string_view>

class URL
{
public:
  URL(const std::string_view &protocol, const std::string_view &resource)
      : protocol_{protocol}, resource_{resource} {};

  std::string full_url();

private:
  std::string protocol_;
  std::string resource_;
};

std::string URL::full_url()
{
  return protocol_ + "://" + resource_;
}

int main()
{
  URL url1{"https", "propertykrowd.com"};
  URL url2{std::string("https"), "legacy.propertykrowd.com"};

  std::cout << "url1: " << url1.full_url() << std::endl;
  std::cout << "url2: " << url2.full_url() << std::endl;
}
