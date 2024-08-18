#include "value_converters.hpp"
#include <QColor>
#include <QMetaType>
#include <QObject>
#include <QQmlListProperty>
#include <QQmlListReference>
#include <QQuickItem>
#include <quite/proto/types.pb.h>

#include <entt/meta/factory.hpp>
#include <entt/meta/meta.hpp>
namespace quite::probe
{
namespace
{
constexpr auto value_meta = QMetaType::fromType<proto::Value>();
}

template <typename TBase, auto TFncPtr>
void register_trivial_converter()
{
    QMetaType::registerConverter<TBase, proto::Value>([](const TBase &value) {
        proto::Value cnv;
        std::invoke(TFncPtr, cnv, value);
        return cnv;
    });
}

#define ADD_CLASS_MEMBER(member_name)                                                                                  \
    {                                                                                                                  \
        auto &&member_val = object_val->add_value();                                                                   \
        *member_val->mutable_name() = #member_name;                                                                    \
        auto &&read_member = value.member_name();                                                                      \
        QMetaType::convert(QMetaType::fromType<std::remove_cvref_t<decltype(read_member)>>(),                          \
                           &read_member,                                                                               \
                           value_meta,                                                                                 \
                           member_val->mutable_value());                                                               \
    }

#define ADD_CLASS_CONVERTER(class_name)                                                                                \
    QMetaType::registerConverter<class_name, proto::Value>([](const class_name &value) {                               \
    proto::Value cnv;                                                                                                  \
    auto &&object_val = cnv.mutable_class_val();                                                                       \
    *object_val->mutable_type_name() = #class_name;

#define END_CLASS_CONVERTER                                                                                            \
    return cnv;                                                                                                        \
    });

void register_converters()
{
    register_trivial_converter<float, &proto::Value::set_double_val>();
    register_trivial_converter<double, &proto::Value::set_double_val>();
    register_trivial_converter<bool, &proto::Value::set_bool_val>();
    register_trivial_converter<qint8, &proto::Value::set_int_val>();
    register_trivial_converter<qint16, &proto::Value::set_int_val>();
    register_trivial_converter<qint32, &proto::Value::set_int_val>();
    register_trivial_converter<qint64, &proto::Value::set_int_val>();
    register_trivial_converter<quint8, &proto::Value::set_int_val>();
    register_trivial_converter<quint16, &proto::Value::set_int_val>();
    register_trivial_converter<quint32, &proto::Value::set_int_val>();

    entt::meta<QColor>();

    QMetaType::registerConverter<QString, proto::Value>([](const QString &value) {
        proto::Value cnv;
        *cnv.mutable_string_val() = value.toStdString();
        return cnv;
    });

    QMetaType::registerConverter<QObjectList, proto::Value>([](const QObjectList &values) {
        proto::Value cnv;
        for (auto &&value : std::as_const(values))
        {
            cnv.mutable_array_val()->add_value()->mutable_object_val()->set_object_id(
                reinterpret_cast<std::uint64_t>(value));
        }
        return cnv;
    });

    ADD_CLASS_CONVERTER(QRect)
    ADD_CLASS_MEMBER(x);
    ADD_CLASS_MEMBER(y);
    ADD_CLASS_MEMBER(width);
    ADD_CLASS_MEMBER(height);
    END_CLASS_CONVERTER

    ADD_CLASS_CONVERTER(QRectF)
    ADD_CLASS_MEMBER(x);
    ADD_CLASS_MEMBER(y);
    ADD_CLASS_MEMBER(width);
    ADD_CLASS_MEMBER(height);
    END_CLASS_CONVERTER

    ADD_CLASS_CONVERTER(QPoint)
    ADD_CLASS_MEMBER(x);
    ADD_CLASS_MEMBER(y);
    END_CLASS_CONVERTER

    QMetaType::registerConverter<proto::Value, QRect>([](const proto::Value &value) -> std::optional<QRect> {
        if (not(value.has_class_val() and value.class_val().type_name() == "QRect"))
        {
            return std::nullopt;
        }
        auto &&class_val = value.class_val().value();

        QRect rect;

        {
            auto it = std::find_if(class_val.begin(), class_val.end(), [](auto &&kv) {
                return (kv.name() == "x" and kv.value().has_int_val());
            });
            if (it != class_val.end())
            {
                decltype(rect.x()) x{};
                QMetaType::convert(
                    value_meta, &it->value(), QMetaType::fromType<std::remove_cvref_t<decltype(x)>>(), &x);
                rect.setX(x);
            }
        }
    });
}
} // namespace quite::probe
