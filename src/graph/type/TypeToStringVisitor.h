#pragma once

#include <sstream>

#include "TypeVisitor.h"

namespace EN {
using namespace std;
class TypeToStringVisitor : public TypeVisitor {
public:
  virtual ~TypeToStringVisitor();
  virtual const string getResult();
  virtual void visit(const PrimitiveType &type) override;
  virtual void visit(const ArrayType &type) override;

private:
  stringstream ss;
};
} // namespace EN
