#pragma once

#include <string>
#include <memory>
#include <optional>

#include "ENExpr.h"
#include "ENType.h"

namespace EN
{
    using namespace std;
    class NotificationParameter
    {
    public:
        const string name;
        const weak_ptr<Type> type;
        const optional<weak_ptr<Expr>> defaultValue;
        NotificationParameter(const string name, weak_ptr<Type> type, weak_ptr<Expr> defaultValue);
        NotificationParameter(const string name, weak_ptr<Type> type);
    };
}