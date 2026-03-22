#include <iostream>
#include <format>

int main()
{
    int number = 42;
    float pi = 3.14159;
    std::string text = "Alice: " + std::format("pi {} number {}", pi, number);
    std::cout << text << std::endl;
    return 0;
}