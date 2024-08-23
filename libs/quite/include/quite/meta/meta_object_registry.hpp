#pragma once
#include <unordered_map>
#include "meta_object.hpp"

namespace quite
{

class MetaObjectRegistry
{
  public:
  private:
    std::unordered_map<TypeId, MetaObject> meta_objects_;
};

} // namespace quite
