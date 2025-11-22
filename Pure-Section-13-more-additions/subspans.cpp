#include <iostream>
#include <numeric>
#include <span>
#include <string_view>
#include <vector>

template <typename T, std::size_t size>
void printSpan(std::string_view message, const std::span<T, size> sp, std::size_t max = size)
{
    std::cout << std::format("{:<20} :: [", message);

    for (std::size_t idx = 0; idx < sp.size(); ++idx)
    {
        std::cout << std::format("{}{}", sp[idx], (idx == sp.size() - 1 ? "" : ", "));

        if (idx == max)
        {
            std::cout << "...";
            break;
        }
    }

    std::cout << "]\n";
}

int main()
{
    std::vector<int> v(10);
    std::iota(v.begin(), v.end(), 1);

    std::span s1{v};
    printSpan("s1", s1);

    auto s1_first3 = s1.first(3);
    std::cout << std::endl;
    printSpan("Dynamic First 3", s1_first3);
    printSpan("Static First 3", s1.first<3>());

    auto s1_last5 = s1.last(5);
    std::cout << std::endl;
    printSpan("Dynamic Last 5", s1_last5);
    printSpan("Static Last 5", s1.last<5>());

    auto s1_middle4 = s1.subspan(3, 4);
    std::cout << std::endl;
    printSpan("From 3", s1.subspan(3));
    printSpan("Middle 4", s1_middle4);
    printSpan("Static Middle 4", s1.subspan<3, 4>());
}
