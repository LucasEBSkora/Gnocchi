#include "UnaryExpr.h"
#include "ExprVisitor.h"

namespace EN {
UnaryExpr::UnaryExpr(Operator op, shared_ptr<Expr> operand, Direction dir)
    : op{op}, operand{operand}, dir{dir} {}
UnaryExpr::~UnaryExpr() {}
void UnaryExpr::accept(ExprVisitor &visit) const { visit.visit(*this); }
} // namespace EN