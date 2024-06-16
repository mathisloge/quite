#include "application_overview.hpp"

namespace quite::studio
{
ApplicationOverview::ApplicationOverview(std::shared_ptr<Application> application)
    : application_(std::move(application))
{}
} // namespace quite::studio
