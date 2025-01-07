#include "PrimitiveType.h"

#include <sstream>

#include <TypeVisitor.h>

namespace EN
{

    std::map<PrimitiveType::Primitive, PrimitiveType> PrimitiveType::flyweightMap;

    const PrimitiveType &PrimitiveType::getPrimitiveType(Primitive value)
    {
        if (flyweightMap.find(value) == flyweightMap.end())
            flyweightMap.insert({value, PrimitiveType{value}});

        return flyweightMap.at(value);
    }

    void PrimitiveType::accept(TypeVisitor &visit) const
    {
        visit.visit(*this);
    }

    PrimitiveType::~PrimitiveType()
    {
    }

    PrimitiveType::PrimitiveType(Primitive value) : value{value} {}
}