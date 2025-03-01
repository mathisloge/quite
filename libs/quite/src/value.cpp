#include "quite/value.hpp"
#include <quite/value/object_id.hpp>
#include "quite/remote_object.hpp"

namespace quite
{
struct ValueConverter
{
    entt::meta_any operator()(std::int64_t value) const
    {
        return entt::forward_as_meta(value);
    }

    entt::meta_any operator()(std::uint64_t value) const
    {
        return entt::forward_as_meta(value);
    }

    entt::meta_any operator()(double value) const
    {

        return entt::forward_as_meta(value);
    }

    entt::meta_any operator()(bool value) const
    {
        return entt::forward_as_meta(value);
    }

    entt::meta_any operator()(std::string value) const
    {
        return entt::forward_as_meta(std::move(value));
    }

    entt::meta_any operator()(const std::shared_ptr<RemoteObject> &value) const
    {
        return entt::forward_as_meta(ObjectReference{.object_id = value->id(), .type_id = value->type_id()});
    }

    entt::meta_any operator()(const xyz::indirect<ArrayObject> &value) const
    {
        return {};
        // quite::proto::Value v;
        // auto &&array = v.mutable_array_val();
        // for (auto &&val : value->values)
        //{
        //     *array->add_value() = convert(val);
        // }
        // return v;
    }

    entt::meta_any operator()(const xyz::indirect<ClassObject> &value) const
    {
        return {};
        // quite::proto::Value v;
        // auto &&class_val = v.mutable_class_val();
        // class_val->set_type_name(value->type_name);
        // for (auto &&member : value->members)
        //{
        //     auto &&class_member = class_val->add_value();
        //     class_member->set_name(member.name);
        //     *class_member->mutable_value() = convert(member.value);
        // }
        // return v;
    }
};

entt::meta_any convert(const quite::Value &value)
{
    return std::visit(ValueConverter{}, value);
}
} // namespace quite
