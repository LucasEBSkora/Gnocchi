#include "VertexAccessExpr.h"

#include "ENScope.h"
#include "ExprVisitor.h"

namespace EN {
VertexAccessExpr::VertexAccessExpr(string id, Scope &scope)
    : id{id}, scope{scope} {}
VertexAccessExpr::~VertexAccessExpr() {}
void VertexAccessExpr::accept(ExprVisitor &visit) const { visit.visit(*this); }

weak_ptr<Vertex> VertexAccessExpr::getVertex() {
  if (vertex.expired()) {
    resolve();
  }
  return vertex;
}
void VertexAccessExpr::resolve(weak_ptr<Vertex> vertex) {
  this->vertex = vertex;
}

void VertexAccessExpr::resolve() { this->vertex = scope.getVertex(id); }
} // namespace EN