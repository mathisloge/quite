#pragma once
#include <cstdint>
#include <filesystem>
#include <memory>
#include <vector>
#include "quitelib_export.h"

namespace quite
{
class QUITELIB_EXPORT Image
{
  public:
    explicit Image(std::vector<std::byte> image_data, std::uint32_t width, std::uint32_t height, int channels);
    Image(Image &&);
    virtual ~Image();

    void save_to(const std::filesystem::path &destination);

  private:
    class Impl;
    std::unique_ptr<Impl> impl_;
};
} // namespace quite
