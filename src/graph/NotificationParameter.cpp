#include "NotificationParameter.h"

namespace EN
{
    NotificationParameter::NotificationParameter(const string name, weak_ptr<Type> type, weak_ptr<Expr> defaultValue) : name{name}, type{type}, defaultValue{defaultValue} {}
    NotificationParameter::NotificationParameter(const string name, weak_ptr<Type> type) : name{name}, type{type} {}
}