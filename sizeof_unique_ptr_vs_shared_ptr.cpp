#include <iostream>

// pragma allows to avoid aligment problem at the expense of performance
#pragma pack(1)
class Foo
{
    char m_char;
    int m_value;
};
#pragma pack()

int main()
{
    std::unique_ptr<int> ptr1 = std::make_unique<int>(42);
    std::shared_ptr<int> ptr2 = std::make_shared<int>(42);

    std::cout << std::endl << sizeof(ptr1); // 8 bytes (size of unique_ptr)
    std::cout << std::endl << sizeof(ptr2); // 16 bytes (size of shared_ptr)
    std::cout << std::endl << sizeof(int); // 4 bytes (size of int)
    std::cout << std::endl << sizeof(int*); // 8 bytes (size of int*)4
    std::cout << std::endl << sizeof(char); // 1 byte
    std::cout << std::endl << sizeof(char*); // 8 bytes

    std::cout << std::endl << sizeof(Foo); // 5 byte
    std::cout << std::endl << sizeof(Foo*); // 8 bytes

    std::cout << std::endl << sizeof(void*); // 8 bytes
    //std::cout << std::endl << sizeof(void); // compilation error

    return 0;
}