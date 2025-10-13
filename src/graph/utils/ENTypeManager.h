#pragma once

#include <memory>
#include <vector>

#include "ENType.h"
#include "ENExpr.h"

namespace EN {
using namespace std;
class TypeManager {
public:
  weak_ptr<Type> addArrayType(const weak_ptr<Type> baseType,
                              vector<shared_ptr<Expr>> dimensions);

private:
  vector<shared_ptr<Type>> storedTypes;
};
} // namespace EN