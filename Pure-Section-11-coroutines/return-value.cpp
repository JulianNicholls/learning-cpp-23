#include <coroutine>
#include <iostream>

class Task
{
public:
  struct promise_type
  {
    auto get_return_object()
    {
      return Task{std::coroutine_handle<promise_type>::from_promise(*this)};
    }

    // Starts suspended
    auto initial_suspend()
    {
      return std::suspend_always{};
    }

    // Ends suspended too
    auto final_suspend() noexcept
    {
      return std::suspend_always{};
    }

    auto unhandled_exception() {}

    void return_value(int value)
    {
      std::cout << "  promise_type::return_value()\n";

      ret_value = value;
    }

    int ret_value{};
  };

  Task(const std::coroutine_handle<promise_type> &handle) : handle_(handle) {}

  ~Task()
  {
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

  int get_value() const
  {
    return handle_.promise().ret_value;
  }

private:
  std::coroutine_handle<promise_type> handle_;
};

Task coAdd(int x, int y)
{
  co_await std::suspend_always{};
  co_return (x + y);
}

int main()
{
  std::cout << "main - Calling coAdd\n";
  auto task = coAdd(3543, 45432543);

  while (!task.done())
  {
    std::cout << "\nmain - Resuming coAdd\n";
    task.resume();
  }

  std::cout << "\nmain - coAdd is done\n";
  std::cout << "Result is " << task.get_value() << "\n";
}
