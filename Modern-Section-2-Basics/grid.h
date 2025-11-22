#ifndef GRID_H
#define GRID_H

#include "life.h"
#include "cell.h"

class Grid
{
public:
  void create(int row, int col);
  void draw() const;
  void randomise();
  bool will_survive(int row, int col) const;
  bool will_create(int row, int col) const;
  void update(const Grid &next);

private:
  Cell cells_[rowmax + 2][colmax + 2];

  int neighbours(int row, int col) const;
};

void calculate(const Grid &current, Grid &next);
#endif // GRID_H
