#include "ArrayType.h"

#include "TypeVisitor.h"

namespace EN
{
    void ArrayType::accept(TypeVisitor &visit) const
    {
        visit.visit(*this);
    };

    ArrayType::~ArrayType() {}
    ArrayType::ArrayType(const std::weak_ptr<Type> baseType, std::vector<std::shared_ptr<Expr>> dimensions)
        : baseType{baseType}, dimensions{dimensions}
    {
    }

}