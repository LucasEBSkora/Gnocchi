#pragma once

#include "ENExpr.h"
#include "ENVertex.h"

#include <memory>
#include <string>

namespace EN {
class Scope;

class VertexAccessExpr : public Expr {
public:
  VertexAccessExpr(string id, Scope &scope);
  ~VertexAccessExpr();
  virtual void accept(ExprVisitor &visit) const override;
  const string id;
  weak_ptr<Vertex> getVertex();
  void resolve(weak_ptr<Vertex> vertex);

private:
  void resolve();
  Scope &scope;
  weak_ptr<Vertex> vertex;
};
} // namespace EN