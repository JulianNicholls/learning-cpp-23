#include <iomanip>
#include <iostream>
#include <numeric>
#include <string>
#include <random>
#include <vector>

void print(const std::vector<int> &v)
{
  for (int i : v)
  {
    std::cout << i << ", ";
  }

  std::cout << std::endl;
}

void show_iota_and_sum()
{
  std::vector<int> vec(10);

  std::cout << "\niota and sums\n";

  iota(vec.begin(), vec.end(), 95);
  print(vec);

  // accumulate is a sequential operation
  auto sum = std::accumulate(vec.cbegin(), vec.cend(), 0);
  std::cout << "Sum of vec = " << sum << std::endl;

  auto odd_sum = std::accumulate(vec.cbegin(), vec.cend(), 0, [](int sum, int n)
                                 { return (n % 2 == 1) ? sum + n : sum; });
  std::cout << "Sum of odd members in vec = " << odd_sum << std::endl;

  // C++17 intrduces reduce, which is parallelisable
  auto rsum = std::reduce(vec.cbegin(), vec.cend(), 0);
  std::cout << "Sum of vec via reduce = " << rsum << std::endl;
}

void show_write_only()
{
  std::vector<int> vec(10);

  std::cout << "\nwrite only\n";

  std::fill(vec.begin(), vec.end(), 95);
  print(vec);

  auto rest = std::fill_n(vec.begin(), 5, 42);
  std::fill_n(rest, 3, 34);
  print(vec);

  // Add to the vector
  std::fill_n(std::back_inserter(vec), 5, 55);
  print(vec);

  std::generate(vec.begin(), vec.end(), [x = 0]() mutable
                { ++x; return x * x; });
  print(vec);
}

void show_for_each()
{
  // for_each is actual INFerior to a simple range loop these days, if accessing the whole range
  // It is essentially a hangover from C++98, but may be useful for a subset of a range

  std::cout << "\nfor_each\n";

  std::vector<int> vec(20);

  std::generate(vec.begin(), vec.end(), [x = 0]() mutable
                { ++x; return x * x; });

  std::for_each(vec.cbegin(), vec.cend(), [](int x)
                { std::cout << x << ", "; });

  std::cout << std::endl;
}

void show_copying()
{
  std::vector<int> vec(10);
  std::vector<int> vec2(10);
  std::vector<int> empty;

  std::cout << "\ncopying\n";

  iota(vec.begin(), vec.end(), 1);

  std::copy(vec.cbegin(), vec.cend(), vec2.begin());

  std::copy(vec.cbegin(), vec.cend(), std::back_inserter(empty));
  std::copy(vec.cbegin(), vec.cend(), std::back_inserter(empty));
  std::copy_n(vec.cbegin() + 4, 5, std::back_inserter(empty));

  print(vec);
  print(vec2);
  print(empty); // No longer

  empty.clear();
  std::copy_if(vec.cbegin(), vec.cend(), std::back_inserter(empty), [](int n)
               { return n % 2 == 0; });
  print(empty); // No longer
}

void show_partials()
{
  std::vector<int> vec(20);
  std::vector<int> sums;
  std::vector<int> diffs;
  std::vector<int> products;

  std::cout << "\nPartials\n";

  iota(vec.begin(), vec.end(), 1);
  print(vec);

  partial_sum(std::cbegin(vec), std::cend(vec), std::back_inserter(sums));
  std::cout << "Sums:  ";
  print(sums);

  adjacent_difference(sums.cbegin(), sums.cend(), std::back_inserter(diffs));
  std::cout << "Diffs: ";
  print(diffs);

  // inner_product = a1*b1 + a2*b2 ...
  auto result = std::inner_product(vec.cbegin(), vec.cend(), sums.cbegin(), 0);
  std::cout << "Product: " << result << std::endl;

  // Overloaded inner_product
  std::vector<float> measured;
  std::vector<float> expected;

  // Convert to float vectors, measured with an error
  srand(time(0));

  std::transform(vec.cbegin(), vec.cend(), std::back_inserter(measured), [](int n)
                 { return static_cast<float>(n + 0.5 - (1.0 * rand() / RAND_MAX)); });
  std::transform(vec.cbegin(), vec.cend(), std::back_inserter(expected), [](int n)
                 { return static_cast<float>(n); });

  auto max_diff = std::inner_product(
    measured.cbegin(), measured.cend(), expected.cbegin(), 0.0,
    [](float a, float b) { return std::max(a, b); },    // Second operation
    [](auto a, auto b)   { return std::fabs(a - b); }); // First operation

  std::cout << "max diff: " << max_diff << std::endl;

  // C++ 17 has std::transform_reduce which allows for parallelisation.
}

void show_randoms()
{
  std::cout << "\nRandoms\n  Old Style\n  RAND_MAX: " << RAND_MAX << "\n\n";

// Old-style, raw rand(), 0.0..1.0, 1..100

  for(int i = 0; i < 10; ++i) {
    std::cout << std::setw(12) << rand() << "  "
              << std::setw(10) << std::left << 1.0 * rand() / RAND_MAX
              << std::setw(5) << std::right << std::round(99.0 * rand() / RAND_MAX + 1)
              << std::endl;
  }

  // New-style

  std::cout << "\n  New Style\n";

  std::random_device  seeder;   // External source of entropy, at least in theory
  std::default_random_engine dre(seeder());
  std::mt19937 mt(seeder());      // Use this, preferably
  std::uniform_int_distribution<int> eng_uniform(1, 100);

  for (int i = 0; i < 10; ++i)
  {
    std::cout << std::setw(12) << dre()
              << std::setw(12) << mt()
              << std::setw(5) << eng_uniform(mt)
              << std::endl;
  }

  std::cout << "\nShuffle\n";
  std::vector<int> vec{2, 6, 5, 3, 10, 8, 11, 12, 19, 14, 15, 16, 16, 17};

  std::shuffle(vec.begin(), vec.end(), mt);
  print(vec);
  std::shuffle(vec.begin(), vec.end(), mt);
  print(vec);
  std::shuffle(vec.begin(), vec.end(), mt);
  print(vec);
}

int main()
{
  show_iota_and_sum();
  show_write_only();
  show_for_each();
  show_copying();
  show_partials();
  show_randoms();

  std::cout << std::endl;
  return 0;
}
