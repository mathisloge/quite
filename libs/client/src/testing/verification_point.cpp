#include "quite/client/testing/verification_point.hpp"
#include <fstream>
#include <nlohmann/json.hpp>
#include <quite/image_utils.hpp>
#include <quite/logger.hpp>
#include "quite/client/utils/dump_properties.hpp"

DEFINE_LOGGER(vp_logger)
namespace fstd = std::filesystem;
namespace quite::testing
{

bool has_verification_point(const std::string &name)
{
    return fstd::exists(fstd::path(name).replace_extension(".png")) and
           fstd::exists(fstd::path(name).replace_extension(".json"));
}

AsyncResult<void> create_verification_point(client::RemoteObjectPtr object, const std::string &name)
{
    const auto snapshot = co_await object->take_snapshot();
    if (not snapshot.has_value())
    {
        co_return std::unexpected(snapshot.error());
    }
    const auto props = co_await dump_properties(object, {"objectName", "width", "height", "children", "visible"});
    if (not props.has_value())
    {
        co_return std::unexpected(props.error());
    }

    snapshot->save_to(fstd::path(name).replace_extension(".png"));

    std::ofstream o{fstd::path(name).replace_extension(".json")};
    o << std::setw(4) << *props << std::endl;
    co_return {};
}

AsyncResult<bool> verify_verification_point(client::RemoteObjectPtr object, const std::string &name)
{
    bool verified = true;
    const auto snapshot = co_await object->take_snapshot();
    if (not snapshot.has_value())
    {
        LOG_ERROR(vp_logger(), "Error while creating the snapshot: {}", snapshot.error().message);
        co_return std::unexpected(snapshot.error());
    }

    const auto props = co_await dump_properties(object, {"objectName", "width", "height", "children", "visible"});
    if (not props.has_value())
    {
        LOG_ERROR(vp_logger(), "Error while fetching the properties: {}", props.error().message);
        co_return std::unexpected(props.error());
    }

    if (not has_verification_point(name))
    {
        co_return make_error_result(ErrorCode::failed_precondition, fmt::format("Could not locate {}.png|.json", name));
    }

    const Image expected_snapshot{fstd::path(name).replace_extension(".png")};
    std::ifstream json_prop_file(fstd::path(name).replace_extension(".json"));
    const nlohmann::json expected_props = nlohmann::json::parse(json_prop_file);

    //! TODO: maybe flatten both json objects and then iterating over them with the cmp op. It would then be quite easy
    //! to tell exactly which properties do not match.
    verified = (*props == expected_props);
    if (not verified)
    {
        LOG_INFO(vp_logger(), "Properties do not match.");
        std::ofstream o{fmt::format("{}_current.json", name)};
        o << std::setw(4) << *props << std::endl;
    }

    const auto cmp_result = pixel_match(expected_snapshot.data(), snapshot->data(), PixelCompareOptions{});
    if (not cmp_result.has_value())
    {
        LOG_ERROR(vp_logger(), "Error while comparing the images: {}", cmp_result.error().message);
        co_return std::unexpected(cmp_result.error());
    }

    verified = (verified && cmp_result->diff == 0);
    if (not verified)
    {
        LOG_INFO(vp_logger(), "Images does not match. Failed with compare {}", cmp_result->diff);
        cmp_result->diff_image.save_to(fmt::format("{}_diff.png", name));
        snapshot->save_to(fmt::format("{}_current.png", name));
    }

    co_return verified;
}
} // namespace quite::testing
