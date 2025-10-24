#pragma once

#include <ENExpr.h>
#include <list>
#include <memory>

namespace EN {
using namespace std;
class Edge {
public:
  Edge(shared_ptr<Expr> source, shared_ptr<Expr> destination, shared_ptr<Expr> when, shared_ptr<Expr> with);
  shared_ptr<Expr> source;
  shared_ptr<Expr> destination;
  shared_ptr<Expr> when;
  shared_ptr<Expr> with;
  static list<shared_ptr<Edge>> createMultipleEdges(list<shared_ptr<Expr>> sources, list<shared_ptr<Expr>> destinations,
                                                    shared_ptr<Expr> when, shared_ptr<Expr> with);
};
} // namespace EN