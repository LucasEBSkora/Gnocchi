#pragma once

#include <stdexcept>
#include <string>

namespace EN {
using namespace std;
class SemanticException : public runtime_error {
public:
  SemanticException(const string &message);
};

} // namespace EN