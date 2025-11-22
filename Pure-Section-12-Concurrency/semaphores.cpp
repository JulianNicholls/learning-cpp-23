#include <barrier>
#include <format>
#include <functional>
#include <iostream>
#include <semaphore>
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

// std::counting_semaphore sem{3};     // Allow three threads to access the 'DB' at a time.
std::binary_semaphore sem{1}; // Allow only one thread to access the 'DB' at a time.

void worker(int duration, const std::string &name)
{
    sem.acquire();
    std::cout << std::format("{} opened a connection\n", name);
    do_work(duration, name);
    std::cout << std::format("{} closed a connection\n", name);
    sem.release();

    std::cout << std::format("{} complete\n", name);
}

int main()
{
    std::vector<std::jthread> threads;

    //    std::cout << "Only 3 threads will execute at a time\n\n";
    std::cout << "Only 1 thread will execute at a time\n\n";

    threads.emplace_back(worker, 3, "A");
    threads.emplace_back(worker, 7, "B");
    threads.emplace_back(worker, 4, "C");
    threads.emplace_back(worker, 2, "D");
    threads.emplace_back(worker, 5, "E");
    threads.emplace_back(worker, 6, "F");

    for (auto &t : threads)
    {
        t.join();
    }

    std::cout << "All threads are complete.\n";
}
