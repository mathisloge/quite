#pragma once
#include <quite/meta/meta_types.hpp>
#include "quite/proto/meta.pb.h"
namespace quite::proto
{
meta::PrimitiveType from_protocol(const MetaPrimitiveType &type);
meta::ListType from_protocol(const MetaListType &type);
meta::MapType from_protocol(const MetaMapType &type);
meta::ObjectType from_protocol(const MetaObjectType &type);

void to_protocol(const meta::Type &type, MetaType &proto);
} // namespace quite::proto
