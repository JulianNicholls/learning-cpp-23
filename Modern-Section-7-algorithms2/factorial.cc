// Yet another way to calculate a factorial
#include <iostream>
#include <numeric>
#include <vector>

using namespace std;

int main() {
	// 19. Calculate the factorial of 6 (6 x 5 x 4 ... x 1)
	vector<int> numbers(6);
	iota(numbers.begin(), numbers.end(), 1);
	cout << "The factorial of 6 is " << accumulate(numbers.begin(), numbers.end(), 1,
											[] (int a, int b) { return a*b; }
	);
}