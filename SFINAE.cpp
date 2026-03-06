#include <iostream>
#include <vector>

// SFINAE -> Substitution Failure Is Not An Error

template<typename T>
auto foo(T t ) -> decltype(t.size())
{
    return t.size();
}

template<typename T>
void foox(T t)
{
    typename T::type x;
}

int main(void)
{
    std::vector<int> vec {0, 10};
    std::cout << std::endl << foo(vec);

    // int data = 0;
    // std::cout << std::endl << foo(data);

    return 0;
}