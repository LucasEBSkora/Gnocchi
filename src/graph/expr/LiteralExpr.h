#pragma once

#include "ENExpr.h"
#include <variant>

namespace EN {

using LiteralVariant = variant<long long, unsigned long long, float, double, char, string, bool>;

class LiteralExpr : public Expr {
public:
  enum Literal { INT = 0, UINT = 1, FLOAT = 2, DOUBLE = 3, CHAR = 4, STRING = 5, BOOL = 6 };

  LiteralExpr(LiteralVariant value);
  ~LiteralExpr();
  Literal getLiteralType() const;
  long long getInt() const;
  unsigned long long getUint() const;
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
} // namespace EN