#pragma once

// boost
#include <boost/uuid/uuid.hpp>

// std
#include <string>
#include <memory>
#include <utility>

namespace lexikan
{
    class IHasUUID
    {
    public:
        using Ptr = std::shared_ptr<IHasUUID>;
        using ConstPtr = std::shared_ptr<IHasUUID const>;
        using WeakPtr = std::weak_ptr<IHasUUID>;

        IHasUUID();
        ~IHasUUID() = default;

        const boost::uuids::uuid& getUUID() const;
        static std::string toString(boost::uuids::uuid id_);

    private:
        boost::uuids::uuid _id;
    };
}
