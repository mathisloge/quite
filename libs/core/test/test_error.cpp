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
