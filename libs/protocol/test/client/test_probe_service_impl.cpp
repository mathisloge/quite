// SPDX-FileCopyrightText: 2025, 2026 Mathis Logemann <mathis@quite.rocks>
//
// SPDX-License-Identifier: MIT

#include <agrpc/test.hpp>
#include <gmock/gmock.h>
#include <grpcpp/test/mock_stream.h>
#include <gtest/gtest.h>
#include <quite/value/object_query.hpp>
#include "grpc_context_test.hpp"
#include "probe_service_impl.hpp"
#include "quite/proto/probe_mock.grpc.pb.h"

using ::testing::NiceMock;
using ::testing::Return;

namespace quite::proto::test
{
namespace
{
class ProbeServiceImplTest : public GrpcContextTest
{
  protected:
    NiceMock<MockProbeServiceStub> stub_;
};
} // namespace

TEST_F(ProbeServiceImplTest, FindObjectReturnsObjectReference)
{
    NiceMock<grpc::testing::MockClientAsyncResponseReader<ObjectReply>> reader;
    EXPECT_CALL(reader, Finish).WillOnce([this](ObjectReply *response, grpc::Status *status, void *tag) {
        *status = grpc::Status::OK;
        response->set_object_id(42);
        response->set_type_id(7);
        agrpc::process_grpc_tag(*grpc_context_, tag, true);
    });
    EXPECT_CALL(stub_, PrepareAsyncFindObjectRaw).WillOnce(Return(&reader));

    ProbeServiceImpl service{grpc_context_, stub_, nullptr};
    auto [result] = stdexec::sync_wait(service.find_object(ObjectQuery{})).value();

    ASSERT_TRUE(result.has_value());
    EXPECT_EQ(result->object_id, 42u);
    EXPECT_EQ(result->type_id, 7u);
}

TEST_F(ProbeServiceImplTest, FindObjectPropagatesErrorStatus)
{
    NiceMock<grpc::testing::MockClientAsyncResponseReader<ObjectReply>> reader;
    EXPECT_CALL(reader, Finish).WillOnce([this](ObjectReply *, grpc::Status *status, void *tag) {
        *status = grpc::Status{grpc::StatusCode::NOT_FOUND, "no such object"};
        agrpc::process_grpc_tag(*grpc_context_, tag, true);
    });
    EXPECT_CALL(stub_, PrepareAsyncFindObjectRaw).WillOnce(Return(&reader));

    ProbeServiceImpl service{grpc_context_, stub_, nullptr};
    auto [result] = stdexec::sync_wait(service.find_object(ObjectQuery{})).value();

    ASSERT_FALSE(result.has_value());
    EXPECT_EQ(result.error().code, ErrorCode::not_found);
}
} // namespace quite::proto::test
