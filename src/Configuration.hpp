#pragma once

// Configuration
#include <lexikanConfig.hpp>

// jsoncpp
#ifdef WITH_JSONCPP
#include <json/json.h>
#endif

// spdlog
#include <spdlog/spdlog.h>

// local
#include "Base.hpp"

// std
#include <string>
#include <memory>
#include <utility>

namespace lexikan
{
    class Configuration : public Base
    {
    public:
        using Ptr = std::shared_ptr<Configuration>;
        using ConstPtr = std::shared_ptr<Configuration const>;
        using WeakPtr = std::weak_ptr<Configuration>;

        Configuration() = default;
        Configuration(const std::string& path_ = "config.json");
        Configuration(Configuration&) = default;
        Configuration(Configuration&&) = default;
        ~Configuration() = default;
    
    private:
        
    };
}
