#include <format>
#include <iostream>
#include <numbers>
#include <print>
#include <string>
#include <vector>

using std::cout, std::endl;
using std::format;
using std::print, std::println;
using std::string;

// template <typename... Args>
// void println(std::format_string<Args...> fmt, Args &&...args)
// {
//   cout << format(fmt, std::forward<Args>(args)...) << endl;
// };

struct Employee
{
    int id;
    string name;
    string language;
};

void simple()
{
    cout << format("{}, {}\n", 1, 2);
    cout << format("{1}, {0}\n", 1, 2);
    cout << format("{0} + {0} = {1}\n", 1, 2);     // Perfectly legal to specify the same one multiple times
    cout << format("{0} + {0} = {{{1}}}\n", 1, 2); // Double curlies escapes curlies

    // cout << format("{2}, {0}\n", 1, 2);  // Index out of range = compile error
    // cout << format("{}, {0}\n", 1, 2);   // Indices not all specified = compile error
}

void actual_formatting()
{
    // { index: fill align sign # 0 width .precision L type }

    char c('A');
    std::string s{"String"};

    println("\n{0:d} {0:#x} {0:X} {0:#o} {0:#b} {0:c}", 63);
    println("{0:f} {0:g} {0:e} {0:a}", 163.3344556); // f = fixed 6dp, g = general 6sf, e = exponential, a = hex
    println("{:c}", c);
    println("{:s}", s);
    println("{0:p}", static_cast<void *>(&s));

    println("\n|{:<8}|", "Four"); // Left   alignment
    println("|{:>8}|", "Four");   // Right  alignment
    println("|{:*^8}|", "Four");  // Centre alignment

    println("\n|{:<10}|", 123.4567);
    println("|{:>10}|", 123.4567);
    println("|{:=>10}|", 123.4567); // Fill character must have an alignment too

    // sign = -   (default) positive nothing, negative -
    // sign = +   positive +, negative -
    // sign = ' ' positive ' ', negative -

    println("\n|{0:*>5}| |{0:*>-5}| |{0:*>+5}| |{0:*> 5}|", 123);
    println("|{:>-5}|", -123);

    // Leading 0s

    println("\n{:#010x}", 123);
    println("{:#010o}", 123);
    println("{:#010b}", 123);
    println("{:#010d}", 123);
    println("{0:#0{1}d}\n", 123, 5); // Specify width with another field

    // Precision

    println("{}", std::numbers::pi);   // Default is full precision
    println("{:f}", std::numbers::pi); // Specifying f sets 6dp
    println("{:.8f}", std::numbers::pi);
    println("|{:10.4f}|", std::numbers::pi); // .4 is 4dp

    println("{:.5}\n", "Two Words");
}

void user_struct()
{
    const std::vector<Employee> emps{
        {100, "Bjarne", "C++"},
        {200, "James", "Java"},
        {50, "Anders", "C#"},
        {250, "Dennis", "C"},
        {145, "Guido", "Python"}};

    for (const auto &emp : emps)
    {
        println("{0:>4}  {1:<10}  {2:^8}", emp.id, emp.name, emp.language);
    }
}

void locales()
{
    println("\nLocale: {:11} :: {:L}", std::locale().name(), 1'000'000.25);

    std::locale::global(std::locale("en_GB.UTF-8"));
    println("Locale: {:11} :: {:L}", std::locale().name(), 1'000'000.25);

    std::locale::global(std::locale("en_IN.UTF-8"));
    println("Locale: {:11} :: {:L}", std::locale().name(), 1'000'000.25);

    std::locale::global(std::locale("de_DE.UTF-8"));
    println("Locale: {:11} :: {:L}", std::locale().name(), 1'000'000.25);
}

int main()
{
    simple();
    actual_formatting();
    user_struct();
    locales();
}
