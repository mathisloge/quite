#include <pybind11/chrono.h>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <quite/property.hpp>
#include <quite/test/application.hpp>
#include <quite/test/application_manager.hpp>
#include <quite/test/remote_object.hpp>
#include <quite/value/object_query.hpp>
#include <quite/version.hpp>

namespace py = pybind11;

namespace quite::test
{
class ObjectQueryBuilder
{
  public:
    ObjectQueryBuilder &set_parent(const ObjectQueryBuilder &parent)
    {
        query_->container = parent.query_;
        return *this;
    }

    ObjectQueryBuilder &add_property(std::string key, std::int64_t value)
    {
        return add_property(std::move(key), entt::forward_as_meta(value));
    }

    ObjectQueryBuilder &add_property(std::string key, double value)
    {
        return add_property(std::move(key), entt::forward_as_meta(value));
    }

    ObjectQueryBuilder &add_property(std::string key, bool value)
    {
        return add_property(std::move(key), entt::forward_as_meta(value));
    }

    ObjectQueryBuilder &add_property(std::string key, std::string value)
    {
        return add_property(std::move(key), entt::forward_as_meta(std::move(value)));
    }

    std::shared_ptr<ObjectQuery> query()
    {
        return query_;
    }

  private:
    ObjectQueryBuilder &add_property(std::string key, entt::meta_any value)
    {
        query_->properties.insert_or_assign(std::move(key), std::move(value));
        return *this;
    }

  private:
    std::shared_ptr<ObjectQuery> query_{std::make_shared<ObjectQuery>()};
};

} // namespace quite::test

PYBIND11_MODULE(_quite, m)
{
    using namespace quite::test;

    m.doc() = "quite - a ui testing framework. See https://github.com/mathisloge/ng-quite";

    auto py_application_manager = py::class_<ApplicationManager>(m, "ApplicationManager");
    auto py_application = py::class_<Application>(m, "Application");
    auto py_remote_object = py::class_<RemoteObject>(m, "RemoteObject");
    auto py_object_query_builder = py::class_<ObjectQueryBuilder>(m, "ObjectQueryBuilder");
    py::class_<quite::ObjectQuery, std::shared_ptr<quite::ObjectQuery>> py_object_query(m, "ObjectQuery");

    py_application_manager.def(py::init())
        .def("create_host_application",
             &ApplicationManager::create_host_application,
             py::arg{"path_to_application"},
             py::arg{"args"} = std::vector<std::string>{},
             py::arg{"environment"} = std::unordered_map<std::string, std::string>{});

    py_application //
        .def("find_object",
             &Application::find_object,
             py::arg{"object_query"},
             "Try to get an instance of an object by the given query. If the object might not be present directly, use "
             "try_find_object.")
        .def("try_find_object",
             &Application::try_find_object,
             py::arg{"object_query"},
             py::arg{"timeout"},
             "Try to get a object in the specified time.")
        .def("wait_for_connected",
             &Application::wait_for_connected,
             py::arg{"timeout"} = std::chrono::seconds{5},
             "Wait until the application is connected.")
        .def("exit", &Application::exit, "Request to exit the application.");

    py_remote_object.doc() = "Represents an object from the test application.";
    py_remote_object.def("mouse_action", &RemoteObject::mouse_action)
        .def("take_snapshot", &RemoteObject::take_snapshot);

    py_object_query_builder.def(py::init())
        .def("set_parent", &ObjectQueryBuilder::set_parent, py::arg{"parent_object_query_builder"}, "Sets the parent.")
        .def("query", &ObjectQueryBuilder::query, "Creates a object query to be used to e.g. find an object.")
        .def("add_property",
             py::overload_cast<std::string, std::int64_t>(&ObjectQueryBuilder::add_property),
             py::arg{"key"},
             py::arg{"value"},
             "Adds the property to the search requirements")
        .def("add_property",
             py::overload_cast<std::string, double>(&ObjectQueryBuilder::add_property),
             py::arg{"key"},
             py::arg{"value"})
        .def("add_property",
             py::overload_cast<std::string, bool>(&ObjectQueryBuilder::add_property),
             py::arg{"key"},
             py::arg{"value"})
        .def("add_property",
             py::overload_cast<std::string, std::string>(&ObjectQueryBuilder::add_property),
             py::arg{"key"},
             py::arg{"value"});

    m.attr("__version__") = quite::kVersion;
    m.attr("__version_git_ref__") = quite::kGitRef;
}
