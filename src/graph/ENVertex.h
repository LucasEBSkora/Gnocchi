#pragma once

#include "ENGraphCommon.h"
#include "ENType.h"
#include "ENEdge.h"
#include "NotificationParameter.h"

#include <vector>
#include <optional>
#include <memory>

namespace EN
{
    enum AllowedOperations
    {
        NONE = 0,
        READ = 1,
        WRITE = 2,
        NOTIFY = 4,
        ALL = 7
    };

    class Vertex
    {
    public:
        Vertex(
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
            const std::vector<std::shared_ptr<Edge>> bodyEdges);

        ~Vertex();

        const std::weak_ptr<Type> type;
        const std::string id;
        const Visibility visibility;
        const std::vector<NotificationParameter> notificationParameters;
        const std::shared_ptr<Expr> stateExpr;
        bool boundState;
        const std::vector<std::string> interfaces;
        const std::shared_ptr<Expr> initialValue;
        const int allowedOperations;
        const std::shared_ptr<Expr> defaultWhen;
        const std::shared_ptr<Expr> defaultWith;

        const std::vector<std::shared_ptr<Edge>> getEdges() const;

    private:
        const std::vector<std::shared_ptr<Edge>> bodyEdges;
    };
}
