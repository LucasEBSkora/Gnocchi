#include "ArrayType.h"

#include "TypeVisitor.h"

namespace EN
{
    void ArrayType::accept(TypeVisitor &visit) const
    {
        visit.visit(*this);
    };

    ArrayType::~ArrayType() {}
    ArrayType::ArrayType(const Type &baseType, std::vector<unsigned int> dimensions)
        : baseType{baseType}, dimensions{dimensions} {}

}