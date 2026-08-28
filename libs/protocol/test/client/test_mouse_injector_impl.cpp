// SPDX-FileCopyrightText: 2025, 2026 Mathis Logemann <mathis@quite.rocks>
//
// SPDX-License-Identifier: MIT

#include <agrpc/test.hpp>
#include <gmock/gmock.h>
#include <grpcpp/test/mock_stream.h>
#include <gtest/gtest.h>
#include "grpc_context_test.hpp"
#include "mouse_injector_impl.hpp"
#include "quite/proto/probe_mock.grpc.pb.h"

using ::testing::NiceMock;
using ::testing::Return;

namespace quite::proto::test
{
namespace
{
class MouseInjectorImplTest : public GrpcContextTest
{
  protected:
    NiceMock<MockProbeServiceStub> stub_;
};
} // namespace

TEST_F(MouseInjectorImplTest, SingleActionSucceeds)
{
    NiceMock<grpc::testing::MockClientAsyncResponseReader<VoidResponse>> reader;
    EXPECT_CALL(reader, Finish).WillOnce([this](VoidResponse *, grpc::Status *status, void *tag) {
        *status = grpc::Status::OK;
        agrpc::process_grpc_tag(*grpc_context_, tag, true);
    });
    EXPECT_CALL(stub_, PrepareAsyncMouseActionRaw).WillOnce(Return(&reader));

    MouseInjectorImpl injector{grpc_context_, stub_};
    const core::MouseAction action{.position = {1.0, 2.0},
                                   .button = core::MouseButton::left,
                                   .trigger = core::MouseTrigger::click,
                                   .modifier = core::KeyboardModifier::none};
    auto [result] = stdexec::sync_wait(injector.single_action(42, action)).value();

    EXPECT_TRUE(result.has_value());
}

TEST_F(MouseInjectorImplTest, SingleActionPropagatesErrorStatus)
{
    NiceMock<grpc::testing::MockClientAsyncResponseReader<VoidResponse>> reader;
    EXPECT_CALL(reader, Finish).WillOnce([this](VoidResponse *, grpc::Status *status, void *tag) {
        *status = grpc::Status{grpc::StatusCode::UNAVAILABLE, "probe unreachable"};
        agrpc::process_grpc_tag(*grpc_context_, tag, true);
    });
    EXPECT_CALL(stub_, PrepareAsyncMouseActionRaw).WillOnce(Return(&reader));

    MouseInjectorImpl injector{grpc_context_, stub_};
    const core::MouseAction action{.position = {1.0, 2.0},
                                   .button = core::MouseButton::left,
                                   .trigger = core::MouseTrigger::click,
                                   .modifier = core::KeyboardModifier::none};
    auto [result] = stdexec::sync_wait(injector.single_action(42, action)).value();

    ASSERT_FALSE(result.has_value());
    EXPECT_EQ(result.error().code, ErrorCode::unavailable);
}
} // namespace quite::proto::test
