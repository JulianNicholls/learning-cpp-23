// Find the words that two text files have in common
#include <iostream>
#include <numeric>
#include <iterator>
#include <algorithm>
#include <vector>
#include <fstream>
#include <string>

using namespace std;

// Return a copy of the argument string
// with non-alphabetical characters removed, converted to lower case
string normalize(const string& s) {
	string retval{""};
	
	copy_if(begin(s), end(s), back_inserter(retval),
				[](char c) { return isalpha(c); }
	);
	transform(begin(retval), end(retval), begin(retval), 
				[] (char c) { return tolower(c); }
	);
	
	return retval;
}

int main() {
	// 18. Read two files of words and display the words which are common to both files
    std::ifstream wif{"words.txt"};
    std::ifstream wif2{"words2.txt"};

    if (wif && wif2) {
		// Read word.txt and word2.txt into vectors
        istream_iterator<string> iit{wif};
        istream_iterator<string> eof;
        vector<string> in_words{iit, eof};
		istream_iterator<string> iit2{wif2};
        vector<string> in_words2{iit2, eof};

		// Normalize the words.txt vector
		vector<string> words, words2;
		transform(cbegin(in_words), cend(in_words), back_inserter(words), normalize);
		sort(begin(words), end(words));
		auto last = unique(begin(words), end(words));
		words.erase(last, end(words));
		
		// Normalize the words2.txt vector
		transform(cbegin(in_words2), cend(in_words2), back_inserter(words2), normalize);
		sort(begin(words2), end(words2));
		auto last2 = unique(begin(words2), end(words2));
		words2.erase(last2, end(words2));
		
		// Find the set intersection of the two vectors
		cout << "words.txt and words2.txt have the following words in common:" << endl;
        ostream_iterator<string> out(cout, "\n");
        std::set_intersection(cbegin(words), cend(words),
                              cbegin(words2), cend(words2), out);
    }
}