

# File main.cpp

[**File List**](files.md) **>** [**libs**](dir_6719ab1f1f7655efc2fa43f7eb574fd1.md) **>** [**probeqt**](dir_22ab9f3959c1273824a5221c73ee839d.md) **>** [**tests**](dir_c1613d43beada98aaa8aaa25db1fb827.md) **>** [**main.cpp**](probeqt_2tests_2main_8cpp.md)

[Go to the documentation of this file](probeqt_2tests_2main_8cpp.md)


```C++
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
```


