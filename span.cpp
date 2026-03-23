#include <iostream>
#include <span>
#include <algorithm>

void operate(std::span<int> data)
{
    for (int value : data)
    {
        std::cout << value << " ";
    }
    std::cout << std::endl;
}

int main()
{
    int arr[] = {1, 2, 3, 4, 5};
    std::vector<int> vec = {1, 1, 1, 6, 7, 8, 9, 10};

    std::sort(vec.begin(), vec.end());
    //std::reverse(vec.begin(), vec.end());

    auto it = std::unique(vec.begin(), vec.end());
    vec.erase(it, vec.end());

    operate(arr);
    operate(vec);

    std::string str = "Hello, World!";

    std::reverse(str.begin(), str.end());
    std::cout << "str: " << str << std::endl;

    std::sort(str.begin(), str.end());
    std::cout << "str: " << str << std::endl;
    return 0;
}