#pragma once
#include <cstdint>
#include <expected>
#include <exec/task.hpp>
#include "errors.hpp"
#include "image.hpp"
#include "quitelib_export.h"
#include "value_handle.hpp"
namespace quite
{

using ObjectId = std::uint64_t;

class QUITELIB_EXPORT RemoteObject
{
  public:
    explicit RemoteObject(ObjectId id);
    virtual ~RemoteObject();

    virtual exec::task<Result<std::unordered_map<std::string, std::unique_ptr<Value>>>> fetch_properties(
        const std::vector<std::string_view> &properties) = 0;

    virtual exec::task<Result<void>> mouse_action() = 0;

    virtual exec::task<Result<Image>> take_snapshot() = 0;

    // virtual exec::task<void> take_snapshot() = 0;

    // muss ein template mit beliebigen argumenten sein.
    // value_handle setProperty(std::string_view property_name, value_handle property_value);

    // muss ein template mit beliebigen argumenten sein.
    // value_handle invoke(std::string_view method_name);

  protected:
    const ObjectId id_;
};
} // namespace quite
