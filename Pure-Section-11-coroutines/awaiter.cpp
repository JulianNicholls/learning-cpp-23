#include <coroutine>
#include <iostream>

struct Awaiter
{
  bool await_ready()
  {
    std::cout << "  Awaiter::await_ready (no suspend)\n";
//    return false;     // Suspending
    return true;      // Not Suspending
  }

  void await_suspend(std::coroutine_handle<> handle)
  {
    std::cout << "  Awaiter::await_suspend\n";
  }

  void await_resume()
  {
    std::cout << "  Awaiter::await_resume\n";
  }
};

class Task
{
public:
  struct promise_type
  {
    ~promise_type() { }

    auto get_return_object()
    {
      return Task{std::coroutine_handle<promise_type>::from_promise(*this)};
    }

    // Starts suspended
    auto initial_suspend()
    {
      return std::suspend_never{};
    }

    // Ends suspended too
    auto final_suspend() noexcept
    {
      return std::suspend_always{};
    }

    auto unhandled_exception() { }

    void return_void() { }
  };

  Task(const std::coroutine_handle<promise_type> &handle) : handle_(handle) { }

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

private:
  std::coroutine_handle<promise_type> handle_;
};

Task coFunction()
{
  co_await Awaiter{};

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
