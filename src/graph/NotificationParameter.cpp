#include "NotificationParameter.h"

namespace EN
{
    NotificationParameter::NotificationParameter(const std::string name, std::weak_ptr<Type> type, std::weak_ptr<Expr> defaultValue) : name{name}, type{type}, defaultValue{defaultValue} {}
    NotificationParameter::NotificationParameter(const std::string name, std::weak_ptr<Type> type) : name{name}, type{type} {}
}