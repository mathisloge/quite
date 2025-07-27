

# File image\_utils.hpp

[**File List**](files.md) **>** [**core**](dir_6f77a39b07c019ccd7492ea87272f732.md) **>** [**include**](dir_25de89a49d1da2858ac6330785c12b40.md) **>** [**quite**](dir_6f50b8774c4552618988001c2022dcf6.md) **>** [**image\_utils.hpp**](image__utils_8hpp.md)

[Go to the documentation of this file](image__utils_8hpp.md)


```C++
#pragma once
#include <optional>
#include "quite/image.hpp"
#include "quite/quite_core_export.hpp"
#include "quite/result.hpp"

namespace quite
{
struct PixelCompareOptions
{
    float threshold{0.1};                                   // matching threshold (0 to 1); smaller is more sensitive
    bool skip_anti_aliasing{false};                         // whether to skip anti-aliasing detection
    float alpha{0.1};                                       // opacity of original image in diff output
    std::array<uint8_t, 3> anti_aliased_color{255, 255, 0}; // color of anti-aliased pixels in diff output
    std::array<uint8_t, 3> diff_color{255, 0, 0};           // color of different pixels in diff output
    std::optional<std::array<uint8_t, 3>>
        diff_color_alt;    // whether to detect dark on light differences between img1 and img2 and set an alternative
                           // color to differentiate between the two
    bool diff_mask{false}; // draw the diff over a transparent background (a mask)
};

struct ImageCompareResult
{
    int diff{};
    Image diff_image;
};

QUITE_CORE_EXPORT Result<ImageCompareResult> pixel_match(const ImageView &expected_img,
                                                         const ImageView &actual_img,
                                                         const PixelCompareOptions &options = {});
} // namespace quite
```


