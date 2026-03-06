#include <iostream>
#include <vector>

template<typename T>
auto foo(T t ) -> decltype(t.size())
{
    return t.size();
}

int main(void)
{
    std::vector<int> vec {0, 10};
    std::cout << std::endl << foo(vec);

    // int data = 0;
    // std::cout << std::endl << foo(data);

    return 0;
}