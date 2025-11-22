#ifndef BITMAP_H
#define BITMAP_H

#include <cstdint>
#include <string>
#include <vector>

// A bitmap is a 16-bit format, so packed as 2 bytes
#pragma pack(push, 2)
struct BitmapHeader
{
    char header[2]{'B', 'M'};
    int32_t file_size;
    int32_t reserved{0};
    int32_t data_offset;
};
#pragma pack(pop)

// Info header is also 16-bit aligned, but needs no hints
// because everything algns on its own width.
struct BitmapInfoHeader
{
    int32_t header_size{40};
    int32_t width;
    int32_t height;
    int16_t planes{1};
    int16_t bits_per_pixel{24};
    int32_t compression{0};
    int32_t data_size{0};
    int32_t horizontal_resolution{2400};
    int32_t vertical_resolution{2400};
    int32_t colours{0};
    int32_t important_colours{0};
};

// Pixel is byte aligned
struct BitmapPixel
{ // Note: BGR, NOT RGB
    uint8_t blue;
    uint8_t green;
    uint8_t red;
};

class Bitmap
{
  public:
    Bitmap(std::string filename)
        : filename_(filename)
        , pixels_(width_ * height_) {};
    void set_pixel(int x, int y, BitmapPixel p);
    void set_row(int row, BitmapPixel p);
    void set_all(BitmapPixel p);
    bool write();

  private:
    int pixelOffset(int x, int y)
    {
        return y * width_ + x;
    };

    int width_{800};
    int height_{600};
    std::string filename_;
    std::vector<BitmapPixel> pixels_;
};

#endif // BITMAP_H
