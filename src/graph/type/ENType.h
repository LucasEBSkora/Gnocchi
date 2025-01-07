#ifndef __EN_TYPE_H__
#define __EN_TYPE_H__

#include <string>
#include <map>

namespace EN
{
    class TypeVisitor;

    class Type
    {
    public:
        virtual std::string toString() const;
        virtual void accept(TypeVisitor &visit) const = 0;
        virtual ~Type();
    };

}
#endif