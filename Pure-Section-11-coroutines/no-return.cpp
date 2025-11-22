#include <coroutine>
#include <iostream>

class Task
{
public:
  struct promise_type
  {
    promise_type()
    { // The supplied default suffices actually since there are no data members
      std::cout << "  promise_type::constructor()\n";
    }

    ~promise_type()
    {
      std::cout << "  promise_type::~promise_type()\n";
    }

    auto get_return_object()
    {
      std::cout << "  promise_type::get_return_object()\n";
      return Task{std::coroutine_handle<promise_type>::from_promise(*this)};
    }

    // Starts suspended
    auto initial_suspend()
    {
      std::cout << "  promise_type::initial_suspend()\n";
      return std::suspend_always{};
    }

    // Ends suspended too
    auto final_suspend() noexcept
    {
      std::cout << "  promise_type::final_suspend()\n";
      return std::suspend_always{};
    }

    auto unhandled_exception()
    {
      std::cout << "  promise_type::unhandled_exception()\n";
    }

    void return_void()
    {
      std::cout << "  promise_type::return_void()\n";
    }
  };

  Task(const std::coroutine_handle<promise_type> &handle) : handle_(handle)
  {
    std::cout << "  Task::constructor()\n";
  }

  ~Task()
  {
    std::cout << "  Task::~Task()\n";
    if (handle_)
      handle_.destroy();
  }

  void resume()
  {
    handle_.resume();
  }

  bool done()
  {
    return handle_.done();
  }

private:
  std::coroutine_handle<promise_type> handle_;
};

Task coFunction()
{
  std::cout << " coFunction - Started\n";

  std::cout << " coFunction - co_awaiting\n";
  co_await std::suspend_always{};

  std::cout << " coFunction - resuming\n";

  std::cout << " coFunction - Returning\n";
  co_return;
}

int main()
{
  std::cout << "main - Calling coFunction\n";
  auto task = coFunction();

  while (!task.done())
  {
    std::cout << "\nmain - Resuming coFunction\n";
    task.resume();
  }

  std::cout << "\nmain - coFunction is done\n";
}
