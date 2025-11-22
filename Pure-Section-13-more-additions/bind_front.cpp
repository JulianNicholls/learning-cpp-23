#include <functional>
#include <print>
#include <ranges>
#include <vector>

class Handler
{
  public:
    void update(int id)
    {
        std::println("Update: {}", id);
    }
};

int main()
{
    std::vector v{2, 8, 3, 4, 2, 5, 7};

    // These three lines are equivalent
    //    auto it = std::ranges::find_if(v, [](int i) { return i != 2; });
    //    auto it = std::ranges::find_if(v, std::bind(std::not_equal_to<int>{}, 2, std::placeholders::_1));
    auto it = std::ranges::find_if(v, std::bind_front(std::not_equal_to<int>{}, 2));

    if (it != v.end())
        std::println("Found {}", *it);

    Handler h{};

    auto u_h1 = std::bind_front(&Handler::update, h);
    u_h1(100);

    auto u_h2 = std::bind_front(&Handler::update, h, 120);
    u_h2();
}
