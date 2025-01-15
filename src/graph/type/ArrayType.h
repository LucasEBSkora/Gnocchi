#pragma once

#include "ENType.h"

#include <vector>
#include <memory>

namespace EN
{
    class ArrayType : public Type
    {
    public:
        virtual void accept(TypeVisitor &visit) const override;
        virtual ~ArrayType();
        ArrayType(const std::weak_ptr<Type> baseType, std::vector<unsigned int> dimensions);

        const std::weak_ptr<Type> &baseType;
        const std::vector<unsigned int> dimensions;
    };

}