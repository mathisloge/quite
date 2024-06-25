#include "value_converters.hpp"
#include <QColor>
#include <QMetaType>
#include <quite/proto/types.pb.h>

namespace quite::probe
{
template <typename TBase, auto TFncPtr>
void register_trivial_converter()
{
    QMetaType::registerConverter<TBase, proto::Value>([](const TBase &value) {
        proto::Value cnv;
        std::invoke(TFncPtr, cnv, value);
        return cnv;
    });
}

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

    QMetaType::registerConverter<QString, proto::Value>([](const QString &value) {
        proto::Value cnv;
        *cnv.mutable_string_val() = value.toStdString();
        return cnv;
    });
}
} // namespace quite::probe
