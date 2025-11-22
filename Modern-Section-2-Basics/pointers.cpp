// pointers.cpp

#include <iostream>

int main() {
    int a = 10;
    int* p = &a; // Pointer to an integer

    std::cout << "Value of a: " << a << std::endl;
    std::cout << "Address of a: " << &a << std::endl;
    std::cout << "Value of p (address of a): " << p << std::endl;
    std::cout << "Value pointed to by p: " << *p << std::endl;

    *p = 20; // Change the value of a using the pointer
    std::cout << "New value of a: " << a << std::endl;

    return 0;
}
