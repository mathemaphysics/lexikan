#pragma once

// std
#include <string>

namespace lexikan
{
	class HasName
	{
	public:
        HasName(const std::string& name_ = "None");
		~HasName() = default;

        /**
         * @brief Get the name
         * 
         * @return const std::string& The name
         */
        virtual const std::string& getName() const;

    protected:

        /**
         * @brief Set the name
         * 
         * @param name_ The name to set it to
         */
        virtual void setName(const std::string& name_);

    private:
        std::string _name;
	};
}
