#include <iostream>

using std::cout, std::endl;

template <int N>
int fibonacci()
{
  return fibonacci<N - 1>() + fibonacci<N - 2>();
}

template <>
int fibonacci<1>()
{
  return 1;
}

template <>
int fibonacci<0>()
{
  return 0;
}

template<int N>
int fibonacci17() {
  if constexpr (N > 1)
    return fibonacci17<N-1>() + fibonacci17<N-2>();

    return N;
}

int main()
{
  constexpr int i{45};

  cout << "fib(" << i << ") = " << fibonacci<i>() << endl;
  cout << "fib17(" << i << ") = " << fibonacci17<i>() << endl;
}
