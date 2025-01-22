#pragma once

#include <exception>
#include <string>

namespace EN
{
    class SemanticException : public std::exception
    {
    public:
        SemanticException(const std::string &message);
        const char *what() const noexcept override;

    private:
        std::string message;
    };

}