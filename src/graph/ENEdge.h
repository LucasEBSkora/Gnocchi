#pragma once

#include <ENExpr.h>
#include <memory>

namespace EN {
using namespace std;
class Edge {
public:
  Edge(shared_ptr<Expr> source, shared_ptr<Expr> destination,
       shared_ptr<Expr> when, shared_ptr<Expr> with);
  shared_ptr<Expr> source;
  shared_ptr<Expr> destination;
  shared_ptr<Expr> when;
  shared_ptr<Expr> with;
};
} // namespace EN