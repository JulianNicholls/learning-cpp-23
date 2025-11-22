#include <iostream>

#include "life.h"
#include "cell.h"

void Cell::draw(int row, int col) const {
  // Move the cursor to row, col with Esc[n;mH and draw the cell
  std::cout << "\x1b[" << row + 1 << ';' << col + 1 << 'H';
  std::cout << (alive_ ? live_cell : empty_cell);
}
