// Local
#include "IHasUUID.hpp"

// std
#include <sstream>

// boost
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>

namespace lexikan
{
    IHasUUID::IHasUUID()
    {
        boost::uuids::random_generator generator;
        _id = generator();
    };

    const boost::uuids::uuid& IHasUUID::getUUID() const
    {
        return _id;
    }

    std::string IHasUUID::toString() const
    {
        auto uuidStream = std::ostringstream();
        uuidStream << _id;
        return uuidStream.str();
    }
}