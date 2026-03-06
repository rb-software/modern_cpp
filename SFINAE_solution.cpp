#include <iostream>
#include <vector>

// SFINAE -> Substitution Failure Is Not An Error

template<typename T>
typename std::enable_if<std::is_integral<T>::value>::type
foo(T t )
{
    std::cout << std::endl << "Integral";
}

// Simple solution
// template<typename T>
// typename std::enable_if<std::is_integral<T>>
// foo(T t )
// {
//     std::cout << std::endl << "Integral";
// }

int main(void)
{
    // std::vector<int> vec {0, 10};
    // std::cout << std::endl << foo(vec);

    int data = 0;
    foo(data);

    // Error missing candidate
    // double fp = 0.0;
    // foo(fp);

    return 0;
}