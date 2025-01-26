#include "ExprToStringVisitor.h"
#include "LiteralExpr.h"
#include "NotifyExpr.h"
#include "VertexAccessExpr.h"

namespace EN
{
    ExprToStringVisitor::~ExprToStringVisitor() {}

    const string ExprToStringVisitor::getResult()
    {
        return ss.str();
    }
    void ExprToStringVisitor::visit(const LiteralExpr &expr)
    {

        switch (expr.getLiteralType())
        {
        case LiteralExpr::INT:
            ss << expr.getInt();
            break;
        case LiteralExpr::FLOAT:
            ss << expr.getFloat() << 'f';
            break;
        case LiteralExpr::DOUBLE:
            ss << expr.getDouble();
            break;
        case LiteralExpr::CHAR:
            ss << expr.getChar();
            break;
        case LiteralExpr::STRING:
            ss << '"' << expr.getString() << '"';
            break;
        case LiteralExpr::BOOL:
            ss << (expr.getBool() ? "true" : "false");
            break;

        default:
            break;
        }
    }

    void ExprToStringVisitor::visit(const NotifyExpr &expr)
    {

        ss << "( ";
        for (auto param : expr.params)
        {
            param->accept(*this);
            ss << ' ';
        }
        ss << ") -> ";
        expr.target->accept(*this);
    }

    void ExprToStringVisitor::visit(const VertexAccessExpr &expr)
    {
        ss << expr.id;
    }
}