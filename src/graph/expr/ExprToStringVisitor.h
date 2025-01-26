#pragma once

#include <sstream>

#include "ExprVisitor.h"
#include "ENOperators.h"

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
        virtual void visit(const UnaryExpr &expr);
        virtual void visit(const BinaryExpr &expr);

        virtual std::string opToString(Operator op);

    private:
        stringstream ss;
    };
}