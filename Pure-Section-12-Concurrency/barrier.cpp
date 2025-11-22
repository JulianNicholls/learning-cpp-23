#include <barrier>
#include <format>
#include <functional>
#include <iostream>
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

constexpr int PHASES = 3;

void worker(int duration, const std::string &name, std::barrier<void (*)() noexcept> &barrier)
{
    for (int i = 0; i < PHASES; ++i)
    {
        std::cout << std::format("{} started  phase #{}\n", name, i + 1);
        do_work(duration, name);
        std::cout << std::format("{} finished phase #{}\n", name, i + 1);

        barrier.arrive_and_wait();
    }

    std::cout << std::format("{} complete\n", name);
}

void onPhaseComplete() noexcept
{
    static int phase = 1;

    std::cout << std::format("\n:: Phase {} finished ::\n\n", phase++);
}

int main()
{
    std::vector<std::jthread> threads;
    std::barrier<void (*)() noexcept> barrier{4, onPhaseComplete}; // The callback is optional

    std::cout << "Threads will run each phase and then wait for each other\n\n";

    threads.emplace_back(worker, 3, "A", std::ref(barrier));
    threads.emplace_back(worker, 7, "B", std::ref(barrier));
    threads.emplace_back(worker, 4, "C", std::ref(barrier));
    threads.emplace_back(worker, 2, "D", std::ref(barrier));

    for (auto &t : threads)
    {
        t.join();
    }
}
