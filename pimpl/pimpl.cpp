#include <string_view>
#include <vector>

#include "pimpl.h"

class Foo::Impl
{
public:
    static constexpr std::string_view m_name = "Crypto";
    std::vector<size_t> m_dummyVector {};
};

Foo::Foo()
    : m_impl(std::make_unique<Impl>())
{}

Foo::~Foo() = default;