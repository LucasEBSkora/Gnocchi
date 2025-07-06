#pragma once

#include "ENType.h"

#include <vector>
#include <memory>

#include "ENExpr.h"

namespace EN
{
    using namespace std;

    class ArrayType : public Type
    {
    public:
        virtual void accept(TypeVisitor &visit) const override;
        virtual ~ArrayType();
        ArrayType(const weak_ptr<Type> baseType, vector<shared_ptr<Expr>> dimensions);
        virtual bool operator==(const Type& other) const override;

        const weak_ptr<Type> &baseType;
        const vector<shared_ptr<Expr>> dimensions;
    };

}