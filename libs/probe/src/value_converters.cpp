#include "value_converters.hpp"
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
    register_trivial_converter<double, &proto::Value::set_double_val>();
    register_trivial_converter<bool, &proto::Value::set_bool_val>();

    QMetaType::registerConverter<QString, proto::Value>([](const QString &value) {
        proto::Value cnv;
        *cnv.mutable_string_val() = value.toStdString();
        return cnv;
    });
}
} // namespace quite::probe
