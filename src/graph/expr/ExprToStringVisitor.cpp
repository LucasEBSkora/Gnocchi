#include "ExprToStringVisitor.h"
#include "LiteralExpr.h"

namespace EN
{
    ExprToStringVisitor::~ExprToStringVisitor() {}

    const std::string ExprToStringVisitor::getResult()
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
            ss << expr.getString();
            break;
        case LiteralExpr::BOOL:
            ss << (expr.getBool() ? "true" : "false");
            break;

        default:
            break;
        }
    }
}