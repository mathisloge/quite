#include <pybind11/pybind11.h>
#include <quite/version.hpp>

#define STRINGIFY(x) #x
#define MACRO_STRINGIFY(x) STRINGIFY(x)

namespace py = pybind11;

PYBIND11_MODULE(_quite, m)
{

    m.attr("__version__") = quite::kVersion;
}
