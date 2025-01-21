#include "quite/testing/verification_point.hpp"
#include <fstream>
#include <nlohmann/json.hpp>
#include <quite/logger.hpp>
#include "quite/utils/dump_properties.hpp"

DEFINE_LOGGER(vp_logger)

namespace
{
constexpr auto kRequestedProperties =
    std::array<std::string, 5>{"objectName", "width", "height", "children", "visible"};
}
namespace quite::testing
{
AsyncResult<bool> create_verification_point(RemoteObjectPtr object, const std::string &name)
{
    const auto snapshot = co_await object->take_snapshot();
    if (not snapshot.has_value())
    {
        co_return std::unexpected(snapshot.error());
    }
    const auto props = co_await dump_properties(object, std::span{kRequestedProperties});
    if (not props.has_value())
    {
        co_return std::unexpected(props.error());
    }

    snapshot->save_to(std::filesystem::path(name).replace_extension(".png"));

    std::ofstream o{std::filesystem::path(name).replace_extension(".json")};
    o << std::setw(4) << *props << std::endl;

    co_return true;
}

AsyncResult<bool> verify_verification_point(RemoteObjectPtr object, const std::string &name)
{
    bool verified = true;
    const auto snapshot = co_await object->take_snapshot();
    if (not snapshot.has_value())
    {
        LOG_ERROR(vp_logger, "Error while creating the snapshot: {}", snapshot.error().message);
        co_return std::unexpected(snapshot.error());
    }
    const auto props = co_await dump_properties(object, kRequestedProperties);
    if (not props.has_value())
    {
        LOG_ERROR(vp_logger, "Error while fetching the properties: {}", props.error().message);
        co_return std::unexpected(props.error());
    }

    const Image expected_snapshot{std::filesystem::path(name).replace_extension(".png")};
    std::ifstream json_prop_file(std::filesystem::path(name).replace_extension(".json"));
    const nlohmann::json expected_props = nlohmann::json::parse(json_prop_file);

    //! TODO: maybe flatten both json objects and then iterating over them with the cmp op. It would then be quite easy
    //! to tell exactly which properties do not match.
    verified = (*props == expected_props);
    if (not verified)
    {
        LOG_INFO(vp_logger, "Properties do not match.");
        std::ofstream o{fmt::format("{}_current.json", name)};
        o << std::setw(4) << *props << std::endl;
    }

    Image diff_img;
    const auto diff_pixels = pixel_match(expected_snapshot.data(), snapshot->data(), PixelCompareOptions{}, diff_img);
    if (not diff_pixels.has_value())
    {
        LOG_ERROR(vp_logger, "Error while comparing the images: {}", diff_pixels.error().message);
        co_return std::unexpected(diff_pixels.error());
    }

    verified = (verified && diff_pixels == 0);
    if (not verified)
    {
        LOG_INFO(vp_logger, "Images does not match. Failed with compare {}", *diff_pixels);
        diff_img.save_to(fmt::format("{}_diff.png", name));
        snapshot->save_to(fmt::format("{}_current.png", name));
    }

    co_return verified;
}
} // namespace quite::testing
