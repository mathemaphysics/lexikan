#pragma once

// Local
#include <HasName.hpp>

// std
#include <string>

namespace lexikan
{
    HasName::HasName(const std::string &name_)
        : _name{name_}
    {}

    /**
     * @brief Get the name
     *
     * @return const std::string& The name
     */
    const std::string &HasName::getName() const
    {
        return this->_name;
    }

    /**
     * @brief Set the name
     *
     * @param name_ The name to set it to
     */
    void HasName::setName(const std::string &name_)
    {
        this->_name = name_;
    }
}
