#include <memory>
#include <iostream>

struct Test
{
    //Default constructor

    Test()
    {
        std::cout << std::endl << "Default constructor called" << std::endl;
    }
    
    //Destructor
    ~Test()
    {
        std::cout << std::endl << "Destructor called" << std::endl;
    }
};

int main()
{
    std::weak_ptr<Test> wp;

    std::cout << std::endl << "Size of weak_ptr: " << sizeof(wp);

    {
        std::shared_ptr<Test> sp1 = std::make_shared<Test>();
        std::cout << std::endl << "Size of shared_ptr: " << sizeof(sp1);
        wp = sp1;
    }

    if (auto sp = wp.lock())
    {
        std::cout << std::endl << "Object is still alive, use count: " << sp.use_count() << std::endl;
    }
    else
    {
        std::cout << std::endl << "Object has been destroyed" << std::endl;
    }

    std::cout << std::endl << "End of main function" << std::endl;

    return 0;
}