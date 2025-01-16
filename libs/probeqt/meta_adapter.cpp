#include "meta_adapter.hpp"

namespace quite::probe
{

AsyncResult<meta::Type> MetaAdapter::find_type_by_id(meta::TypeId type_id)
{
    return type_registry_.lookup_type(type_id);
}
} // namespace quite::probe
