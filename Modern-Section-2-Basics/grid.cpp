#include <iostream>

#include "grid.h"

void Grid::create(int row, int col)
{
  cells_[row][col].create();
}

void Grid::draw() const
{
  for (int row = 0; row < rowmax; ++row)
  {
    for (int col = 0; col < colmax; ++col)
    {
      cells_[row][col].draw(row, col);
    }
  }
}

void Grid::randomise()
{
  const int factor = 5;
  const int cutoff = RAND_MAX / factor;

  // time_t now;
  // time(&now)
  // srand(now);

  for (int row = 1; row < rowmax; ++row)
  {
    for (int col = 1; col < colmax; ++col)
    {
      if (rand() / cutoff == 0)
        create(row, col);
    }
  }
}

bool Grid::will_survive(int row, int col) const
{
  if (!cells_[row][col].is_alive())
    return false;

    auto count = neighbours(row, col);

    return (count >= min_neighbours && count <= max_neighbours);
}

bool Grid::will_create(int row, int col) const
{
  if (cells_[row][col].is_alive())
    return false;

  auto count = neighbours(row, col);

  return (count >= min_parents && count <= max_parents);
}

void Grid::update(const Grid& other) {
  for (int row = 1; row < rowmax; ++row)
  {
    for (int col = 1; col < colmax; ++col)
    {
      cells_[row][col] = other.cells_[row][col];
    }
  }
}

void calculate(const Grid& current, Grid& next) {
  for (int row = 1; row < rowmax; ++row)
  {
    for (int col = 1; col < colmax; ++col)
    {
      if(current.will_survive(row, col) || current.will_create(row, col))
        next.create(row, col);
    }
  }
}

// Private

int Grid::neighbours(int row, int col) const {
  return cells_[row - 1][col - 1].is_alive() +
         cells_[row - 1][col].is_alive() +
         cells_[row - 1][col + 1].is_alive() +
         cells_[row][col - 1].is_alive() +
         cells_[row][col + 1].is_alive() +
         cells_[row + 1][col - 1].is_alive() +
         cells_[row + 1][col].is_alive() +
         cells_[row + 1][col + 1].is_alive();
}
