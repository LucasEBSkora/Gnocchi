#include "ExprToStringVisitor.h"
#include "LiteralExpr.h"
#include "NotifyExpr.h"
#include "VertexAccessExpr.h"
#include "UnaryExpr.h"
#include "BinaryExpr.h"

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

    void ExprToStringVisitor::visit(const BinaryExpr &expr)
    {
        expr.left->accept(*this);
        ss << ' ' << opToString(expr.op) << ' ';
        expr.right->accept(*this);
    }

    void ExprToStringVisitor::visit(const UnaryExpr &expr)
    {
        if (expr.dir == UnaryExpr::LEFT)
        {
            ss << opToString(expr.op);
            expr.operand->accept(*this);
        }
        else
        {
            expr.operand->accept(*this);
            ss << opToString(expr.op);
        }
    }

    string ExprToStringVisitor::opToString(Operator op)
    {
        switch (op)
        {
        case Operator::HOLON_OP:
            return "<>";
        case Operator::ASSIGN:
            return ":=";
        case Operator::ASSIGN_PLUS:
            return "+=";
        case Operator::ASSIGN_MINUS:
            return "-=";
        case Operator::ASSIGN_MUL:
            return "*=";
        case Operator::ASSIGN_DIV:
            return "/=";
        case Operator::ASSIGN_MOD:
            return "%=";
        case Operator::ASSIGN_AND:
            return "&=";
        case Operator::ASSIGN_OR:
            return "|=";
        case Operator::ASSIGN_XOR:
            return "^=";
        case Operator::LOGIC_OR:
            return "||";
        case Operator::LOGIC_XOR:
            return "^^";
        case Operator::LOGIC_AND:
            return "&&";
        case Operator::BINARY_OR:
            return "|";
        case Operator::BINARY_XOR:
            return "^";
        case Operator::BINARY_AND:
            return "&";
        case Operator::EQ:
            return "==";
        case Operator::NE:
            return "!=";
        case Operator::LT:
            return "<";
        case Operator::LE:
            return "<=";
        case Operator::GT:
            return ">";
        case Operator::GE:
            return ">=";
        case Operator::SHIFT_LEFT:
            return "<<";
        case Operator::SHIFT_RIGHT:
            return ">>";
        case Operator::PLUS:
            return "+";
        case Operator::MINUS:
            return "-";
        case Operator::MUL:
            return "*";
        case Operator::DIV:
            return "/";
        case Operator::MOD:
            return "%";
        case Operator::LOGIC_NOT:
            return "!";
        case Operator::BINARY_NOT:
            return "~";
        case Operator::INC:
            return "++";
        case Operator::DEC:
            return "--";
        default:
            return "";
        }
    }

}