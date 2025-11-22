#include <array>
#include <iostream>
#include <span>
#include <vector>

template <typename T, std::size_t size>
void printSpan(const std::span<T, size> sp, std::size_t max = size)
{
    std::cout << "[";

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

void static_extent()
{
    int a[]{1, 2, 3, 4, 5};
    std::array arr{6, 7, 8, 9, 10};
    std::vector vec{11, 12, 14, 15, 16};

    std::span s1{a};   // Implicitly span<int, 5>
    std::span s2{arr}; // Implicitly span<int, 5>
    std::span<int, 5> s3{vec};
    std::span<int, 3> s4{vec.data(), 3};

    s2 = s1; // OK
    // s1 = s4;		// Not OK, different sizes

    a[0] = 100; // Spans have reference semantics, we're showing the live state
    // std::cout << std::format("s1[0] = {}\n", s1[0]);

    std::span<const int, 5> s6{arr};
    // s6[1] = 100;	// Not OK, span is const

    std::cout << "Static\n\n";
    printSpan(s1);
    printSpan(s2);
    printSpan(s3);
    printSpan(s4);
    printSpan(s6);
}

void dynamic_extent()
{
    int a[]{1, 2, 3, 4, 5};
    std::array arr{6, 7, 8, 9, 10};
    std::vector vec{11, 12, 14, 15, 16};

    std::span<int> s1{a}; // Dynamically sized
    std::span<int> s2{arr};
    std::span<int> s3{a, 3};

    std::span s5{std::data(a), 3};
    std::span s6{std::data(a) + 2, 3};

    std::span s7{std::data(arr), 3};
    std::span s8{std::data(arr) + 2, 3};

    std::span s9{std::data(vec), 3};
    std::span s10{std::data(vec) + 2, 3};

    std::cout << "\nDynamic\n\n";
    printSpan(s1);
    printSpan(s2);
    printSpan(s3);
    printSpan(s5);
    printSpan(s6);
    printSpan(s7);
    printSpan(s8);
    printSpan(s9);
    printSpan(s10);

    s2 = s3; // Fine because they're dynamic
}

void bad_stuff()
{
    std::vector<std::string> languages{"C++", "Ruby", "C", "Python", "BASIC", "JavaScript"};
    std::span oops{languages};

    std::cout << "\nPossibly bad\n";
    printSpan(oops); // This will be fine

    // Because we update languages here, oops is not necessarily still valid
    languages.push_back("Algol 68");

    printSpan(oops); // This is undefined behaviour, cue the demons!
}

int main()
{
    static_extent();
    dynamic_extent();

    bad_stuff();
}
