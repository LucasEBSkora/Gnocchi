#pragma once

#include "ENEdge.h"
#include "ENGraphCommon.h"
#include "ENType.h"
#include "ENVertex.h"
#include "NotificationParameter.h"
#include <memory>

namespace EN {
using namespace std;

class VertexBuilder {
public:
  VertexBuilder();
  VertexBuilder &setType(weak_ptr<Type> type);
  VertexBuilder &setId(string id);
  VertexBuilder &setVisibility(Visibility visibility);
  VertexBuilder &
  addNotificationParameter(NotificationParameter notificationParameter);
  VertexBuilder &setStateExpr(shared_ptr<Expr> stateExpr);
  VertexBuilder &setBoundState(bool boundState);
  VertexBuilder &addInterface(string interface);
  VertexBuilder &setInitialValue(shared_ptr<Expr> initialValue);
  VertexBuilder &enableAllOperations();
  VertexBuilder &disableAllOperations();
  VertexBuilder &toggleOperationEnabled(AllowedOperations op);
  VertexBuilder &setDefaultWhen(shared_ptr<Expr> defaultWhen);
  VertexBuilder &setDefaultWith(shared_ptr<Expr> defaultWith);
  VertexBuilder &addBodyEdge(shared_ptr<Edge> edge);

  shared_ptr<Vertex> build();

private:
  weak_ptr<Type> type;
  string id;
  Visibility visibility;
  vector<NotificationParameter> notificationParameters;
  shared_ptr<Expr> stateExpr;
  bool boundState;
  vector<string> interfaces;
  shared_ptr<Expr> initialValue;
  int allowedOperations;
  shared_ptr<Expr> defaultWhen;
  shared_ptr<Expr> defaultWith;
  vector<shared_ptr<Edge>> bodyEdges;
};

} // namespace EN