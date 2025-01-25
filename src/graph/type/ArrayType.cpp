#include "ArrayType.h"

#include "TypeVisitor.h"

namespace EN
{
    void ArrayType::accept(TypeVisitor &visit) const
    {
        visit.visit(*this);
    };

    ArrayType::~ArrayType() {}
    ArrayType::ArrayType(const weak_ptr<Type> baseType, vector<shared_ptr<Expr>> dimensions)
        : baseType{baseType}, dimensions{dimensions}
    {
    }

}