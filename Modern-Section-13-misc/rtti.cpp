#include <iostream>
#include <typeinfo>

using std::cout, std::endl;

inline namespace Graphics  // The namespace is only here to spice up the type_info names
{
  class Shape
  {
  public:
    virtual ~Shape() {};
  };

  class Triangle : public Shape
  {
  public:
    void func() { cout << "Function unique to triangles\n"; }
  };

  class Circle : public Shape
  {
  public:
    void func() { cout << "Function unique to circles\n"; }
  };

  class Square : public Shape
  {
  };
}

int main()
{
  // using namespace Graphics;

  Circle circle;
  Circle circle2;
  Triangle triangle;
  Square square;

  Shape *pShape = &circle;

  if (typeid(*pShape) == typeid(circle))
    cout << "pShape points to a Circle\n";

  if (typeid(*pShape) == typeid(triangle))
    cout << "pShape points to a Triangle\n";

  const std::type_info &tShape = typeid(*pShape);
  const std::type_info &tCircle = typeid(circle2);
  const std::type_info &tTriangle = typeid(triangle);
  const std::type_info &tSquare = typeid(square);

  // Hash code is of the type, not the instance
  cout << "Circle 1: " << tShape.name() << "   :: " << tShape.hash_code() << endl;
  cout << "Circle 2: " << tCircle.name() << "   :: " << tCircle.hash_code() << endl;
  cout << "Square:   " << tSquare.name() << "   :: " << tSquare.hash_code() << endl;
  cout << "Triangle: " << tTriangle.name() << " :: " << tTriangle.hash_code() << endl;
  cout << endl;

  // pShape->func(); // This is not possible, Shape doesn't have func

  Circle *pCirc = dynamic_cast<Circle *>(pShape);
  Triangle *pTri = dynamic_cast<Triangle *>(pShape);

  if (pCirc)
    pCirc->func();
  else
    cout << "pShape wasn't a pointer to a circle\n";

  if (pTri)
    pTri->func();
  else
    cout << "pShape wasn't a pointer to a triangle\n";
}
