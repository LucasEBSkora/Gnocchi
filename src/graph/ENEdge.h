#pragma once

#include <memory>
#include <ENExpr.h>

namespace EN
{
    class Edge
    {
    public:
        Edge(std::shared_ptr<Expr> source, std::shared_ptr<Expr> destination, std::shared_ptr<Expr> when, std::shared_ptr<Expr> with);
        std::shared_ptr<Expr> source;
        std::shared_ptr<Expr> destination;
        std::shared_ptr<Expr> when;
        std::shared_ptr<Expr> with;
    };
}