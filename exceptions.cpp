#include <iostream>

class Foo
{
public:
    Foo(int value) noexcept
        : m_value(value)
    {}

    int getValue()  const
    {
        if (m_value %2 == 0)
        {
            throw std::runtime_error("Value cannot be even");
        }
        else
        {
            return m_value;
        }
    }

private:
    int m_value;
};

int main()
{
    std::cout << "Hello World!" << std::endl;

    Foo foo(4);

    try
    {
        std::cout << foo.getValue() << std::endl;
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }

    return 0;
}