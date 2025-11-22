#include <iostream>
#include <string>
#include <thread>

using namespace std::chrono_literals;

void do_work(int duration, const std::string &name)
{
    for (int i = 0; i < duration; ++i)
    {
        std::cout << name << ' ' << std::flush;
        std::this_thread::sleep_for(500ms);
    }
}

void task()
{
    do_work(5, "Task");
}

int main()
{
    std::thread thetask{task};

    std::cout << "Thread started\n";
    thetask.join(); // Await completion

    // Hooray, the latest Clang has jthread

    std::jthread thecpp20task(task);
    std::cout << "\nC++20 Thread started\n";

    std::cout << std::endl;
}
