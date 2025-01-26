#include "BinaryExpr.h"

#include "ExprVisitor.h"

namespace EN
{
    BinaryExpr::BinaryExpr(shared_ptr<Expr> left, Operator op, shared_ptr<Expr> right) : left{left}, op{op}, right{right}
    {
    }

    BinaryExpr::~BinaryExpr()
    {
    }

    void BinaryExpr::accept(ExprVisitor &visit) const
    {
        visit.visit(*this);
    }

}