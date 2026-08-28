// SPDX-FileCopyrightText: 2025, 2026 Mathis Logemann <mathis@quite.rocks>
//
// SPDX-License-Identifier: MIT

#include <atomic>
#include <filesystem>
#include <fmt/format.h>
#include <gtest/gtest.h>
#include <quite/client/testing/verification_point.hpp>
#include <unistd.h>
#include "fakes/fake_property.hpp"
#include "fakes/fake_remote_object.hpp"

using namespace quite;
using namespace quite::client;
using namespace quite::client::test;
using namespace quite::testing;

namespace
{
Image make_test_image(std::byte fill)
{
    std::vector<std::byte> data(2 * 2 * 4, fill);
    return Image{std::move(data), 2, 2, 4};
}

std::filesystem::path unique_temp_dir()
{
    static std::atomic<int> counter{0};
    return std::filesystem::temp_directory_path() / fmt::format("quite_vp_test_{}_{}", getpid(), counter++);
}

class VerificationPointTest : public ::testing::Test
{
  protected:
    void SetUp() override
    {
        dir_ = unique_temp_dir();
        std::filesystem::create_directories(dir_);
        path_ = (dir_ / "vp").string();
    }

    void TearDown() override
    {
        std::filesystem::remove_all(dir_);
    }

    static std::shared_ptr<FakeRemoteObject> make_object(Image snapshot, bool with_object_name_property = true)
    {
        std::unordered_map<std::string, PropertyPtr> properties;
        if (with_object_name_property)
        {
            properties.emplace("objectName",
                               std::make_shared<FakeProperty>(
                                   "objectName", Result<entt::meta_any>{entt::meta_any{std::string{"Button"}}}));
        }
        auto object = std::make_shared<FakeRemoteObject>(1, std::move(properties));
        object->set_snapshot(std::move(snapshot));
        return object;
    }

    std::filesystem::path dir_;
    std::string path_;
};
} // namespace

TEST_F(VerificationPointTest, HasVerificationPointFalseWhenMissing)
{
    EXPECT_FALSE(has_verification_point(path_));
}

TEST_F(VerificationPointTest, CreateWritesPngAndJson)
{
    auto [result] =
        stdexec::sync_wait(create_verification_point(make_object(make_test_image(std::byte{100})), path_)).value();

    ASSERT_TRUE(result.has_value());
    EXPECT_TRUE(has_verification_point(path_));
}

TEST_F(VerificationPointTest, CreatePropagatesSnapshotError)
{
    auto object = make_object(Image{});
    object->set_take_snapshot_error(Error{.code = ErrorCode::unavailable, .message = "no display"});

    auto [result] = stdexec::sync_wait(create_verification_point(object, path_)).value();

    ASSERT_FALSE(result.has_value());
    EXPECT_EQ(result.error().code, ErrorCode::unavailable);
}

TEST_F(VerificationPointTest, VerifySucceedsAgainstIdenticalSnapshot)
{
    stdexec::sync_wait(create_verification_point(make_object(make_test_image(std::byte{100})), path_));

    auto [result] =
        stdexec::sync_wait(verify_verification_point(make_object(make_test_image(std::byte{100})), path_)).value();

    ASSERT_TRUE(result.has_value());
    EXPECT_TRUE(*result);
}

TEST_F(VerificationPointTest, VerifyFailsOnPixelMismatch)
{
    stdexec::sync_wait(create_verification_point(make_object(make_test_image(std::byte{100})), path_));

    auto [result] =
        stdexec::sync_wait(verify_verification_point(make_object(make_test_image(std::byte{255})), path_)).value();

    ASSERT_TRUE(result.has_value());
    EXPECT_FALSE(*result);
}

TEST_F(VerificationPointTest, VerifyFailsOnPropertyMismatch)
{
    stdexec::sync_wait(create_verification_point(make_object(make_test_image(std::byte{100}), true), path_));

    auto [result] =
        stdexec::sync_wait(verify_verification_point(make_object(make_test_image(std::byte{100}), false), path_))
            .value();

    ASSERT_TRUE(result.has_value());
    EXPECT_FALSE(*result);
}

TEST_F(VerificationPointTest, VerifyFailsWhenNoVerificationPointExists)
{
    auto [result] =
        stdexec::sync_wait(verify_verification_point(make_object(make_test_image(std::byte{100})), path_)).value();

    ASSERT_FALSE(result.has_value());
    EXPECT_EQ(result.error().code, ErrorCode::failed_precondition);
}

TEST_F(VerificationPointTest, VerifyPropagatesSnapshotError)
{
    stdexec::sync_wait(create_verification_point(make_object(make_test_image(std::byte{100})), path_));

    auto object = make_object(Image{});
    object->set_take_snapshot_error(Error{.code = ErrorCode::unavailable, .message = "no display"});

    auto [result] = stdexec::sync_wait(verify_verification_point(object, path_)).value();

    ASSERT_FALSE(result.has_value());
    EXPECT_EQ(result.error().code, ErrorCode::unavailable);
}
