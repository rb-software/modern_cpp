#include <iostream>
#include <memory>

class Foo 
{
public:
    Foo(void* data)
        : m_data(data)
    {
        std::cout << std::endl << __func__;
    }
    ~Foo()
    {
        std::cout << std::endl << __func__;
    }

    // Accessor
    void* getData() const
    {
        return m_data;
    }

private:
    // Some generic data 
    void* m_data;
};

int main()
{
    size_t inputData = SIZE_MAX;

    // shared_ptr make_shared  
    {
        // -> 1 allocation Foo object and control block in one memory block
        // -> efective and cache friendly
        auto ptr1 = std::make_shared<Foo>(&inputData);
        std::cout << std::endl << *static_cast<size_t*>(ptr1->getData());
    }

    // shared_ptr
    {
        // -> 2 allocations, first for Foo object second for control block
        // -> old approach
        auto ptr2 = std::shared_ptr<Foo>(new Foo(&inputData));
        std::cout << std::endl << *static_cast<size_t*>(ptr2->getData());
    }

    return 0;
}