#include <pybind11/pybind11.h>
#include <quite/application.hpp>
#include <quite/version.hpp>

namespace quite::python
{
class PyRemoteObject
{
  public:
    ~PyRemoteObject() = default;

    void reset()
    {
        remote_obj_ = nullptr;
    }

    static PyRemoteObject Create(RemoteObjectPtr obj)
    {
        return PyRemoteObject{std::move(obj)};
    }

  private:
    PyRemoteObject(RemoteObjectPtr obj)
        : remote_obj_{std::move(obj)}
    {}

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

        return PyRemoteObject::Create(obj.value());
    }

    void exit()
    {
        stdexec::sync_wait([this]() -> exec::task<void> { co_await application_->exit(); }());
    }

    ~PyApplication()
    {
        exit();
    }

  private:
    ApplicationPtr application_;
};
} // namespace quite::python

namespace py = pybind11;

PYBIND11_MODULE(_quite, m)
{
    using namespace quite::python;

    py::class_<PyApplication>(m, "Application") //
        .def(py::init<const std::string &>())
        .def("find_object", &PyApplication::find_object)
        .def("exit", &PyApplication::exit);

    py::class_<PyRemoteObject>(m, "RemoteObject") //
        .def("reset", &PyRemoteObject::reset);

    m.attr("__version__") = quite::kVersion;
}
