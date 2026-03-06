#include <iostream>
#include <vector>

// SFINAE -> Substitution Failure Is Not An Error
// C++17
template<typename T>
void foo(T)
{
    if constexpr(std::is_integral_v<T>)
    {
        std::cout << std::endl << "Integral";
    }
    else
    {
        std::cout << std::endl << "Not integral"; 
    }
}

int main(void)
{
    double data = 0;
    foo(data);

    return 0;
}