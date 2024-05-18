#include <quite/remote_object.hpp>
namespace quite
{
RemoteObject::RemoteObject(ObjectId id)
    : id_{id}
{}

RemoteObject::~RemoteObject() = default;
} // namespace quite
/*

#include <spdlog/spdlog.h>
#include "remote_object.hpp"
#include "rpc/make_create_screenshot_request.hpp"
#include "rpc/make_mouse_click_request.hpp"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <stb_image_write.h>
namespace quite
{
RemoteObject::RemoteObject(const std::shared_ptr<ApiHandle> &api_handle, ObjectId id, std::string_view type_name)
    : api_handle_{api_handle}
    , id_{id}
    , type_name_{type_name}
{}

RemoteObject::~RemoteObject() = default;

ObjectId RemoteObject::id() const noexcept
{
    return id_;
}

std::shared_ptr<ApiHandle> RemoteObject::api_handle() const
{
    return api_handle_;
}

exec::task<void> RemoteObject::mouse_click()
{
    const auto response = co_await make_mouse_click_request(
        api_handle_->object_client().context(), api_handle_->object_client().stub(), id_);
    if (not response.has_value())
    {
        spdlog::error("could not mouse_click object {}", id_);
    }
}

exec::task<void> RemoteObject::take_snapshot()
{
    const auto response = co_await make_create_screenshot_request(
        api_handle_->object_client().context(), api_handle_->object_client().stub(), id_);
    spdlog::error("XXX, take_snapshot has value: {}", response.has_value());
    if (response.has_value())
    {
        spdlog::debug("Image {}x{}", response->metadata().width(), response->metadata().height());
        spdlog::debug("Image size={}", response->data().size());

        int x = response->metadata().width();
        int y = response->metadata().height();
        int channels = 4;
        const bool written =
            stbi_write_png("/home/mathis/dev/ng-quite/test2.png", x, y, channels, response->data().data(), x * 4);

        spdlog::debug("written={}", written);
    }
}

} // namespace quite
*/
