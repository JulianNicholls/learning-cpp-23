#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <array>

namespace constants {
  const int npegs = 4;
  const int nturns = 10;
  const int ncolours = 5;
}

using PegArray = std::array<char, constants::npegs>;
using ColourArray = std::array<char, constants::ncolours>;

namespace constants {
  const ColourArray colours = {'R', 'G', 'B', 'Y', 'C'};
}

#endif    // CONSTANTS_H
