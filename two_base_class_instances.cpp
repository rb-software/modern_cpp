#include <iostream>

class B
{
public:
    B()
    {
        std::cout << std::endl << __func__;
    }
};

class C : public B
{
public:
    C()
    {
        std::cout << std::endl << __func__;
    }
};

// Warning -> two B objects (common class design problem) 
class D : public virtual B, public C 
{
public:
    D()
    {
        std::cout << std::endl << __func__;
    }
}; 

int main()
{
    D obj;
    return 0;
}
