#include "TracyQmlInjection.hpp"
#include <glad/glad.h>
#include <qquickwindow.h>

#include <tracy/Tracy.hpp>
#include <tracy/TracyOpenGL.hpp>

TracyQmlInjection::TracyQmlInjection()
{
    connect(this, &QQuickItem::windowChanged, this, [this]() {
        connect(
            window(),
            &QQuickWindow::beforeRendering,
            this,
            [this]() {
                if (not has_init_)
                {
                    has_init_ = true;
                    qDebug() << "XXX LOAD" << gladLoadGL();
                    TracyGpuContext;
                }
            },
            Qt::DirectConnection);
        connect(
            window(),
            &QQuickWindow::frameSwapped,
            this,
            [this]() {
                if (has_init_)
                {
                    qDebug() << "collecting";
                    TracyGpuCollect;
                }
            },
            Qt::DirectConnection);

        connect(
            window(),
            &QQuickWindow::afterFrameEnd,
            this,
            [this]() {
                if (has_init_)
                {
                    FrameMark;
                }
            },
            Qt::DirectConnection);
    });
}

TracyQmlInjection::~TracyQmlInjection() = default;
