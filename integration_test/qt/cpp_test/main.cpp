// SPDX-FileCopyrightText: 2025 Mathis Logemann <mathis@quite.rocks>
//
// SPDX-License-Identifier: MIT

#include <boost/ut.hpp>
#include <quite/setup_logger.hpp>

int main(int argc, char *argv[])
{
    quite::setup_logger();
    return static_cast<int>(
        boost::ut::cfg<>.run({.report_errors = true, .argc = argc, .argv = const_cast<const char **>(argv)}));
}
