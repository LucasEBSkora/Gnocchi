#pragma once

#include <string>
#include <map>

namespace EN
{
    class TypeVisitor;

    class Type
    {
    public:
        std::string toString() const;
        virtual void accept(TypeVisitor &visit) const = 0;
        virtual ~Type();
    };

}