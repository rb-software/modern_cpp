#include <iostream>
#include <utility>
#include <cstddef>

struct Foo
{
    Foo()
    {
        std::cout << std::endl << __func__;
    }

    ~Foo()
    {
        std::cout << std::endl << __func__;
    }

    void trigger()
    {
        std::cout << std::endl << __func__;
    }
};

template <typename T>
class UniquePtr
{
public:
    constexpr UniquePtr() noexcept // default constructor
        : m_ptr(nullptr)
        {}

    explicit UniquePtr(T* ptr = nullptr) noexcept // Raw ptr constructor
        : m_ptr(ptr)
        {
            std::cout << std::endl << __func__;
        }

    UniquePtr(const UniquePtr& ptr) = delete; // copy constructor
    UniquePtr& operator=(const UniquePtr& ptr) = delete; // move assigment operator

    UniquePtr(UniquePtr&& ptr) noexcept // move constructor
        : m_ptr(std::exchange(ptr.m_ptr, nullptr))
    {
        std::cout << std::endl << __func__ << " -> std::move()";
    }

    ~UniquePtr()
    {
        delete m_ptr;
    }

    T* operator->() const noexcept
    {
        return m_ptr;
    }

    T* get() const noexcept
    {
        return m_ptr;
    }

    T& operator*() const noexcept
    {
        return *m_ptr;
    }

    T* release() noexcept
    {
        std::cout << std::endl << __func__;
        return std::exchange(m_ptr, nullptr);
    }

    void reset(T* ptr = nullptr) noexcept
    {
        if (m_ptr)
        {
            delete m_ptr;
        }

        m_ptr = ptr;
    };

    explicit operator bool() const noexcept
    {
        return m_ptr != nullptr;
    }

private:
    T* m_ptr = nullptr;
};

int main()
{
    UniquePtr<Foo> ptr(new Foo);

    // Basic usage
    ptr->trigger();
    ptr.get()->trigger();
    (*ptr).trigger();

    // Reset with new object
    ptr.reset(new Foo);
    ptr->trigger();

    if (ptr)
    {
        std::cout << std::endl << "Object exits";
    }

   /*
    int tmp = ptr; // blocked by operator bool()
    */

    ptr.release();

    //UniquePtr<Foo> ptr2(new Foo);
    //UniquePtr<Foo> ptr3 = ptr2; // copy constructor has been deleted

    UniquePtr<Foo> ptr4(new Foo);
    //ptr4 = ptr2; // assignment operator has been deleted

    // Both below are equivalent
    UniquePtr<Foo> ptr5(std::move(ptr4));
    UniquePtr<Foo> ptr6 = std::move(ptr4);

    return 0;
}