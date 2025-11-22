#include <iostream>

using std::cout, std::endl;

class Shape
{
public:
  virtual ~Shape() { cout << "Destructing Shape\n"; }

  virtual void draw() const { cout << "Drawing a generic shape\n"; }
  virtual float area() const = 0;
};

class Circle : public Shape
{
public:
  virtual ~Circle() { cout << "Destructing Circle\n"; }

  void draw() const override { cout << "Drawing a circle\n"; } // override highlights the fact
  float area() const override
  {
    cout << "Calculating area of circle";
    return 3.6;
  }
};

class Triangle : public Shape
{
public:
  virtual ~Triangle() { cout << "Destructing Triangle\n"; }

  virtual void draw() const override { cout << "Drawing a triangle\n"; }
  float area() const override
  {
    cout << "Calculating area of triangle";
    return 6.6;
  }
};

class Square : public Shape
{
public:
  virtual ~Square() { cout << "Destructing Square\n"; }

  virtual void draw() const override { cout << "Drawing a square\n"; }
  float area() const override
  {
    cout << "Calculating area of square";
    return 6.6;
  }
};
