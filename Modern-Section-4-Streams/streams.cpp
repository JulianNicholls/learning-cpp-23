#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <string>

// Read a word at a time
void read_with_shift()
{
  std::ifstream ifile("test.txt");

  if (ifile)
  {
    std::cout << "Words\n";

    std::string text;

    while (ifile >> text)
    {
      std::cout << text << ", ";
    }

    ifile.close();

    std::cout << std::endl;
  }
}

void read_lines()
{
  std::ifstream ifile("test.txt");

  if (ifile)
  {
    std::cout << "\nLines\n";

    std::string text;

    while (getline(ifile, text))
    {
      std::cout << text << "<LF>\n";
    }

    ifile.close();
  }
}

// ofstream is buffered, to flush it you can send << std::flush.
// cout is line-buffered.
// using cin (also line-buffered) to input will flush cout.
void write_with_shift()
{
  std::ifstream ifile("test.txt");
  std::ofstream ofile("test-1.txt", std::ios::app); // Open in append mode

  if (ifile && ofile)
  {
    std::cout << "\nWriting test-1.txt\n";

    std::string text;

    while (ifile >> text)
    {
      ofile << text << " ";
    }

    ifile.close();

    ofile << std::endl;
    ofile.close();
  }
}

void read_write_block()
{
  const int buffer_size = 1024;
  char *filebuf = new char[buffer_size];
  std::string filename{"streams.cpp"};
  std::ifstream ifile(filename);

  if (!ifile)
  {
    std::cerr << "Could not open " << filename << std::endl;
    return;
  }

  std::cout << "\nBlock Read / Write\n";
  std::streamsize count;

  do
  {
    count = ifile.read(filebuf, buffer_size).gcount();

    std::cout << "### " << count << " characters\n";
    // std::cout.write(filebuf, count);   // Save some real-estate by not actually outputting it
  } while (count != 0);

  std::cout << std::endl;
  delete[] filebuf;
}

void simple_manipulators()
{
  std::cout << std::boolalpha << "'false' is " << false << std::endl;
  std::cout << "'false' value is " << std::noboolalpha << false << std::endl;

  // setw is right-justified...
  std::cout << "\nTwenty: |" << std::setw(3) << 20 << "|\n";
  std::cout << "Five:   |" << std::setw(3) << 5 << "|\n";

  // ...which can be changed with left and right
  std::cout << "\nTwenty: |" << std::left << std::setw(3) << 20 << "|\n";
  std::cout << "Five:   |" << std::right << std::setw(3) << 5 << "|\n";

  // ...as can the fill
  std::cout << "\nTwenty: |" << std::setfill('0') << std::setw(3) << 20 << "|\n";
  std::cout << "Five:   |" << std::setfill('#') << std::setw(3) << 5 << "|\n";

  // Reset the defaults, like a good citizen
  std::cout << std::right << std::setfill(' ');
}

void floating_point()
{
  const double pi = 3.141592653;
  const double c = 299'792'458;

  // default is 6 sig fig, manipulable with scientific and uppercase
  std::cout << "pi: " << pi << std::endl;
  std::cout << "c:  " << c << std::endl;

  // fixed, never uses scientific notation, has 6 decimal places
  std::cout << "\npi: " << std::fixed << pi << std::endl;
  std::cout << "c:  " << c << std::endl;

  // Fixed and defaultfloat can have their sig fig changed
  std::cout << "\npi: " << std::setprecision(9) << pi << std::endl;
  std::cout << "c:  " << std::setprecision(0) << c << std::endl;

  std::cout << "\npi: " << std::defaultfloat << std::setprecision(10) << pi << std::endl;
  std::cout << "c:  " << c << std::endl;

  // Reset the defaults, like a good citizen
  std::cout << std::defaultfloat << std::setprecision(6);
}

template <typename T>
std::string myToString(const T &v)
{
  std::ostringstream out;

  out << v;

  return out.str();
}

void string_stream()
{
  const double pi = 3.141592653;
  const auto ss{myToString(pi)};

  std::cout << "\npi (cout): " << std::setprecision(10) << pi << std::endl;
  std::cout << "pi (sstr): " << ss << std::endl;

  // Reset the defaults, like a good citizen
  std::cout << std::defaultfloat << std::setprecision(6);
}

int main()
{
  read_with_shift();
  read_lines();
  write_with_shift();
  read_write_block();
  simple_manipulators();
  floating_point();
  string_stream();

  // There are stream iterators, but they seem to be there for completeness
  // just repeating the same operations with different syntax.
  // They enable some algorithms later on.

  std::cout << std::endl;
}
