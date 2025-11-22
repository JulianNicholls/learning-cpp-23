#include <coroutine>
#include <iostream>

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

    // Either this or Awaitable::operastor co_await()
    //auto await_transform(int value)
    //{
      //std::cout << "  promise_type::await_transform(" << value << ")\n";
      //return std::suspend_always{};
    //}

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

struct Awaitable
{
  auto operator co_await() {
    std::cout << "  Awaitable::co_await\n";
    return std::suspend_always{};
  }
};

Task coFunction()
{
  co_await Awaitable{};

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
