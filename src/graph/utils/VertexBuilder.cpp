#include "VertexBuilder.h"

namespace EN {
VertexBuilder::VertexBuilder() : allowedOperations{AllowedOperations::ALL} {}

VertexBuilder &VertexBuilder::setType(weak_ptr<Type> type) {
  this->type = type;
  return *this;
}

VertexBuilder &VertexBuilder::setId(string id) {
  this->id = id;
  return *this;
}

VertexBuilder &VertexBuilder::setVisibility(Visibility visibility) {
  this->visibility = visibility;
  return *this;
}

VertexBuilder &VertexBuilder::addNotificationParameter(NotificationParameter notificationParameter) {
  notificationParameters.push_back(notificationParameter);
  return *this;
}

VertexBuilder &VertexBuilder::setStateExpr(shared_ptr<Expr> stateExpr) {
  this->stateExpr = std::move(stateExpr);
  return *this;
}

VertexBuilder &VertexBuilder::setBoundState(bool boundState) {
  this->boundState = boundState;
  return *this;
}

VertexBuilder &VertexBuilder::addInterface(string interface) {
  this->interfaces.push_back(interface);
  return *this;
}

VertexBuilder &VertexBuilder::setInitialValue(shared_ptr<Expr> initialValue) {
  this->initialValue = move(initialValue);
  return *this;
}

VertexBuilder &VertexBuilder::setEnabledOperations(AllowedOperations op) {
  this->allowedOperations = AllowedOperations::ALL & op;
  return *this;
}

VertexBuilder &VertexBuilder::setDisabledOperations(AllowedOperations op) {
  this->allowedOperations = AllowedOperations::ALL & ~op;
  return *this;
}

VertexBuilder &VertexBuilder::setDefaultWhen(shared_ptr<Expr> defaultWhen) {
  this->defaultWhen = move(defaultWhen);
  return *this;
}

VertexBuilder &VertexBuilder::setDefaultWith(shared_ptr<Expr> defaultWith) {
  this->defaultWith = move(defaultWith);
  return *this;
}

VertexBuilder &VertexBuilder::addBodyEdge(shared_ptr<Edge> edge) {
  bodyEdges.push_back(edge);
  return *this;
}

shared_ptr<Vertex> VertexBuilder::build() {
  return make_shared<Vertex>(type, id, visibility, notificationParameters, stateExpr, boundState, interfaces,
                             initialValue, allowedOperations, defaultWhen, defaultWith, bodyEdges);
}
} // namespace EN