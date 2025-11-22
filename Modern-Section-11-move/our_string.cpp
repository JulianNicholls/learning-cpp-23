#include <format>
#include <iostream>

#include "our_string.h"

void OurString::print(std::ostream &os = std::cout) const
{
    if (data_)
        os << std::format("Size: {}, Content: {}, ({})\n", size_, data_, static_cast<void *>(data_));
    else
        os << "Empty";
}
