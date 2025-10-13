#pragma once

#include "ENExpr.h"

#include <memory>
#include <vector>

namespace EN {

class NotifyExpr : public Expr {
public:
  NotifyExpr(vector<shared_ptr<Expr>> params, shared_ptr<Expr> target);
  ~NotifyExpr();
  virtual void accept(ExprVisitor &visit) const override;

  vector<shared_ptr<Expr>> params;
  shared_ptr<Expr> target;
};
} // namespace EN