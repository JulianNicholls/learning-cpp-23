#include <fstream>
#include <iostream>
#include <string>
#include <thread>

using namespace std::chrono_literals;

std::string fileData(std::ifstream& input, std::size_t bytes)
{
  std::string output{};
  output.resize(bytes);

  std::this_thread::sleep_for(500ms);

  input.read(output.data(), bytes);

  return output;
}

int main()
{
  std::ifstream input{"pangrams.txt"};

  if(!input)
  {
    throw std::logic_error{"Cannot open pangrams.txt"};
  }

  std::cout << fileData(input, 18) << '\n';
  std::cout << fileData(input, 25) << '\n';
  std::cout << fileData(input, 20) << '\n';
  std::cout << fileData(input, 18) << '\n';

  std::cout << "[main running]\n";
}
