#include <iostream>

class Number
{
public:
    Number(const int & input) : m_number(input)
    {
        std::cout << std::endl << __func__;
    }

    ~Number()
    {
        std::cout << std::endl << __func__;
    }

private:
    size_t m_number;
};

Number* foo()
{
    return new Number(10);
}

int main()
{
    std::unique_ptr<Number> localPtr { foo() };
    return 0;
}