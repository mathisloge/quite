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
#include "quite/proto/types.pb.h"

using ::testing::NiceMock;
using ::testing::Return;

namespace quite::proto::test
{
namespace
{
// nullptr would fail sanitizers: ProbeServiceImpl dereferences value_converter_ unconditionally
class NullValueConverter final : public IValueConverter
{
  public:
    entt::meta_any from(ObjectReference /*ref*/) const override
    {
        return {};
    }
};

class ProbeServiceImplTest : public GrpcContextTest
{
  protected:
    NiceMock<MockProbeServiceStub> stub_;
    std::shared_ptr<IValueConverter> value_converter_{std::make_shared<NullValueConverter>()};
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

TEST_F(ProbeServiceImplTest, GetObjectPropertiesReturnsValues)
{
    NiceMock<grpc::testing::MockClientAsyncResponseReader<GetObjectPropertiesResponse>> reader;
    EXPECT_CALL(reader, Finish)
        .WillOnce([this](GetObjectPropertiesResponse *response, grpc::Status *status, void *tag) {
            *status = grpc::Status::OK;
            Value value;
            value.set_int_val(42);
            (*response->mutable_property_values())["answer"] = value;
            agrpc::process_grpc_tag(*grpc_context_, tag, true);
        });
    EXPECT_CALL(stub_, PrepareAsyncGetObjectPropertiesRaw).WillOnce(Return(&reader));

    ProbeServiceImpl service{grpc_context_, stub_, value_converter_};
    auto [result] = stdexec::sync_wait(service.get_object_properties(1, {"answer"})).value();

    ASSERT_TRUE(result.has_value());
    ASSERT_TRUE(result->contains("answer"));
    EXPECT_EQ(result->at("answer").cast<std::int64_t>(), 42);
}

TEST_F(ProbeServiceImplTest, GetObjectPropertiesPropagatesErrorStatus)
{
    NiceMock<grpc::testing::MockClientAsyncResponseReader<GetObjectPropertiesResponse>> reader;
    EXPECT_CALL(reader, Finish).WillOnce([this](GetObjectPropertiesResponse *, grpc::Status *status, void *tag) {
        *status = grpc::Status{grpc::StatusCode::NOT_FOUND, "no such object"};
        agrpc::process_grpc_tag(*grpc_context_, tag, true);
    });
    EXPECT_CALL(stub_, PrepareAsyncGetObjectPropertiesRaw).WillOnce(Return(&reader));

    ProbeServiceImpl service{grpc_context_, stub_, value_converter_};
    auto [result] = stdexec::sync_wait(service.get_object_properties(1, {"answer"})).value();

    ASSERT_FALSE(result.has_value());
    EXPECT_EQ(result.error().code, ErrorCode::not_found);
}

TEST_F(ProbeServiceImplTest, SetObjectPropertySucceeds)
{
    NiceMock<grpc::testing::MockClientAsyncResponseReader<SetObjectPropertyResponse>> reader;
    EXPECT_CALL(reader, Finish).WillOnce([this](SetObjectPropertyResponse *, grpc::Status *status, void *tag) {
        *status = grpc::Status::OK;
        agrpc::process_grpc_tag(*grpc_context_, tag, true);
    });
    EXPECT_CALL(stub_, PrepareAsyncSetObjectPropertyRaw).WillOnce(Return(&reader));

    ProbeServiceImpl service{grpc_context_, stub_, nullptr};
    auto [result] =
        stdexec::sync_wait(service.set_object_property(1, "name", entt::meta_any{std::string{"a"}})).value();

    EXPECT_TRUE(result.has_value());
}

TEST_F(ProbeServiceImplTest, SetObjectPropertyPropagatesErrorStatus)
{
    NiceMock<grpc::testing::MockClientAsyncResponseReader<SetObjectPropertyResponse>> reader;
    EXPECT_CALL(reader, Finish).WillOnce([this](SetObjectPropertyResponse *, grpc::Status *status, void *tag) {
        *status = grpc::Status{grpc::StatusCode::FAILED_PRECONDITION, "read-only property"};
        agrpc::process_grpc_tag(*grpc_context_, tag, true);
    });
    EXPECT_CALL(stub_, PrepareAsyncSetObjectPropertyRaw).WillOnce(Return(&reader));

    ProbeServiceImpl service{grpc_context_, stub_, nullptr};
    auto [result] =
        stdexec::sync_wait(service.set_object_property(1, "name", entt::meta_any{std::string{"a"}})).value();

    ASSERT_FALSE(result.has_value());
    EXPECT_EQ(result.error().code, ErrorCode::failed_precondition);
}

TEST_F(ProbeServiceImplTest, QueryTopLevelViewsReturnsViews)
{
    NiceMock<grpc::testing::MockClientAsyncResponseReader<GetViewsResponse>> reader;
    EXPECT_CALL(reader, Finish).WillOnce([this](GetViewsResponse *response, grpc::Status *status, void *tag) {
        *status = grpc::Status::OK;
        auto *view1 = response->add_object();
        view1->set_object_id(1);
        view1->set_type_id(10);
        auto *view2 = response->add_object();
        view2->set_object_id(2);
        view2->set_type_id(20);
        agrpc::process_grpc_tag(*grpc_context_, tag, true);
    });
    EXPECT_CALL(stub_, PrepareAsyncGetViewsRaw).WillOnce(Return(&reader));

    ProbeServiceImpl service{grpc_context_, stub_, nullptr};
    auto [result] = stdexec::sync_wait(service.query_top_level_views()).value();

    ASSERT_TRUE(result.has_value());
    ASSERT_EQ(result->size(), 2u);
    EXPECT_EQ((*result)[0].object_id, 1u);
    EXPECT_EQ((*result)[1].object_id, 2u);
}

TEST_F(ProbeServiceImplTest, QueryTopLevelViewsPropagatesErrorStatus)
{
    NiceMock<grpc::testing::MockClientAsyncResponseReader<GetViewsResponse>> reader;
    EXPECT_CALL(reader, Finish).WillOnce([this](GetViewsResponse *, grpc::Status *status, void *tag) {
        *status = grpc::Status{grpc::StatusCode::UNAVAILABLE, "probe unreachable"};
        agrpc::process_grpc_tag(*grpc_context_, tag, true);
    });
    EXPECT_CALL(stub_, PrepareAsyncGetViewsRaw).WillOnce(Return(&reader));

    ProbeServiceImpl service{grpc_context_, stub_, nullptr};
    auto [result] = stdexec::sync_wait(service.query_top_level_views()).value();

    ASSERT_FALSE(result.has_value());
    EXPECT_EQ(result.error().code, ErrorCode::unavailable);
}

TEST_F(ProbeServiceImplTest, InvokeMethodReturnsValue)
{
    NiceMock<grpc::testing::MockClientAsyncResponseReader<MethodCallResponse>> reader;
    EXPECT_CALL(reader, Finish).WillOnce([this](MethodCallResponse *response, grpc::Status *status, void *tag) {
        *status = grpc::Status::OK;
        response->mutable_return_value()->mutable_value()->set_int_val(7);
        agrpc::process_grpc_tag(*grpc_context_, tag, true);
    });
    EXPECT_CALL(stub_, PrepareAsyncInvokeMethodRaw).WillOnce(Return(&reader));

    ProbeServiceImpl service{grpc_context_, stub_, value_converter_};
    auto [result] = stdexec::sync_wait(service.invoke_method(1, "getValue()", {})).value();

    ASSERT_TRUE(result.has_value());
    ASSERT_TRUE(result->allow_cast<std::int64_t>());
    EXPECT_EQ(result->cast<std::int64_t>(), 7);
}

TEST_F(ProbeServiceImplTest, InvokeMethodReturnsVoidWhenNoValue)
{
    NiceMock<grpc::testing::MockClientAsyncResponseReader<MethodCallResponse>> reader;
    EXPECT_CALL(reader, Finish).WillOnce([this](MethodCallResponse *response, grpc::Status *status, void *tag) {
        *status = grpc::Status::OK;
        response->mutable_return_value();
        agrpc::process_grpc_tag(*grpc_context_, tag, true);
    });
    EXPECT_CALL(stub_, PrepareAsyncInvokeMethodRaw).WillOnce(Return(&reader));

    ProbeServiceImpl service{grpc_context_, stub_, value_converter_};
    auto [result] = stdexec::sync_wait(service.invoke_method(1, "setValue(int)", {})).value();

    ASSERT_TRUE(result.has_value());
    EXPECT_EQ(result->type().info(), entt::type_id<void>());
}

TEST_F(ProbeServiceImplTest, InvokeMethodPropagatesErrorStatus)
{
    NiceMock<grpc::testing::MockClientAsyncResponseReader<MethodCallResponse>> reader;
    EXPECT_CALL(reader, Finish).WillOnce([this](MethodCallResponse *, grpc::Status *status, void *tag) {
        *status = grpc::Status{grpc::StatusCode::INVALID_ARGUMENT, "no such method"};
        agrpc::process_grpc_tag(*grpc_context_, tag, true);
    });
    EXPECT_CALL(stub_, PrepareAsyncInvokeMethodRaw).WillOnce(Return(&reader));

    ProbeServiceImpl service{grpc_context_, stub_, value_converter_};
    auto [result] = stdexec::sync_wait(service.invoke_method(1, "doesNotExist()", {})).value();

    ASSERT_FALSE(result.has_value());
    EXPECT_EQ(result.error().code, ErrorCode::invalid_argument);
}

TEST_F(ProbeServiceImplTest, TakeSnapshotReturnsImage)
{
    // streaming reader is actually deleted by gRPC, unlike the unary one - must be heap-allocated
    EXPECT_CALL(stub_, PrepareAsyncCreateScreenshotRaw).WillOnce([this](auto &&...) {
        auto reader = std::make_unique<NiceMock<grpc::testing::MockClientAsyncReader<ImageResponse>>>();
        EXPECT_CALL(*reader, StartCall).WillOnce([this](void *tag) {
            agrpc::process_grpc_tag(*grpc_context_, tag, true);
        });
        EXPECT_CALL(*reader, Read)
            .WillOnce([this](ImageResponse *response, void *tag) {
                response->mutable_metadata()->set_width(2);
                response->mutable_metadata()->set_height(1);
                response->set_data("ab");
                agrpc::process_grpc_tag(*grpc_context_, tag, true);
            })
            .WillOnce([this](ImageResponse *, void *tag) { agrpc::process_grpc_tag(*grpc_context_, tag, false); });
        EXPECT_CALL(*reader, Finish).WillOnce([this](grpc::Status *status, void *tag) {
            *status = grpc::Status::OK;
            agrpc::process_grpc_tag(*grpc_context_, tag, true);
        });
        return reader.release();
    });

    ProbeServiceImpl service{grpc_context_, stub_, nullptr};
    auto [result] = stdexec::sync_wait(service.take_snapshot(1)).value();

    ASSERT_TRUE(result.has_value());
    const auto image_data = result->data();
    EXPECT_EQ(image_data.width, 2u);
    EXPECT_EQ(image_data.height, 1u);
    ASSERT_EQ(image_data.data.size(), 2u);
    EXPECT_EQ(static_cast<char>(image_data.data[0]), 'a');
    EXPECT_EQ(static_cast<char>(image_data.data[1]), 'b');
}

TEST_F(ProbeServiceImplTest, TakeSnapshotPropagatesErrorStatus)
{
    EXPECT_CALL(stub_, PrepareAsyncCreateScreenshotRaw).WillOnce([this](auto &&...) {
        auto reader = std::make_unique<NiceMock<grpc::testing::MockClientAsyncReader<ImageResponse>>>();
        EXPECT_CALL(*reader, StartCall).WillOnce([this](void *tag) {
            agrpc::process_grpc_tag(*grpc_context_, tag, true);
        });
        EXPECT_CALL(*reader, Read).WillOnce([this](ImageResponse *, void *tag) {
            agrpc::process_grpc_tag(*grpc_context_, tag, false);
        });
        EXPECT_CALL(*reader, Finish).WillOnce([this](grpc::Status *status, void *tag) {
            *status = grpc::Status{grpc::StatusCode::UNAVAILABLE, "no display"};
            agrpc::process_grpc_tag(*grpc_context_, tag, true);
        });
        return reader.release();
    });

    ProbeServiceImpl service{grpc_context_, stub_, nullptr};
    auto [result] = stdexec::sync_wait(service.take_snapshot(1)).value();

    ASSERT_FALSE(result.has_value());
    EXPECT_EQ(result.error().code, ErrorCode::unavailable);
}
} // namespace quite::proto::test
