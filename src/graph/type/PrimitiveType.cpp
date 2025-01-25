#include "PrimitiveType.h"

#include <sstream>

#include <TypeVisitor.h>

namespace EN
{
    using namespace std;

    map<PrimitiveType::Primitive, shared_ptr<PrimitiveType>> PrimitiveType::flyweightMap;

    const weak_ptr<PrimitiveType> PrimitiveType::getPrimitiveType(Primitive value)
    {
        if (flyweightMap.find(value) == flyweightMap.end())
            flyweightMap.emplace(value, make_shared<PrimitiveType>(value));

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