#pragma once

#include <sstream>

#include "ExprVisitor.h"

namespace EN
{
    class ExprToStringVisitor : public ExprVisitor
    {
    public:
        virtual ~ExprToStringVisitor();
        virtual const std::string getResult();
        virtual void visit(const LiteralExpr &expr);

    private:
        std::stringstream ss;
    };
}