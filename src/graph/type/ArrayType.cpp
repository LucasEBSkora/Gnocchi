#include "ArrayType.h"

#include "TypeVisitor.h"

namespace EN {
void ArrayType::accept(TypeVisitor &visit) const { visit.visit(*this); };

ArrayType::~ArrayType() {}
ArrayType::ArrayType(const weak_ptr<Type> baseType,
                     vector<shared_ptr<Expr>> dimensions)
    : baseType{baseType}, dimensions{dimensions} {}

bool ArrayType::operator==(const Type &other) const {
  try {
    const ArrayType &otherArray = dynamic_cast<const ArrayType &>(other);
    return (*otherArray.baseType.lock() == *baseType.lock()) &&
           (otherArray.dimensions.size() == dimensions.size());
  } catch (bad_cast) {
    return false;
  }
}
} // namespace EN