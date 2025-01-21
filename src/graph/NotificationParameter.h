#pragma once

#include <string>
#include <memory>
#include <optional>

#include "ENExpr.h"
#include "ENType.h"

namespace EN
{

    class NotificationParameter
    {
    public:
        const std::string name;
        const std::weak_ptr<Type> type;
        const std::optional<std::weak_ptr<Expr>> defaultValue;
        NotificationParameter(const std::string name, std::weak_ptr<Type> type, std::weak_ptr<Expr> defaultValue);
        NotificationParameter(const std::string name, std::weak_ptr<Type> type);
    };
}