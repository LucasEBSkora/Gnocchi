#pragma once

#include <string>

namespace EN
{
    class ExprVisitor;

    class Expr
    {
    public:
        std::string toString() const;
        virtual void accept(ExprVisitor &visit) const = 0;
        virtual ~Expr();
    };
}