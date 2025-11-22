#include <print>
#include <vector>

// ssize returns the size of a container as a signed value.
// AFAICS it only really becomes important when the value is changed afterward, e.g. ssize(container) -1
// That would fail with an empty container and container.size().

int main()
{
    std::vector nums{1, 5, 9, 3};

    for (int i = 0; i <= std::ssize(nums) - 1; ++i)
    {
        std::print("{} ", nums[i]);
    }
}
