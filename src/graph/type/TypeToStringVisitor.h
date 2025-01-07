#pragma once

#include <sstream>

#include "TypeVisitor.h"

namespace EN
{
    class TypeToStringVisitor : public TypeVisitor
    {
    public:
        virtual ~TypeToStringVisitor();
        virtual const std::string getResult();
        virtual void visit(const PrimitiveType &type) override;
        virtual void visit(const ArrayType &type) override;

    private:
        std::stringstream ss;
    };
}
