#pragma once
#include <quite/meta/meta_types.hpp>
#include "quite/proto/meta.pb.h"
#include "quite/quite_protocol_export.hpp"
namespace quite::proto
{
meta::PrimitiveType QUITE_PROTOCOL_EXPORT from_protocol(const MetaPrimitiveType &type);
meta::ListType QUITE_PROTOCOL_EXPORT from_protocol(const MetaListType &type);
meta::MapType QUITE_PROTOCOL_EXPORT from_protocol(const MetaMapType &type);
meta::ObjectTypePtr QUITE_PROTOCOL_EXPORT from_protocol(const MetaObjectType &type);
meta::EnumTypePtr QUITE_PROTOCOL_EXPORT from_protocol(const MetaEnumType &type);

void QUITE_PROTOCOL_EXPORT to_protocol(const meta::Type &type, MetaType &proto);
} // namespace quite::proto
