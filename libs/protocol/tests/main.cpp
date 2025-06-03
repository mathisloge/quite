#include <boost/ut.hpp>
#include <quite/crash_handler.hpp>
#include <quite/setup_logger.hpp>

int main(int argc, char *argv[])
{
    quite::register_crash_handler();
    quite::setup_logger();
    return static_cast<int>(
        boost::ut::cfg<>.run({.report_errors = true, .argc = argc, .argv = const_cast<const char **>(argv)}));
}
