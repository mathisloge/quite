// SPDX-FileCopyrightText: 2025 Mathis Logemann <mathis@quite.rocks>
//
// SPDX-License-Identifier: MIT

#include <QEventLoop>
#include <QObject>
#include <QString>
#include <boost/ut.hpp>
#include <fmt/base.h>
#include <fmt/std.h>
#include <quite/error.hpp>
#include <quite/meta_any_formatter.hpp>
#include <quite/value/object_query.hpp>
#include "method_invoker.hpp"

using namespace quite;
using namespace quite::probe;
using namespace boost::ut;
using namespace std::literals::string_view_literals;

namespace
{
class TestObject : public QObject
{
    Q_OBJECT
  public:
    Q_INVOKABLE int add(int a, int b) // NOLINT
    {
        return a + b;
    }
    Q_INVOKABLE void setValue(int v) // NOLINT
    {
        value = v;
    }
    Q_INVOKABLE int getValue() const // NOLINT
    {
        return value;
    }
    Q_INVOKABLE QString echo(const QString &s) // NOLINT
    {
        return s;
    }
    int value{0};
};
} // namespace

static suite<"qtprobe methodinvoker"> _ = [] { // NOLINT
    "invoke int add(int,int)"_test = [] {
        MethodInvoker invoker;

        TestObject obj;
        entt::meta_any obj_any = static_cast<QObject *>(&obj);
        std::vector<entt::meta_any> params = {entt::forward_as_meta(1), entt::forward_as_meta(2)};
        auto result = invoker.invoke_method(obj_any, "add(int,int)", params);

        expect(result.has_value());
        expect(result->cast<int>() == 3);
    };

    "invoke void setValue(int) and getValue"_test = [] {
        MethodInvoker invoker;

        TestObject obj;
        entt::meta_any obj_any = static_cast<QObject *>(&obj);
        std::vector<entt::meta_any> params = {42};
        auto set_result = invoker.invoke_method(obj_any, "setValue(int)", params);

        expect(set_result.has_value());

        std::vector<entt::meta_any> get_params;
        auto get_result = invoker.invoke_method(obj_any, "getValue()", get_params);

        expect(get_result.has_value());
        expect(get_result->cast<int>() == 42);
    };

    "invoke QString echo(QString)"_test = [] {
        MethodInvoker invoker;

        TestObject obj;
        entt::meta_any obj_any = static_cast<QObject *>(&obj);
        std::vector<entt::meta_any> params = {std::string{"hello"}};
        auto result = invoker.invoke_method(obj_any, "echo(QString)", params);

        expect(result.has_value());
        expect(result->cast<QString>().toStdString() == "hello"sv);
    };

    "invoke with wrong method name returns error"_test = [] {
        MethodInvoker invoker;

        TestObject obj;
        entt::meta_any obj_any = static_cast<QObject *>(&obj);
        std::vector<entt::meta_any> params;
        auto result = invoker.invoke_method(obj_any, "doesNotExist()", params);

        expect(!result.has_value());
        expect(result.error().code == ErrorCode::invalid_argument);
    };

    "invoke with wrong argument count returns error"_test = [] {
        MethodInvoker invoker;

        TestObject obj;
        entt::meta_any obj_any = static_cast<QObject *>(&obj);
        std::vector<entt::meta_any> params = {1}; // add(int,int) expects 2
        auto result = invoker.invoke_method(obj_any, "add(int,int)", params);

        expect(!result.has_value());
        expect(result.error().code == ErrorCode::failed_precondition);
    };
};

#include "test_method_invoker.moc"
