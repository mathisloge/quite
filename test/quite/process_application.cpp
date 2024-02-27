#include <iostream>
#include <asio/posix/stream_descriptor.hpp>
#include <asio/readable_pipe.hpp>
#include <catch2/catch_test_macros.hpp>
#include <quite/application.hpp>
#include <spawn.h>
#include <spdlog/spdlog.h>
#include <tester_app.hpp>

TEST_CASE("Test if a process application can be created")
{
    spdlog::set_level(spdlog::level::level_enum::trace);

    asio::io_context io_context;
    auto  work = asio::make_work_guard(io_context);


    auto app = quite::Application::createApplication(io_context, TESTER_APP_PATH);

    io_context.run();
}
