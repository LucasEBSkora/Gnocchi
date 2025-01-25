#pragma once

#include <string>
#include <stdexcept>

namespace EN
{
    using namespace std;
    class SemanticException : public runtime_error
    {
    public:
        SemanticException(const string &message);
    };

}