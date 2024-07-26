#include "grpc_value.hpp"
#include <ranges>
#include "grpc_remote_object.hpp"

namespace quite::grpc_impl
{
quite::Result<quite::Value> convert(const quite::proto::Value &value,
                                    quite::grpc_impl::ProbeServiceHandle probe_service)
{
    if (value.has_bool_val())
    {
        return value.bool_val();
    }
    if (value.has_int_val())
    {
        return value.int_val();
    }
    if (value.has_double_val())
    {
        return value.double_val();
    }
    if (value.has_string_val())
    {
        return value.string_val();
    }
    if (value.has_object_val())
    {
        return std::make_shared<quite::grpc_impl::GrpcRemoteObject>(value.object_val().object_id(),
                                                                    std::move(probe_service));
    }
    if (value.has_array_val())
    {
        quite::ArrayObject array{};
        array.values.reserve(value.array_val().value_size());
        for (auto &&val : value.array_val().value())
        {
            // todo: propagate potential error up
            array.values.emplace_back(*convert(val, probe_service));
        }
        return xyz::indirect<quite::ArrayObject>(std::move(array));
    }
    if (value.has_class_val())
    {
        quite::ClassObject class_obj{};
        class_obj.type_name = value.class_val().type_name();
        class_obj.members.reserve(value.class_val().value_size());
        for (auto &&val : value.class_val().value())
        {
            // todo: propagate potential error up
            class_obj.members.emplace_back(val.name(), *convert(val.value(), probe_service));
        }
        return xyz::indirect<quite::ClassObject>(std::move(class_obj));
    }

    return std::unexpected(quite::Error{
        .code = quite::ErrorCode::invalid_argument,
        .message =
            fmt::format("Could not convert value. Has value field={}",
                        (value.value_oneof_case() != quite::proto::Value::ValueOneofCase::VALUE_ONEOF_NOT_SET))});
}

struct ValueConverter
{
    quite::proto::Value operator()(std::int64_t value) const
    {
        quite::proto::Value v;
        v.set_int_val(std::move(value));
        return v;
    }

    quite::proto::Value operator()(double value) const
    {
        quite::proto::Value v;
        v.set_double_val(std::move(value));
        return v;
    }

    quite::proto::Value operator()(bool value) const
    {
        quite::proto::Value v;
        v.set_bool_val(std::move(value));
        return v;
    }

    quite::proto::Value operator()(std::string value) const
    {
        quite::proto::Value v;
        v.set_string_val(std::move(value));
        return v;
    }

    quite::proto::Value operator()(const std::shared_ptr<RemoteObject> &value) const
    {
        quite::proto::Value v;
        v.mutable_object_val()->set_object_id(value->id());
        return v;
    }

    quite::proto::Value operator()(const xyz::indirect<ArrayObject> &value) const
    {
        quite::proto::Value v;
        auto &&array = v.mutable_array_val();
        for (auto &&val : value->values)
        {
            *array->add_value() = convert(val);
        }
        return v;
    }

    quite::proto::Value operator()(const xyz::indirect<ClassObject> &value) const
    {
        quite::proto::Value v;
        auto &&class_val = v.mutable_class_val();
        class_val->set_type_name(value->type_name);
        for (auto &&member : value->members)
        {
            auto &&class_member = class_val->add_value();
            class_member->set_name(member.name);
            *class_member->mutable_value() = convert(member.value);
        }
        return v;
    }
};

quite::proto::Value convert(const quite::Value &value)
{
    return std::visit(ValueConverter{}, value);
}
} // namespace quite::grpc_impl
