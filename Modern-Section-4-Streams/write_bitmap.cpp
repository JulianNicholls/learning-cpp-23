#include <iostream>

#include "bitmap.h"

int main()
{
  const int width = 800;
  const int height = 600;
  const int mid_x = width / 2;
  const int mid_y = height / 2;
  const int x_unit = mid_x / 4;
  const int y_unit = mid_y / 4;

  std::string filename{"cpp.bmp"};
  Bitmap bmp(filename);

  BitmapPixel background{255, 50, 50};
  bmp.set_all(background);

  BitmapPixel cyan{255, 255, 50};

  // Draw stem of 'C'
  for (int x = 0; x < x_unit; ++x)
    for (int y = y_unit; y < height - y_unit; ++y)
      bmp.set_pixel(x, y, cyan);

  // Draw top and bottom of 'C'
  for (int x = x_unit; x < mid_x + x_unit; ++x)
  {
    for (int y = 0; y < y_unit; ++y)
      bmp.set_pixel(x, y, cyan);

    for (int y = height - y_unit; y < height; ++y)
      bmp.set_pixel(x, y, cyan);
  }

  // Draw first +
  for (int x = mid_x - 2 * x_unit; x < mid_x; ++x)
  {
    for (int y = mid_y - y_unit / 2; y < mid_y + y_unit / 2; ++y)
    {
      bmp.set_pixel(x, y, cyan);
    }
  }

  for (int x = mid_x - 3 * x_unit / 2; x < mid_x - x_unit / 2; ++x)
  {
    for (int y = 3 * y_unit; y < 5 * y_unit; ++y)
    {
      bmp.set_pixel(x, y, cyan);
    }
  }

  // Draw second +
  for (int x = 5 * x_unit; x < 7 * x_unit; ++x)
  {
    for (int y = mid_y - y_unit / 2; y < mid_y + y_unit / 2; ++y)
    {
      bmp.set_pixel(x, y, cyan);
    }
  }

  for (int x = mid_x + 3 * x_unit / 2; x < mid_x + 5 * x_unit / 2; ++x)
  {
    for (int y = 3 * y_unit; y < 5 * y_unit; ++y)
    {
      bmp.set_pixel(x, y, cyan);
    }
  }

  if (bmp.write())
    std::cout << "Wrote " << filename << " successfully\n";
  else
    std::cerr << "Failed to write " << filename << std::endl;
}
