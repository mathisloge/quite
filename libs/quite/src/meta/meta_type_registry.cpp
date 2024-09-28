#include "quite/meta/meta_type_registry.hpp"
#include "meta_type_storage.hpp"

namespace quite::meta
{
MetaTypeRegistry::MetaTypeRegistry()
    : storage_{std::make_unique<MetaTypeStorage>()}
{}

MetaTypeRegistry::~MetaTypeRegistry() = default;

MetaTypeStorage &MetaTypeRegistry::storage()
{
    return *storage_;
}

} // namespace quite::meta