// SPDX-FileCopyrightText: 2025 Mathis Logemann <mathis@quite.rocks>
//
// SPDX-License-Identifier: MIT

#include <QMap>
#include <QObject>
#include <catch2/catch_test_macros.hpp>
#include <quite/logger.hpp>
#include <quite/setup_logger.hpp>
#include "qt_meta_registry.hpp"

using namespace quite;
using namespace quite::probe;

DEFINE_LOGGER(test);

class MyTestClassMetaRegistry : public QObject
{
    Q_OBJECT

  public Q_SLOTS:
    quint64 compute(quint64 val1, quint8 val2)
    {
        return val1 + val2;
    }

    double compute(float val1, qint8 val2)
    {
        return val1 * static_cast<float>(val2);
    }
};

namespace my_meta_namespace
{
Q_NAMESPACE

enum class SomeMetaEnum
{
    unknown = 0,
    value1 = 1,
    value100 = 100,
    valuem1 = -1
};
Q_ENUM_NS(SomeMetaEnum);
} // namespace my_meta_namespace

TEST_CASE("Test QtMetaRegistry", "[meta]")
{
    setup_logger();
    QtMetaRegistry meta_registry;
    SECTION("Lookup QObject type by id")
    {
        stdexec::sync_wait([&]() -> exec::task<void> {
            const auto lookup_result =
                co_await meta_registry.lookup_type(QMetaType::fromType<MyTestClassMetaRegistry>().id());
            REQUIRE(lookup_result.has_value());
            REQUIRE(std::holds_alternative<meta::ObjectTypePtr>(*lookup_result));
            auto &&meta_obj = std::get<meta::ObjectTypePtr>(*lookup_result);
            REQUIRE(meta_obj != nullptr);
            LOG_DEBUG(test(), "Object {}", fmt::format("{}", *meta_obj));
            REQUIRE(meta_obj->name == "MyTestClassMetaRegistry");
            REQUIRE(meta_obj->id == QMetaType::fromType<MyTestClassMetaRegistry>().id());
            REQUIRE(meta_obj->properties.size() == 1);
            REQUIRE(meta_obj->properties[0].name == "objectName");
            REQUIRE(std::ranges::find_if(meta_obj->methods, [](auto &&method) {
                        return method.name == "compute(qulonglong,uchar)";
                    }) != meta_obj->methods.end());
            REQUIRE(std::ranges::find_if(meta_obj->methods, [](auto &&method) {
                        return method.name == "compute(float,signed char)";
                    }) != meta_obj->methods.end());
        }());
    }

    SECTION("Lookup Enum type by id")
    {
        stdexec::sync_wait([&]() -> exec::task<void> {
            const auto lookup_result =
                co_await meta_registry.lookup_type(QMetaType::fromType<my_meta_namespace::SomeMetaEnum>().id());
            if (not lookup_result.has_value())
            {
                LOG_ERROR(test(), "Error trying to fetch: {}", fmt::format("{}", lookup_result.error().message));
            }
            else
            {
                LOG_DEBUG(test(), "Object {}", fmt::format("{}", *lookup_result));
            }
            REQUIRE(lookup_result.has_value());
            REQUIRE(std::holds_alternative<meta::EnumTypePtr>(*lookup_result));
            auto &&meta_enum = std::get<meta::EnumTypePtr>(*lookup_result);
            REQUIRE(meta_enum != nullptr);
            REQUIRE(meta_enum->id == QMetaType::fromType<my_meta_namespace::SomeMetaEnum>().id());
            REQUIRE(meta_enum->name == "my_meta_namespace::SomeMetaEnum");
            REQUIRE(meta_enum->values.size() == 4);
            REQUIRE(meta_enum->values.contains("valuem1"));
            REQUIRE(meta_enum->values["valuem1"] == -1);
            REQUIRE(meta_enum->values.contains("value1"));
            REQUIRE(meta_enum->values["value1"] == 1);
            REQUIRE(meta_enum->values.contains("value100"));
            REQUIRE(meta_enum->values["value100"] == 100);
            REQUIRE(meta_enum->values.contains("unknown"));
            REQUIRE(meta_enum->values["unknown"] == 0);
        }());
    }

    SECTION("Lookup List type by id")
    {
        using TestListType = QVector<double>;
        constexpr auto kTestType = QMetaType::fromType<TestListType>();
        stdexec::sync_wait([&]() -> exec::task<void> {
            const auto lookup_result = co_await meta_registry.lookup_type(QMetaType::fromType<TestListType>().id());
            if (not lookup_result.has_value())
            {
                LOG_ERROR(test(), "Error trying to fetch: {}", fmt::format("{}", lookup_result.error().message));
            }
            else
            {
                LOG_DEBUG(test(), "Object {}", fmt::format("{}", *lookup_result));
            }
            REQUIRE(lookup_result.has_value());
            REQUIRE(std::holds_alternative<meta::ListType>(*lookup_result));
            auto &&meta_list = std::get<meta::ListType>(*lookup_result);
            REQUIRE(meta_list.name == "QList<double>");
            REQUIRE(meta_list.id == kTestType.id());
            REQUIRE(meta_list.value_type == QMetaType::fromType<double>().id());
        }());
    }

    SECTION("Lookup Map type by id")
    {
        using TestListType = QMap<QString, int>;
        constexpr auto kTestType = QMetaType::fromType<TestListType>();
        stdexec::sync_wait([&]() -> exec::task<void> {
            const auto lookup_result = co_await meta_registry.lookup_type(kTestType.id());
            if (not lookup_result.has_value())
            {
                LOG_ERROR(test(), "Error trying to fetch: {}", fmt::format("{}", lookup_result.error().message));
            }
            else
            {
                LOG_DEBUG(test(), "Object {}", fmt::format("{}", *lookup_result));
            }
            REQUIRE(lookup_result.has_value());
            REQUIRE(std::holds_alternative<meta::MapType>(*lookup_result));
            auto &&meta_map = std::get<meta::MapType>(*lookup_result);
            REQUIRE(meta_map.name == "QMap<QString,int>");
            REQUIRE(meta_map.id == kTestType.id());
            REQUIRE(meta_map.key_type == QMetaType::fromType<QString>().id());
            REQUIRE(meta_map.value_type == QMetaType::fromType<int>().id());
        }());
    }

    SECTION("Lookup primitive build in type by id")
    {
        using TestListType = QMap<QString, int>;
        constexpr auto kTestType = QMetaType::Void;
        stdexec::sync_wait([&]() -> exec::task<void> {
            const auto lookup_result = co_await meta_registry.lookup_type(kTestType);
            if (not lookup_result.has_value())
            {
                LOG_ERROR(test(), "Error trying to fetch: {}", fmt::format("{}", lookup_result.error().message));
            }
            else
            {
                LOG_DEBUG(test(), "Object {}", fmt::format("{}", *lookup_result));
            }
            REQUIRE(lookup_result.has_value());
            REQUIRE(std::holds_alternative<meta::PrimitiveType>(*lookup_result));
            auto &&meta_primitive = std::get<meta::PrimitiveType>(*lookup_result);
            REQUIRE(meta_primitive == meta::PrimitiveType::type_void);
        }());
    }
}
#include "test_qt_meta_registry.moc"
