#include "ENEdge.h"

namespace EN {
Edge::Edge(shared_ptr<Expr> source, shared_ptr<Expr> destination,
           shared_ptr<Expr> when, shared_ptr<Expr> with)
    : source{source}, destination{destination}, when{when}, with{with} {}
} // namespace EN