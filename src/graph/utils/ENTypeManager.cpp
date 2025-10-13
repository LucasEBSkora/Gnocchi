#include "ENTypeManager.h"

#include "ArrayType.h"

namespace EN {
weak_ptr<Type> TypeManager::addArrayType(const weak_ptr<Type> baseType,
                                         vector<shared_ptr<Expr>> dimensions) {
  shared_ptr<Type> newType = make_shared<ArrayType>(baseType, dimensions);
  for (shared_ptr<Type> type : storedTypes) {
    if (*newType == *type) {
      return type;
    }
  }

  storedTypes.push_back(newType);
  return newType;
}
} // namespace EN