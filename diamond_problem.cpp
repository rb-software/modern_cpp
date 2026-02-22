#include <iostream>

class base 
{
public:
    base()
    {
        std::cout << std::endl << __func__;
    }
    ~base()
    {
        std::cout << std::endl << __func__;
    }
};

class c : public virtual base
{
public:
    c()
    {
        std::cout << std::endl << __func__;
    }
    ~c()
    {
        std::cout << std::endl << __func__;
    }
};

class d : public virtual base
{
public:
    d()
    {
        std::cout << std::endl << __func__;
    }
    ~d()
    {
        std::cout << std::endl << __func__;
    }
};

class border_class final : public c, public d
{
public:
    border_class()
    {
        std::cout << std::endl << __func__;
    }
    ~border_class()
    {
        std::cout << std::endl << __func__;
    }
};

int main()
{
    border_class obj;
    return 0;
}