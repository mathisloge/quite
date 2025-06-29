#include "quite/image.hpp"
#include <algorithm>
#include <utility>
#define STB_IMAGE_WRITE_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
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

Image::Image()
    : impl_{std::make_unique<Impl>(std::vector<std::byte>{}, 0, 0, 0)}
{}

Image::Image(std::vector<std::byte> image_data, std::uint32_t width, std::uint32_t height, int channels)
    : impl_{std::make_unique<Impl>(std::move(image_data), width, height, channels)}
{}

Image::Image(const std::filesystem::path &filename)
{
    int w, h, channels;
    auto *data = stbi_load(filename.c_str(), &w, &h, &channels, 0);
    if (data != nullptr)
    {
        const size_t image_size = w * h * channels;
        std::vector<std::byte> image_data{reinterpret_cast<std::byte *>(data),
                                          reinterpret_cast<std::byte *>(data) + image_size};
        stbi_image_free(data);
        impl_ = std::make_unique<Impl>(std::move(image_data), w, h, channels);
    }
    else
    {
        impl_ = std::make_unique<Impl>(std::vector<std::byte>{}, 0, 0, 0);
    }
}

Image::Image(Image &&other) noexcept
    : impl_{std::exchange(other.impl_, nullptr)}
{}

Image &Image::operator=(Image &&other) noexcept
{
    impl_ = std::exchange(other.impl_, nullptr);
    return *this;
}

Image::Image(const Image &other)
    : Image{}
{
    *this = other;
}

Image &Image::operator=(const Image &other)
{
    if (this == &other)
    {
        return *this;
    }
    std::ranges::copy(other.impl_->image_data_, std::back_inserter(impl_->image_data_));
    this->impl_->channels_ = other.impl_->channels_;
    this->impl_->width_ = other.impl_->width_;
    this->impl_->height_ = other.impl_->height_;
    return *this;
}

Image::~Image() = default;

void Image::save_to(const std::filesystem::path &destination) const
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
