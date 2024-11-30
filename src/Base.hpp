#pragma once

// std
#include <string>
#include <any>

namespace lexikan
{

class Base
{
public:
    Base();
    ~Base() = default;

private:
    std::any _value;
};

}