#pragma once

// std
#include <string>
#include <memory>
#include <utility>

// local
#include "Base.hpp"

namespace lexikan
{
    class Dictionary : public Base
    {
    public:
        using Ptr = std::shared_ptr<Dictionary>;
        using ConstPtr = std::shared_ptr<Dictionary const>;
        using WeakPtr = std::weak_ptr<Dictionary>;
    
        Dictionary() = default;
        Dictionary(Dictionary&) = default;
        Dictionary(Dictionary&&) = default;
        ~Dictionary() = default;
    };
}