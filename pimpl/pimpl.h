#pragma once
#include <memory>

class Foo
{
public:
    Foo();
    ~Foo();

private:
    class Impl;
    std::unique_ptr<Impl> m_impl;
};