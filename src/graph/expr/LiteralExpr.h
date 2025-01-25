#pragma once

#include "ENExpr.h"
#include <variant>

namespace EN
{

    using LiteralVariant = variant<long long, float, double, char, string, bool>;

    class LiteralExpr : public Expr
    {
    public:
        enum Literal
        {
            INT = 0,
            FLOAT = 1,
            DOUBLE = 2,
            CHAR = 3,
            STRING = 4,
            BOOL = 5
        };

        LiteralExpr(LiteralVariant value);
        ~LiteralExpr();
        Literal getLiteralType() const;
        long long getInt() const;
        float getFloat() const;
        double getDouble() const;
        char getChar() const;
        string getString() const;
        bool getBool() const;
        const LiteralVariant &get() const;
        virtual void accept(ExprVisitor &visit) const override;

    private:
        const LiteralVariant value;
    };
}