#include <iostream>
#include <fstream>

// #pragma pack(push, 1) // Pack as much as possible, I'm actually surprised that an ARM CPU can used unaligned data
struct Point
{
  char c;
  int32_t x;
  int32_t y;
};
// #pragma pack(pop)

int main()
{
  Point p{'a', 1, 2};
  std::ofstream ofile("file.bin", std::fstream::binary);

  if (ofile.is_open())
  {
    ofile.write(reinterpret_cast<char *>(&p), sizeof(Point));
    ofile.close();
  }

  std::ifstream ifile("file.bin", std::fstream::binary);
  Point p2;

  if (ifile.is_open())
  {
    ifile.read(reinterpret_cast<char *>(&p2), sizeof(Point));
    ifile.close();

    std::cout << "Read " << ifile.gcount() << " bytes\n";
    std::cout << "Read (" << p2.x << ", " << p2.y << ") = " << p2.c << std::endl;
  }
}
