// SPDX-FileCopyrightText: 2025, 2026 Mathis Logemann <mathis@quite.rocks>
//
// SPDX-License-Identifier: MIT

#include <agrpc/test.hpp>
#include <gmock/gmock.h>
#include <grpcpp/test/mock_stream.h>
#include <gtest/gtest.h>
#include "grpc_context_test.hpp"
#include "meta_registry_impl.hpp"
#include "quite/proto/meta_service_mock.grpc.pb.h"

using ::testing::NiceMock;
using ::testing::Return;

namespace quite::proto::test
{
namespace
{
class MetaRegistryImplTest : public GrpcContextTest
{
  protected:
    NiceMock<MockMetaServiceStub> stub_;
};
} // namespace

TEST_F(MetaRegistryImplTest, LookupTypeReturnsPrimitiveType)
{
    NiceMock<grpc::testing::MockClientAsyncResponseReader<MetaFindTypeResponse>> reader;
    EXPECT_CALL(reader, Finish).WillOnce([this](MetaFindTypeResponse *response, grpc::Status *status, void *tag) {
        *status = grpc::Status::OK;
        response->mutable_type()->set_primitive_type(MetaPrimitiveType::double_);
        agrpc::process_grpc_tag(*grpc_context_, tag, true);
    });
    EXPECT_CALL(stub_, PrepareAsyncFindTypeRaw).WillOnce(Return(&reader));

    MetaRegistryImpl registry{grpc_context_, stub_};
    auto [result] = stdexec::sync_wait(registry.lookup_type(1)).value();

    ASSERT_TRUE(result.has_value());
    ASSERT_TRUE(std::holds_alternative<meta::PrimitiveType>(*result));
    EXPECT_EQ(std::get<meta::PrimitiveType>(*result), meta::PrimitiveType::type_double);
}

TEST_F(MetaRegistryImplTest, LookupTypePropagatesErrorStatus)
{
    NiceMock<grpc::testing::MockClientAsyncResponseReader<MetaFindTypeResponse>> reader;
    EXPECT_CALL(reader, Finish).WillOnce([this](MetaFindTypeResponse *, grpc::Status *status, void *tag) {
        *status = grpc::Status{grpc::StatusCode::NOT_FOUND, "unknown type"};
        agrpc::process_grpc_tag(*grpc_context_, tag, true);
    });
    EXPECT_CALL(stub_, PrepareAsyncFindTypeRaw).WillOnce(Return(&reader));

    MetaRegistryImpl registry{grpc_context_, stub_};
    auto [result] = stdexec::sync_wait(registry.lookup_type(1)).value();

    ASSERT_FALSE(result.has_value());
    EXPECT_EQ(result.error().code, ErrorCode::not_found);
}
} // namespace quite::proto::test
