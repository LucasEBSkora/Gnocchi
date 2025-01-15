#pragma once

namespace EN
{

    class LiteralExpr;

    class ExprVisitor
    {
    public:
        virtual void visit(const LiteralExpr &expr) = 0;
    };

}