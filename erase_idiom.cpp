#include <iostream>


int main(void)
{
    std::vector<int> v = {1, 2, 3, 4, 5};

    v.erase(std::remove(v.begin(), v.end(), 2), v.end());

    std::cout << "Size: " << v.size() << std::endl;

    for (auto i : v)
    {
        std::cout << i << " ";
    }

    return 0;
}