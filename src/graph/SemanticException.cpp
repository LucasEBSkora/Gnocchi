#include "SemanticException.h"

namespace EN {

SemanticException::SemanticException(const string &message)
    : runtime_error{"NOPL compilation exception: " + message} {}
} // namespace EN