// Finding unique words in a text file
#include <iostream>
#include <iterator>
#include <algorithm>
#include <vector>
#include <fstream>
#include <string>
#include <cctype>

using namespace std;

// Return a copy of the argument string
// with non-alphabetical characters removed, converted to lower case
string normalize(const string& s) {
	string retval{""};
	
	copy_if(cbegin(s), cend(s), back_inserter(retval),
				[](char c) { return isalpha(c); }
	);
	transform(begin(retval), begin(retval), begin(retval), 
				[] (char c) { return tolower(c); }
	);

	return retval;
}

int main() {
	// Read a file of words
	std::ifstream wif{"words.txt"};

    if (wif) {
        istream_iterator<string> iit{wif};
        istream_iterator<string> eof;
		vector<string> in_words{iit, eof};
		
		// 14. Display each word once
		// Ignore space characters, punctuation and capitalization
		vector<string> words;

		// Normalize the string and sort it
		transform(cbegin(in_words), cend(in_words), back_inserter(words), normalize);
		sort(begin(words), end(words));
		
		// Remove duplicates
		auto last = unique(begin(words), end(words));
		words.erase(last, end(words));
		
		cout << "words.txt contains the following words:" << endl;
		ostream_iterator<string> oi(cout, ", ");
		copy(cbegin(words), cend(words), oi);
		cout << endl;
		
		// 15. Count the total number of words in the file
		cout << endl << "words.txt contains " << in_words.size() << " words" << endl;
    }
}