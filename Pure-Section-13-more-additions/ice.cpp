#include <print>

#include <type_traits>

const char *getstring()
{
    if (std::is_constant_evaluated())
        return "Compile time call";

    return "Runtime call";
}

consteval const char *getstringcev()
{
    if (std::is_constant_evaluated())
        return "Compile time call";

    return "Runtime call";
}

constexpr const char *getstringcex()
{
    if (std::is_constant_evaluated())
        return "Compile time call";

    return "Runtime call";
}

// This is interesting, but I'm not sure if I understand the use for it.
// The example at https://en.cppreference.com/w/cpp/types/is_constant_evaluated.html
// is more useful.

int main()
{
    std::println("getstring:    {}", getstring());
    std::println("getstringcev: {}", getstringcev());

    constexpr auto s1 = getstringcex();

    std::println("getstringcex: {}", getstringcex());
    std::println("  via s1:     {}", s1);
}
