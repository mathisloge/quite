#pragma once
#include <array>
#include <cstdint>
#include <filesystem>
#include <memory>
#include <optional>
#include <span>
#include <vector>
#include <quite/disable_copy_move.hpp>
#include "quite/quite_client_export.hpp"
#include "quite/result.hpp"

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
class QUITE_CLIENT_EXPORT Image
{
  public:
    QUITE_DISABLE_COPY(Image);
    Image();
    explicit Image(std::vector<std::byte> image_data, std::uint32_t width, std::uint32_t height, int channels);
    explicit Image(const std::filesystem::path &filename);
    Image(Image &&) noexcept;
    Image &operator=(Image &&other) noexcept;
    virtual ~Image();

    void save_to(const std::filesystem::path &destination) const;
    ImageView data() const;

  private:
    class Impl;
    std::unique_ptr<Impl> impl_;
};

struct PixelCompareOptions
{
    float threshold{0.1};                        // matching threshold (0 to 1); smaller is more sensitive
    bool includeAA{false};                       // whether to skip anti-aliasing detection
    float alpha{0.1};                            // opacity of original image in diff output
    std::array<uint8_t, 3> aaColor{255, 255, 0}; // color of anti-aliased pixels in diff output
    std::array<uint8_t, 3> diffColor{255, 0, 0}; // color of different pixels in diff output
    std::optional<std::array<uint8_t, 3>>
        diffColorAlt; // whether to detect dark on light differences between img1 and img2 and set an alternative color
                      // to differentiate between the two
    bool diffMask{false}; // draw the diff over a transparent background (a mask)
};

QUITE_CLIENT_EXPORT Result<int> pixel_match(const ImageView &expected_img,
                                            const ImageView &actual_img,
                                            const PixelCompareOptions &options,
                                            Image &output_image);
} // namespace quite
