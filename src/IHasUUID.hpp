#pragma once

// boost
#include <boost/uuid/uuid.hpp>

// std
#include <string>

namespace lexikan
{
    class IHasUUID
    {
    public:
        IHasUUID();
        ~IHasUUID() = default;

        const boost::uuids::uuid& getUUID() const;
        std::string toString() const;

    private:
        boost::uuids::uuid _id;
    };
}
