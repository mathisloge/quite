#include <QCoreApplication>
#include <catch2/catch_session.hpp>
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
    quill::LogLevel lvl;
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
    quite::probe::register_converters(entt::locator<quite::ValueRegistry>::emplace());
    qInstallMessageHandler(quite_message_handler);
    quite::setup_logger();
    QCoreApplication app{argc, argv};

    const int result = Catch::Session().run(argc, argv);

    return result;
}
