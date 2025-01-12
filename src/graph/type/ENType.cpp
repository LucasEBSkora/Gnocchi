#include "ENType.h"

#include "TypeVisitor.h"
#include "TypeToStringVisitor.h"

#include <sstream>

namespace EN
{

    Type::~Type()
    {
    }

    std::string Type::toString() const
    {
        TypeToStringVisitor visitor;
        this->accept(visitor);
        return visitor.getResult();
    }

}