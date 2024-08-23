#pragma once
#include <quite/application.hpp>
#include "quite_testing_export.h"

namespace quite::test
{
QUITE_TESTING_EXPORT ApplicationPtr start_application(const std::string &app_path);
}
