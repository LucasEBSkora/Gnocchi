#include "SemanticException.h"

#include <string.h>

namespace EN
{

    SemanticException::SemanticException(const std::string &message) : message{"NOPL compilation exception: " + message}
    {
    }

    const char *SemanticException::what() const noexcept
    {
        return message.c_str();
    }

}