#pragma once
#include <cstdint>
#include <filesystem>
#include <memory>
#include <vector>
#include "quitelib_export.h"

namespace quite
{

struct ImageView
{
    std::uint32_t width;
    std::uint32_t height;
    int channels;
    std::span<const std::byte> data;
};
class QUITELIB_EXPORT Image
{
  public:
    explicit Image(std::vector<std::byte> image_data, std::uint32_t width, std::uint32_t height, int channels);
    Image(Image &&);
    virtual ~Image();

    void save_to(const std::filesystem::path &destination);
    ImageView data() const;

  private:
    class Impl;
    std::unique_ptr<Impl> impl_;
};
} // namespace quite
