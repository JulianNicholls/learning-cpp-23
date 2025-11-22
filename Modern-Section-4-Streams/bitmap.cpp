#include <fstream>
#include <iostream>

#include "bitmap.h"

bool Bitmap::write()
{
    BitmapHeader file_header;
    BitmapInfoHeader info_header;

    // Calculate the size of the bitmap
    file_header.file_size = sizeof(BitmapHeader) + sizeof(BitmapInfoHeader) + width_ * height_ * sizeof(BitmapPixel);
    file_header.data_offset = sizeof(BitmapHeader) + sizeof(BitmapInfoHeader);

    // Set the image width and height
    info_header.width = width_;
    info_header.height = height_;

    // Open the file
    std::fstream ofile(filename_, std::fstream::out | std::fstream::binary);

    if (!ofile.is_open())
        return false;

    // Write the file and info headers
    ofile.write(reinterpret_cast<char *>(&file_header), sizeof(BitmapHeader));
    ofile.write(reinterpret_cast<char *>(&info_header), sizeof(BitmapInfoHeader));

    // Write the pixel data
    ofile.write(reinterpret_cast<char *>(pixels_.data()), pixels_.size() * sizeof(BitmapPixel));

    if (!ofile)
        return false;

    ofile.close();

    return true;
}

void Bitmap::set_pixel(int x, int y, BitmapPixel p)
{
    auto idx = pixelOffset(x, y);

    pixels_[idx] = p;
}

void Bitmap::set_row(int row, BitmapPixel p)
{
    auto idx = pixelOffset(0, row);

    // This could, of course, be done in terms of set_pixel.
    for (int x = 0; x < width_; ++x)
        pixels_[idx++] = p;
}

void Bitmap::set_all(BitmapPixel p)
{
    for (int y = 0; y < height_; ++y)
        set_row(y, p);
}
