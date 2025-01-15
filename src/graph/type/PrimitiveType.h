#pragma once

#include <string>
#include <map>
#include <memory>

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

        static const std::weak_ptr<PrimitiveType> getPrimitiveType(Primitive value);
        virtual void accept(TypeVisitor &visit) const override;
        virtual ~PrimitiveType();
        const Primitive value;
        // Public just so we can use make_shared on this without any tricks, not to be used
        PrimitiveType(Primitive value);

    private:
        static std::map<Primitive, std::shared_ptr<PrimitiveType>> flyweightMap;
    };

}