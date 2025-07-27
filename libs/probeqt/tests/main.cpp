// SPDX-FileCopyrightText: 2025 Mathis Logemann <mathis@quite.rocks>
//
// SPDX-License-Identifier: MIT

#include <QCoreApplication>
#include <boost/ut.hpp>
#include <quill/Frontend.h>
#include <quill/LogMacros.h>
#include <quill/core/LogLevel.h>
#include <quite/logger.hpp>
#include <quite/setup_logger.hpp>
#include <quite/value/value_registry.hpp>
#include "value_converters.hpp"

DEFINE_LOGGER(qt_log)

namespace
{
void quite_message_handler(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
    quill::LogLevel lvl{};
    switch (type)
    {
    case QtDebugMsg:
        lvl = quill::LogLevel::Debug;
        break;
    case QtInfoMsg:
        lvl = quill::LogLevel::Info;
        break;
    case QtWarningMsg:
        lvl = quill::LogLevel::Warning;
        break;
    case QtFatalMsg:
        lvl = quill::LogLevel::Critical;
        break;
    default:
        lvl = quill::LogLevel::Debug;
    }
    LOG_RUNTIME_METADATA(qt_log(), lvl, context.file, context.line, context.function, "{}", msg.toStdString());
}
} // namespace

int main(int argc, char *argv[])
{
    quite::setup_logger();
    qInstallMessageHandler(quite_message_handler);
    quite::probe::register_converters(entt::locator<quite::ValueRegistry>::emplace());
    QCoreApplication app{argc, argv};
    return static_cast<int>(
        boost::ut::cfg<>.run({.report_errors = true, .argc = argc, .argv = const_cast<const char **>(argv)}));
}
