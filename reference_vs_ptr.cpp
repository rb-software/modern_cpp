#include <iostream>

int main(void)
{
    int x = 10, y = 20;
    
    // Pointer
    int* ptr = &x;
    ptr = &y;       // OK
    *ptr = 99;      // y = 99

    // Reference
    int& ref = x;   // ref is an alias for x
    ref = y;        // ref = 99 copying y to ref, which is x, so x = 99
    ref = 87;       // x = 87

    std::cout << "x: " << x << std::endl; // 87
    std::cout << "y: " << y << std::endl; // 99


    std::cout << &x << std::endl; // address of x
    std::cout << &y << std::endl; // address of y

    std::cout << &ref << std::endl; // address of x (same as &x)
    std::cout << ptr << std::endl;  // address of y (same as &y)

    return 0;
}