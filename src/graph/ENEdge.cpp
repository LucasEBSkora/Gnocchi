#include "ENEdge.h"
#include "ENExpr.h"
#include <memory>

namespace EN {
Edge::Edge(shared_ptr<Expr> source, shared_ptr<Expr> destination, shared_ptr<Expr> when, shared_ptr<Expr> with)
    : source{source}, destination{destination}, when{when}, with{with} {}

list<shared_ptr<Edge>> Edge::createMultipleEdges(list<shared_ptr<Expr>> sources, list<shared_ptr<Expr>> destinations,
                                                 shared_ptr<Expr> when, shared_ptr<Expr> with) {
  list<shared_ptr<Edge>> edges;
  for (shared_ptr<Expr> source : sources) {
    for (shared_ptr<Expr> destination : destinations) {
      edges.push_back(make_shared<Edge>(source, destination, when, with));
    }
  }
  return edges;
}
} // namespace EN
