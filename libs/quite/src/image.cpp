#include <utility>
#include <quite/image.hpp>
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <stb_image_write.h>

namespace quite
{
class Image::Impl final
{
  public:
    explicit Impl(std::vector<std::byte> image_data, std::uint32_t width, std::uint32_t height, int channels)
        : image_data_{std::move(image_data)}
        , width_{width}
        , height_{height}
        , channels_{channels}
    {}
    ~Impl() = default;

  public:
    std::vector<std::byte> image_data_;
    std::uint32_t width_;
    std::uint32_t height_;
    int channels_;
};

Image::Image(std::vector<std::byte> image_data, std::uint32_t width, std::uint32_t height, int channels)
    : impl_{std::make_unique<Impl>(std::move(image_data), width, height, channels)}
{}

Image::Image(Image &&other)
    : impl_{std::exchange(other.impl_, nullptr)}
{}

Image::~Image() = default;

void Image::save_to(const std::filesystem::path &destination)
{
    const bool written = stbi_write_png(destination.c_str(),
                                        impl_->width_,
                                        impl_->height_,
                                        impl_->channels_,
                                        impl_->image_data_.data(),
                                        impl_->width_ * impl_->channels_);
}

ImageView Image::data() const
{
    return ImageView{
        .width = impl_->width_,
        .height = impl_->height_,
        .channels = impl_->channels_,
        .data = impl_->image_data_,
    };
}
} // namespace quite
