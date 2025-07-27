

# File test\_error.cpp

[**File List**](files.md) **>** [**core**](dir_6f77a39b07c019ccd7492ea87272f732.md) **>** [**test**](dir_57af785f642af5d82b5c3ebf8a595104.md) **>** [**test\_error.cpp**](test__error_8cpp.md)

[Go to the documentation of this file](test__error_8cpp.md)


```C++
#include <boost/ut.hpp>
#include <quite/error.hpp>

using namespace quite;
using namespace boost::ut;
using namespace std::literals::string_view_literals;

static suite<"core::error"> _ = [] {
    "formatting"_test = [] {
        const quite::Error error{
            .code = quite::ErrorCode::deadline_exceeded,
            .message = "test message",
        };
        expect(that % "(error_code: deadline_exceeded: message: test message)"sv == fmt::format("{}", error));
    };
};
```


