#include <algorithm>
#include <format>
#include <print>
#include <random>
#include <ranges>
#include <vector>

using Pair = std::pair<int, std::string>;
using PairVector = std::vector<Pair>;

template <typename Container>
void print(Container &&container, std::string message = "", std::string separator = ", ")
{
    std::println("====== {} ======", message);

    for (const auto &v : container)
    {
        std::print("{:>3}{}", v, separator);
    }

    std::println();
}

void naive_views(std::vector<int> &data)
{
    std::ranges::take_view /*<std::ranges::ref_view<std::vector<int>>>*/ a1{data, 3};
    std::ranges::drop_view /*<std::ranges::ref_view<std::vector<int>>>*/ a2{data, 3};

    print(data, "Vector", ",");

    print(a1, "First 3 (take_view)", ",");
    print(a2, "Not the first 3 (drop_view)", ",");

    PairVector numbers{
        {1, "one"},
        {2, "two"},
        {3, "three"},
        {4, "four"},
        {5, "five"},
        {6, "six"},
    };

    std::ranges::keys_view<std::views::all_t<PairVector &>> key_view(numbers);
    std::ranges::values_view<std::views::all_t<PairVector &>> value_view(numbers);
    std::ranges::elements_view<std::views::all_t<PairVector &>, 0> element_view0(numbers);
    std::ranges::elements_view<std::views::all_t<PairVector &>, 1> element_view1(numbers);

    std::println();
    print(key_view, "Keys", ",");
    print(value_view, "Values");

    std::println();
    print(element_view0, "Element 0", ",");
    print(element_view1, "Element 1");
}

int main()
{
    std::vector<int> data(11);

    std::ranges::generate(data, []() { return std::random_device{}() % 100 + 1; });

    naive_views(data);
}
