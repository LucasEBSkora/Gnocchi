#include "NotificationParameter.h"

namespace EN {
NotificationParameter::NotificationParameter(const string name, weak_ptr<Type> type, shared_ptr<Expr> defaultValue)
    : name{name}, type{type}, defaultValue{defaultValue} {}
NotificationParameter::NotificationParameter(const string name, weak_ptr<Type> type) : name{name}, type{type} {}
NotificationParameter::NotificationParameter() {}
} // namespace EN