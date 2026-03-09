#include <iostream>

struct Empty
{};

struct Foo
{
    int value;
    // C++20
    //[[no_unique_address]] 
    Empty e;
};

struct FooEx : Empty
{
    int value;
};

int main()
{
    std::cout << std::endl << sizeof(Empty);
    std::cout << std::endl << sizeof(Foo);
    std::cout << std::endl << sizeof(FooEx); // EBO - Empty Base Optimization

    return 0;
}