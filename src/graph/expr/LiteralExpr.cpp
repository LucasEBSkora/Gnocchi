#include "LiteralExpr.h"
#include "ExprVisitor.h"

namespace EN {
LiteralExpr::LiteralExpr(LiteralVariant value) : value{value} {}
LiteralExpr::~LiteralExpr() {}

LiteralExpr::Literal LiteralExpr::getLiteralType() const {
  return (LiteralExpr::Literal)value.index();
}

long long LiteralExpr::getInt() const { return std::get<long long>(value); }
float LiteralExpr::getFloat() const { return std::get<float>(value); }
double LiteralExpr::getDouble() const { return std::get<double>(value); }
char LiteralExpr::getChar() const { return std::get<char>(value); }
string LiteralExpr::getString() const { return std::get<string>(value); }
bool LiteralExpr::getBool() const { return std::get<bool>(value); }
const LiteralVariant &LiteralExpr::get() const { return value; }
void LiteralExpr::accept(ExprVisitor &visit) const { visit.visit(*this); }

} // namespace EN