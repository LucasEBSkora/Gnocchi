#pragma once

namespace EN {

class LiteralExpr;
class NotifyExpr;
class VertexAccessExpr;
class UnaryExpr;
class BinaryExpr;

class ExprVisitor {
public:
  virtual void visit(const LiteralExpr &expr) = 0;
  virtual void visit(const NotifyExpr &expr) = 0;
  virtual void visit(const VertexAccessExpr &expr) = 0;
  virtual void visit(const UnaryExpr &expr) = 0;
  virtual void visit(const BinaryExpr &expr) = 0;
};

} // namespace EN