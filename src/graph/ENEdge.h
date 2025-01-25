#pragma once

#include <memory>
#include <ENExpr.h>

namespace EN
{
    using namespace std;
    class Edge
    {
    public:
        Edge(shared_ptr<Expr> source, shared_ptr<Expr> destination, shared_ptr<Expr> when, shared_ptr<Expr> with);
        shared_ptr<Expr> source;
        shared_ptr<Expr> destination;
        shared_ptr<Expr> when;
        shared_ptr<Expr> with;
    };
}