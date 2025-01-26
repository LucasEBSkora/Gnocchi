#include "VertexAccessExpr.h"

#include "ExprVisitor.h"
#include "SemanticException.h"
namespace EN
{
    VertexAccessExpr::VertexAccessExpr(string id) : id{id} {}
    VertexAccessExpr::VertexAccessExpr(string id, weak_ptr<Scope> scope) : id{id}, scope{scope} {}
    VertexAccessExpr::~VertexAccessExpr() {}
    void VertexAccessExpr::accept(ExprVisitor &visit) const
    {
        visit.visit(*this);
    }

    weak_ptr<Vertex> VertexAccessExpr::getVertex()
    {
        if (vertex.expired())
        {
            resolve();
        }
        return vertex;
    }
    void VertexAccessExpr::resolve(weak_ptr<Vertex> vertex)
    {
        this->vertex = vertex;
    }

    void VertexAccessExpr::resolve()
    {
        if (scope.expired())
        {
            throw SemanticException("Vertex " + id + " can't be resolved automatically without knowing enclosing scope!");
        }
        this->vertex = scope.lock()->getVertex(id);
    }
}