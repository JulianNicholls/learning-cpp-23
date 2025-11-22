#include <bitset>
#include <iomanip>
#include <iostream>

using std::bitset;
using std::cout, std::endl;

int main()
{
  bitset<8> byte("10101101");
  bitset<16> word(0xcafe);
  bitset<8> bin(0b01111011);

  cout << "byte = " << byte << endl;
  cout << "word = " << word.to_ulong() << " :: " << std::hex << word.to_ulong() << std::dec << endl;
  cout << "word = " << word.to_string() << endl;
  cout << "bin  = " << bin << endl;

  cout << "\nword has " << word.size() << " bits\n";

  cout << "\nBits of byte (LSB->MSB): ";
  for (size_t i = 0; i < byte.size(); ++i)
    cout << byte[i] << " ";

  cout << "\nBounds checking access\n";

  try {
    cout << "Bit 16 of word = " << word.test(16) << endl;
  }
  catch(std::exception& ex) {
    cout << "Exception: " << ex.what()<< endl;
  }

  // All the usual logical operations are possible

  cout << "\n~byte      = " << ~byte << endl;
  cout << "byte & bin = " << (byte & bin) << endl;
  cout << "byte | bin = " << (byte | bin) << endl;
  cout << "byte ^ bin = " << (byte ^ bin) << endl;
  cout << "byte << 3  = " << (byte << 3) << endl;
  cout << "bin  >> 2  = " << (bin >> 2) << endl;

  cout << "\nbyte.all() = " << std::boolalpha << byte.all() << endl;
  cout << "byte.any() = " << byte.any() << endl;
  cout << "bin.none() = " << bin.none() << endl;
  cout << "bin.count()= " << bin.count() << endl;

  // There are member functions set(), reset(), and flip().
  // By themselves they act on all bits, but can take a bit number
}
