#include <pybind11/pybind11.h>
#include <quite/application.hpp>
#include <quite/version.hpp>

namespace quite::python
{
class PyRemoteObject
{
  public:
    PyRemoteObject(RemoteObjectPtr obj)
        : remote_obj_{std::move(obj)}
    {}

    ObjectId id() const
    {
        return remote_obj_->id();
    }

    ~PyRemoteObject() = default;

  private:
    RemoteObjectPtr remote_obj_;
};

class PyApplication
{
  public:
    PyApplication(const std::string &app_path)
        : application_{Application::CreateApplication(app_path)}
    {}

    PyRemoteObject find_object(const std::string &object_name)
    {
        const ObjectQuery query{.properties = {{"objectName", object_name}}};
        auto obj =
            std::get<Result<RemoteObjectPtr>>(stdexec::sync_wait([this, &query]() -> AsyncResult<RemoteObjectPtr> {
                                                  auto obj = co_await application_->find_object(query);
                                                  co_return obj;
                                              }())
                                                  .value());

        if (not obj.has_value())
        {
            throw std::runtime_error(
                fmt::format("Could not find object with query {}. Failed with error: {}", query, obj.error().message));
        }

        return PyRemoteObject{obj.value()};
    }

    void exit()
    {
        stdexec::sync_wait([this]() -> exec::task<void> { co_await application_->exit(); }());
    }

    ~PyApplication() = default;

  private:
    ApplicationPtr application_;
};
} // namespace quite::python

namespace py = pybind11;

PYBIND11_MODULE(_quite, m)
{
    using namespace quite::python;

    m.doc() = "quite - the (q)t (ui) (te)sting framework. See https://github.com/mathisloge/ng-quite";

    auto pyApplication = py::class_<PyApplication>(m, "Application");
    auto pyRemoteObject = py::class_<PyRemoteObject>(m, "RemoteObject");

    pyApplication //
        .def(py::init<const std::string &>(), py::arg("application_path"))
        .def("find_object",
             &PyApplication::find_object,
             py::arg{"object_query"},
             "try to get an instance of an object by the given query.")
        .def("exit", &PyApplication::exit, "Request to exit the application.");

    pyRemoteObject //
        .def_property_readonly("id", &PyRemoteObject::id, "returns the id of the remote object.");

    m.attr("__version__") = quite::kVersion;
}
