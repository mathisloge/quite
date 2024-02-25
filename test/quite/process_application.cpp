#include <catch2/catch_test_macros.hpp>
#include <quite/application.hpp>
#include <tester_app.hpp>
#include <uvw/loop.h>


TEST_CASE("Test if a process application can be created")
{
    auto loop = uvw::loop::get_default();

    auto app = quite::Application::createApplication(TESTER_APP_PATH);

    loop->run();
}
