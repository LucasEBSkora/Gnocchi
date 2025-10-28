#pragma once

#include <memory>
#include <optional>
#include <string>

#include "ENExpr.h"
#include "ENType.h"

namespace EN {
using namespace std;
class NotificationParameter {
public:
  string name;
  weak_ptr<Type> type;
  optional<shared_ptr<Expr>> defaultValue;
  NotificationParameter(const string name, weak_ptr<Type> type, shared_ptr<Expr> defaultValue);
  NotificationParameter(const string name, weak_ptr<Type> type);
  NotificationParameter();
};
} // namespace EN