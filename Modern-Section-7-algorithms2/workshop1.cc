// Using algorithm calls to process vectors of numbers
#include <iostream>
#include <random>
#include <algorithm>
#include <vector>
#include <fstream>
#include <iterator>

using namespace std;

static std::mt19937 mt;                            // Unseeded (for testing)
// static std::random_device rd;
// static std::mt19937 mt(rd());                   // Seeded

namespace exercises {
    int get() {
	    std::uniform_int_distribution<int> ud(0, 1000);
	    return ud(mt);
	}
}

template <class T>
void print(const vector<T>& vec) {
	ostream_iterator<T> oi(cout, ",");
	copy(cbegin(vec), cend(vec), oi);
	cout << endl;
}

int main() {
	// 1. Fill a vector with 10 random integers between 0 and 1000
	std::vector<int> vec(10);
    std::generate_n(begin(vec), 10, exercises::get);

	cout << "Vector elements: " << endl;
	
	// 2. Display the vector elements on the screen
    print(vec);
	
	// 3. Find the maximum element in the vector
	auto maxit = std::max_element(cbegin(vec), cend(vec));
    
	// We will need the value for question 7
	int maxval = *maxit;
	
	cout << endl << "Maximum element in vector is " << maxval << endl;
	
	// 4. Find the index of this element
	cout << "The index of this maximum element is " << distance(cbegin(vec), maxit) << endl;
	
	// 5. Sum the elements of the vector
	cout << "The sum of the elements of the vector is " << accumulate(cbegin(vec), cend(vec), 0) << endl;

	// 6. Count the number of odd numbers in the original vector
	int n = std::count_if(cbegin(vec), cend(vec), [] (int i) { return i%2;});
    std::cout << "The original vector contains " << n << " odd elements\n" << endl;
	
	// 7. Normalize the vector (divide all the elements by the largest)
	// and put the results into a vector of doubles,
	// without setting the size of the output vector first
	vector<double> norm;
	std::transform(cbegin(vec), cend(vec), back_inserter(norm),
                                     [maxval] (int i) { return (double)i/maxval;}
					);
 
	std::cout << "\nNormalized version of the vector: ";
    print(norm);	

	
	// 8. Make a sorted copy of the vector.
	// Without using a functor or a lambda (or equivalent),
	// find the first element greater than 455
	vector<int> scratch;
	copy(cbegin(vec), cend(vec), back_inserter(scratch));
	sort(begin(scratch), end(scratch));
    auto it = std::upper_bound(cbegin(scratch), cend(scratch), 455);
	cout << endl << "The first element greater than 455 is " << *it << endl;
	// and the number of elements > 455
    std::cout << "Vector contains " << distance(it, cend(scratch)) << " elements greater than 455\n";
	
	// 9. Copy all the odd numbers to a vector of doubles,
	// without setting the size of the output vector first
	vector<double> odds;
    std::copy_if(cbegin(vec), cend(vec), back_inserter(odds),
                                    [] (int i) { return i%2; }
				);
    cout << endl << "Vector of odd elements: " << endl;
	print(odds);
	
	// 10. Sort the vector in descending order
	std::sort(begin(vec), end(vec), [] (int l, int r) { return r < l; } );
	std::cout << "\nSorted vector: ";
	print(vec);
	cout << endl;
	
	// 11. Randomly shuffle all but the first and the last element of the vector
	shuffle(next(begin(vec)), prev(end(vec)), mt);
	cout << "Shuffled vector:" << endl;
	print(vec);
	
	// 12. Remove all the odd numbers from the vector
	auto last = std::remove_if(begin(vec), end(vec),
                                                   [] (int i) { return i%2; });
	vec.erase(last, end(vec));
	std::cout << "\nVector after removing odd elements" << endl;
	print(vec);
	
	// 13. Write the remaining elements to a text file on a single line
	// as a comma separated list, without a trailing comma
	std::ofstream ofile("test.txt");

	// Make sure there is at least one element in vec before we iterate over it
	if (ofile && cbegin(vec) != cend(vec)) {
		std::ostream_iterator<int> out(ofile, ",");
		std::copy(cbegin(vec), prev(cend(vec)), out);
		std::ostream_iterator<int> out2(ofile);
		std::copy(prev(cend(vec)), cend(vec), out2);
	}
}