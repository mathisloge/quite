// SPDX-FileCopyrightText: 2025, 2026 Mathis Logemann <mathis@quite.rocks>
//
// SPDX-License-Identifier: MIT

#pragma once
#include <thread>
#include <agrpc/grpc_context.hpp>
#include <gtest/gtest.h>

namespace quite::proto::test
{
// agrpc::process_grpc_tag needs a running GrpcContext to post onto
class GrpcContextTest : public ::testing::Test
{
  protected:
    void SetUp() override
    {
        grpc_context_ = std::make_shared<agrpc::GrpcContext>();
        grpc_context_->work_started();
        runner_ = std::thread{[this] { grpc_context_->run(); }};
    }

    void TearDown() override
    {
        grpc_context_->work_finished();
        runner_.join();
    }

    std::shared_ptr<agrpc::GrpcContext> grpc_context_;

  private:
    std::thread runner_;
};
} // namespace quite::proto::test
