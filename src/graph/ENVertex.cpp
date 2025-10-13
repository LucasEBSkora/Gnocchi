#include "ENVertex.h"

namespace EN {
using namespace std;
Vertex::Vertex(const weak_ptr<Type> type, const string id,
               const Visibility visibility,
               const vector<NotificationParameter> notificationParameters,
               const shared_ptr<Expr> stateExpr, bool boundState,
               const vector<string> interfaces,
               const shared_ptr<Expr> initialValue, const int allowedOperations,
               const shared_ptr<Expr> defaultWhen,
               const shared_ptr<Expr> defaultWith,
               const vector<shared_ptr<Edge>> bodyEdges)
    : type{type}, id{id}, visibility{visibility},
      notificationParameters{notificationParameters}, stateExpr{stateExpr},
      boundState{boundState}, interfaces{interfaces},
      initialValue{initialValue}, allowedOperations{allowedOperations},
      defaultWhen{defaultWhen}, defaultWith{defaultWith}, bodyEdges{bodyEdges} {
}

Vertex::~Vertex() {}

const vector<shared_ptr<Edge>> Vertex::getEdges() const { return bodyEdges; }

bool Vertex::operationAllowed(AllowedOperations op) const {
  return allowedOperations & int(op);
}

} // namespace EN