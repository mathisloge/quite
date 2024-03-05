#include <agrpc/asio_grpc.hpp>
#include <asio/detached.hpp>
#include <catch2/catch_test_macros.hpp>
#include <quite/application.hpp>
#include <quite/object_client.hpp>
#include <spawn.h>
#include <spdlog/spdlog.h>
#include <tester_app.hpp>

TEST_CASE("Test if a process application can be created")
{
    spdlog::set_level(spdlog::level::level_enum::trace);

    asio::io_context io_context;
    // auto  work = asio::make_work_guard(io_context);

    auto app = quite::Application::createApplication(io_context, TESTER_APP_PATH);

    std::this_thread::sleep_for(std::chrono::seconds{1});

    agrpc::GrpcContext grpc_context;
    quite::ObjectClient client{grpc_context};

    std::jthread grpc_context_thread{[&] { grpc_context.run(); }};

    asio::co_spawn(
        io_context,
        [&]() -> asio::awaitable<void> {
            const auto msg = co_await client.sayHello("hey");
            spdlog::critical("MSG {}", msg);
            co_return;
        },
        asio::detached);
    io_context.run();
}
