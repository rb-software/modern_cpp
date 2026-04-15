#include <iostream>

int main()
{
    std::vector<int> v1 = {1, 2, 3, 4, 5};

    std::vector<int> v2{v1}; // copy constructor
    std::vector<int> v3 = v1; // copy constructor
    std::vector<int> v4(std::move(v1)); // move constructor
    std::vector<int> v5 = std::move(v2); // move constructor
    std::vector<int> v6(v1); // copy constructor

    std::vector<int> v7; // default constructor
    v7.resize(v3.size()); // resize to fit the size of v3
    std::copy(v3.begin(), v3.end(), v7.begin());

    std::array<int, 5> a1 = {1, 2, 3, 4, 5};
    std::array<int, 5> a2;

    std::copy(a1.begin(), a1.end(), a2.begin());

    return 0;
}