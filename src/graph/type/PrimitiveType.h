#ifndef __EN_PRIMITIVE_TYPE_H__
#define __EN_PRIMITIVE_TYPE_H__

#include <string>
#include <map>

#include "ENType.h"

namespace EN
{

    class PrimitiveType : public Type
    {
    public:
        enum Primitive
        {
            INT8,
            INT16,
            INT24,
            INT32,
            INT,
            UIT8,
            UINT16,
            UINT24,
            UINT32,
            UINT,
            FLOAT,
            DOUBLE,
            NUMBER,
            BOOL,
            CHAR,
        };

        static const PrimitiveType &getPrimitiveType(Primitive value);
        virtual void accept(TypeVisitor &visit) const override;
        virtual ~PrimitiveType();
        const Primitive value;

    private:
        PrimitiveType(Primitive value);
        static std::map<Primitive, PrimitiveType> flyweightMap;
    };

}
#endif