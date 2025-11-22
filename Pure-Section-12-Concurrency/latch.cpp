#include <format>
#include <functional>
#include <iostream>
#include <latch>
#include <string>
#include <thread>
#include <vector>

using namespace std::chrono_literals;

void do_work(int duration, const std::string &name)
{
    for (int i = 0; i < duration; ++i)
    {
        std::cout << name << ' ' << std::flush;
        std::this_thread::sleep_for(500ms);
    }
}

void worker(int duration, const std::string &name, std::latch &lt)
{
    std::cout << std::format("{} started  initialisation\n", name);
    do_work(duration, name);
    std::cout << std::format("{} finished initialisation\n", name);

    lt.wait();

    do_work(10, std::format("^{}^", name));
}

int main()
{
    std::vector<std::jthread> threads;
    std::latch lt{4};

    threads.emplace_back(worker, 3, "A", std::ref(lt));
    threads.emplace_back(worker, 7, "B", std::ref(lt));
    threads.emplace_back(worker, 4, "C", std::ref(lt));
    threads.emplace_back(worker, 2, "D", std::ref(lt));

    std::cout << "Press enter to signal threads ";
    std::cin.get();

    lt.count_down(4);
}
