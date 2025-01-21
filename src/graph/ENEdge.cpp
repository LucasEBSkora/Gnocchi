#include "ENEdge.h"

namespace EN
{
    Edge::Edge(std::shared_ptr<Expr> source, std::shared_ptr<Expr> destination,
               std::shared_ptr<Expr> when, std::shared_ptr<Expr> with)
        : source{source}, destination{destination}, when{when}, with{with}
    {
    }
}