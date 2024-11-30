// Local
#include <lexikanConfig.hpp>

// Local
#include "Base.hpp"

// spdlog
#include <spdlog/spdlog.h>

namespace lexikan
{
    Base::Base()
    {
        auto str = this->toString();
        auto logger = spdlog::get(PROJECT_NAME);
        logger->info("UUID: {}", str);
    }
}