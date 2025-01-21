#include "ENVertex.h"

namespace EN
{

    Vertex::Vertex(
        const std::weak_ptr<Type> type,
        const std::string id,
        const Visibility visibility,
        const std::vector<NotificationParameter> notificationParameters,
        const std::shared_ptr<Expr> stateExpr,
        bool boundState,
        const std::vector<std::string> interfaces,
        const std::shared_ptr<Expr> initialValue,
        const int allowedOperations,
        const std::shared_ptr<Expr> defaultWhen,
        const std::shared_ptr<Expr> defaultWith,
        const std::vector<std::shared_ptr<Edge>> bodyEdges)
        : type{type}, id{id}, visibility{visibility},
          notificationParameters{notificationParameters}, stateExpr{stateExpr},
          boundState{boundState}, interfaces{interfaces}, initialValue{initialValue},
          allowedOperations{allowedOperations}, defaultWhen{defaultWhen},
          defaultWith{defaultWith}, bodyEdges{bodyEdges}
    {
    }

    Vertex::~Vertex()
    {
    }

    const std::vector<std::shared_ptr<Edge>> Vertex::getEdges() const
    {
        return bodyEdges;
    }

}