#include <iostream>

using std::cout, std::endl;

// Classes with any virtual fiuncions should have a virtual destructor
class Shape
{
public:
  virtual ~Shape() {cout << "Goodbye from Shape\n";}

  void draw() const { cout << "Drawing a generic shape\n"; }
  virtual void draw() const { cout << "Drawing a generic shape\n"; }
  virtual float area() const = 0;
};

class Circle : public Shape
{
public:
  virtual ~Circle() { cout << "Goodbye from Circle\n"; }

  void draw() const { cout << "Drawing a circle\n"; }
  void draw() const override { cout << "Drawing a circle\n"; } // override highlights the fact
  float area() const override
  {
    cout << "Calculating area of circle";
    return 3.6;
  }
};

class Triangle final : public Shape   // Nothing can be derived from Triangle
{
public:
  virtual ~Triangle() { cout << "Goodbye from Triangle\n"; }

  void draw() const { cout << "Drawing a triangle\n"; }
  virtual void draw() const override { cout << "Drawing a triangle\n"; }  // A member function can also be final
  float area() const override
  {
    cout << "Calculating area of triangle";
    return 6.6;
  }
};

int main()
{
  Circle circle;
  Triangle tri;
  Shape *pshape = &circle;
  Shape &rshape = tri;

  // The circle will draw a circle, but the ptr and ref will draw a shape
  cout << "Circle: ";
  circle.draw();
  cout << "Triangle: ";
  tri.draw();
  cout << "pShape: ";
  pshape->draw();
  cout << "rShape: ";
  rshape.draw();

  // Thsee all draw a circle
  cout << "\nCircle: ";
  circle.draw();
  cout << "Triangle: ";
  tri.draw();
  cout << "pShape: ";
  pshape->draw();
  cout << "rShape: ";
  rshape.draw();

  cout << endl;   // Before destructors
}
