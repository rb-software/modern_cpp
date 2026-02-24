#include <iostream>

struct ControlBlock
{
    size_t ref_count;

    ControlBlock() 
        : ref_count{1} {}
};

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

template<typename T>
class SharedPtr
{
public:
    explicit SharedPtr(T* ptr = nullptr) noexcept
        : m_ptr(ptr) 
    {
        std::cout <<std::endl << __func__ << " " << __LINE__;

        if (m_ptr)
        {
            std::cout <<std::endl << __func__ << " not nullptr " << __LINE__;
            m_control_block = new ControlBlock; 
        }
        else
        {
            std::cout <<std::endl << __func__ << " nullptr " << __LINE__;
            m_control_block = nullptr;
        }
    }

    SharedPtr(const SharedPtr& other) noexcept
        : m_ptr(other.m_ptr)
        , m_control_block(other.m_control_block)
    {
        std::cout <<std::endl << __func__ << " " << __LINE__;

        if (m_control_block)
        {
            ++m_control_block->ref_count;
        } 
    }

    SharedPtr& operator=(const SharedPtr& other) noexcept
    {
        std::cout <<std::endl << __func__ << " " << __LINE__;

        if (this == &other)
        {
            return *this;
        }

        release();

        m_ptr = other.m_ptr;
        m_control_block = other.m_control_block;

        if (m_control_block)
        {
            ++m_control_block->ref_count;
        }

        return *this;
    }

    ~SharedPtr() noexcept
    {
        release();
    }

    size_t use_count() const noexcept
    {
        return m_control_block ? m_control_block->ref_count : 0;
    }

private:
    void release()
    {
        std::cout <<std::endl << __func__;

        if (!m_control_block)
        {
            return;
        }

        --m_control_block->ref_count;

        if (m_control_block->ref_count == 0)
        {
            delete m_ptr;
            delete m_control_block;
        }
    }

    T* m_ptr = nullptr;
    ControlBlock* m_control_block = nullptr;
};

int main(void)
{
    SharedPtr<Foo> ptr(new Foo);
    std::cout <<std::endl << ptr.use_count();

    SharedPtr<Foo> ptr2 = ptr;
    std::cout << std::endl << ptr2.use_count();

    SharedPtr<Foo> ptr3(new Foo);
    SharedPtr<Foo> ptr4;
    ptr4 = ptr3;

    return 0;
}
