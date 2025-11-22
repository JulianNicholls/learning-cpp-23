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
        std::print("{}{}", v, separator);
    }

    std::println();
}

namespace Join
{
void run()
{
    std::vector<std::string> words{"C++ ", "is ", "a ", "general ", "purpose ", "programming ", "language."};

    // Flattened is a correct name, it certainly doesn't join.
    auto flattened = std::views::join(words);

    print(words, "Words");
    print(flattened, "Flattened", "");

    std::println();
}
};

namespace Split
{
void run()
{
    std::string line{"C++ is a general-purpose programming language."};

    auto split = std::views::split(line, std::string{" "});
    std::vector<std::string> words{};

    for (const auto &inner_range : split)
    {
        std::string word{};

        for (auto ch : inner_range)
        {
            word.push_back(ch);
        }

        words.push_back(word);
    }

    print(words, "words from line", ", ");

    std::println();
}
};

namespace Split23
{
void run()
{
    std::string line{"C++ is a general-purpose programming language."};

    auto split = std::views::split(line, std::string{" "});
    std::vector<std::string> words{};

    for (const auto &inner_range : split)
    {
        std::string_view word{inner_range};

        words.emplace_back(word);
    }

    print(words, "23: words from line", ", ");

    std::println();
}
};

namespace Filter
{
void run()
{
    std::vector<int> data(11);

    std::ranges::generate(data, []() { return std::random_device{}() % 100; });

    print(data, "data", ",");

    auto filtered = std::views::filter(data, [](const auto v) { return v > 50; });

    print(filtered, "filtered > 50", ",");

    std::println();
}
}

namespace TakeWhile
{
void run()
{
    std::string text{"C++ Language,Bjarne Stroustrup"};

    auto view = std::views::take_while(text, [](char ch) { return ch != ','; });

    print(view, "take_while", "");

    std::println();
}
}

namespace DropWhile
{
void run()
{
    std::string text{"    C++ Language,Bjarne Stroustrup"};

    auto view = std::views::drop_while(text, [](char ch) { return ch == ' '; });

    print(view, "drop_while", "");

    std::println();
}
}

namespace Transform
{
void run()
{
    std::string text{"C++ Language,Bjarne Stroustrup"};

    auto upper = std::views::transform(text, [](char ch) { return static_cast<char>(toupper(ch)); });

    print(upper, "transform", "");

    std::println();
}
}

int main()
{
    Join::run();
    Split::run();
    Split23::run();
    Filter::run();
    TakeWhile::run();
    DropWhile::run();
    Transform::run();
}
