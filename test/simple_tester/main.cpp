#include <QDebug>
#include <QGuiApplication>
#include <QTimer>
#include <QtQuick/QQuickView>
#include <quite/probe.hpp>
#include <spdlog/spdlog.h>

#include <QQuickItem>

#include <entt/container/dense_map.hpp>
#include <entt/meta/factory.hpp>
#include <entt/meta/meta.hpp>
#include <entt/meta/utility.hpp>

using namespace entt::literals;

struct TestObj
{
    int x;
    int y;
};

int main(int argc, char *argv[])
{
    quite::setupHooks();
    QGuiApplication app(argc, argv);

    QQuickView view;
    view.setObjectName("rootView");
    view.setResizeMode(QQuickView::SizeRootObjectToView);
    view.setSource(QUrl("qrc:///main.qml"));
    view.show();

    view.children();

    QTimer timer;
    QObject::connect(&timer, &QTimer::timeout, [] { spdlog::debug("hello from test app"); });

    {
        entt::meta<TestObj>() //
            .data<&TestObj::x>("x"_hs)
            .data<&TestObj::y>("y"_hs);

        std::unordered_map<entt::hashed_string::hash_type, std::string> names{{"x"_hs, "x"}, {"y"_hs, "y"}};

        auto custom_meta_type = entt::resolve<TestObj>();

        TestObj obj{10, 20};

        auto rect_any = custom_meta_type.construct();
        rect_any.set("x"_hs, 1);

        for (auto &&[x, y] : custom_meta_type.data())
        {
            qDebug() << "resolved" << x << names.at(x) << "=" << y.get(rect_any).cast<int>();
        }
    }

    return QGuiApplication::exec();
}
