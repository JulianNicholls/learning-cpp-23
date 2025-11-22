// Counting the number of lines and characters in a text file
#include <iostream>
#include <iterator>
#include <algorithm>
#include <vector>
#include <fstream>
#include <string>

using namespace std;

int main() {
	// 16. Count the number of lines in the file
    std::ifstream wif("words.txt");

    if (wif) {
        istreambuf_iterator<char> iit{wif};
        istreambuf_iterator<char> eof;
		string in_words{iit, eof};
		
		auto nlines = count(cbegin(in_words), cend(in_words), '\n');
		
		std::cout << "The file contains " << nlines << " lines\n";
	
		// 17. Count the number of characters in the file				
		std::cout << "File contains " << in_words.size() << " characters\n";
	}
}