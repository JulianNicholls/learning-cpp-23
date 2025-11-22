#include <chrono>
#include <iostream>
#include <vector>

using namespace std::chrono;
using namespace std::chrono_literals;

using std::cout, std::endl;

long fibonacci(unsigned long n)
{
  static std::vector<unsigned long> cache{1, 1};

  if(cache.size() > n) return cache[n];

  cache[n] = fibonacci(n - 1) + fibonacci(n - 2);

  return cache[n];
}

const unsigned long limit = 40;

int main()
{
  auto start = steady_clock::now();
  unsigned long n = fibonacci(limit);
  auto finish = steady_clock::now();
  auto elapsed = duration_cast<milliseconds>(finish - start).count();

  cout << "Fibonacci(" << limit << ") = " << n << endl;
  cout << "Time taken: " << elapsed << "ms\n";

  start = steady_clock::now();
  n = fibonacci(limit + 5);
  finish = steady_clock::now();
  elapsed = duration_cast<milliseconds>(finish - start).count();

  cout << "Fibonacci(" << limit + 5 << ") = " << n << endl;
  cout << "Time taken: " << elapsed << "ms\n";
}
