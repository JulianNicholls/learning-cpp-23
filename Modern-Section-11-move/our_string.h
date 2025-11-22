#ifndef OUR_STRING_H
#define OUR_STRING_H

#include <iostream>
#include <ranges>
#include <string_view>

class OurString
{
  public:
    constexpr OurString() = default;
    constexpr OurString(size_t size)
        : size_{size}
        , data_{new char[size]}
    {
    }
    constexpr OurString(const std::string_view &str)
        : size_(str.size())
        , data_(new char[str.size()])
    {
        memcpy(data_, str.data(), size_);
    }

    ~OurString() noexcept
    {
        std::cout << "Destructor called: " << static_cast<void *>(data_) << std::endl;

        delete[] data_;
    }

    OurString(const OurString &other)
    {
        std::cout << "Copy constructor called\n";

        size_ = other.size_;
        data_ = new char[other.size_];

        memcpy(data_, other.data_, size_);
    }

    constexpr OurString(OurString &&other) noexcept
        : OurString()
    {
        std::cout << "Move constructor called\n";

        swap(other);
    }

    OurString &operator=(const OurString &other)
    {
        OurString temp{other};

        swap(temp);

        return *this;
    }

    OurString &operator=(OurString &&other) noexcept
    {
        std::cout << "Move operator = called\n";

        OurString temp{std::move(other)};

        swap(temp);

        return *this;
    }

    // Strictly speaking, this should be broken because there is no terminating
    // null
    void print(std::ostream &os) const;

    constexpr void swap(OurString &other) noexcept
    {
        std::ranges::swap(size_, other.size_);
        std::ranges::swap(data_, other.data_);
    }

    constexpr size_t size() const
    {
        return size_;
    }

  private:
    size_t size_ = 0;
    char *data_ = nullptr;
};

inline std::ostream &operator<<(std::ostream &os, const OurString &str)
{
    str.print(os);

    return os;
}

#endif // OUR_STRING_H
