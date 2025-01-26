#include "NotifyExpr.h"

#include "ExprVisitor.h"

namespace EN
{
    NotifyExpr::NotifyExpr(vector<shared_ptr<Expr>> params, shared_ptr<Expr> target) : params{params}, target{target}
    {
    }

    NotifyExpr::~NotifyExpr()
    {
    }

    void NotifyExpr::accept(ExprVisitor &visit) const
    {
        visit.visit(*this);
    }

}