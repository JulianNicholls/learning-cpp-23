#include <coroutine>
#include <iostream>

class Generator
{
public:
  struct promise_type
  {
    auto get_return_object()
    {
      return Generator{std::coroutine_handle<promise_type>::from_promise(*this)};
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

    auto yield_value(int value)
    {
      std::cout << "  promise_type::yield_value()\n";

      y_value = value;

      return std::suspend_always{};
    }

    int y_value{};
  };

  Generator(const std::coroutine_handle<promise_type> &handle) : handle_(handle) {}

  ~Generator()
  {
    if (handle_)
      handle_.destroy();
  }

  void resume()
  {
    handle_.resume();
  }

  bool done() const
  {
    return handle_.done();
  }

  int get_value() const
  {
    return handle_.promise().y_value;
  }

private:
  std::coroutine_handle<promise_type> handle_;
};

Generator coFunction()
{
  co_yield 42;

  co_yield 69;

  co_yield 314;
}

Generator coGenerate(int begin, int end, int step = 1)
{
  for(int idx = begin; idx <= end; idx += step) {
    co_yield idx;
  }
}

int main()
{
  std::cout << "main - Calling coFunction\n";
  auto task = coGenerate(1, 10);

  while (!task.done())
  {
    std::cout << "\nmain - Resuming coGenerator\n";
    task.resume();
    std::cout << "Value: " << task.get_value() << "\n";
  }

  std::cout << "\nmain - coGenerator is done\n";
}
