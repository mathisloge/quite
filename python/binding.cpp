#include <pybind11/chrono.h>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/stl/filesystem.h>
#include <quite/client/property.hpp>
#include <quite/setup_logger.hpp>
#include <quite/test/expect.hpp>
#include <quite/test/probe.hpp>
#include <quite/test/probe_manager.hpp>
#include <quite/test/property.hpp>
#include <quite/test/remote_object.hpp>
#include <quite/value/object_query.hpp>
#include <quite/version.hpp>

namespace py = pybind11;

PYBIND11_MODULE(_quite, m)
{
    using namespace quite::test;
    m.doc() = "quite - a ui testing framework. See https://github.com/mathisloge/ng-quite";

    auto py_probe_manager = py::class_<ProbeManager>(m, "ProbeManager");
    auto py_probe = py::class_<Probe>(m, "Probe");
    auto py_remote_object = py::class_<RemoteObject>(m, "RemoteObject");
    auto py_property = py::class_<Property>(m, "Property");
    auto py_image = py::class_<quite::Image>(m, "Image");
    auto py_image_view = py::class_<quite::ImageView>(m, "ImageView");
    auto py_expect = py::class_<IExpectBuilder>{m, "IExpectBuilder"};

    py_probe_manager //
        .def(py::init())
        .def("launch_qt_probe_application",
             &ProbeManager::launch_probe_application,
             py::arg{"name"},
             py::arg{"path_to_application"},
             py::arg{"args"} = std::vector<std::string>{})
        .def("connect_to_probe", &ProbeManager::connect_to_probe, py::arg{"name"});

    py_probe //
        .def("find_object",
             &Probe::find_object,
             py::arg{"object_query"},
             "Try to get an instance of an object by the given query. If the object might not be present directly, use "
             "try_find_object.")
        .def("try_find_object",
             &Probe::try_find_object,
             py::arg{"object_query"},
             py::arg{"timeout"},
             "Try to get a object in the specified time.")
        .def("wait_for_connected",
             &Probe::wait_for_connected,
             py::arg{"timeout"} = std::chrono::seconds{5},
             "Wait until the application is connected.")
        .def("exit", &Probe::exit, "Request to exit the application.");

    py_remote_object.doc() = "Represents an object from the test application.";
    py_remote_object //
        .def("mouse_action", &RemoteObject::mouse_action)
        .def("take_snapshot", &RemoteObject::take_snapshot)
        .def("invoke",
             &RemoteObject::invoke_method,
             py::arg{"method"},
             "Invokes the given method. Has to be the fully qualified name. If the qualified name is unknown, use the "
             "meta API to query the methods.")
        .def("property", &RemoteObject::property, py::arg{"name"}, "Reads a property from the object");

    py_property.doc() = "Represents a property which is tied to a remote objects property";
    py_property //
        .def("fetch", &Property::fetch)
        .def("value", &Property::value)
        .def("wait_for_value", &Property::wait_for_value, py::arg{"target_value"}, py::arg{"timeout"});

    py_image.doc() =
        "Holds the data of an image in the format of RGBA. Use .data() with other libraries for more complex use cases";
    py_image //
        .def(py::init())
        .def(py::init<std::filesystem::path>(), py::arg{"file_path"})
        .def("save_to", &quite::Image::save_to, py::arg{"file_path"})
        .def("data", &quite::Image::data);

    py_image_view.doc() = "A non owning reference to the data of an Image.";
    py_image_view
        .def(
            "data",
            [](quite::ImageView view) { return py::memoryview::from_memory(view.data.data(), view.data.size_bytes()); })
        .def_readonly("channels", &quite::ImageView::channels)
        .def_readonly("width", &quite::ImageView::width)
        .def_readonly("height", &quite::ImageView::height);

    py::class_<quite::ObjectQuery>(m, "ObjectQuery").def(py::init<quite::ObjectQueryBuilder>());
    py::class_<quite::ObjectQueryBuilder>(m, "ObjectQueryBuilder")
        .def(py::init<>())
        .def("with_property",
             py::overload_cast<std::string, std::int64_t>(&quite::ObjectQueryBuilder::with_property),
             py::arg{"key"},
             py::arg{"value"},
             "Adds the property to the search requirements")
        .def("with_property",
             py::overload_cast<std::string, double>(&quite::ObjectQueryBuilder::with_property),
             py::arg{"key"},
             py::arg{"value"})
        .def("with_property",
             py::overload_cast<std::string, bool>(&quite::ObjectQueryBuilder::with_property),
             py::arg{"key"},
             py::arg{"value"})
        .def("with_property",
             py::overload_cast<std::string, std::string>(&quite::ObjectQueryBuilder::with_property),
             py::arg{"key"},
             py::arg{"value"})
        .def("with_parent", &quite::ObjectQueryBuilder::with_parent, py::arg("parent"));
    py::implicitly_convertible<quite::ObjectQueryBuilder, quite::ObjectQuery>();

    m.def("make_query", &quite::make_query, "Create a new ObjectQuery");

    m.def("expect", &expect, py::arg{"object"});
    py_expect.def("screenshot", &IExpectBuilder::to_have_screenshot, py::arg{"name"});

    m.attr("__version__") = quite::kVersion;
    m.attr("__version_git_ref__") = quite::kGitRef;
}
