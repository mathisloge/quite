// SPDX-FileCopyrightText: 2025 Mathis Logemann <mathis@quite.rocks>
//
// SPDX-License-Identifier: MIT

#pragma once
#include <cstdint>
#include <filesystem>
#include <span>
#include <vector>
#include "quite/quite_core_export.hpp"

namespace quite
{
using PixelData = std::span<std::byte>;
struct ImageView
{
    std::uint32_t width;
    std::uint32_t height;
    int channels;
    PixelData data;
};
class QUITE_CORE_EXPORT Image
{
  public:
    Image();
    explicit Image(std::vector<std::byte> image_data, std::uint32_t width, std::uint32_t height, int channels);
    explicit Image(const std::filesystem::path &filename);
    Image(Image &&) noexcept;
    Image &operator=(Image &&other) noexcept;
    Image(const Image &);
    Image &operator=(const Image &other);
    virtual ~Image();

    void save_to(const std::filesystem::path &destination) const;
    ImageView data() const;

  private:
    class Impl;
    std::unique_ptr<Impl> impl_;
};
} // namespace quite
