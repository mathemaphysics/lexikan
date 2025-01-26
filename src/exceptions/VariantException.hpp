#pragma once

// std
#include <exception>
#include <string>

namespace lexikan::exceptions
{
    class VariantException : public std::exception
    {
    public:
        // Constructor to allow optional custom error message
        explicit VariantException(const std::string& message = "Failed to convert")
            : _message(message) {}

        // Override the what() function from std::exception
        virtual const char* what() const noexcept override {
            return _message.c_str();
        }

    private:
        std::string _message;  // Stores the error message
    };
}