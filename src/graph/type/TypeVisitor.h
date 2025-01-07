#pragma once

namespace EN
{
    class PrimitiveType;
    class ArrayType;

    class TypeVisitor
    {
    public:
        virtual void visit(const PrimitiveType &type) = 0;
        virtual void visit(const ArrayType &type) = 0;
    };
} // namespace EN
