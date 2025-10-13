#pragma once

#include "ENExpr.h"
#include "ENOperators.h"

#include <memory>

namespace EN {
class BinaryExpr : public Expr {
public:
  BinaryExpr(shared_ptr<Expr> left, Operator op, shared_ptr<Expr> right);
  ~BinaryExpr();
  virtual void accept(ExprVisitor &visit) const override;
  const shared_ptr<Expr> left;
  const Operator op;
  const shared_ptr<Expr> right;
};
} // namespace EN