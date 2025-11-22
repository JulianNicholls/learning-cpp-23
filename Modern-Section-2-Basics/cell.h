#ifndef CELL_H
#define CELL_H

class Cell
{
public:
  Cell() : alive_{false} {};

  void draw(int row, int col) const;
  void create() { alive_ = true; };
  void erase() { alive_ = false; };

  bool is_alive() const { return alive_; };

private:
  bool alive_;
};

#endif // CELL_H
