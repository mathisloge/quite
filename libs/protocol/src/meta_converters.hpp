// SPDX-FileCopyrightText: 2025 Mathis Logemann <mathis@quite.rocks>
//
// SPDX-License-Identifier: MIT

#pragma once
#include <quite/meta/meta_types.hpp>
#include "quite/proto/meta.pb.h"
namespace quite::proto
{
meta::PrimitiveType from_protocol(const MetaPrimitiveType &type);
meta::ListType from_protocol(const MetaListType &type);
meta::MapType from_protocol(const MetaMapType &type);
meta::ObjectTypePtr from_protocol(const MetaObjectType &type);
meta::EnumTypePtr from_protocol(const MetaEnumType &type);

void to_protocol(const meta::Type &type, MetaType &proto);
} // namespace quite::proto
