#include <iostream>
#include <memory>
#include <vector>
#include <string>

#include "shapes.h"

using std::cout, std::endl;
using std::unique_ptr;
using std::vector;

unique_ptr<Shape> shape_factory(int sides)
{
  if (sides < 3)
    return std::make_unique<Circle>();
  else if (sides == 3)
    return std::make_unique<Triangle>();
  else if (sides == 4)
    return std::make_unique<Square>();
  else
    throw new std::runtime_error("Can't create a shape with " + std::to_string(sides) + " sides");
};

int main()
{
  vector<unique_ptr<Shape>> shapes;

  shapes.push_back(shape_factory(1));
  shapes.push_back(shape_factory(3));
  shapes.push_back(shape_factory(4));

  for (auto &it : shapes)
    it->draw();
}
