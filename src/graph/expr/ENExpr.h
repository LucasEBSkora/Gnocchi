#pragma once

#include <string>

namespace EN {
using namespace std;

class ExprVisitor;

class Expr {
public:
  string toString() const;
  virtual void accept(ExprVisitor &visit) const = 0;
  virtual ~Expr();
};
} // namespace EN