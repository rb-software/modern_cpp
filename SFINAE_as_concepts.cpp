#include <iostream>

class Test
{
public:
    Test() = default;
    Test(double x) : m_x(x) {}

    double getX() const { return m_x; }
private:
    double m_x{0};
};

template<typename T>
concept HasGetX = requires(T obj)
{
   { obj.getX() } ->std::same_as<double>;
};

auto getX(const HasGetX auto& obj)
{
    return obj.getX();
}

int main()
{
    std::cout << "Hello, Concepts!" << std::endl;

    Test t(42);
    std::cout << "Value of x: " << getX(t) << std::endl;

    return 0;
}