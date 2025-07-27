// SPDX-FileCopyrightText: 2025 Mathis Logemann <mathis@quite.rocks>
//
// SPDX-License-Identifier: MIT

#include <CLI/CLI.hpp>
#include <quite/setup_logger.hpp>

int main(int argc, char **argv)
{
    CLI::App app{"Enables to start applications or attaching a probe to running applications"};
    argv = app.ensure_utf8(argv);

    CLI11_PARSE(app, argc, argv);

    quite::setup_logger();

    return 0;
}
