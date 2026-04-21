#include <iostream>
#include <memory>

struct B;

struct A
{
    std::shared_ptr<B> b;

    ~A()
    {
        std::cout << std::endl << __func__;
    }
};

struct B
{
    std::weak_ptr<A> a; // Problem when using std::shared_ptr<A> a; because of circular reference

    ~B()
    {
        std::cout << std::endl << __func__;
    }
};

int main()
{
    auto a = std::make_shared<A>();
    auto b = std::make_shared<B>();

    a->b = b;
    b->a = a;

    return 0;
}