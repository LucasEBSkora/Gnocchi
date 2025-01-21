#include "VertexBuilder.h"

namespace Gnocchi
{
    VertexBuilder::VertexBuilder() : allowedOperations{AllowedOperations::ALL} {}

    VertexBuilder &VertexBuilder::setType(std::weak_ptr<Type> type)
    {
        this->type = type;
        return *this;
    }

    VertexBuilder &VertexBuilder::setId(std::string id)
    {
        this->id = id;
        return *this;
    }

    VertexBuilder &VertexBuilder::setVisibility(Visibility visibility)
    {
        this->visibility = visibility;
        return *this;
    }

    VertexBuilder &VertexBuilder::addNotificationParameter(NotificationParameter notificationParameter)
    {
        notificationParameters.push_back(notificationParameter);
        return *this;
    }

    VertexBuilder &VertexBuilder::setStateExpr(std::shared_ptr<Expr> stateExpr)
    {
        this->stateExpr = std::move(stateExpr);
        return *this;
    }

    VertexBuilder &VertexBuilder::setBoundState(bool boundState)
    {
        this->boundState = boundState;
        return *this;
    }

    VertexBuilder &VertexBuilder::addInterface(std::string interface)
    {
        this->interfaces.push_back(interface);
        return *this;
    }

    VertexBuilder &VertexBuilder::setInitialValue(std::shared_ptr<Expr> initialValue)
    {
        this->initialValue = std::move(initialValue);
        return *this;
    }

    VertexBuilder &VertexBuilder::enableAllOperations()
    {
        this->allowedOperations = AllowedOperations::ALL;
        return *this;
    }

    VertexBuilder &VertexBuilder::disableAllOperations()
    {
        this->allowedOperations = 0;
        return *this;
    }

    VertexBuilder &VertexBuilder::toggleOperationEnabled(AllowedOperations op)
    {
        this->allowedOperations ^= int(op);
        return *this;
    }

    VertexBuilder &VertexBuilder::setDefaultWhen(std::shared_ptr<Expr> defaultWhen)
    {
        this->defaultWhen = std::move(defaultWhen);
        return *this;
    }

    VertexBuilder &VertexBuilder::setDefaultWith(std::shared_ptr<Expr> defaultWith)
    {
        this->defaultWith = std::move(defaultWith);
        return *this;
    }

    VertexBuilder &VertexBuilder::addBodyEdge(std::shared_ptr<Edge> edge)
    {
        bodyEdges.push_back(edge);
        return *this;
    }

    std::shared_ptr<Vertex> VertexBuilder::build()
    {
        return std::make_shared<Vertex>(type, id, visibility, notificationParameters, stateExpr, boundState, interfaces, initialValue, allowedOperations, defaultWhen, defaultWith, bodyEdges);
    }
}