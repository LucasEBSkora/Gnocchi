#pragma once

namespace EN
{
    class PrimitiveType;

    class TypeVisitor
    {
    public:
        virtual void visit(const PrimitiveType &type) = 0;
    };
} // namespace EN
