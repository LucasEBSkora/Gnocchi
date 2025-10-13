#include "ENExpr.h"

#include "ExprToStringVisitor.h"

namespace EN {

Expr::~Expr() {}

string Expr::toString() const {
  ExprToStringVisitor visitor;
  this->accept(visitor);
  return visitor.getResult();
}

} // namespace EN