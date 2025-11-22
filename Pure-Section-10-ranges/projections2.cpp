#include <algorithm>
#include <format>
#include <iostream>
#include <random>
#include <ranges>
#include <vector>

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

  auto printer = [](auto x) { std::cout << x << '\n'; };

  // These do the same thing
  // auto names = [](auto &doc) { return doc.name; };
  // for_each(docs, printer, names);      // or
  // for_each(docs, printer, &Document::name);

  auto ink = [](const auto& doc) { return std::format("{:>2}K", doc.size / 1024); };
  std::ranges::for_each(docs, printer, ink);

  auto upper = [](const auto &doc)
  {
    auto name{doc.name};

    std::ranges::for_each(name, [](char &ch)
                          { ch = toupper(ch); });

    return name;
  };

  std::cout << '\n';
  std::ranges::for_each(docs, printer, upper);

  // std::ranges::sort(docs, [](const Document& lhs, const Document& rhs) { return lhs.size < rhs.size; });
  std::ranges::sort(docs, std::less{}, &Document::size);

  std::cout << '\n';
  std::ranges::for_each(docs, printer);

  auto pos = std::ranges::min_element(docs, /*std::less*/{}, &Document::size);
  std::cout << "\nSmallest Document:\n  " << *pos << '\n';
}
