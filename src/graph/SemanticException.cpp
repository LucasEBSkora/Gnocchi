#include "SemanticException.h"

#include <string.h>

namespace EN
{

    SemanticException::SemanticException(const string &message) : runtime_error{"NOPL compilation exception: " + message}
    {
    }
}