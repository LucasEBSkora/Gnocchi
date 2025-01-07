#include "TypeToStringVisitor.h"

#include "PrimitiveType.h"
namespace EN
{

    TypeToStringVisitor::~TypeToStringVisitor() {}

    const std::string TypeToStringVisitor::getResult()
    {
        return ss.str();
    }
    void TypeToStringVisitor::visit(const PrimitiveType &type)
    {
        const char *stringValue;
        switch (type.value)
        {
        case PrimitiveType::INT8:
            stringValue = "int8";
            break;
        case PrimitiveType::INT16:
            stringValue = "int16";
            break;
        case PrimitiveType::INT24:
            stringValue = "int24";
            break;
        case PrimitiveType::INT32:
            stringValue = "int32";
            break;
        case PrimitiveType::INT:
            stringValue = "int";
            break;
        case PrimitiveType::UIT8:
            stringValue = "uit8";
            break;
        case PrimitiveType::UINT16:
            stringValue = "uint16";
            break;
        case PrimitiveType::UINT24:
            stringValue = "uint24";
            break;
        case PrimitiveType::UINT32:
            stringValue = "uint32";
            break;
        case PrimitiveType::UINT:
            stringValue = "uint";
            break;
        case PrimitiveType::FLOAT:
            stringValue = "float";
            break;
        case PrimitiveType::DOUBLE:
            stringValue = "double";
            break;
        case PrimitiveType::NUMBER:
            stringValue = "number";
            break;
        case PrimitiveType::BOOL:
            stringValue = "bool";
            break;
        case PrimitiveType::CHAR:
            stringValue = "char";
            break;
        default:
            break;
        }

        ss << stringValue;
    }
}