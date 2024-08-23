#pragma once
#include <quite/property.hpp>
#include <quite/proto/types.pb.h>
#include "probe_handle.hpp"

namespace quite::grpc_impl
{
quite::Result<quite::Value> convert(const quite::proto::Value &value,
                                    quite::grpc_impl::ProbeServiceHandle probe_service);
quite::proto::Value convert(const quite::Value &value);
} // namespace quite::grpc_impl
