#include <coroutine>
#include <fstream>
#include <iostream>
#include <thread>

class Task {
public:
  struct promise_type {
    Task get_return_object() {
      return {std::coroutine_handle<promise_type>::from_promise(*this)};
    }

    // Starts suspended
    auto initial_suspend() { return std::suspend_always{}; }

    // Ends suspended too
    auto final_suspend() noexcept { return std::suspend_always{}; }

    auto unhandled_exception() {}

    void return_void() { std::cout << "  promise_type::return_void()\n"; }

    auto await_transform(std::size_t bytes) {
      using namespace std::chrono_literals;

      output_.resize(bytes);
      std::this_thread::sleep_for(500ms);
      input_.read(output_.data(), bytes);
      return std::suspend_always{};
    }

    std::ifstream input_;
    std::string output_{};
  };

  Task(const std::coroutine_handle<promise_type> &handle) : handle_(handle) {}

  ~Task() {
    if (handle_)
      handle_.destroy();
  }

  void resume() { handle_.resume(); }

  bool done() { return handle_.done(); }

  void open_file(const std::string &filename) {
    handle_.promise().input_.open(filename);

    if (!handle_.promise().input_) {
      throw std::logic_error("Cannot open file");
    }
  }

  std::string read_bytes() const { return handle_.promise().output_; }

private:
  std::coroutine_handle<promise_type> handle_;
};

Task fileData() {
  std::cout << "\n    fileData - Acquiring Data\n";

  co_await 18;
  co_await 24;
  co_await 35;
  co_await 19;

  std::cout << "    fileData - Complete\n";
  co_return;
}

int main() {
  std::cout << "main - Starting fileData\n";
  auto task = fileData();

  task.open_file("pangrams.txt");

  while(!task.done()) {
    task.resume();
    std::cout << task.read_bytes() << '\n';
    std::cout << "[main running]\n";
  }

  std::cout << "\nmain - fileData is done\n";
}
