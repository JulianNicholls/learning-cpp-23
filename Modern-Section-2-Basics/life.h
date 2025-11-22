#ifndef LIFE_H
#define LIFE_H

#include <string>

const std::string live_cell{"\x1b[1;37mX"};
const std::string empty_cell{"\x1b[0m "};

const int rowmax = 80;
const int colmax = 180;

// Conway's parameters
const int min_neighbours = 2;
const int max_neighbours = 3;
const int min_parents = 3;
const int max_parents = 3;

#endif  // LIFE_H
