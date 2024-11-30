#pragma once

// Local
#include "IHasUUID.hpp"

namespace lexikan
{
    class Base : public IHasUUID
    {
    public:
        Base();
        ~Base() = default;
    };
}