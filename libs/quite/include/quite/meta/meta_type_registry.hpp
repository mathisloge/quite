#pragma once
#include <quite/async_result.hpp>
#include <quite/meta/meta_types.hpp>

namespace quite::meta
{
class MetaTypeStorage;
class MetaTypeRegistry
{
  public:
    MetaTypeRegistry();
    virtual ~MetaTypeRegistry();

    virtual AsyncResult<Type> resolve_type(TypeId type_id) = 0;
    virtual AsyncResult<Type> resolve_type(std::string_view type_name) = 0;

  protected:
    MetaTypeStorage &storage();

  private:
    std::unique_ptr<MetaTypeStorage> storage_;
};

} // namespace quite::meta
