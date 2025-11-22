#include <algorithm>
#include <format>
#include <iostream>
#include <random>
#include <ranges>
#include <vector>

// Default projection for for_each
// I don't really understand the need for all this.
// It seems to me that I should be able to just return e
struct Identity
{
  template <typename T>
  constexpr T &&operator()(T &&e) const noexcept
  {
    return std::forward<T>(e);
  }
};

template <typename Range, typename Functor, typename Projection = Identity>
void for_each(Range &&range, Functor functor, Projection proj = {})
{
  auto beg = range.begin();
  auto end = range.end();

  while (beg != end)
  {
    auto &&elem = std::invoke(proj, *beg++);
    functor(elem);
  }
}

struct Document
{
  std::string name{};
  size_t size{};
  std::string type{};
  std::string tags{};

  size_t docsize() { return size; };

  friend std::ostream &operator<<(std::ostream &os, const Document &doc)
  {
    return os << std::format("{:<12}  {:>6}  {:<8} {:<10}", doc.name, doc.size, doc.type, doc.tags);
  }
};

int main()
{
  std::vector<Document> docs{
      {"Reports", 5123, "Word", "internal"},
      {"Sales", 71591, "Excel", "public"},
      {"Revenue", 80163, "Excel", "internal"},
      {"Portfolio", 85103, "PDF", "public"},
      {"Customers", 70213, "Excel", "internal"},
      {"Quotation", 50092, "Word", "public"},
  };

  auto printer = [](auto x)
  { std::cout << x << '\n'; };

  // These do the same thing
  // auto names = [](auto &doc) { return doc.name; };
  // for_each(docs, printer, names);      // or
  // for_each(docs, printer, &Document::name);

  auto ink = [](auto &doc)
  { return std::format("{:>2}K", doc.size / 1024); };
  for_each(docs, printer, ink);

  auto upper = [](const auto &doc)
  {
    auto name{doc.name};

    for_each(name, [](char &ch)
             { ch = toupper(ch); });

    return name;
  };

  std::cout << '\n';
  for_each(docs, printer, upper);

  std::cout << '\n';
  for_each(docs, printer);

  // std::vector<int> data(10);

  // std::ranges::generate(data, []() {
  //   return std::random_device{}() % 10;
  // });
}
