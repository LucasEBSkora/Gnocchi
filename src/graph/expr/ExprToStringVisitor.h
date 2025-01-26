#pragma once

#include <sstream>

#include "ExprVisitor.h"

namespace EN
{
    using namespace std;
    class ExprToStringVisitor : public ExprVisitor
    {
    public:
        virtual ~ExprToStringVisitor();
        virtual const string getResult();
        virtual void visit(const LiteralExpr &expr);
        virtual void visit(const NotifyExpr &expr);
        virtual void visit(const VertexAccessExpr &expr);

    private:
        stringstream ss;
    };
}