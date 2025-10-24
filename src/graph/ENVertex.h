#pragma once

#include "ENEdge.h"
#include "ENGraphCommon.h"
#include "ENType.h"
#include "NotificationParameter.h"

#include <memory>
#include <vector>

namespace EN {
using namespace std;
enum AllowedOperations : int { NONE = 0, READ = 1, LISTEN = 2, NOTIFY = 4, ALL = 7 };

class Vertex {
public:
  Vertex(const weak_ptr<Type> type, const string id, const Visibility visibility,
         const vector<NotificationParameter> notificationParameters, const shared_ptr<Expr> stateExpr, bool boundState,
         const vector<string> interfaces, const shared_ptr<Expr> initialValue, const int allowedOperations,
         const shared_ptr<Expr> defaultWhen, const shared_ptr<Expr> defaultWith,
         const vector<shared_ptr<Edge>> bodyEdges);

  ~Vertex();

  const weak_ptr<Type> type;
  const string id;
  const Visibility visibility;
  const vector<NotificationParameter> notificationParameters;
  const shared_ptr<Expr> stateExpr;
  bool boundState;
  const vector<string> interfaces;
  const shared_ptr<Expr> initialValue;
  const int allowedOperations;
  const shared_ptr<Expr> defaultWhen;
  const shared_ptr<Expr> defaultWith;

  const vector<shared_ptr<Edge>> getEdges() const;
  bool operationAllowed(AllowedOperations op) const;

private:
  const vector<shared_ptr<Edge>> bodyEdges;
};
} // namespace EN
