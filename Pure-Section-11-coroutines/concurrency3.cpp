#include <coroutine>
#include <format>
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
      throw std::logic_error(
          std::format("Cannot open {} for reading", filename));
    }
  }

  std::string read_bytes() const { return handle_.promise().output_; }

private:
  std::coroutine_handle<promise_type> handle_;
};

struct FileAwaiter {
  bool await_ready() { return false; }

  void await_suspend(std::coroutine_handle<Task::promise_type> handle) {
    using namespace std::chrono_literals;

    std::this_thread::sleep_for(200ms);

    // It was surprisingly difficult to get neither the last read text twice
    // or not at all!

    // eof() only becomes true when no bytes have been read because we're
    // ALREADY at the end of file. 
    // It does not trigger when the last byte has been read.
    if (handle.promise().input_.eof()) {
      next_available = false;
      handle.promise().output_ = "";

      return;
    }

    std::string buffer{};
    buffer.resize(bytes);

    handle.promise().input_.read(buffer.data(), bytes);
    handle.promise().output_ = buffer;

    next_available = true;
  }

  bool await_resume() { return next_available; }

  std::size_t bytes;
  bool next_available{};
};

Task fileData() {
  std::cout << "\n    fileData - Acquiring Data\n";
  bool available = true;

  while (available) {
    available = co_await FileAwaiter{16};
  }

  std::cout << "    fileData - Complete\n";
  co_return;
}

int main() {
  std::cout << "main - Starting fileData\n";
  auto task = fileData();

  task.open_file("pangrams.txt");

  while (!task.done()) {
    task.resume();
    std::cout << std::format("TEXT:{:>55}\n", task.read_bytes());
    std::cout << "[main running]\n";
  }

  std::cout << "\nmain - fileData is done\n";
}
