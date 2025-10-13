#pragma once

#include "ENExpr.h"
#include "ENOperators.h"

#include <memory>

namespace EN {

class UnaryExpr : public Expr {
public:
  enum Direction { LEFT, RIGHT };
  UnaryExpr(Operator op, shared_ptr<Expr> operand, Direction dir);
  ~UnaryExpr();
  virtual void accept(ExprVisitor &visit) const override;
  const Operator op;
  const shared_ptr<Expr> operand;
  const Direction dir;
};
} // namespace EN