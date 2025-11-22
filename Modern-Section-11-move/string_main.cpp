#include <iostream>

#include "our_string.h"

using std::cout, std::endl;

int main()
{
    OurString a{"Fiver"};

    cout << "a: " << a << endl;

    OurString b{"Sixers"};

    cout << "b: " << b << endl;

    cout << "Copy assign from a to b\n";
    b = a;
    cout << "a: " << a << endl;
    cout << "b: " << b << endl;

    cout << "Copy construct c from b\n";
    OurString c(b);

    cout << "a: " << a << endl;
    cout << "b: " << b << endl;
    cout << "c: " << c << endl;

    cout << "Move construct d from b\n";
    OurString d(std::move(b));

    cout << "a: " << a << endl;
    cout << "b: " << b << endl;
    cout << "c: " << c << endl;
    cout << "d: " << d << endl;

    //  cout << "Move assign a to c\n";
    c = std::move(a);

    cout << "a: " << a << endl;
    cout << "b: " << b << endl;
    cout << "c: " << c << endl;
    cout << "d: " << d << endl;
}
