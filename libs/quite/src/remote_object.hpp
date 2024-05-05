#pragma once
#include <quite/basic_remote_object.hpp>
namespace quite
{
class RemoteObject : public BasicRemoteObject
{
  public:
    explicit RemoteObject(ObjectId id);
    ~RemoteObject() override;

    exec::task<value_handle> getProperty(std::string_view property_name) override;
};
} // namespace quite
