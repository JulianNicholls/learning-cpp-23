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

void task(std::stop_token st)
{
    while (true)
    {
        std::cout << '.' << std::flush;
        std::this_thread::sleep_for(250ms);

        if (st.stop_requested())
        {
            std::cout << "Task Stopped\n";
            return;
        }
    }

    // do_work(5, "Task");
}

int main()
{
    std::jthread thetask(task);
    std::cout << "jthread started\n";

    std::cout << "Press enter to stop the task ";
    std::cin.get();

    thetask.request_stop();

    std::cout << "main finishedi\n";
}
