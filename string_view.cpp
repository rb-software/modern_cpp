#include <iostream>

// C++ 17
const std::string_view& testStringView(const std::string_view& data)
{
    return data; 
}

std::string_view& testStringNonConst(std::string_view& data)
{
    return data; 
}

std::string testStringByReference(std::string& data)
{
    return data; 
}

std::string testStringByValue(std::string data)
{
    return data; 
}

std::string_view dandling() 
{
    return std::string("Hello, World !");
}

int main(void)
{
    std::string text = "Data to print";
    const std::string_view textDummy = "Data to print";
    std::string_view textNonConst = "Data to print";

    std::cout << std::endl << testStringView(textDummy);
    std::cout << std::endl << testStringNonConst(textNonConst);

    std::cout << std::endl << testStringView(text);

    std::cout << std::endl << testStringByReference(text);
    std::cout << std::endl << testStringByValue(text);

    // Dendling example
    std::cout << std::endl << dandling();

    return 0; 
}