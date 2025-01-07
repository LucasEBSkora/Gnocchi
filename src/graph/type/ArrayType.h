#pragma once

#include "ENType.h"

#include <vector>

namespace EN
{
    class ArrayType : public Type
    {
    public:
        virtual void accept(TypeVisitor &visit) const override;
        virtual ~ArrayType();
        ArrayType(const Type &baseType, std::vector<unsigned int> dimensions);

        const Type &baseType;
        const std::vector<unsigned int> dimensions;
    };

}