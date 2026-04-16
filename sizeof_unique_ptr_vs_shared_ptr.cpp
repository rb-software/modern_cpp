#include <iostream>

int main()
{
    std::unique_ptr<int> ptr1 = std::make_unique<int>(42);
    std::shared_ptr<int> ptr2 = std::make_shared<int>(42);

    std::cout << std::endl << sizeof(ptr1); // 8 bytes (size of unique_ptr)
    std::cout << std::endl << sizeof(ptr2); // 16 bytes (size of shared_ptr)

    return 0;
}