#include <cstdlib>
#include <CLI/App.hpp>

int main(int argc, char **argv)
{
    CLI::App app{"A simple test program"};
    argv = app.ensure_utf8(argv);

    int exit_code{EXIT_SUCCESS};
    app.add_option("--exit-code", exit_code, "The exit code to return")->envname("TEST_EXIT_CODE");

    CLI11_PARSE(app, argc, argv);

    return exit_code;
}
