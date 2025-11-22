#include <algorithm>
#include <array>
#include <deque>
#include <forward_list>
#include <iostream>
#include <list>
#include <ranges>
#include <set>
#include <string_view>
#include <unordered_set>
#include <vector>

template <typename Range>
void print(const Range &range, std::string_view message = "", std::size_t max = 10)
{
    std::cout << std::format("{:<20} :: [", message);

    using it_cat = typename std::iterator_traits<typename Range::iterator>::iterator_category;
    std::size_t max_size{};

    if constexpr (std::is_same_v<it_cat, std::forward_iterator_tag>)
    {
        max_size = std::distance(range.begin(), range.end()) - 1;
    }
    else
    {
        max_size = range.size() - 1;
    }

    std::size_t i{};

    for (const auto &e : range)
    {
        std::cout << std::format("{}{}", e, (i == max_size ? "" : ", "));

        if (i == max)
        {
            std::cout << "...";
            break;
        }

        ++i;
    }

    std::cout << "]\n";
}

int main()
{
    std::array arr{1, 2, 3, 2, 2, 4, 2, 7, 2, 9};

    std::vector<int> vec{std::begin(arr), std::end(arr)};
    print(vec, "vector");
    //    auto new_end = std::ranges::remove(vec, 2);
    //    vec.erase(new_end.begin(), new_end.end());
    std::erase(vec, 2);
    print(vec, "vector erased");

    std::list<int> list{std::begin(arr), std::end(arr)};
    print(list, "list");
    //    list.remove(2);
    std::erase(list, 2);
    print(list, "list erased");

    std::forward_list<int> f_list{std::begin(arr), std::end(arr)};
    print(f_list, "f_list");
    //    f_list.remove(2);
    std::erase(f_list, 2);
    print(f_list, "f_list erased");

    std::deque<int> dq{std::begin(arr), std::end(arr)};
    print(dq, "deque");
    //    auto deque_end = std::ranges::remove(dq, 2);
    //    dq.erase(deque_end.begin(), deque_end.end());
    std::erase(dq, 2);
    print(dq, "deque erased");

    std::set<int> st{std::begin(arr), std::end(arr)};
    print(st, "set");
    st.erase(2); // std::erase not necessary or valid for sets
    print(st, "set erased");

    std::multiset<int> ms{std::begin(arr), std::end(arr)};
    print(ms, "multiset");
    ms.erase(2);
    print(ms, "multiset erased");

    std::unordered_set<int> us{std::begin(arr), std::end(arr)};
    print(us, "unordered_set");
    us.erase(2); // std::erase not necessary or valid for unordered_sets
    print(us, "unordered_set erased");

    std::unordered_multiset<int> ums{std::begin(arr), std::end(arr)};
    print(ums, "unordered_multiset");
    // ums.erase(2); // std::erase not necessary or valid for sets
    std::erase_if(ums, [](const auto &item) { return item < 3; });
    print(ums, "um <3 erased");
}
