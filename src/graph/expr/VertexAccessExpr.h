#pragma once

#include "ENExpr.h"
#include "ENVertex.h"
#include "ENScope.h"

#include <string>
#include <memory>

namespace EN
{

    class VertexAccessExpr : public Expr
    {
    public:
        VertexAccessExpr(string id);
        VertexAccessExpr(string id, weak_ptr<Scope> scope);
        ~VertexAccessExpr();
        virtual void accept(ExprVisitor &visit) const override;
        const string id;
        weak_ptr<Vertex> getVertex();
        void resolve(weak_ptr<Vertex> vertex);

    private:
        void resolve();
        weak_ptr<Scope> scope;
        weak_ptr<Vertex> vertex;
    };
}