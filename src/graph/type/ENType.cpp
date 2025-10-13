#include "ENType.h"

#include "TypeToStringVisitor.h"

namespace EN {

Type::~Type() {}

string Type::toString() const {
  TypeToStringVisitor visitor;
  this->accept(visitor);
  return visitor.getResult();
}

} // namespace EN