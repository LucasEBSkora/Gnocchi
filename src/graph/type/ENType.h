#pragma once

#include <string>

namespace EN {
using namespace std;

class TypeVisitor;

class Type {
public:
  string toString() const;
  virtual void accept(TypeVisitor &visit) const = 0;
  virtual ~Type();
  virtual bool operator==(const Type &other) const = 0;
};

} // namespace EN