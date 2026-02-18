#include <iostream>
#include <memory>

int main(void)
{
    // Heap allocation
    std::unique_ptr<int> ptr(new int);
    *ptr = 9;
    std::cout << std::endl << *ptr;

    // Heap allocation
    auto modernPtr = std::make_unique<int>(10);
    std::cout << std::endl << *modernPtr;

    // Stack allocation
    int foo = 0;
    std::unique_ptr<int> ptrStack(&foo);
    std::cout << std::endl << ptrStack;

    return 0;
}