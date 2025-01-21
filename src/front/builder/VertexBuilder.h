#pragma once

#include "ENGraph.h"
#include "ENType.h"
#include "ENEdge.h"
#include "ENVertex.h"
#include "NotificationParameter.h"
#include <memory>

using namespace EN;

namespace Gnocchi
{
    class VertexBuilder
    {
    public:
        VertexBuilder();
        VertexBuilder &setType(std::weak_ptr<Type> type);
        VertexBuilder &setId(std::string id);
        VertexBuilder &setVisibility(Visibility visibility);
        VertexBuilder &addNotificationParameter(NotificationParameter notificationParameter);
        VertexBuilder &setStateExpr(std::shared_ptr<Expr> stateExpr);
        VertexBuilder &addInterface(std::string interface);
        VertexBuilder &setInitialValue(std::shared_ptr<Expr> initialValue);
        VertexBuilder &enableAllOperations();
        VertexBuilder &disableAllOperations();
        VertexBuilder &toggleOperationEnabled(AllowedOperations op);
        VertexBuilder &setDefaultWhen(std::shared_ptr<Expr> defaultWhen);
        VertexBuilder &setDefaultWith(std::shared_ptr<Expr> defaultWith);
        VertexBuilder &addBodyEdge(std::shared_ptr<Edge> edge);

        std::shared_ptr<Vertex> build();

    private:
        std::weak_ptr<Type> type;
        std::string id;
        Visibility visibility;
        std::vector<NotificationParameter> notificationParameters;
        std::shared_ptr<Expr> stateExpr;
        std::vector<std::string> interfaces;
        std::shared_ptr<Expr> initialValue;
        int allowedOperations;
        std::shared_ptr<Expr> defaultWhen;
        std::shared_ptr<Expr> defaultWith;
        std::vector<std::shared_ptr<Edge>> bodyEdges;
    };

}