#include <catch2/catch_test_macros.hpp>
#include <cmrc/cmrc.hpp>
#include <quite/image.hpp>
#include <quite/image_utils.hpp>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

CMRC_DECLARE(testrc);
using namespace quite;

namespace
{
Image load_from_rc(const std::string &file_path)
{
    auto fs = cmrc::testrc::get_filesystem();
    auto image_f = fs.open(file_path);

    int w, h, channels;
    auto data =
        stbi_load_from_memory(reinterpret_cast<const stbi_uc *>(image_f.begin()), image_f.size(), &w, &h, &channels, 0);
    const size_t image_size = w * h * channels;
    std::vector<std::byte> image_data{reinterpret_cast<std::byte *>(data),
                                      reinterpret_cast<std::byte *>(data) + image_size};

    return Image{std::move(image_data), static_cast<uint32_t>(w), static_cast<uint32_t>(h), channels};
}
} // namespace

TEST_CASE("Image diff")
{
    const Image actual_image{load_from_rc("assets/actual_image.png")};
    const Image expected_image{load_from_rc("assets/expected_image.png")};
    const Image expected_diff_image{load_from_rc("assets/diff_image.png")};

    Image diff_image;
    auto diff_result = pixel_match(actual_image.data(), expected_image.data(), PixelCompareOptions{}, diff_image);

    REQUIRE(diff_result.has_value());
    REQUIRE(*diff_result == 192);
    REQUIRE(std::equal(
        diff_image.data().data.cbegin(), diff_image.data().data.cend(), expected_diff_image.data().data.cbegin()));
}

TEST_CASE("Image diff with different sizes")
{
    const Image sample1{std::vector<std::byte>{2000}, 20, 10, 10};
    const Image sample2{std::vector<std::byte>{1000}, 10, 10, 10};
    Image diff_image;
    auto diff_result = pixel_match(sample1.data(), sample2.data(), PixelCompareOptions{}, diff_image);

    REQUIRE(not diff_result.has_value());
}
