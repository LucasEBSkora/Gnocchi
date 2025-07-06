#pragma once

#include <string>
#include <map>

namespace EN
{
    using namespace std;

    class TypeVisitor;

    class Type
    {
    public:
        string toString() const;
        virtual void accept(TypeVisitor &visit) const = 0;
        virtual ~Type();
        virtual bool operator==(const Type& other) const = 0;
    };

}