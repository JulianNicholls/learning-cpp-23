#include <algorithm>
#include <cassert>
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

struct BackedupDocuments
{
  std::vector<Document> docs{};

  void operator()(Document &other)
  {
    if (other.type == "Word")
    {
      docs.push_back(other);
      other.type = "PDF";
    }
  }
};

template <typename Container>
void print(Container &&container, std::string message = "", std::string separator = ", ")
{
  std::cout << std::format("====== {} ======\n", message);

  for (const auto &v : container)
  {
    std::cout << v << separator;
  }

  std::cout << '\n';
}

void show_for_each()
{
  std::vector<Document> docs{
      {"Reports", 5123, "Word", "internal"},
      {"Sales", 71591, "Excel", "public"},
      {"Revenue", 80163, "Excel", "internal"},
      {"Portfolio", 85103, "PDF", "public"},
      {"Customers", 70213, "Excel", "internal"},
      {"Quotation", 50092, "Word", "public"},
  };

  // auto doc_backup = std::for_each(docs.begin(), docs.end(), BackedupDocuments{});

  auto [itr, fnObj] = std::ranges::for_each(docs, BackedupDocuments{});

  assert(itr == docs.end());

  print(fnObj.docs, "Backed Up", "\n");
  print(docs, "Original after backup", "\n");
}

void show_copy_if()
{
  std::vector<Document> docs{
      {"Reports", 5123, "Word", "internal"},
      {"Sales", 71591, "Excel", "public"},
      {"Revenue", 80163, "Excel", "internal"},
      {"Portfolio", 85103, "PDF", "public"},
      {"Customers", 70213, "Excel", "internal"},
      {"Quotation", 50092, "Word", "public"},
  };

  std::vector<Document> copies(9);

  copies.emplace_back("Budgeting", 88123, "Excel", "internal");
  copies.emplace_back("Expenses", 21798, "Excel", "internal");
  copies.emplace_back("Tax", 78312, "Excel", "internal");

  print(docs, "Original", "\n");

  // auto itr = std::copy_if(docs.begin(), docs.end(), copies.begin(), [](const Document& doc) { return doc.type == "Excel"; });

  // if(itr != copies.end()) {
  //   std::cout << *itr << '\n';
  // }

  auto [in, out] = std::ranges::copy_if(docs, copies.begin(), [](const Document &doc)
                                        { return doc.type == "Excel"; });

  assert(in == docs.end());

  print(copies, "Copies", "\n");
}

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

  auto [min, max] = std::ranges::minmax_element(docs, [](const auto &d1, const auto& d2) { return d1.size < d2.size; });

  std::cout << "Min: " << *min << '\n';
  std::cout << "Max: " << *max << '\n';
}
